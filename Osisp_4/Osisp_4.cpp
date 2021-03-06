// Osisp_4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Osisp_4.h"
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <vector>
#include <fstream>
#include "Sort.h"
using namespace std;

#define MAX_LOADSTRING 100
#define ID_LABEL_FILE 1001
#define ID_LABEL_IN   1002
#define ID_LABEL_REZ  1003
#define ID_LABEL_TH   1004
#define ID_BUTTON	  2001
#define ID_EDIT_FILE  3001
#define ID_EDIT_IN    3002
#define ID_EDIT_REZ   3003
#define ID_EDIT_TH   3004


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;
HWND hEdit4;
HWND hWndButton;
HWND TitleLabel1;
HWND TitleLabel2;
HWND TitleLabel3;
HWND TitleLabel4;



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT				onCreateWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT				onButton(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void	       stringToFile(char* filename, string string);
string	       readFileForEdit(char* name);
int			   Check(string s);
vector<string> reader;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OSISP4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OSISP4));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OSISP4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(230, 230, 250));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OSISP4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"Sort File Util", WS_OVERLAPPEDWINDOW,
	     810,600 ,810, 600,  nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		return onCreateWindow(hWnd, message, wParam, lParam);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUTTON:
			return onButton(hWnd, message, wParam, lParam);
			break;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam); //îñâîáîæäàåì î÷åðåäü ïðèëîæåíèÿ îò íåðàñïîçíàíûõ
}

	LRESULT onCreateWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		hWndButton = CreateWindow("button", "Sort", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			720, 30, 60, 20, hWnd, (HMENU)ID_BUTTON, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		UpdateWindow(hWndButton);


		hEdit1 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
			130, 30, 590, 20, hWnd, (HMENU)ID_EDIT_FILE, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

		hEdit2 = CreateWindow("Edit", NULL, WS_VSCROLL | WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE| ES_READONLY| ES_WANTRETURN,
			30, 120, 360, 150, hWnd, (HMENU)ID_EDIT_IN, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

		hEdit3 = CreateWindow("Edit", NULL, WS_VSCROLL | WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE| ES_READONLY| ES_WANTRETURN,
			420, 120, 360, 150, hWnd, (HMENU)ID_EDIT_REZ, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		
		hEdit4 = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL,
			130, 60, 40, 20, hWnd, (HMENU)ID_EDIT_TH, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);


		TitleLabel1 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "   File Name", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			30, 30, 100, 20, hWnd, (HMENU)ID_LABEL_FILE, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

		TitleLabel2 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Input File", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			30, 90, 80, 20, hWnd, (HMENU)ID_LABEL_IN, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);


		TitleLabel3 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC","Exit file", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			420, 90, 80, 20, hWnd, (HMENU)ID_LABEL_REZ, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

		TitleLabel4 = CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", "Thread count", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			30, 60, 100, 20, hWnd, (HMENU)ID_LABEL_TH, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);






		return 0;
	}


	LRESULT onButton(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		char name[500];
		char cipher_namename[500];
		char buff[200];
		string s, ex, th;
		int threadCount;
		

		GetWindowText(hEdit1, name, 500);
	
		GetWindowText(hEdit4, buff, 200);
		th = buff;
		threadCount = Check(th);
		if (threadCount != -1) {

			strcpy_s(cipher_namename, name);
			strcat_s(cipher_namename, "(sorted).txt");

			s = readFileForEdit(name);
			
			if (s != "0") {
				SetWindowText(hEdit2, s.c_str());
				//C:/Users/Ksusha/Source/Repos/Osisp_4/Osisp_4/test.txt
				stringToFile(cipher_namename, mainFunc(threadCount,reader));

				SetWindowText(hEdit3, readFileForEdit(cipher_namename).c_str());
			}
			else {
				MessageBox(NULL, "Invalid file input", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
			}
		}
		else {
			MessageBox(NULL, "Invalid thread input", " Try again", MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION | MB_DEFAULT_DESKTOP_ONLY);
		}
		return 0;
		
	}

	string readFileForEdit(char* name) {
		ifstream file(name);
		if (!file) {
			return "0";
		}
		else {
			string s = "";
			string ex = "";
			while (getline(file, ex)) {
				reader.push_back(ex);
				s = s + ex;
				s = s + "\r\n";
			}
			file.close();

			return s;
		}
	}

	void stringToFile(char* filename, string string) {
    	ofstream out(filename, ios_base::app);
		out << string;
		out.close();
	}

	int Check(string s) {
		int res = atoll(s.c_str());
		if (res > 0) {
			return res;
		}
		return -1;
	}