/*****************************************************************************\
*                                                                             *
* Title: Main.cc                                                              *
*                                                                             *
* Description: Main file, with client implementation.                         *
*                                                                             *
* Author: vlnnt								      *
*                                                                             *
* IDE: Visual Studio 2019                                                     *
*                                                                             *
\*****************************************************************************/

#include "ConfigProcess.h"

int main() {

	setlocale(LC_ALL, "RU");

	DWORD PID {};
	ConfigProcess configInstance;

	/* output of the user menu */
	configInstance.Client();
	
	while (true) {

		/* entering the process id */
		cin >> PID;

		/* when killing a process, updates the console */
		if (configInstance.TerminateProcesses(PID, 1)) {
			configInstance.UpdateProcesses();
			configInstance.Client();
		}

		/* when entering 1, updates the console */
		if (PID == 1) {
			configInstance.UpdateProcesses();
			configInstance.Client();
		}

		/* if an incorrect number is entered, updates the console */
		if (PID != 1 || configInstance.TerminateProcesses(PID, 1)) {
			configInstance.UpdateProcesses();
			configInstance.Client();
		}
	}

	return 0;
}