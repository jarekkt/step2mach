//=====================================================================
//
//	Plugin.cpp - the optional custom part of the plugin
//
//	this source file can be filled with the actual custom code that
//	makes the plugin work. it is the choice of the developer to enable
//	which functions will be used from the available MachDevice calls.
//
//	if this is a mixed mode dll each function can be declared as either
//	an unmanaged or managed function.
//
//	please see the documentation in Plugin.h for the #define statements
//	that control each functions compilation.
//
//	if this is a mixed mode dll and you need to keep global managed
//	reference please see the MG class in ManagedGlobal.h
//
//	please read the notes and comments in MachDevice.cpp for general
//	information and disclaimers.
//
//=====================================================================

#include "stdafx.h"
#include "Plugin.h"
#include "MachDevice.h"
#include "ConfigDialog.h"
#include "PlugInControlDialog.h"
#include "XMLNetProfile.h"
#include "ManagedGlobal.h"
#include "MyDevice.h"

#include <stdlib.h>


//---------------------------------------------------------------------
//	the default namespace for managed functions and classes
//---------------------------------------------------------------------

using namespace mach_plugin;

//---------------------------------------------------------------------
//	data area
//---------------------------------------------------------------------

int					menuStart;				// the starting menu id
MyDeviceClass	 *  MyDevice;

//---------------------------------------------------------------------
//
//	piInitControl() - Plugin extension of InitControl()
//
//		XML file can NOT be accessed since SetProName hasn't
//		been called yet
//
//		called EVEN if plugin is disabled
//
//---------------------------------------------------------------------



#ifdef PI_INITCONTROL
#ifdef _MANAGED
#pragma PI_MIX_INITCONTROL
#endif
bool piInitControl()
{
	menuStart = GetMenuRange(MENU_COUNT);

	MyDevice  = new MyDeviceClass;

	MyDevice->InitControl();

	return true;
}
#endif

//---------------------------------------------------------------------
//
//	piSetProName() - Plugin extension of SetProName()
//
//		XML file CAN be accessed
//
//		called EVEN if plugin is disabled
//
//---------------------------------------------------------------------

#ifdef PI_SETPRONAME
#ifdef _MANAGED
#pragma PI_MIX_SETPRONAME
#endif
char* piSetProName(LPCSTR name)
{
	Step2MachConfig^	Config = gcnew Step2MachConfig;
	XMLNetProfile^	profile    = gcnew XMLNetProfile(gcnew String(ProfileName), "Step2Mach_plugin", true);

	profile->Load();

	Config->dev_ip_address = profile->ReadString("dev_ip_address");
	if(Config->dev_ip_address == "")
	{
		Config->dev_ip_address = "169.254.1.3";
	}

	Config->debug_mode  = profile->ReadBool("debug_mode",false);


	MG::Config  = Config;

	return "Step2Mach-v2.0.0.0";
}
#endif




//---------------------------------------------------------------------
//
//	piPostInitControl() - Plugin extension of PostInitControl()
//
//		XML file can NOT be accessed
//
//		called ONLY if plugin is enabled
//
//---------------------------------------------------------------------

#ifdef PI_POSTINITCONTROL
#ifdef _MANAGED
#pragma PI_MIX_POSTINITCONTROL
#endif
void piPostInitControl()
{
	HMENU			hMachMenu = GetMenu(MachView->MachFrame->m_hWnd);
	HMENU			hPluginMenu = 0;
	int				machMenuCnt = GetMenuItemCount(hMachMenu);
	MENUITEMINFO	mii;
	LPTSTR			txt;


	for (int i = 0; i < machMenuCnt; i++)
	{
		mii.cbSize     = sizeof(MENUITEMINFO);
		mii.fMask      = MIIM_FTYPE | MIIM_ID | MIIM_SUBMENU | MIIM_STRING;
		mii.dwTypeData = NULL;

		if (GetMenuItemInfo(hMachMenu, i, true, &mii))
		{
			txt = (LPTSTR) malloc(++mii.cch);
			mii.dwTypeData = txt;

			if (GetMenuItemInfo(hMachMenu, i, true, &mii))
			{
				if (strcmp(txt, "PlugIn Control") == 0)
				{
					hPluginMenu = mii.hSubMenu;
					i = machMenuCnt;
				}
			}

			free(txt);
		}

		if (hPluginMenu)
		{
			InsertMenu(hPluginMenu, -1, MF_BYPOSITION, menuStart  , "Step2Mach");
		}
	}

	Step2MachConfig^	Config = MG::Config;
	std::string			dev_ip_address = MyDeviceClass::nets2s(Config->dev_ip_address);


	MyDevice->Reconfigure(dev_ip_address.c_str(),Config->debug_mode);


}
#endif

//---------------------------------------------------------------------
//
//	piConfig() - Plugin extension of Config()
//
//		called if user presses CONFIG in Config|Config Plugins
//		even if plugin is disabled
//
//		XML file CAN be accessed
//
//---------------------------------------------------------------------

#ifdef PI_CONFIG
#ifdef _MANAGED
#pragma PI_MIX_CONFIG
#endif
void piConfig()
{
	ConfigDialog^	configDialog = gcnew ConfigDialog();


	configDialog->ShowDialog();
}
#endif

