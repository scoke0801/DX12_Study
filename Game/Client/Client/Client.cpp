// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"
#include "Game.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

Game* g_game;

WindowInfo g_WindowInfo;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) { break;  }

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        g_game->PreUpdate();
    }


    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;// MAKEINTRESOURCEW(IDC_GSCLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
  
   // 생성할 윈도우의 형식을 지정해줍니다.
   DWORD dwStyle =
       WS_OVERLAPPED	    //디폴트 윈도우.타이틀 바와 크기 조절이 안되는 경계선을 갖는 윈도우를 만듭니다.
       | WS_SYSMENU	        //시스템 메뉴를 가진 윈도우를 만듭니다.
       | WS_MINIMIZEBOX     //최소화 버튼을 갖는 윈도우를 만듭니다.
       | WS_CAPTION;	    //타이틀 바를 가진 윈도우를 만들며 WS_BORDER 스타일을 포함합니다.

   RECT rtClient, rtDesktop; 

   // 윈도우가 생성될 위치를 화면의 중간이 되도록 합니다.
   GetWindowRect(GetDesktopWindow(), &rtDesktop); // 화면의 크기를 얻어옴

   // 클라이언트의 크기를 설정합니다.
   rtClient.left = rtClient.top = 0;
   rtClient.right = static_cast<LONG>(CLIENT_WIDTH);
   rtClient.bottom = static_cast<LONG>(CLIENT_HEIGHT);

   // 윈도우 사이즈에서 추가되는 크기들 (캡션, 외각선 등)을 보정합니다.
   AdjustWindowRect(&rtClient, dwStyle, FALSE);

   //클라이언트가 생성될 좌표가 데스크톱의 중앙이 되도록 지정합니다.
   POINT ptClientPos;

   ptClientPos.x = static_cast<LONG>( (rtDesktop.right - rtClient.right) * 0.5f );
   ptClientPos.y = static_cast<LONG>( (rtDesktop.bottom - rtClient.bottom) * 0.5f );

   LONG width = rtClient.right - rtClient.left;
   LONG height = rtClient.bottom - rtClient.top;

   HWND hWnd = CreateWindowW(
       szWindowClass,		//윈도우 클래스 명
       szTitle,			    //타이틀에 입력될 문자열
       dwStyle,			    //윈도우 스타일
       ptClientPos.x,		//응용 프로그램이 시작될 x좌표
       ptClientPos.y,		//응용 프로그램이 시작될 y좌표
       width,               //응용 프로그램의 가로 길이
       height,              //응용 프로그램의 세로 길이 
       nullptr,			    //부모 윈도우
       nullptr,			    //메뉴 핸들
       hInstance,			//인스턴스 핸들 
       nullptr				//추가 파라메터
   );

   // 윈도우가 정상적으로 생성되지 않았다면 프로그램을 종료하도록 합니다.
   if (!hWnd)
   {
       return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   g_WindowInfo.hwnd = hWnd;
   g_WindowInfo.width = width;
   g_WindowInfo.height = height;
   g_WindowInfo.windowed = true;

   g_game = new Game();
   g_game->Init(g_WindowInfo);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    { 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
