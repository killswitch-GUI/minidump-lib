#pragma once
// minidump.h
#include <windows.h>


namespace MiniDump
{
	class MiniDumpFunctions
	{
	public:
		// perfrom mini-dump on process id
		bool MiniDumpProc(DWORD procid, LPCTSTR FileName);
	private:
		HANDLE OpenProcessHandle(DWORD procid);
		HANDLE OpenFileHandle(LPCTSTR FileName);
	};

}