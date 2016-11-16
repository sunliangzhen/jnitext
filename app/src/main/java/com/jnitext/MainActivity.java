package com.jnitext;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("NdkJniDemo");//之前在build.gradle里面设置的so名字，必须一致}
    }

    EditText et;
    text text2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        et = (EditText) findViewById(R.id.et_text);
        TextView textView = (TextView) findViewById(R.id.tv);
        textView.setText(text.sayHelloInC("adcd") + "");
        passIntArray();
        text2 = new text(this);
        text2.callbackShowToast();
    }

    public void passIntArray() {
        int[] array = new int[]{1, 2, 3, 4, 5};
        text.arrElementsIncrease(array);
        for (int i : array) {
            Log.d("test", i + "");
        }
    }

    public void showToast(String s) {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_SHORT).show();
    }

    public void encode(View v) {
        //获取edittext的文字
        String word = et.getText().toString();
        //传递c加密处理
        word = text2.encodeInC(word);
        //把处理后的结果显示到edittext上
        et.setText(word);
    }

    public void decode(View v) {
        //获取edittext的文字
        String word = et.getText().toString();
        //传递c加密处理
        word = text2.decodeInC(word);
        //把处理后的结果显示到edittext上
        et.setText(word);
    }
}
