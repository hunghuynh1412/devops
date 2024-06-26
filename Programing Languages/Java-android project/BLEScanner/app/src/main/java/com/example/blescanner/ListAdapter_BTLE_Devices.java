package com.example.blescanner;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class ListAdapter_BTLE_Devices extends ArrayAdapter<BLE_Device> {

    Activity activity;
    int layoutResourceID;
    ArrayList<BLE_Device> devices;

    public ListAdapter_BTLE_Devices(Activity activity, int resource, ArrayList<BLE_Device> objects) {
        super(activity.getApplicationContext(), resource, objects);

        this.activity = activity;
        layoutResourceID = resource;
        devices = objects;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        if (convertView == null) {
            LayoutInflater inflater =
                    (LayoutInflater) activity.getApplicationContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(layoutResourceID, parent, false);
        }

        BLE_Device device = devices.get(position);
        String name = device.getName();
        String address = device.getAddress();
        int rssi = device.getRSSI();

        TextView tv = null;

        tv = (TextView) convertView.findViewById(R.id.show_name);
        if (name != null && name.length() > 0) {
            tv.setText(device.getName());
        }
        else {
            tv.setText("No Name");
        }

        tv = (TextView) convertView.findViewById(R.id.show_rssi);
        tv.setText("RSSI: " + Integer.toString(rssi));

        tv = (TextView) convertView.findViewById(R.id.show_macaddr);
        if (address != null && address.length() > 0) {
            tv.setText("MAC: "+ device.getAddress());
        }
        else {
            tv.setText("No Address");
        }

        return convertView;
    }
}
