/*****************************************************************
|
|      Android JNI Interface
|
|      (c) 2002-2012 Plutinosoft LLC
|      Author: Sylvain Rebaud (sylvain@plutinosoft.com)
|
 ****************************************************************/

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include <assert.h>

#ifdef _ANDROID_
#include <jni.h>
#include <android/log.h>
#endif

#include <string.h>
#include <sys/types.h>

#include "platinum-jni.h"
//#include "Platinum.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"
#include "receiver.h"


/*----------------------------------------------------------------------
|   logging
+---------------------------------------------------------------------*/
NPT_SET_LOCAL_LOGGER("platinum.android.jni")

#ifdef _ANDROID_
/*----------------------------------------------------------------------
|   functions
+---------------------------------------------------------------------*/
__attribute__((constructor)) static void onDlOpen(void)
{
}

#endif

#ifdef _ANDROID_
/*----------------------------------------------------------------------
|    JNI_OnLoad
+---------------------------------------------------------------------*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    NPT_LogManager::GetDefault().Configure("plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.outputs=2;.ConsoleHandler.colors=false;.ConsoleHandler.filter=59");
    return JNI_VERSION_1_4;
}
#endif

#ifdef _ANDROID_
/*
 * Class:     com_plutinosoft_platinum_UPnP
 * Method:    _init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ga_iloveyaya_testUPnP_init(JNIEnv *env, jclass clz)
#else
long Java_ga_iloveyaya_testUPnP_init()
#endif
{
    NPT_LOG_INFO("init");
    PLT_UPnP* self = new PLT_UPnP();
#ifdef _ANDROID_
    return (jlong)self;
#else
	return (long)self;
#endif
}

#ifdef _ANDROID_
/*
 * Class:     com_plutinosoft_platinum_UPnP
 * Method:    _start
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ga_iloveyaya_testUPnP_startservice(JNIEnv *env, jclass clz, jlong _self, jstring dev_name)
#else
int Java_ga_iloveyaya_testUPnP_startservice(long _self, const char *dev_name)
#endif
{
    NPT_LOG_INFO("start");
    PLT_UPnP* self = (PLT_UPnP*)_self;
    
#ifdef _ANDROID_
	char *str_name = const_cast<char *>(env->GetStringUTFChars(tablePath_, 0));
#else
	const char *str_name = dev_name;
#endif
	IMediaActionReceiver *dele = new IMediaActionReceiver();
	PLT_MediaRenderer *render = new PLT_MediaRenderer(str_name/*"Platinum Media Renderer"*/,
                              false,
                              "e6572b54-f3c7-2d91-2fb5-b757f2537e21");
	render->SetDelegate(dele);
    PLT_DeviceHostReference device(render);

    self->AddDevice(device);

    return self->Start();
}

#ifdef _ANDROID_
/*
 * Class:     com_plutinosoft_platinum_UPnP
 * Method:    _stop
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ga_iloveyaya_testUPnP_stopservice(JNIEnv *env, jclass clz, jlong _self)
#else
int Java_ga_iloveyaya_testUPnP_stopservice(long _self)
#endif
{
    NPT_LOG_INFO("stop");
    PLT_UPnP* self = (PLT_UPnP*)_self;
    
    return self->Stop();
}