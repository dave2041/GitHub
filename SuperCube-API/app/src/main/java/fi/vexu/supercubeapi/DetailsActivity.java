package fi.vexu.supercubeapi;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ListView;
import android.os.SystemClock;
import android.os.Handler;
import java.util.ArrayList;
import java.util.List;

import android.widget.ArrayAdapter;

import static android.view.WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON;

public class DetailsActivity extends AppCompatActivity {
    private final static String TAG = DetailsActivity.class.getSimpleName();

    public static final String EXTRAS_DEVICE_NAME = "DEVICE_NAME";
    public static final String EXTRAS_DEVICE_ADDRESS = "DEVICE_ADDRESS";
    public static final String COMPLETED_CUBE = "12 34 56 78 33 33 33 33 12 34 56 78 9A BC 00 00";

    private TextView textViewState;

    private SuperCube mSuperCube;

    TextView timer ;
    long MillisecondTime, StartTime, TimeBuff, UpdateTime = 0L ;
    Handler handler;
    int Seconds, Minutes, MilliSeconds ;
    Boolean timerRunning = false;

    private Boolean mUserReady = false;

    List<String> times;
    TimeAdapter timeAdapter;
    ListView timeListView;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);
        getWindow().addFlags(FLAG_KEEP_SCREEN_ON);

        final Intent intent = getIntent();
        String mDeviceName = intent.getStringExtra(EXTRAS_DEVICE_NAME);
        String mDeviceAddress = intent.getStringExtra(EXTRAS_DEVICE_ADDRESS);
        getSupportActionBar().setTitle(mDeviceName);

        textViewState = findViewById(R.id.textState);

        handler = new Handler() ;

        timer = (TextView)findViewById(R.id.tvTimer);

        final Button getMoves = findViewById(R.id.getmoves);
        final Button setReady = findViewById(R.id.btReady);
        final Button getBattery = findViewById(R.id.getbattery);
        final Button getMystery1 = findViewById(R.id.getmystery1);
        final Button getMystery2 = findViewById(R.id.getmystery2);
        final Button getMystery3 = findViewById(R.id.getmystery3);
        final Button getMystery4 = findViewById(R.id.getmystery4);
        final Button resetSolved = findViewById(R.id.resetsolved);
        //final Button resetCustom = findViewById(R.id.resetcustom);
        final TextView cubeState = findViewById(R.id.cubestatus);
        final TextView cubeInfo = findViewById(R.id.cubeinfo);
        timeListView = findViewById(R.id.historylist);

        times = new ArrayList<>();
        timeAdapter = new TimeAdapter(this, android.R.layout.simple_list_item_1, times);
        timeListView.setAdapter(timeAdapter);

        if (savedInstanceState != null) {
            mSuperCube = savedInstanceState.getParcelable("superCube");
        } else {
            mSuperCube = new SuperCube(mDeviceName, mDeviceAddress);
        }
        mSuperCube.connect(this);
        mSuperCube.setSuperCubeListener(new SuperCubeListener() {
            @Override
            public void onStatusReceived() {
                cubeState.setText(SuperCube.bytesToString(mSuperCube.getCubeState()));

                if(!timerRunning && mUserReady) {
                    StartTime = SystemClock.uptimeMillis();
                    handler.postDelayed(runnable, 0);
                    timerRunning = true;
                } else {
                    if(SuperCube.bytesToString(mSuperCube.getCubeState()).contains(COMPLETED_CUBE))
                    {
                        handler.removeCallbacks(runnable);
                        timerRunning = false;
                        mUserReady = false;

                        String strTime = "" + Minutes + ":"
                                + String.format("%02d", Seconds) + ":"
                                + String.format("%03d", MilliSeconds);

                        times.add(strTime);
                        timeListView.invalidateViews();
                        setReady.setBackgroundColor(Color.parseColor("#FFFFFF"));
                    }
                }
            }

            @Override
            public void onBatteryReceived(int battery) {
                cubeInfo.setText("Battery level: " + battery);
            }


            @Override
            public void onMovesReceived(int moves) {
                cubeInfo.setText("Total moves: " + moves);
            }

            @Override
            public void onResetReceived(byte[] response) {
                cubeInfo.setText("Cube reset: " + SuperCube.bytesToString(response));
            }

            @Override
            public void onOtherReceived(byte[] response) {
                cubeInfo.setText("Other received: " + SuperCube.bytesToString(response));
            }

            @Override
            public void onCubeReady() {
                getMoves.setClickable(true);
                getBattery.setClickable(true);
                getMystery1.setClickable(true);
                getMystery2.setClickable(true);
                getMystery3.setClickable(true);
                getMystery4.setClickable(true);
                resetSolved.setClickable(true);
                setReady.setClickable(true);
                //resetCustom.setClickable(true); disabled
            }

            @Override
            public void onConnectionStateUpdated() {
                textViewState.setText(mSuperCube.getConnectionState());
            }
        });
        textViewState.setText(mSuperCube.getConnectionState());

        getMoves.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.requestMoveCount();
            }
        });
        getBattery.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.requestBatteryLevel();
            }
        });
        getMystery1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.requestMystery1();
            }
        });
        getMystery2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.requestMystery2();
            }
        });
        getMystery3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.requestMystery3();
            }
        });
        getMystery4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.requestMystery4();
            }
        });
        resetSolved.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSuperCube.resetSolved();
            }
        });
        setReady.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mUserReady = true;
                setReady.setBackgroundColor(Color.parseColor("#00FF00"));
            }
        });
        /*resetCustom.setOnClickListener(new View.OnClickListener() { //disabled
            @Override
            public void onClick(View view) {
                mSuperCube.resetCustom();
            }
        });*/
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (!isChangingConfigurations()) {
            mSuperCube.disconnect();
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle state) {
        super.onSaveInstanceState(state);
        state.putParcelable("superCube", mSuperCube);
    }

    public Runnable runnable = new Runnable() {

        public void run() {

            MillisecondTime = SystemClock.uptimeMillis() - StartTime;

            UpdateTime = TimeBuff + MillisecondTime;

            Seconds = (int) (UpdateTime / 1000);

            Minutes = Seconds / 60;

            Seconds = Seconds % 60;

            MilliSeconds = (int) (UpdateTime % 1000);

            timer.setText("" + Minutes + ":"
                    + String.format("%02d", Seconds) + ":"
                    + String.format("%03d", MilliSeconds));

            handler.postDelayed(this, 0);
        }

    };
}

class TimeAdapter extends ArrayAdapter<String> {
    TimeAdapter(Context context, int resource, List<String> items) {
        super(context, resource, items);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View v = convertView;

        if (v == null) {
            LayoutInflater vi;
            vi = LayoutInflater.from(getContext());
            v = vi.inflate(android.R.layout.simple_list_item_1, null);
        }
        final String time = getItem(position);
        TextView tt1 = v.findViewById(android.R.id.text1);
        tt1.setText(time);

        return v;
    }

}