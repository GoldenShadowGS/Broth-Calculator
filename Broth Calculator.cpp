// Broth Calculator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Broth Calculator.h"
#include <string>
#include <sstream>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


int MeatKilograms = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_BROTHCALCULATOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BROTHCALCULATOR));

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

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BROTHCALCULATOR));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BROTHCALCULATOR);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
HWND hWndLabel1 = nullptr;
HWND hWndLabel2 = nullptr;
HWND hWndLabel3 = nullptr;
HWND hWndEdit = nullptr;
HWND hWndEditResult = nullptr;
HWND hWndEditResult2 = nullptr;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	int windowWidth = 700;
	int windowHeight = 200;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hWndLabel1 = CreateWindowEx(0, L"static", L"Enter Kilograms of Ptarmigan Meat: ",
		WS_CHILD | WS_VISIBLE, 5, 10, 240,
		20, hWnd, NULL, NULL, NULL);

	hWndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"",
		WS_CHILD | WS_VISIBLE, 260, 10, 100,
		20, hWnd, (HMENU)IDM_EDITBOX, NULL, NULL);

	hWndLabel2 = CreateWindowEx(0, L"static", L"Calories per Broth: ",
		WS_CHILD | WS_VISIBLE, 5, 40, 130,
		20, hWnd, NULL, NULL, NULL);

	hWndLabel3 = CreateWindowEx(0, L"static", L"Total Calories: ",
		WS_CHILD | WS_VISIBLE, 5, 70, 130,
		20, hWnd, NULL, NULL, NULL);

	hWndEditResult = CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"",
		WS_CHILD | WS_VISIBLE, 140, 40, 500,
		20, hWnd, (HMENU)IDC_STATICBOX, NULL, NULL);

	hWndEditResult2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"Edit", L"",
		WS_CHILD | WS_VISIBLE, 140, 70, 500,
		20, hWnd, (HMENU)IDC_STATICBOX2, NULL, NULL);

	SendDlgItemMessage(hWnd, IDC_STATICBOX, EM_SETREADONLY, TRUE, 0);
	SendDlgItemMessage(hWnd, IDC_STATICBOX2, EM_SETREADONLY, TRUE, 0);

	//Create Button
	//HWND hwndButton = CreateWindowW(
	//	L"BUTTON",  // Predefined class; Unicode assumed 
	//	L"OK",      // Button text 
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
	//	10,         // x position 
	//	100,         // y position 
	//	120,        // Button width
	//	50,        // Button height
	//	hWnd,     // Parent window
	//	(HMENU)IDM_OKBUTTON,       // menu ID.
	//	(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
	//	NULL);      // Pointer not needed.
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

std::wstring FormatWithCommas(double value)
{
	std::wstringstream ss;
	ss.imbue(std::locale(""));
	ss.precision(2);
	ss << std::fixed << value;
	return ss.str();
}

//void swprintfcomma(WCHAR* buffer, int buffersize, double n)
//{
//	if (n < 1000)
//	{
//		swprintf(buf + buffersize, L"%d", n);
//		return;
//	}
//	swprintfcomma(buf, buffersize, n / 1000);
//	sprintf(buf + buffersize, buffersize, ",%03d", n % 1000);
//	return;
//}

//std::wstring formatNumberString(double n)
//{
//	WCHAR buffer[256] = {};
//	memset(buffer, 9, sizeof(buffer));
//	swprintfcomma(buffer, 0, n);
//	std::wstring result = buffer;
//	return result;
//}


double CalculateCalories()
{
	std::wstringstream ss;
	WCHAR windowtext[128] = {};
	GetWindowText(hWndEdit, windowtext, 128);
	ss << windowtext;
	ss >> MeatKilograms;
	double caloriesPerBroth = pow(1.25, MeatKilograms) * 170;
	return caloriesPerBroth;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
			//case IDM_OKBUTTON:
			//	CalculateCalories();
			//	InvalidateRect(hWnd, nullptr, false);
			//	break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_EDITBOX:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				double calories = CalculateCalories();
				//std::wstring caltext = std::to_wstring(calories);
				SetDlgItemText(hWnd, IDC_STATICBOX, FormatWithCommas(calories).c_str());
				SetDlgItemText(hWnd, IDC_STATICBOX2, FormatWithCommas(calories * 4 * MeatKilograms).c_str());
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//std::wstring textvalue = std::to_wstring(CalorieValue);
		//TextOutW(hdc, 5, 5, textvalue.c_str(), (int)textvalue.size());

		//WCHAR buffer[128] = {};
		//GetWindowTextW(hWndEdit, buffer, 128);
		//TextOutW(hdc, 5, 5, buffer, 128);

		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
