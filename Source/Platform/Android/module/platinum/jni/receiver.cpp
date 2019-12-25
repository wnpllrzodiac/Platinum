#include "receiver.h"

void
IMediaActionReceiver::ActionInflect(int cmd, const char* value, const char* data)
{	
	/*
    NPT_LOG_INFO("------------------->@@@@@@@############.\n");
    int status;
    JNIEnv *env = NULL;
    bool isAttach = false;
    status = jvm->GetEnv((void**) &env, JNI_VERSION_1_4);

    if(status != JNI_OK) 
    {
        status = jvm->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            return;
        }
        isAttach = true;
    }

    jstring valueString = NULL;
    jstring dataString = NULL;

    jclass inflectClass = g_inflectClass;
    jmethodID inflectMethod = g_methodID;

    if (inflectClass == NULL || inflectMethod == NULL)
    { 
        goto end;
    }


    valueString = env->NewStringUTF(value);
    dataString = env->NewStringUTF(data);

    env->CallStaticVoidMethod(inflectClass, inflectMethod,valueString, dataString,cmd);

    env->DeleteLocalRef(valueString);
    env->DeleteLocalRef(dataString);
    end:
    if (env->ExceptionOccurred())
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    if (isAttach)
    {
        jvm->DetachCurrentThread();
    }*/

}

NPT_Result IMediaActionReceiver::OnGetCurrentConnectionInfo(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

// AVTransport
NPT_Result IMediaActionReceiver::OnNext(PLT_ActionReference& action)
{
	NPT_String curURI;
    action->GetArgumentValue("CurrentURI", curURI);
    NPT_String metaData ;
    action->GetArgumentValue("CurrentURIMetaData", metaData);
    ActionInflect(MEDIA_RENDER_CTL_MSG_NEXT, curURI.GetChars(),	 metaData.GetChars());
    return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnPause(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnPlay(PLT_ActionReference& action)
{
	printf("OnPlay() \n");
	ActionInflect(MEDIA_RENDER_CTL_MSG_PLAY, action->GetActionDesc().GetName().GetChars(), "");
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnPrevious(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnSeek(PLT_ActionReference& action)
{
	ActionInflect(MEDIA_RENDER_CTL_MSG_SEEK, action->GetActionDesc().GetName().GetChars(), "");
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnStop(PLT_ActionReference& action)
{
	printf("OnStop() \n");
	ActionInflect(MEDIA_RENDER_CTL_MSG_STOP, action->GetActionDesc().GetName().GetChars(), "");
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnSetAVTransportURI(PLT_ActionReference& action)
{
	NPT_String curURI;
	action->GetArgumentValue("CurrentURI", curURI);
	printf("OnSetAVTransportURI: %s\n", curURI.GetChars());
	ActionInflect(MEDIA_RENDER_CTL_MSG_SET_AV_URL, curURI.GetChars(), "");
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnSetPlayMode(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

// RenderingControl
NPT_Result IMediaActionReceiver::OnSetVolume(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnSetVolumeDB(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnGetVolumeDBRange(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}

NPT_Result IMediaActionReceiver::OnSetMute(PLT_ActionReference& action)
	{
	return NPT_SUCCESS;
}

