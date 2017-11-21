#ifndef __JNI_CALL_H__
#define __JNI_CALL_H__

//#ifdef ANDROID
#include <jni.h>
#include<android/log.h>
#define TAG "log_jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)

//#else
//#define LOGD(...) fprintf(stderr, __VA_ARGS__);// 定义LOGD类型
//#endif

//typedef int BOOL;
#define true 1
#define false 0


#endif
