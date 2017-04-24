# Microsoft Developer Studio Project File - Name="NPS7510" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=NPS7510 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NPS7510.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NPS7510.mak" CFG="NPS7510 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NPS7510 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NPS7510 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NPS7510 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "NPS7510 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\iVex\NPS7510"
# PROP Intermediate_Dir "..\..\..\Debug\iVex\NPS7510"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\DMR\DMRXXX\NPS7510" /I "..\NPS7510" /I "..\..\..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\Public\Public.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\iVex\Device\NPS7510.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NPS7510 - Win32 Release"
# Name "NPS7510 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\PUB\__Alarm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__AlarmCTPT.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Data.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__DevSet.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__DFT.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Edit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Event.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__HZ12x12.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__HZ16x16.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Key.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__LCD.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__LCDMem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Measure.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Output.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__PQPhQh.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\__Protect.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Switch.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Time.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Tool.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__WaveRecord.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\_MyAppNPS7510.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\_MyHMINPS7510.c
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\ArEEPROM_iVEX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\ArRTC_iVEX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\Flash_iVex.cpp
# End Source File
# Begin Source File

SOURCE=..\PUB\HDIFDMR.cpp
# End Source File
# Begin Source File

SOURCE=.\HDIFNPS7510.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyApp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\MyComm_iVEX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyHMIDMR.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyMenu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyMenu160x160.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\MyMenuNPS7510.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyPage.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyPage160x160.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\MyPageNPS7510.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyPG_Protect.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\MyPG_ProtectNPS7510.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyPG_WaveRecord.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyProtocol.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyProtocolMODBUS.c
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyTable.c
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyTableDMR.c
# End Source File
# Begin Source File

SOURCE=.\NPS7510.cpp
# End Source File
# Begin Source File

SOURCE=.\NPS7510.def
# End Source File
# Begin Source File

SOURCE=.\NPS7510.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\Protect.c
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\PUB\__Alarm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__AlarmCTPT.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__DevSet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__DFT.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Edit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Event.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Key.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__LCD.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__LCDMem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Main1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Measure.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Output.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__PQPhQh.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\__Protect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Switch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Time.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__Tool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\__WaveRecord.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\_Main1DMR.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\_MyAppNPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\_MyHMINPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\ArEEPROM_iVEX.h
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\ArRTC_iVEX.h
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\Flash_iVEX.h
# End Source File
# Begin Source File

SOURCE=..\PUB\HDIFDMR.h
# End Source File
# Begin Source File

SOURCE=.\HDIFNPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\Main.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyApp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\HDLIB\MyComm_iVEX.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyHmi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyHMIDMR.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyLock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyMenu160x160.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\MyMenuNPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyPage160x160.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\MyPageNPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyPG_Protect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\MyPG_ProtectNPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyPG_WaveRecord.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyProtocol.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyProtocolMODBUS.h
# End Source File
# Begin Source File

SOURCE=..\..\..\PUB\MyTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\PUB\MyTableDMR.h
# End Source File
# Begin Source File

SOURCE=.\NPS7510.h
# End Source File
# Begin Source File

SOURCE=..\..\..\DMR\DMRXXX\NPS7510\Protect.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\NPS7510.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
