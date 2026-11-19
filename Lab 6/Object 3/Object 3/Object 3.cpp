// Object 3.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Object 3.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hMainWnd;
float determinant;
BOOL hasMatrix = FALSE;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
float               DeterminantCalculator(int** matrix, int size);
int**               TakeMatrixFromClipboard(HWND hWnd, int size);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    std::wstring ws(lpCmdLine);
    hMainWnd = (HWND)std::stoi(std::string(ws.begin(), ws.end()));

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OBJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBJECT3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBJECT3);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        SetWindowPos(hWnd, nullptr, 0, 0, 300, 300, SWP_NOMOVE | SWP_NOZORDER);
        PostMessage(hMainWnd, WM_COMMAND, 10001, (LPARAM)hWnd);
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_MATRIX_DONE:
            {
                int size = LOWORD(lParam);
                int** matrix = TakeMatrixFromClipboard(hWnd, size);
                if (matrix) {
                    determinant = DeterminantCalculator(matrix, size);
                    hasMatrix = TRUE;
                    InvalidateRect(hWnd, nullptr, TRUE);
                }
                break;
            }
            case ID_CHANGE_MAINW:
                hMainWnd = (HWND)lParam;
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
        std::wstring text;

        if (!hasMatrix) {
            text = L"No matrix yet";
        }
        else {
            text = L"Determinant: " + std::to_wstring(determinant);
        }

        const WCHAR* textPtr = text.c_str();

        TextOutW(hdc, 50, 50, textPtr, (int)wcslen(textPtr));

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

float DeterminantCalculator(int** matrix, int size) {
    if (size <= 0 || !matrix) return 0.0;

    std::vector<std::vector<double>> a(size, std::vector<double>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = static_cast<double>(matrix[i][j]);
        }
    }

    double det = 1.0;

    for (int i = 0; i < size; ++i) {
        int pivot = i;
        for (int r = i + 1; r < size; ++r) {
            if (std::abs(a[r][i]) > std::abs(a[pivot][i])) {
                pivot = r;
            }
        }

        if (std::abs(a[pivot][i]) < 1e-9) {
            return 0.0;
        }

        if (pivot != i) {
            std::swap(a[i], a[pivot]);
            det = -det;
        }

        det *= a[i][i];

        for (int r = i + 1; r < size; ++r) {
            double factor = a[r][i] / a[i][i];
            for (int c = i + 1; c < size; ++c) {
                a[r][c] -= factor * a[i][c];
            }
        }
    }

    return det;
}

int** TakeMatrixFromClipboard(HWND hWnd, int n)
{
    UINT format = RegisterClipboardFormatA("Matrix");
    if (format == 0) return 0;
    if (!IsClipboardFormatAvailable(format)) return 0;
    if (!OpenClipboard(hWnd)) return 0;

    int** matrix = NULL;
    HGLOBAL hglb = GetClipboardData(format);

    if (hglb != NULL) {
        int* pData = (int*)GlobalLock(hglb);
        if (pData != NULL) {
            matrix = new int* [n];
            for (int i = 0; i < n; i++) {
                matrix[i] = new int[n];
                memcpy(matrix[i], pData + (i * n), sizeof(int) * n);
            }
            GlobalUnlock(hglb);
        }
    }

    CloseClipboard();
    return matrix;
}