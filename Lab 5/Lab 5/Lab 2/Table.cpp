#include "Table.h"

HWND hWnd;
HWND hList;
HWND hWndDlg;
int SelectedIndex = -1;

void MyTable::Add(std::string name, long xs1, long ys1, long xs2, long ys2) {
    ShapeInfo* shape = new ShapeInfo{ name, xs1, ys1, xs2, ys2 };
    Shapes[ShapeAmount++] = shape;
    if (hWndDlg) {
        PostMessage(hWndDlg, WM_COMMAND, ID_ADD_FIGURE, reinterpret_cast<LPARAM>(shape));
    }
}
ShapeInfo* MyTable::GetShapeAt(int i) {
    return Shapes[i];
}
int MyTable::GetShapeAmount() {
    return ShapeAmount;
}
void MyTable::PopShape(int i) {
    delete Shapes[i];
    for (int x = i; x < ShapeAmount-1;x++) {
        Shapes[x] = Shapes[x + 1];
    }
    ShapeAmount--;
}

void MyTable::Wipeout() {
    for (int x = 0; x < ShapeAmount; x++) {
        delete Shapes[x];
        if (hList) ListView_DeleteItem(hList, 0);
    }
    ShapeAmount = 0;
}


std::wstring StringToWString(const std::string& str) {
    if (str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}


void OpenTable(HWND hMainWnd)
{
    hWnd = hMainWnd;

    HINSTANCE hInst = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hWnd, GWLP_HINSTANCE));
    if (hWndDlg)
    {
        PostMessage(hWndDlg, WM_SYSCOMMAND, SC_CLOSE, 0);
        hWndDlg = nullptr;
        return;
    }
    hWndDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, TableProc);
    ShowWindow(hWndDlg, SW_SHOW);
}


