
#include "NativeCodeAstJni.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

// CLASS_NAMEの部分はJavaのクラス名となりますので、
// <スラッシュ区切りのpkgname>/NativeCodeAst のようにします
#define  CLASS_NAME "com/nagohiyo/number_ten/NativeCodeAst"

void NativeCodeAstJni::showAstJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showAstJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeCodeAstJni::hideAstJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideAstJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeCodeAstJni::initAstJni()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "initAstJni", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
        