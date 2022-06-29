/*****************************************************************************\
*                                                                             *
* Title: ConfigProcess.h                                                      *
*                                                                             *
* Description: Redefining interface fields "IConfigProcess".		      *
*                                                                             *
* Author: vlnnt								      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#pragma once
#ifndef CONFIG_PROCESS_H
#define CONFIG_PROCESS_H

#include "IConfigProcess.h"

class ConfigProcess : public IConfigProcess {
public:
	ConfigProcess();
	~ConfigProcess();

	int __stdcall TerminateProcesses(DWORD dwProcessID, UINT uExitCode) override;
	void __stdcall UpdateProcesses() override;
	static int __stdcall ShowProcesses(HWND hwnd, LPARAM lParam);
	void Client();
		
private:
	DWORD _dwDesiredAccess {PROCESS_TERMINATE};
	BOOL _bInheritHandle {FALSE}; 
	HANDLE _hProcess; 
	BOOL _tResult;
	HANDLE _hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO _csbi;
	DWORD _chCount;
	DWORD _cellCount;
	COORD _startCoords {0,0};
};

#endif // !CONFIG_PROCESS_H