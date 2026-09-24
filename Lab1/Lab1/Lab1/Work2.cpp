#include "Work2.h"
#include "Work3.h"
#include "framework.h"
#include "resource2.h"

static INT_PTR CALLBACK InnerWorkings(HWND hWorkWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDC_NEXT_WORK2:
            EndDialog(hWorkWnd, 0);
            Work3(GetParent(hWorkWnd));
            return (INT_PTR)TRUE;
        case IDCANCEL:
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


int Work2(HWND hWnd) {
    HINSTANCE instance = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hWnd, GWLP_HINSTANCE));

    return static_cast<int>(DialogBoxW(
        instance,
        MAKEINTRESOURCEW(IDD_WORK2_DIALOG),
        hWnd,
        InnerWorkings
    ));
}