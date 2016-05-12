package com.example.pythontest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button useNdk;
    private TextView resultText;

    static {
        System.loadLibrary("crypto");
        System.loadLibrary("ssl");
        System.loadLibrary("python2.7");
        System.loadLibrary("interpreter");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        useNdk = Button.class.cast(findViewById(R.id.ndk_Btn));
        resultText = TextView.class.cast(findViewById(R.id.result_textview));

        //copy test.py sdcard
        useNdk.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        resultText.setText("loading");
        new Thread(new Runnable() {
            @Override
            public void run() {
                final String url = getUrl();
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        resultText.setText(url);
                    }
                });
            }
        }).start();

    }

    public static native String getUrl();
}
