#ifndef _MY_RECEIVER_H_
#define _MY_RECEIVER_H_

#include "PltUPnP.h"
#include "PltMediaRenderer.h"

class IMediaActionReceiver: public PLT_MediaRendererDelegate
{
public:
    static const int MEDIA_RENDER_CTL_MSG_BASE = 0x100;
    static const int MEDIA_RENDER_CTL_MSG_SET_AV_URL = (MEDIA_RENDER_CTL_MSG_BASE+0);
    static const int MEDIA_RENDER_CTL_MSG_STOP = (MEDIA_RENDER_CTL_MSG_BASE+1);
    static const int MEDIA_RENDER_CTL_MSG_PLAY = (MEDIA_RENDER_CTL_MSG_BASE+2);
    static const int MEDIA_RENDER_CTL_MSG_PAUSE = (MEDIA_RENDER_CTL_MSG_BASE+3);
    static const int MEDIA_RENDER_CTL_MSG_SEEK = (MEDIA_RENDER_CTL_MSG_BASE+4);
    static const int MEDIA_RENDER_CTL_MSG_SETVOLUME = (MEDIA_RENDER_CTL_MSG_BASE+5);
    static const int MEDIA_RENDER_CTL_MSG_SETMUTE = (MEDIA_RENDER_CTL_MSG_BASE+6);
    static const int MEDIA_RENDER_CTL_MSG_SETPLAYMODE = (MEDIA_RENDER_CTL_MSG_BASE+7);
    static const int MEDIA_RENDER_CTL_MSG_PRE = (MEDIA_RENDER_CTL_MSG_BASE+8);
    static const int MEDIA_RENDER_CTL_MSG_NEXT = (MEDIA_RENDER_CTL_MSG_BASE+9);
      
public:
    virtual void ActionInflect(int cmd, const char* value, const char* data);
    virtual NPT_Result OnGetCurrentConnectionInfo(PLT_ActionReference& action);

    // AVTransport
    virtual NPT_Result OnNext(PLT_ActionReference& action);
    virtual NPT_Result OnPause(PLT_ActionReference& action);
    virtual NPT_Result OnPlay(PLT_ActionReference& action);
    virtual NPT_Result OnPrevious(PLT_ActionReference& action);
    virtual NPT_Result OnSeek(PLT_ActionReference& action);
    virtual NPT_Result OnStop(PLT_ActionReference& action);
    virtual NPT_Result OnSetAVTransportURI(PLT_ActionReference& action);
    virtual NPT_Result OnSetPlayMode(PLT_ActionReference& action);
   
    // RenderingControl
    virtual NPT_Result OnSetVolume(PLT_ActionReference& action);
    virtual NPT_Result OnSetVolumeDB(PLT_ActionReference& action);
    virtual NPT_Result OnGetVolumeDBRange(PLT_ActionReference& action);
    virtual NPT_Result OnSetMute(PLT_ActionReference& action);
};

#endif