#include "Table.h"

int** matrix;

void setUpMatrix(HWND hWnd, HWND hMainWnd, int n, int minVal, int maxVal) {
    HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hWnd, GWLP_HINSTANCE));

    HWND hList = CreateWindowEx(
        0, WC_LISTVIEW, L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_NOCOLUMNHEADER,
        10, 10, min(cellWidth*n, cellWidth*10), min(cellHeight*n, cellHeight*10),
        hWnd, (HMENU)101, hInstance, NULL
    );

    ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    LVCOLUMN lvc = { 0 };
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    for (int i = 0; i < n; i++) {
        lvc.iSubItem = 0;
        lvc.pszText = (LPWSTR)L"";
        lvc.cx = cellWidth;
        ListView_InsertColumn(hList, i, &lvc);
    }

    matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    // Populate
    for (int i = 0; i < n; i++) {
        matrix[i][0] = randomNumber(minVal, maxVal);
        std::wstring value = std::to_wstring(matrix[i][0]);

        LVITEM lvi = { 0 };
        lvi.mask = LVIF_TEXT;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.pszText = const_cast<wchar_t*>(value.c_str());

        ListView_InsertItem(hList, &lvi);

        for (int j = 1; j < n; j++) {
            matrix[i][j] = randomNumber(minVal, maxVal);
            value = std::to_wstring(matrix[i][j]);
            ListView_SetItemText(hList, i, j, const_cast<wchar_t*>(value.c_str()));
        }
    }

    if (CopyMatrixToClipboard(hWnd, matrix, n) == 1) {
        PostMessage(hMainWnd, WM_COMMAND, 10002, n);
    }
}

int randomNumber(int minVal, int maxVal) {
    return static_cast<int>(round(((float)(rand()) / (float)(RAND_MAX)) * (maxVal - minVal) + minVal));
}

int CopyMatrixToClipboard(HWND hWnd, int** src, int n)
{
    UINT format = RegisterClipboardFormatA("Matrix");
    if (format == 0) return 0;

    size_t size = sizeof(int) * n * n;
    HGLOBAL hglbCopy = GlobalAlloc(GHND, size);
    if (hglbCopy == NULL) return 0;

    int* pTmp = (int*)GlobalLock(hglbCopy);
    if (pTmp == NULL) {
        GlobalFree(hglbCopy);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        memcpy(pTmp + (i * n), src[i], sizeof(int) * n);
    }

    GlobalUnlock(hglbCopy);

    if (!OpenClipboard(hWnd)) {
        GlobalFree(hglbCopy);
        return 0;
    }

    EmptyClipboard();
    if (SetClipboardData(format, hglbCopy) == NULL) {
        CloseClipboard();
        GlobalFree(hglbCopy);
        return 0;
    }

    CloseClipboard();
    return 1;
}