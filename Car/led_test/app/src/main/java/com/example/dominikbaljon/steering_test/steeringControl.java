package com.example.dominikbaljon.steering_test;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.example.dominikbaljon.led_test.R;

import java.io.IOException;
import java.util.UUID;

import static java.lang.Math.abs;


public class steeringControl extends AppCompatActivity {

    Button btnLeftWheel, btnRightWheel, btnDisconnect;
    CustomSeekBar barLeftWheel, barRightWheel;
    TextView TVRightWheel, TVLeftWheel;
    String btAddress = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    private Wheel_Direction left_wheel_direction = Wheel_Direction.FORWARD;
    private Wheel_Direction right_wheel_direction = Wheel_Direction.FORWARD;

    public enum Wheel { RIGHT, LEFT
    }

    private Wheel LastUpdatedWheel = Wheel.RIGHT;

    private Handler handler = new Handler();

    private Runnable runnable = new Runnable() {
        @Override
        public void run() {
            CyclicFunction();

            handler.postDelayed(this, 120);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_led_control);

        Intent newint = getIntent();
        btAddress = newint.getStringExtra(DeviceList.EXTRA_ADDRESS);
        btnLeftWheel = (Button) findViewById(R.id.left_wheel_stop);
        btnRightWheel = (Button) findViewById(R.id.right_wheel_stop);
        btnDisconnect = (Button) findViewById(R.id.disconect_button);
        barLeftWheel = (CustomSeekBar) findViewById(R.id.left_wheel);
        barRightWheel = (CustomSeekBar) findViewById(R.id.right_wheel);
        TVLeftWheel = (TextView) findViewById(R.id.textView_wheel_left);
        TVRightWheel = (TextView) findViewById(R.id.textView_wheel_right);

        new ConnectBt().execute();

        handler.postDelayed(runnable, 120);

        btnLeftWheel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LeftWheelStop();
            }
        });

        btnRightWheel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RightWheelStop();
            }
        });

        btnDisconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Disconnect();
            }
        });

        barLeftWheel.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser == true) {
                    TVLeftWheel.setText(String.valueOf(progress - 60));
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        barRightWheel.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser == true) {
                    TVRightWheel.setText(String.valueOf(progress - 60));
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

    }

    private void SendStringViaBT(String message)
    {
        if (message.length() != 0) {
            if (btSocket != null) {
                try {
                    btSocket.getOutputStream().write(message.getBytes());
                } catch (IOException e) {
                    //msg("Error");
                }
            }
        }
    }

    private void CyclicFunction()
    {
        switch (LastUpdatedWheel){
            case RIGHT:
                LeftWheelUpdate();
                RightWheelUpdate();
                LastUpdatedWheel = Wheel.LEFT;
                break;
            case LEFT:
                RightWheelUpdate();
                LeftWheelUpdate();
                LastUpdatedWheel = Wheel.RIGHT;
                break;
        }
    }

    private void LeftWheelUpdate()
    {
        int left_speed_request = barLeftWheel.getProgress() - 60;

        switch (left_wheel_direction){
            case FORWARD:
                if (left_speed_request < 0)
                    LeftWheelChangeDirection(Wheel_Direction.BACK);
                break;
            case BACK:
                if (left_speed_request > 0)
                    LeftWheelChangeDirection(Wheel_Direction.FORWARD);
                break;
        }

        if (barLeftWheel.isPressed())
        {
            if (left_speed_request != 0)
                LeftWheelChangeSpeed(abs(left_speed_request) + 20);
            else
                LeftWheelChangeSpeed(0);
        }
        else
        {
            LeftWheelChangeSpeed(0);
        }
    }

    private void RightWheelUpdate()
    {
        int right_speed_request = barRightWheel.getProgress() - 60;

        switch (right_wheel_direction){
            case FORWARD:
                if (right_speed_request < 0)
                    RightWheelChangeDirection(Wheel_Direction.BACK);
                break;
            case BACK:
                if (right_speed_request > 0)
                    RightWheelChangeDirection(Wheel_Direction.FORWARD);
                break;
        }

        if (barRightWheel.isPressed())
        {
            if (right_speed_request != 0)
                RightWheelChangeSpeed(abs(right_speed_request) + 20);
            else
                RightWheelChangeSpeed(0);
        }
        else
        {
            RightWheelChangeSpeed(0);
        }
    }

    private void LeftWheelChangeSpeed(int speed)
    {
        String value = String.valueOf(speed);
        if (speed != 0)
            SendStringViaBT("speedleft 0x" + value.substring(value.length() - 2) + '.');
        else
            SendStringViaBT("speedleft 0x00.");
    }

    private void RightWheelChangeSpeed(int speed)
    {
        String value = String.valueOf(speed);
        if (speed != 0)
            SendStringViaBT("speedright 0x" + value.substring(value.length() - 2) + '.');
        else
            SendStringViaBT("speedright 0x00.");
    }

    private void Disconnect() {
        if (btSocket != null)
            try
            {
                btSocket.close();
            }
            catch(IOException e)
            {
                msg("Error");
            }
    }

    private void RightWheelStop() {
        SendStringViaBT("stopright.");
    }

    private void LeftWheelStop() {
        SendStringViaBT("stopleft.");
    }

    private void RightWheelChangeDirection( Wheel_Direction WD)
    {
        switch (WD)
        {
            case FORWARD:
                SendStringViaBT("dirright forward.");
                right_wheel_direction = Wheel_Direction.FORWARD;
                break;
            case BACK:
                SendStringViaBT("dirright back.");
                right_wheel_direction = Wheel_Direction.BACK;
                break;
        }
    }

    private void LeftWheelChangeDirection( Wheel_Direction WD)
    {
        switch (WD)
        {
            case FORWARD:
                SendStringViaBT("dirleft forward.");
                left_wheel_direction = Wheel_Direction.FORWARD;
                break;
            case BACK:
                SendStringViaBT("dirleft back.");
                left_wheel_direction = Wheel_Direction.BACK;
                break;
        }
    }


    private class ConnectBt extends AsyncTask<Void, Void, Void> {
    private boolean ConnectSuccess = true;

    @Override
    protected void onPreExecute() {
        progress = ProgressDialog.show(steeringControl.this, "Connecting...", "Please wait!!!");
    }

    @Override
    protected Void doInBackground(Void... devices) {
        try {
            if (btSocket == null || !isBtConnected) {
                myBluetooth = BluetoothAdapter.getDefaultAdapter();
                BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(btAddress);
                btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                btSocket.connect();
            }
        } catch (IOException e) {
            ConnectSuccess = false;
        }
        return null;
    }

    @Override
    protected void onPostExecute(Void result) {
        super.onPostExecute(result);

        if (!ConnectSuccess) {
            msg("Connectoin Failed. Is it a SPP Bluetooth? Try again.");
            finish();
        } else {
            msg("Connected.");
            isBtConnected = true;
        }
        progress.dismiss();
    }
}

    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_SHORT).show();
    }
}