//---------------------------------------------------------------------
//
//	piStopPlug() - Plugin extension of StopPlug()
//
//---------------------------------------------------------------------

#ifdef PI_STOPPLUG
#ifdef _MANAGED
#pragma PI_MIX_STOPPLUG
#endif
void piStopPlug()
{
	Step2MachConfig^	Config = MG::Config;
	
	XMLNetProfile^	   profile = gcnew XMLNetProfile(gcnew String(ProfileName), "Step2Mach_plugin", true);

	if (profile->Load())
	{
		profile->WriteString("dev_ip_address",Config->dev_ip_address);
		profile->WriteBool("debug_mode",Config->debug_mode);
		profile->Save();
	}
}
#endif

//---------------------------------------------------------------------
//
//	piUpdate() - Plugin extension of Update()
//
//		XML file can NOT be accessed
//
//		called ONLY if plugin is enabled
//
//		WARNING - when you enable a plugin it immediately is added
//		to the update loop. if you haven't initialized some items
//		because PostInitControl() hasn't been called you can get
//		some problems!!!
//
//---------------------------------------------------------------------

#ifdef PI_UPDATE
#ifdef _MANAGED
#pragma PI_MIX_UPDATE
#endif
void piUpdate()
{
	MyDevice->Update();
}
#endif

//---------------------------------------------------------------------
//
//	piNotify() - Plugin extension of Notify()
//
//		among other notices this is where we are notified when the
//		user clicks on our 'PlugIn Control' menu item.
//
//		XML file CAN be accessed on a menu item notify
//
//---------------------------------------------------------------------

#ifdef PI_NOTIFY
#ifdef _MANAGED
#pragma PI_MIX_NOTIFY
#endif
void piNotify(int id)
{
	MyDevice->last_notification = id;

	if (id == menuStart)
	{
		PlugInControlDialog^	pluginControlDialog = gcnew PlugInControlDialog();
		Step2MachConfig^		Config = MG::Config;
		std::string				dev_ip_address;
		DialogResult			dResult;


		while(1)
		{
		
			pluginControlDialog->Address->Text				 = Config->dev_ip_address;
			pluginControlDialog->EnableDebugCB->Checked		 = Config->debug_mode;

			// Execute configuration dialog
			dResult = pluginControlDialog->ShowDialog();
			if (dResult == DialogResult::OK)
			{
				// Apply new configuration
				Config->dev_ip_address = pluginControlDialog->Address->Text;
				Config->debug_mode     = pluginControlDialog->EnableDebugCB->Checked;
				break;
			}	
			else
			{
				// Cancel
				return;
			}
		}

		dev_ip_address = MyDeviceClass::nets2s(Config->dev_ip_address);
		MyDevice->Reconfigure(dev_ip_address.c_str(),Config->debug_mode);
	}
}
#endif

//---------------------------------------------------------------------
//
//	piDoDwell() - Plugin extension of DoDwell()
//
//---------------------------------------------------------------------

#ifdef PI_DODWELL
#ifdef _MANAGED
#pragma PI_MIX_DODWELL
#endif
void piDoDwell(double time)
{
	MyDevice->Dwell(time);
}
#endif

//---------------------------------------------------------------------
//
//	piReset() - Plugin extension of Reset()
//
//---------------------------------------------------------------------

#ifdef PI_RESET
#ifdef _MANAGED
#pragma PI_MIX_RESET
#endif
void piReset()
{
	MyDevice->Reset();
}
#endif

//---------------------------------------------------------------------
//
//	piJogOn() - Plugin extension of JogOn()
//
//---------------------------------------------------------------------

#ifdef PI_JOGON
#ifdef _MANAGED
#pragma PI_MIX_JOGON
#endif
void piJogOn(short axis, short dir, double speed)
{
	MyDevice->JogOn(axis, dir, speed);
}
#endif

//---------------------------------------------------------------------
//
//	piJogOff() - Plugin extension of JogOff()
//
//---------------------------------------------------------------------

#ifdef PI_JOGOFF
#ifdef _MANAGED
#pragma PI_MIX_JOGOFF
#endif
void piJogOff(short axis)
{
	MyDevice->JogOff(axis);
}
#endif

//---------------------------------------------------------------------
//
//	piPurge() - Plugin extension of Purge()
//
//---------------------------------------------------------------------

#ifdef PI_PURGE
#ifdef _MANAGED
#pragma PI_MIX_PURGE
#endif
void piPurge(short flags)
{
	MyDevice->Purge(flags);
}
#endif

//---------------------------------------------------------------------
//
//	piProbe() - Plugin extension of Probe()
//
//---------------------------------------------------------------------

#ifdef PI_PROBE
#ifdef _MANAGED
#pragma PI_MIX_PROBE
#endif
void piProbe()
{
	MyDevice->Probe();
}
#endif 

//---------------------------------------------------------------------
//
//	piHome() - Plugin extension of Home()
//
//---------------------------------------------------------------------

#ifdef PI_HOME
#ifdef _MANAGED
#pragma PI_MIX_HOME
#endif
void piHome(short axis)
{
	MyDevice->Home(axis);
}
#endif