INT_PTR CALLBACK TableProc(HWND hTableWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    MyTable& table = MyTable::getInstance();

    switch (message) {
    case WM_INITDIALOG: {
        setUpTable(hTableWnd);
        return TRUE;
    }
    case WM_COMMAND:
    {
        int wmid = LOWORD(wParam);
        switch (wmid) {
        case IDOK:
        case IDCANCEL:
            DestroyWindow(hTableWnd);
            return TRUE;
            break;
        case ID_ADD_FIGURE:
        {
            ShapeInfo* shape = reinterpret_cast<ShapeInfo*>(lParam);
            addShapeToTable(shape);
            //InvalidateRect(hTableWnd, nullptr, TRUE);
            break;
        }
        case ID_DELETE_SHAPE:
            if (SelectedIndex != -1) {
                table.PopShape(SelectedIndex);
                ListView_DeleteItem(hList, SelectedIndex);
                PostMessage(hWnd, WM_COMMAND, ID_DELETE_SHAPE, SelectedIndex);
            }
            break;
        }
        return TRUE;
    }
    case WM_NOTIFY: {
        LPNMHDR hdr = (LPNMHDR)lParam;

        if (hdr->idFrom == IDD_LIST && hdr->code == LVN_ITEMCHANGED) {
            NMLISTVIEW* pNMLV = (NMLISTVIEW*)lParam;

            //Check if really changed
            if ((pNMLV->uChanged & LVIF_STATE) &&
                (pNMLV->uNewState & LVIS_SELECTED) &&
                !(pNMLV->uOldState & LVIS_SELECTED))
            {
                if (SelectedIndex != -1) PostMessage(hWnd, WM_COMMAND, ID_DESELECT_SHAPE, SelectedIndex);
                SelectedIndex = pNMLV->iItem;
                PostMessage(hWnd, WM_COMMAND, ID_SELECT_SHAPE, SelectedIndex);
            }
        }
        break;
    }
    case WM_DESTROY:
        if (SelectedIndex != -1) PostMessage(hWnd, WM_COMMAND, ID_DESELECT_SHAPE, SelectedIndex);
        hWndDlg = nullptr;
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}



void setUpTable(HWND hTableWnd) {
    // Make sure to use MyTable::getInstance() (not Table.getInstance())
    MyTable& table = MyTable::getInstance();

    HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(
        GetWindowLongPtrW(hTableWnd, GWLP_HINSTANCE));

    hList = CreateWindowEx(
        0, WC_LISTVIEW, L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
        10, 10, 340, 210,
        hTableWnd, (HMENU)IDD_LIST, hInstance, NULL
    );

    ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // Setup
    LVCOLUMN lvc = { 0 };
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    lvc.iSubItem = 0;
    lvc.pszText = (LPWSTR)L"Shape";
    lvc.cx = 100;
    ListView_InsertColumn(hList, 0, &lvc);

    lvc.iSubItem = 1;
    lvc.pszText = (LPWSTR)L"x1";
    lvc.cx = 60;
    ListView_InsertColumn(hList, 1, &lvc);

    lvc.iSubItem = 2;
    lvc.pszText = (LPWSTR)L"y1";
    lvc.cx = 60;
    ListView_InsertColumn(hList, 2, &lvc);

    lvc.iSubItem = 3;
    lvc.pszText = (LPWSTR)L"x2";
    lvc.cx = 60;
    ListView_InsertColumn(hList, 3, &lvc);

    lvc.iSubItem = 4;
    lvc.pszText = (LPWSTR)L"y2";
    lvc.cx = 60 - (table.GetShapeAmount() >= 12 ? GetSystemMetrics(SM_CXVSCROLL) : 0);
    ListView_InsertColumn(hList, 4, &lvc);

    // Populate
    for (int i = 0; i < table.GetShapeAmount(); ++i) {
        ShapeInfo* ptr = table.GetShapeAt(i);
        if (!ptr) continue;

        std::wstring wName = StringToWString(ptr->name);

        LVITEM lvi = { 0 };
        lvi.mask = LVIF_TEXT;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.pszText = const_cast<wchar_t*>(wName.c_str());

        ListView_InsertItem(hList, &lvi);

        std::wstring xs1Str = std::to_wstring(ptr->xs1);
        ListView_SetItemText(hList, i, 1, const_cast<wchar_t*>(xs1Str.c_str()));

        std::wstring ys1Str = std::to_wstring(ptr->ys1);
        ListView_SetItemText(hList, i, 2, const_cast<wchar_t*>(ys1Str.c_str()));

        std::wstring xs2Str = std::to_wstring(ptr->xs2);
        ListView_SetItemText(hList, i, 3, const_cast<wchar_t*>(xs2Str.c_str()));

        std::wstring ys2Str = std::to_wstring(ptr->ys2);
        ListView_SetItemText(hList, i, 4, const_cast<wchar_t*>(ys2Str.c_str()));
    }
}

void addShapeToTable(ShapeInfo* shape) {
    // Convert string
    std::wstring wName = StringToWString(shape->name);

    int i = ListView_GetItemCount(hList);

    LVITEM lvi = { 0 };
    lvi.mask = LVIF_TEXT;
    lvi.iItem = i;
    lvi.iSubItem = 0;
    lvi.pszText = const_cast<wchar_t*>(wName.c_str());

    ListView_InsertItem(hList, &lvi);

    // Use itemIndex (not i) to populate subitems
    std::wstring xs1Str = std::to_wstring(shape->xs1);
    ListView_SetItemText(hList, i, 1, const_cast<wchar_t*>(xs1Str.c_str()));

    std::wstring ys1Str = std::to_wstring(shape->ys1);
    ListView_SetItemText(hList, i, 2, const_cast<wchar_t*>(ys1Str.c_str()));

    std::wstring xs2Str = std::to_wstring(shape->xs2);
    ListView_SetItemText(hList, i, 3, const_cast<wchar_t*>(xs2Str.c_str()));

    std::wstring ys2Str = std::to_wstring(shape->ys2);
    ListView_SetItemText(hList, i, 4, const_cast<wchar_t*>(ys2Str.c_str()));
}