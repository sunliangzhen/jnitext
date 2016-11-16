#include <jni.h>
#include <stdlib.h>
#include <android/log.h>

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


jstring JNICALL Java_com_jnitext_text_getStringFormC(JNIEnv *env, jobject obj) {
    return (*env)->NewStringUTF(env, "这里是来自c的string");
}

jstring JNICALL Java_com_jnitext_text_getStringFormC2(JNIEnv *env, jobject obj) {
    char *cstr = "dddddddddddddddd";
    return (*env)->NewStringUTF(env, cstr);
}

jint JNICALL Java_com_jnitext_text_add(JNIEnv *env, jclass clz, jint x, jint y) {
    return x + y;
}

/*
 * Class:     com_jnitext_text
 * Method:    sayHelloInC
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_jnitext_text_sayHelloInC
        (JNIEnv *env, jclass clz, jstring jstr) {

//调用工具方法把 java中的string 类型 转换成 C 语言中的 char*
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);


//char* cstr = _JString2CStr(env,jstr);
//调用strlen 获取 cstr 字符串的长度
    int length = strlen(rtn);
    int i;
    for (i = 0; i < length; i++) {
        *(rtn + i) += 1;
    }
    return (*env)->NewStringUTF(env, rtn);

}

/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char *_JString2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}
/*
 * Class:     com_jnitext_text
 * Method:    arrElementsIncrease
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_jnitext_text_arrElementsIncrease
        (JNIEnv *env, jclass clz, jintArray jArray) {
    jsize length = (*env)->GetArrayLength(env, jArray);
    LOGD("length = %d", length);
    //jboolean iscopy;
    //jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    int *arrayPointer = (*env)->GetIntArrayElements(env, jArray, NULL);
    int i;
    for (i = 0; i < length; i++) {
        *(arrayPointer + i) += 10;
    }
    return jArray;
}

JNIEXPORT void JNICALL Java_com_jnitext_text_callbackvoidmethod
        (JNIEnv *env, jobject job) {
//jclass      (*FindClass)(JNIEnv*, const char*);
//① 获取字节码对象
    jclass claz = (*env)->FindClass(env, "com/jnitext/text");
//②获取Method对象
//jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    jmethodID methodID = (*env)->GetMethodID(env, claz, "helloFromJava", "()V");
//③通过字节码对象创建一个Object
//④通过对象调用方法
//void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env, job, methodID);
}

JNIEXPORT void JNICALL Java_com_jnitext_text_callbackintmethod
        (JNIEnv *env, jobject clazz) {
//① 获取字节码对象
    jclass claz = (*env)->FindClass(env, "com/jnitext/text");
//②获取Method对象
    jmethodID methodID = (*env)->GetMethodID(env, claz, "add", "(II)I");
//jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
    int result = (*env)->CallIntMethod(env, clazz, methodID, 3, 4);
    LOGD("result = %d", result);
}

JNIEXPORT void JNICALL Java_com_jnitext_text_callbackStringmethod
        (JNIEnv *env, jobject clazz) {
//① 获取字节码对象
    jclass claz = (*env)->FindClass(env, "com/jnitext/text");
//② 获取Method对象
    jmethodID methodid = (*env)->GetMethodID(env, claz, "printString", "(Ljava/lang/String;)V");
//
    jstring result = (*env)->NewStringUTF(env, "hello from c");
    (*env)->CallVoidMethod(env, clazz, methodid, result);

}

JNIEXPORT void JNICALL Java_com_jnitext_text_callbackShowToast
        (JNIEnv *env, jobject clazz) {
    jclass claz = (*env)->FindClass(env, "com/jnitext/text");
    jmethodID methodid = (*env)->GetMethodID(env, claz, "showToast", "(Ljava/lang/String;)V");
//jobject     (*AllocObject)(JNIEnv*, jclass);
//通过字节码对象创建 java对象 在这儿就是创建了mainactivity的对象
//jobject obj =(*env)->AllocObject(env,claz);
    jstring result = (*env)->NewStringUTF(env, "hello from c");
//void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env, clazz, methodid, result);
}

JNIEXPORT jstring JNICALL Java_com_jnitext_text_encodeInC(JNIEnv *env, jobject clazz,
                                                          jstring jstr) {
    //把jstring类型字符串转化成 c能够处理的char* 类型
    char *cstr = _JString2CStr(env, jstr);
    int length = strlen(cstr);
    int i;
    for (i = 0; i < length; i++) {
        *(cstr + i) += 2;
    }
    return (*env)->NewStringUTF(env, cstr);

}

JNIEXPORT jstring JNICALL Java_com_jnitext_text_decodeInC(JNIEnv *env, jobject clazz,
                                                          jstring jstr) {
    char *cstr = _JString2CStr(env, jstr);
    int length = strlen(cstr);
    int i;
    for (i = 0; i < length; i++) {
        *(cstr + i) -= 2;
    }
    return (*env)->NewStringUTF(env, cstr);

}