#include "MatrixWindow.h"

HWND Obj2;

void MakeMatrixWindow(HWND hWnd, HWND _obj2) {
    HINSTANCE instance = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hWnd, GWLP_HINSTANCE));

    Obj2 = _obj2;

    DialogBoxW(
        instance,
        MAKEINTRESOURCEW(IDD_MATRIX_WINDOW),
        hWnd,
        MatrixWindowProc
    );
}

LRESULT CALLBACK MatrixWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // TODO: Start object2.exe and object3.exe
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDOK:
        {
            int n = std::stoi(GetEditText(hWnd, IDC_EDIT_N));
            int minVal = std::stoi(GetEditText(hWnd, IDC_EDIT_MIN));
            int maxVal = std::stoi(GetEditText(hWnd, IDC_EDIT_MAX));

            int data[] = { n,minVal,maxVal };
            
            COPYDATASTRUCT cds;
            cds.dwData = 67;
            cds.cbData = sizeof(data);
            cds.lpData = data;
            SendMessage(Obj2, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);

            EndDialog(hWnd, 1);
            return (INT_PTR)TRUE;
        }
        case IDCANCEL:
            EndDialog(hWnd, 1);
            return (INT_PTR)TRUE;
        default:
            return FALSE;
        }
        break;
    }
    case WM_DESTROY:
        EndDialog(hWnd, 1);
        break;
    default:
        return FALSE;
    }
    return 0;
}

std::wstring GetEditText(HWND hWnd, int ID) {
    HWND hEdit = GetDlgItem(hWnd, ID);
    int length = GetWindowTextLengthW(hEdit);

    if (length == 0) {
        return L"";
    }

    std::wstring text(length + 1, L'\0');
    int copied = GetWindowTextW(hEdit, &text[0], length + 1);
    text.resize(copied);
    return text;
}