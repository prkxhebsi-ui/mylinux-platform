#ifndef MYLINUX_DALVIK_JNI_H
#define MYLINUX_DALVIK_JNI_H

#include "dalvik_types.h"

typedef struct JNIEnv JNIEnv;
typedef struct JavaVM JavaVM;

typedef void *jobject;
typedef void *jclass;
typedef void *jstring;
typedef void *jarray;
typedef void *jmethodID;
typedef void *jfieldID;

typedef int jint;
typedef long long jlong;
typedef unsigned char jboolean;

#define JNI_FALSE 0
#define JNI_TRUE 1
#define JNI_OK 0
#define JNI_ERR (-1)

#endif
