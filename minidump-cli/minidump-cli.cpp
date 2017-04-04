// minidump-cli.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "minidump.h"

using namespace MiniDump;

int main(int argc, char* argv[])
{
	int ProcId;
	LPCTSTR Path;

	wchar_t *command2 = NULL;
	command2 = new wchar_t[256];

	Sleep(10000);
	MiniDumpFunctions d;
	if (argc < 3)
	{
		std::cout << "Minidump Usage: 1345 D:\\dump.DMP" << std::endl;
		return 0;
	}

	ProcId = atoi(argv[1]);

	if (!d.MiniDumpProc(ProcId, L"D:\\test.DMP"))
	{
		std::cout << "Failed to dump process..." << std::endl;
	}
	std::cout << "Process dump done!" << std::endl;

    return 0;
}

