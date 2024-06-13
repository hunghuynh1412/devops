package com.example.blescanner;

import android.app.Activity;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;

import android.content.ServiceConnection;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class BLE_Service extends Service {

    private final static String TAG = BLE_Service.class.getSimpleName();

    public boolean servicesStatus;


    private BluetoothManager mBluetoothManager;
    private BluetoothAdapter mBluetoothAdapter;
    private String mBluetoothDeviceAddress;
    private BluetoothGatt mBluetoothGatt;


    private int mConnectionState = STATE_DISCONNECTED;
    private static final int STATE_DISCONNECTED = 0;
    private static final int STATE_CONNECTING = 1;
    private static final int STATE_CONNECTED = 2;

    public final static String ACTION_GATT_CONNECTED = ".BLE_Service.ACTION_GATT_CONNECTED";
    public final static String ACTION_GATT_DISCONNECTED = ".BLE_Service.ACTION_GATT_DISCONNECTED";
    public final static String ACTION_GATT_SERVICES_DISCOVERED = ".BLE_Service.ACTION_GATT_SERVICES_DISCOVERED";





    public class BLEServiceBinder extends Binder{
        BLE_Service getService(){
            return BLE_Service.this;
        }
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {


        return mBinder;
    }
    private final IBinder mBinder = new BLEServiceBinder();

    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            String intentAction;
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                intentAction = ACTION_GATT_CONNECTED;

                mConnectionState = STATE_CONNECTED;

                broadcastUpdate(intentAction);

                Log.i(TAG, "Connected to GATT server.");
                // Attempts to discover services after successful connection.
                Log.i(TAG, "Attempting to start service discovery:" + mBluetoothGatt.discoverServices());
            } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                intentAction = ACTION_GATT_DISCONNECTED;

                mConnectionState = STATE_DISCONNECTED;

                Log.i(TAG, "Disconnected from GATT server.");

                broadcastUpdate(intentAction);
            }
        }
        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {

            if (status == BluetoothGatt.GATT_SUCCESS) {
                broadcastUpdate(ACTION_GATT_SERVICES_DISCOVERED);
            }
            else {
                Log.w(TAG, "onServicesDiscovered received: " + status);
            }
        }
    };

    public boolean onConnectDevice(final String address) {
        if(mBluetoothAdapter == null || address == null){
            Utils.toast(this.getApplicationContext(),"BluetoothAdapter not initialized or unspecified address.");
            return false;
        }
        mGattCallback.onConnectionStateChange(mBluetoothGatt, BluetoothGatt.GATT_SUCCESS, BluetoothProfile.STATE_CONNECTING);



        final BluetoothDevice mDevice = mBluetoothAdapter.getRemoteDevice(address);
        if (mDevice == null) {
            //Device not found
            Utils.toast(this.getApplicationContext(),"Device not found");
            return false;
        }
        if (mBluetoothDeviceAddress != null && address.equals(mBluetoothDeviceAddress) && mBluetoothGatt != null) {
            Log.d(TAG, "Trying to use an existing mBluetoothGatt for connection.");

            if (mBluetoothGatt.connect()) {
                mConnectionState = STATE_CONNECTING;
                Log.d(TAG, "Connect Success.");
                return true;
            }
            else {
                return false;
            }
        }

        //We want to directly connect to the device, so we are setting the autoConnect
        //parameter to false
        (new Handler(Looper.getMainLooper())).post(() -> {
            mBluetoothGatt = mDevice.connectGatt(BLE_Service.this, true, mGattCallback);
        });
        mBluetoothDeviceAddress = address;
        mConnectionState = STATE_CONNECTING;
        return true;
    }
    public void onDisconnect() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }

        mBluetoothGatt.disconnect();
    }


    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        sendBroadcast(intent);
    }

    public void close() {

        if (mBluetoothGatt == null) {
            return;
        }

        mBluetoothGatt.close();
        mBluetoothGatt = null;
    }

    public boolean initialize() {
        // For API level 18 and above, get a reference to BluetoothAdapter through
        // BluetoothManager.
        if (mBluetoothManager == null) {
            mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
            if (mBluetoothManager == null) {
                Log.e(TAG, "Unable to initialize BluetoothManager.");
                return false;
            }
        }

        mBluetoothAdapter = mBluetoothManager.getAdapter();
        if (mBluetoothAdapter == null) {
            Log.e(TAG, "Unable to obtain a BluetoothAdapter.");
            return false;
        }

        return true;
    }
}
