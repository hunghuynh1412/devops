package com.example.blescanner;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.Bundle;

import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.ScrollView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity implements AdapterView.OnItemClickListener {
    private final static String TAG = MainActivity.class.getSimpleName();
    public static final int REQUEST_ENABLE_BT = 1;
    public static final int BTLE_SERVICES = 2;
    //HashMap contain address and BTLE Devices
    private HashMap<String, BLE_Device> mBTDevicesHashMap;
    private ArrayList<BLE_Device> mBTDevicesArrayList;
    //show devices on device_list layout
    private ListAdapter_BTLE_Devices adapter;
    private ListView listView;
    private Handler mHandler;
    private BLE_Service mBleService;
    private ServiceConnection mServiceConnection;

    private BluetoothAdapter mBluetoothAdapter;
    private boolean mScanning;
    private BluetoothGatt mBluetoohGatt;
    private Intent gattServiceIntent;
    private long scanPeriod = 5000;//5000 ms
    private Button btn_Scan;
    private String mDeviceAddress;
    private BroadcastReceiver_BTState mBTStateUpdateReceiver;

    public MainActivity() {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Use this check to determine whether BLE is supported on the device. Then
        // you can selectively disable BLE-related features.
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Utils.toast(getApplicationContext(), "BLE not supported");
            finish();
        }

        mBTStateUpdateReceiver = new BroadcastReceiver_BTState(getApplicationContext());

        final BluetoothManager bluetoothManager =
                (BluetoothManager) this.getSystemService(Context.BLUETOOTH_SERVICE);
        mBluetoothAdapter = bluetoothManager.getAdapter();
        mHandler = new Handler();
        mBTDevicesHashMap = new HashMap<>();
        mBTDevicesArrayList = new ArrayList<>();

        adapter = new ListAdapter_BTLE_Devices(this, R.layout.device_list, mBTDevicesArrayList);

        listView = new ListView(this);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(this);

        btn_Scan = (Button) findViewById(R.id.btn_scan);
        ((ScrollView) findViewById(R.id.scrollView)).addView(listView);

        btn_Scan = (Button) findViewById(R.id.btn_scan);
        btn_Scan.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                startScan();
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        registerReceiver(mBTStateUpdateReceiver, new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED));

    }

    @Override
    protected void onResume() {
        super.onResume();

        registerReceiver(mBTStateUpdateReceiver, new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED));
    }

    @Override
    protected void onPause() {
        super.onPause();

        stopScan();
    }

    @Override
    protected void onStop() {
        super.onStop();
        if(mBleService != null){
            if(mBleService.servicesStatus){
                unbindService(mServiceConnection);
            }
            mBleService.close();
            mBleService=null;
        }
        unregisterReceiver(mBTStateUpdateReceiver);
        stopScan();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }


    public void startScan(){
        btn_Scan.setText("Scanning...");

        mBTDevicesArrayList.clear();
        mBTDevicesHashMap.clear();

        if (!Utils.checkBluetooth(mBluetoothAdapter)) {
            Utils.requestUserBluetooth(this);
            this.stopScan();
        }
        else {
            scanLeDevice(true);
        }
    }

    public void stopScan() {
        btn_Scan.setText("Scan Again");
        scanLeDevice(false);
    }

    private void scanLeDevice(final boolean enable) {
        if (enable && !mScanning) {
            Utils.toast(this.getApplicationContext(), "Starting BLE scan...");

            // Stops scanning after a pre-defined scan period.
            mHandler.postDelayed(new Runnable() {
                                     @Override
                                     public void run() {
                                         mScanning = false;
                                         if(mBluetoothAdapter.isEnabled()) {
                                             mBluetoothAdapter.stopLeScan(mLeScanCallback);
                                             //Stop scanning
                                             btn_Scan.setText("Scan Again");
                                             scanLeDevice(false);
                                         }
                                     }
                                 },scanPeriod
            );


            mScanning = true;
            mBluetoothAdapter.startLeScan(mLeScanCallback);
        }
        else {
            mScanning = false;
            if(mBluetoothAdapter.isEnabled()) {
                mBluetoothAdapter.stopLeScan(mLeScanCallback);
            }
        }
    }
    // Device scan callback.
    private BluetoothAdapter.LeScanCallback mLeScanCallback =
            new BluetoothAdapter.LeScanCallback() {

                @Override
                public void onLeScan(final BluetoothDevice device, int rssi, byte[] scanRecord) {

                                String address = device.getAddress();
                                if (!mBTDevicesHashMap.containsKey(address)) {
                                    BLE_Device btleDevice = new BLE_Device(device,rssi);
                                    mBTDevicesHashMap.put(address, btleDevice);
                                    mBTDevicesArrayList.add(btleDevice);
                                }
                                else {
                                    mBTDevicesHashMap.get(address).setRSSI(rssi);
                                }

                                adapter.notifyDataSetChanged();



                }
            };

    private ServiceConnection mBLE_ServiceConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {

            // We've bound to LocalService, cast the IBinder and get LocalService instance

            BLE_Service.BLEServiceBinder binder = (BLE_Service.BLEServiceBinder) service;
            mBleService = binder.getService();


            if (!mBleService.initialize()) {
                Log.e(TAG, "Unable to initialize Bluetooth");
                finish();
            }

            mBleService.onConnectDevice(mDeviceAddress);

        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            mBleService = null;

        }
    };
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        // Check which request we're responding to
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_ENABLE_BT) {
            // Make sure the request was successful
            if (resultCode == RESULT_OK) {
                Utils.toast(getApplicationContext(), "Thank you for turning on Bluetooth");
            } else if (resultCode == RESULT_CANCELED) {
                Utils.toast(getApplicationContext(), "Please turn on Bluetooth");
            }
        }

    }
    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        //Next Activity
//        stopScan();
//
       String name = mBTDevicesArrayList.get(position).getName();
       mDeviceAddress = mBTDevicesArrayList.get(position).getAddress();
       //auto connect
//        Utils.toast(this.getApplicationContext(), "Connect Success");
        //create connect on click item
        setContentView(R.layout.connect_device);
        ((TextView) findViewById(R.id.show_name_device)).setText(name + " Services");
        ((TextView) findViewById(R.id.show_address_device)).setText(mDeviceAddress);

        gattServiceIntent = new Intent(this, BLE_Service.class);
        bindService(gattServiceIntent,mBLE_ServiceConnection, BIND_AUTO_CREATE);
        startService(gattServiceIntent);


    }

}