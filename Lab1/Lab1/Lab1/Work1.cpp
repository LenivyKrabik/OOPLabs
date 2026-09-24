#include "framework.h"
#include "Work1.h"
#include "resource1.h"

static INT_PTR CALLBACK InnerWorkings(HWND hWorkWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SCROLLINFO si = { sizeof(SCROLLINFO) };
        si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        si.nMin = 0;
        si.nMax = 109;
        si.nPage = 10;
        si.nPos = 0;

        SetScrollInfo(hWorkWnd, SB_HORZ, &si, TRUE);

        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDOK:
        {
            SCROLLINFO si = { sizeof(SCROLLINFO) };
            si.fMask = SIF_POS;
            GetScrollInfo(hWorkWnd, SB_HORZ, &si);

            EndDialog(hWorkWnd, si.nPos);
            return (INT_PTR)TRUE;
        }
        case IDCANCEL:
            EndDialog(hWorkWnd, -1);
            return (INT_PTR)TRUE;
        default:
            return FALSE;
        }
        break;
    }
    case WM_HSCROLL:
    {
        SCROLLINFO si = { sizeof(SCROLLINFO) };
        si.fMask = SIF_ALL;
        GetScrollInfo(hWorkWnd, SB_HORZ, &si);

        int oldPos = si.nPos;
        int action = LOWORD(wParam);

        switch (action)
        {
        case SB_LINELEFT:       si.nPos -= 1;               break;
        case SB_LINERIGHT:      si.nPos += 1;               break;
        case SB_PAGELEFT:       si.nPos -= si.nPage;        break;
        case SB_PAGERIGHT:      si.nPos += si.nPage;        break;
        case SB_THUMBTRACK:     si.nPos = si.nTrackPos;     break;
        }

        if (si.nPos < si.nMin) si.nPos = si.nMin;
        if (si.nPos > si.nMax) si.nPos = si.nMax;

        if (si.nPos != oldPos)
        {
            si.fMask = SIF_POS;
            SetScrollInfo(hWorkWnd, SB_HORZ, &si, TRUE);
        }
        return (INT_PTR)TRUE;
    }
    case WM_DESTROY:
        EndDialog(hWorkWnd, 1);
        break;
    default:
        return FALSE;
    }
    return 0;
}

int Work1(HWND hWnd) {
    HINSTANCE instance = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hWnd, GWLP_HINSTANCE));

    return static_cast<int>(DialogBoxW(
        instance,
        MAKEINTRESOURCEW(IDD_DIALOGBAR),
        hWnd,
        InnerWorkings
    ));
}