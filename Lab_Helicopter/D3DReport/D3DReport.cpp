// LabProject08-2.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "D3DReport.h"
#include "GameFramework.h"

#define MAX_LOADSTRING 100

HINSTANCE						ghAppInstance;
TCHAR							szTitle[MAX_LOADSTRING];
TCHAR							szWindowClass[MAX_LOADSTRING];

CGameFramework					gGameFramework;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	::LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	::LoadString(hInstance, IDC_D3DREPORT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow)) return(FALSE);

	hAccelTable = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DREPORT));

	while (1)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
		else
		{
			gGameFramework.FrameAdvance();
		}
	}
	gGameFramework.OnDestroy();

	return((int)msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DREPORT));
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_LABPROJECT082);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = ::LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return ::RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	ghAppInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	 // 생성할 윈도우의 형식을 지정해줍니다.
	DWORD dwStyle =
		WS_OVERLAPPED	  //디폴트 윈도우.타이틀 바와 크기 조절이 안되는 경계선을 갖는 윈도우를 만듭니다.
		| WS_SYSMENU	  //시스템 메뉴를 가진 윈도우를 만듭니다.
		| WS_MINIMIZEBOX  //최소화 버튼을 갖는 윈도우를 만듭니다.
		| WS_CAPTION	  //타이틀 바를 가진 윈도우를 만들며 WS_BORDER 스타일을 포함합니다.
	//  | WS_BORDER		  //단선으로 된 경계선(크기 조절 불가능)을 만듭니다
	//  | WS_CLIPCHILDREN //차일드가 위치한 영역은 그리지 않습니다.
	//  | WS_CLIPSIBLINGS //차일드끼리 상호 겹친 영역은 그리기 영역에서 제외
		;

	RECT rtClient, rtDesktop;

	// 윈도우가 생성될 위치를 화면의 중간이 되도록 합니다.
	GetWindowRect(GetDesktopWindow(), &rtDesktop); // 화면의 크기를 얻어옴

	// 클라이언트의 크기를 설정합니다.
	rtClient.left = rtClient.top = 0;
	rtClient.right = FRAME_BUFFER_WIDTH;
	rtClient.bottom = FRAME_BUFFER_HEIGHT;

	// 윈도우 사이즈에서 추가되는 크기들 (캡션, 외각선 등)을 보정합니다.
	AdjustWindowRect(&rtClient, dwStyle, FALSE);

	//클라이언트가 생성될 좌표가 데스크톱의 중앙이 되도록 지정합니다.
	POINT ptClientPos;

	ptClientPos.x = (rtDesktop.right - rtClient.right) * 0.5f;
	ptClientPos.y = (rtDesktop.bottom - rtClient.bottom) * 0.5f;

	HWND hWnd = CreateWindowW(
		szWindowClass,		//윈도우 클래스 명
		szTitle,			//타이틀에 입력될 문자열
		dwStyle,			//윈도우 스타일
		ptClientPos.x,		//응용 프로그램이 시작될 x좌표
		ptClientPos.y,		//응용 프로그램이 시작될 y좌표
		rtClient.right - rtClient.left,//응용 프로그램의 가로 길이
		rtClient.bottom - rtClient.top,//응용 프로그램의 세로 길이 
		nullptr,			//부모 윈도우
		nullptr,			//메뉴 핸들
		hInstance,			//인스턴스 핸들 
		nullptr				//추가 파라메터
	);
	if (!hWnd)
	{
		return FALSE;
	}

	gGameFramework.OnCreate(ghAppInstance, hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

#ifdef _WITH_SWAPCHAIN_FULLSCREEN_STATE
	gGameFramework.ChangeSwapChainState();
#endif

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_SIZE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_KEYDOWN:
	case WM_KEYUP:
		gGameFramework.OnProcessingWindowMessage(hWnd, message, wParam, lParam);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			::DialogBox(ghAppInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			::DestroyWindow(hWnd);
			break;
		default:
			return(::DefWindowProc(hWnd, message, wParam, lParam));
		}
		break;
	case WM_PAINT:
		hdc = ::BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return(::DefWindowProc(hWnd, message, wParam, lParam));
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return((INT_PTR)TRUE);
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			::EndDialog(hDlg, LOWORD(wParam));
			return((INT_PTR)TRUE);
		}
		break;
	}
	return((INT_PTR)FALSE);
}
