#include "resource3.h"
#include "Work3.h"
#include "framework.h"

static INT_PTR CALLBACK InnerWorkings(HWND hWorkWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDC_PREVIOUS_WORK3:
            EndDialog(hWorkWnd, 1);
            return (INT_PTR)TRUE;
        case IDCANCEL:
            EndDialog(hWorkWnd, 0);
            return (INT_PTR)TRUE;
        case IDOK:
            EndDialog(hWorkWnd, 0);
            return (INT_PTR)TRUE;
        default:
            return FALSE;
        }
        break;
    }
    case WM_DESTROY:
        EndDialog(hWorkWnd, 1);
        break;
    default:
        return FALSE;
    }
    return 0;
}

int Work3(HWND hWnd) {
    HINSTANCE instance = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hWnd, GWLP_HINSTANCE));

    return static_cast<int>(DialogBoxW(
        instance,
        MAKEINTRESOURCEW(IDD_WORK3_DIALOG),
        hWnd,
        InnerWorkings
    ));
}