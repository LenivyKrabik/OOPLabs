#include "ToolbarHandler.h"

ToolbarHandler::ToolbarHandler(HWND hWnd, HINSTANCE hInst) {
    TBBUTTON tbb[4]; //масив опису кнопок вікнаToolbar
    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0; //стандартне зображення
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON; //тип елементу - кнопка
    tbb[0].idCommand = ID_POINT_BTN; //цей ID буде у повідомленніWM_COMMAND

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_LINE_BTN;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_RECTANGLE_BTN;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_ELIPS_BTN;

    hwndToolBar = CreateToolbarEx(hWnd, //батьківське вікно
        WS_CHILD | WS_VISIBLE | WS_BORDER
        | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        ID_TOOLBAR, //ID дочірнього вікна Toolbar
        4,
        hInst,
        IDB_TOOLBAR_ICONS,
        tbb,
        4, //кількість кнопок
        24, 24, 24, 24, //розташування та розміри Bitmap
        sizeof(TBBUTTON));
    OnSizeChange(hWnd);
}
void ToolbarHandler::OnSizeChange(HWND hWnd) {
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); //нові розміри головного вікна
        GetWindowRect(hwndToolBar, &rw); //потрібно знати висоту Toolbar
        MoveWindow(hwndToolBar, 0, 0,
            rc.right - rc.left, //ширина Toolbar як у головного вікна
            rw.bottom - rw.top, FALSE);
    }
}
void ToolbarHandler::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_POINT_BTN:
            lstrcpy(lpttt->szText, L"Крапка");
            break;
        case ID_LINE_BTN:
            lstrcpy(lpttt->szText, L"Лінія");
            break;
        case ID_RECTANGLE_BTN:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;
        case ID_ELIPS_BTN:
            lstrcpy(lpttt->szText, L"Еліпс");
            break;
        default: lstrcpy(lpttt->szText, L"Щось невідоме");
        }
    }
}