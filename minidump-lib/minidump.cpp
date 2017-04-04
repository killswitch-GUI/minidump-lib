// minidump.cpp
// compile with: cl /c /EHsc minidump.cpp
// post-build command: lib minidump.obj

// force linker to find the dbghelp.lib from WDK
#pragma comment( lib, "dbghelp" )

#include "minidump.h"
#include <windows.h>
#include "Dbghelp.h"
#include <iostream>

using namespace std;

namespace MiniDump
{
	// perfrom mini-dump on process id
	bool MiniDumpFunctions::MiniDumpProc(DWORD procid, LPCTSTR FileName)
	{
		HANDLE FileHandle;
		HANDLE ProcHandle;

		// Get a file handle
		FileHandle = OpenFileHandle(FileName);
		// Get a proc handle 
		ProcHandle = OpenProcessHandle(procid);

		if (!MiniDumpWriteDump(
			ProcHandle,
			procid,
			FileHandle,
			MiniDumpWithFullMemory,
			NULL,
			NULL,
			NULL
		))
		{
			std::cout << GetLastError() << std::endl;
			return FALSE;
		}
		return TRUE;
	}

	// obtain a windows proc handle to process ID
	HANDLE MiniDumpFunctions::OpenProcessHandle(DWORD procid)
	{
		HANDLE hProcess;

		hProcess = OpenProcess(
			PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_DUP_HANDLE, 
			FALSE,
			procid
			);
		if (hProcess == NULL)
		{
			std::cout << "Failed to get proc handle" << std::endl;
			std::cout << GetLastError() << std::endl;
		}

		return hProcess;
	}

	HANDLE MiniDumpFunctions::OpenFileHandle(LPCTSTR FileName)
	{
		HANDLE FileHandle;

		FileHandle = CreateFile(
			FileName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_HIDDEN,
			NULL
		);
		if (FileHandle == INVALID_HANDLE_VALUE)
		{
			std::cout << "Failed to get file handle" << std::endl;
			std::cout << GetLastError() << std::endl;
		}

		return FileHandle;
	}
	

}