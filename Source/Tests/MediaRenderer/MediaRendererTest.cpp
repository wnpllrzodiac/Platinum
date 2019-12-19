/*****************************************************************
|
|   Platinum - Test UPnP A/V MediaRenderer
|
| Copyright (c) 2004-2010, Plutinosoft, LLC.
| All rights reserved.
| http://www.plutinosoft.com
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of the GNU General Public License
| as published by the Free Software Foundation; either version 2
| of the License, or (at your option) any later version.
|
| OEMs, ISVs, VARs and other distributors that combine and 
| distribute commercially licensed software with Platinum software
| and do not wish to distribute the source code for the commercially
| licensed software under version 2, or (at your option) any later
| version, of the GNU General Public License (the "GPL") must enter
| into a commercial license agreement with Plutinosoft, LLC.
| licensing@plutinosoft.com
| 
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; see the file LICENSE.txt. If not, write to
| the Free Software Foundation, Inc., 
| 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
| http://www.gnu.org/licenses/gpl-2.0.html
|
 ****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "PltUPnP.h"
#include "PltMediaRenderer.h"

typedef int NPT_Result;

#include <stdlib.h>

/*----------------------------------------------------------------------
|   globals
+---------------------------------------------------------------------*/
struct Options {
    const char* friendly_name;
} Options;

/*----------------------------------------------------------------------
|   PrintUsageAndExit
+---------------------------------------------------------------------*/
static void
PrintUsageAndExit(char** args)
{
    fprintf(stderr, "usage: %s [-f <friendly_name>]\n", args[0]);
    fprintf(stderr, "-f : optional upnp server friendly name\n");
    fprintf(stderr, "<path> : local path to serve\n");
    exit(1);
}

/*----------------------------------------------------------------------
|   ParseCommandLine
+---------------------------------------------------------------------*/
static void
ParseCommandLine(char** args)
{
    const char* arg;
    char**      tmp = args+1;

    /* default values */
    Options.friendly_name = NULL;

    while ((arg = *tmp++)) {
        if (!strcmp(arg, "-f")) {
            Options.friendly_name = *tmp++;
        } else {
            fprintf(stderr, "ERROR: too many arguments\n");
            PrintUsageAndExit(args);
        }
    }
}

class myDelegate: public PLT_MediaRendererDelegate
{
public:
	myDelegate(){}
	~myDelegate(){}

	// ConnectionManager
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

NPT_Result myDelegate::OnGetCurrentConnectionInfo(PLT_ActionReference& action)
{
	return 0;
}

// AVTransport
NPT_Result myDelegate::OnNext(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnPause(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnPlay(PLT_ActionReference& action)
{
	printf("OnPlay() \n");
	return 0;
}

NPT_Result myDelegate::OnPrevious(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnSeek(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnStop(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnSetAVTransportURI(PLT_ActionReference& action)
{
	NPT_String curURI;
	action->GetArgumentValue("CurrentURI", curURI);
	printf("OnSetAVTransportURI: %s\n", curURI.GetChars());
	return 0;
}

NPT_Result myDelegate::OnSetPlayMode(PLT_ActionReference& action)
{
	return 0;
}

// RenderingControl
NPT_Result myDelegate::OnSetVolume(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnSetVolumeDB(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnGetVolumeDBRange(PLT_ActionReference& action)
{
	return 0;
}

NPT_Result myDelegate::OnSetMute(PLT_ActionReference& action)
	{
	return 0;
}


/*----------------------------------------------------------------------
|   main
+---------------------------------------------------------------------*/
int
main(int /* argc */, char** argv)
{   
    PLT_UPnP upnp;

    /* parse command line */
    ParseCommandLine(argv);

	myDelegate *dele = new myDelegate();
	PLT_MediaRenderer *render = new PLT_MediaRenderer(Options.friendly_name?Options.friendly_name:"Platinum Media Renderer",
                              false,
                              "e6572b54-f3c7-2d91-2fb5-b757f2537e21");
	render->SetDelegate(dele);
    PLT_DeviceHostReference device(render);

    upnp.AddDevice(device);
    bool added = true;

    upnp.Start();

    char buf[256];
    while (true) {
        fgets(buf, 256, stdin);
        if (*buf == 'q')
            break;

        if (*buf == 's') {
            if (added) {
                upnp.RemoveDevice(device);
				printf("device offline\n");
            } else {
                upnp.AddDevice(device);
				printf("device online\n");
            }
            added = !added;
        }
    }

    upnp.Stop();
    return 0;
}
