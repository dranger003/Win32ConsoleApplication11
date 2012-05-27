// Win32ConsoleApplication11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>

using namespace ClassLibrary1;

int _tmain(int argc, _TCHAR* argv[])
{
    ::CoInitializeEx(NULL, COINIT_MULTITHREADED);

    {
        HRESULT hr;
        IClass1Ptr sp;
        if (SUCCEEDED(hr = sp.CreateInstance(__uuidof(Class1))))
        {
            sp->Ping();
        }
        else
        {
            ::_tprintf(_T("CreateInstance(): %s\n"), _com_error(hr).ErrorMessage());
        }

        ::_getch();
    }

    ::CoUninitialize();

    return 0;
}
