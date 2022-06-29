/*****************************************************************************\
*                                                                             *
* Title: IConfigProcess.h                                                     *
*                                                                             *
* Description: Interface of basic functions for manipulating processes.       *
*                                                                             *
* Author: vlnnt								      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#pragma once
#ifndef ICONFIG_PROCESS_H
#define ICONFIG_PROCESS_H

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

class IConfigProcess {
public:
	virtual ~IConfigProcess(){}
	virtual int __stdcall TerminateProcesses(DWORD dwProcessID, UINT uExitCode) = 0;
	virtual void __stdcall UpdateProcesses() = 0;
};

#endif // !ICONFIG_PROCESS_H