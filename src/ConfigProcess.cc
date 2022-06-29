/*****************************************************************************\
*                                                                             *
* Title: ConfigProcess.cc                                                     *
*                                                                             *
* Description: Implementation of functions of the class "ConfigProcess".      *
*                                                                             *
* Author: vlnnt						                      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#include "ConfigProcess.h"

ConfigProcess::ConfigProcess() :_hProcess{}, _tResult{}, _hStdOut{}, _csbi{}, _chCount{}, _cellCount{} {}

int __stdcall ConfigProcess::TerminateProcesses(DWORD dwProcessID, UINT uExitCode) {

	try {

		_hProcess = OpenProcess(_dwDesiredAccess, _bInheritHandle, dwProcessID);
		if (_hProcess == NULL) { throw std::runtime_error{ "Exception: ID Process isn't correct." }; }
		_tResult = TerminateProcess(_hProcess, uExitCode);
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	return _tResult;
}

void __stdcall ConfigProcess::UpdateProcesses() {

	try {

		_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		if (_hStdOut == INVALID_HANDLE_VALUE) { throw std::runtime_error{ "Exception: Invalid handle value." }; }
		if (!GetConsoleScreenBufferInfo(_hStdOut, &_csbi)) { throw std::runtime_error{ "Exception: Buffer not received." }; }

		_cellCount = _csbi.dwSize.X * _csbi.dwSize.Y;

		if (!FillConsoleOutputCharacter(_hStdOut, (TCHAR)' ', _cellCount, _startCoords, &_chCount)) { throw std::runtime_error{ "Exception: Invalid fill parameter." }; }
		if (!FillConsoleOutputAttribute(_hStdOut, _csbi.wAttributes, _cellCount, _startCoords, &_chCount)) { throw std::runtime_error{ "Exception: Invalid fill parameter." }; }

		SetConsoleCursorPosition(_hStdOut, _startCoords);
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}

int __stdcall ConfigProcess::ShowProcesses(HWND hwnd, LPARAM lParam) {
		
	DWORD dwThreadID;
	DWORD dwProcessID;
	HINSTANCE hInstance;
	char wParamString[MAX_PATH];
	
	try {

		if (!hwnd) { return TRUE; }
		if (!IsWindowVisible(hwnd)) { return TRUE; }
		if (!SendMessage(hwnd, WM_GETTEXT, sizeof(wParamString), (LPARAM)wParamString)) { return TRUE; }

		hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWL_HINSTANCE);
		dwThreadID = GetWindowThreadProcessId(hwnd, &dwProcessID);

		cout << " Process ID: " << dwProcessID << "\t" << "Process Name: " << wParamString << endl;
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	return TRUE;
}

ConfigProcess::~ConfigProcess() {
	CloseHandle(_hProcess);
}

void ConfigProcess::Client() {

	cout << "Enter ID of the process you want to kill." << "\n";
	cout << "If you want to update the list of processes, enter number 1." << "\n" << "\n";
	cout << "====================================== " << " ACTIVE PROCESSES " << " ======================================" << "\n" << "\n";

	EnumWindows(ConfigProcess::ShowProcesses, NULL);
	
	cout << "\n";
	cout << "====================================== " << " ACTIVE PROCESSES " << " ======================================" << "\n" << "\n";
	cout << "Enter the PID: ";
}