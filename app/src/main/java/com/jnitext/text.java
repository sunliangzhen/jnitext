package com.jnitext;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by Administrator on 2016/11/14.
 */

public class text {
    private Context mContext;

    public text(Context context) {
        mContext = context;
    }

    public static native String getStringFormC();

    public static native String getStringFormC2();

    public native int add(int x, int y);

    //传递String类型的参数给C 处理一下返回来
    public static native String sayHelloInC(String s);

    //传递int类型的数组给C
    public static native int[] arrElementsIncrease(int[] intArray);

    public native void callbackvoidmethod();

    public native void callbackintmethod();

    public native void callbackStringmethod();

    public native void callbackShowToast();

    //C调用java空方法
    public void helloFromJava() {
        System.out.println("hello from java");
    }

    //C调用java中参数为string的方法
    public void printString(String s) {
        System.out.println(s);
    }

    public void showToast(String s) {
        Toast.makeText(mContext, s, 0).show();
    }


    public native String encodeInC(String word);

    public native String decodeInC(String word);
}
