// Win32ConsoleApplication11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>

using namespace WindowsFormsApplication4;

int _tmain(int argc, _TCHAR* argv[])
{
    ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    //::CoInitialize(NULL);

    ::_tprintf(_T("U:%ld - _tmain()\n"), ::GetCurrentThreadId());

    {
        {
            {
                CHandle hFile = (CHandle)::CreateFile(
                    _T("C:\\DATA\\BUFFER.dat"),
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    0,
                    NULL);
                ATLASSERT(hFile != INVALID_HANDLE_VALUE);

                DWORD dwSize = ::GetFileSize(hFile, NULL);

                HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
                ATLASSERT(hGlobal != NULL);

                PVOID pvd = (PVOID)::GlobalLock(hGlobal);
                ATLASSERT(pvd != NULL);

                DWORD dwBytes = 0;
                ::ReadFile(hFile, pvd, dwSize, &dwBytes, NULL);

                BOOL bRes = ::GlobalUnlock(hGlobal);

                //::_tprintf(_T("dwSize = %ld, dwBytes = %ld\n"), dwSize, dwBytes);

                {
                    CComPtr<IStream> spStream;
                    HRESULT hr = ::CreateStreamOnHGlobal(hGlobal, TRUE, &spStream);
                    ATLASSERT(SUCCEEDED(hr));

                    {
                        CComPtr<IClass1> spClass1;
                        hr = ::CoUnmarshalInterface(spStream, __uuidof(IClass1), (PVOID*)&spClass1);
                        ATLASSERT(SUCCEEDED(hr));

                        hr = spClass1->Ping();
                        ATLASSERT(SUCCEEDED(hr));
                    }
                }
            }
        }

        //HRESULT hr;
        //IClass1Ptr sp;
        //IClass1* p = NULL;
        //::_tprintf(_T("Creating...\n"));
        //if (SUCCEEDED(hr = sp.CreateInstance(__uuidof(Class1))))
        ////if (SUCCEEDED(hr = ::CoCreateInstance(__uuidof(Class1), NULL, CLSCTX_LOCAL_SERVER, __uuidof(IClass1), (PVOID*)&p)))
        //{
        //    ::_tprintf(_T("Calling Ping()...\n"));

        //    sp->Ping();

        //    //p->Ping();
        //    //p->Release();
        //    //p = NULL;

        //    ::_tprintf(_T("Done.\n"));
        //}
        //else
        //{
        //    ::_tprintf(_T("CreateInstance(): %s\n"), _com_error(hr).ErrorMessage());
        //}

        ::_getch();
    }

    ::CoUninitialize();

    return 0;
}
