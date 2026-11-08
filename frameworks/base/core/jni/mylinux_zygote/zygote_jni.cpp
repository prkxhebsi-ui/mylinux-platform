#include <jni.h>

#include <cerrno>
#include <cstring>

#include "zygote_socket.h"

namespace {

void throwIOException(
    JNIEnv* env,
    const char* message
) {
    jclass exceptionClass =
        env->FindClass("java/io/IOException");

    if (exceptionClass == nullptr) {
        return;
    }

    env->ThrowNew(exceptionClass, message);
}

jint nativeGetServerSocketFd(
    JNIEnv* env,
    jclass,
    jstring socketName
) {
    if (socketName == nullptr) {
        throwIOException(env, "Socket name is null");
        return -1;
    }

    const char* name = env->GetStringUTFChars(
        socketName,
        nullptr
    );

    if (name == nullptr) {
        return -1;
    }

    int fd = mylinux::zygote::getInheritedServerSocket(name);

    env->ReleaseStringUTFChars(socketName, name);

    if (fd < 0) {
        char message[160];

        snprintf(
            message,
            sizeof(message),
            "Invalid inherited Zygote socket: %s",
            strerror(errno)
        );

        throwIOException(env, message);
        return -1;
    }

    return static_cast<jint>(fd);
}

const JNINativeMethod methods[] = {
    {
        const_cast<char*>("nativeGetServerSocketFd"),
        const_cast<char*>("(Ljava/lang/String;)I"),
        reinterpret_cast<void*>(nativeGetServerSocketFd)
    }
};

} // namespace

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(
    JavaVM* vm,
    void*
) {
    JNIEnv* env = nullptr;

    if (vm->GetEnv(
            reinterpret_cast<void**>(&env),
            JNI_VERSION_1_6
        ) != JNI_OK) {
        return JNI_ERR;
    }

    jclass clazz = env->FindClass(
        "com/mylinux/internal/os/NativeZygote"
    );

    if (clazz == nullptr) {
        return JNI_ERR;
    }

    jint result = env->RegisterNatives(
        clazz,
        methods,
        sizeof(methods) / sizeof(methods[0])
    );

    env->DeleteLocalRef(clazz);

    if (result != JNI_OK) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
