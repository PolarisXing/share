#include <windows.h>
#include <shlobj.h>
#include <winuser.h>
// #include <commdlg.h> // 用于打开文件对话框

typedef enum
{
    BUTTON_DIR = 0x1000,
    BUTTON_FILE,
    CHECKBOX_GS,
    CHECKBOX_NX,
    CHECKBOX_DB,
    CHECKBOX_SafeSEH,
} menu_t;

// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static HWND hEdit1, hEdit2, hGroupBox; // 用于保存文本框和组框句柄

  switch (uMsg) {
  case WM_CREATE: {
    // 创建文本框
    hEdit1 = CreateWindowEx(
        0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 50,
        50, 300, 25, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
    hEdit2 = CreateWindowEx(
        0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 50,
        100, 300, 25, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 创建按钮
    CreateWindow(L"BUTTON", L"选择目录",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 400, 50,
                 100, 30, hwnd, (HMENU)BUTTON_DIR,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    CreateWindow(L"BUTTON", L"选择文件",
                 WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 400,
                 100, 100, 30, hwnd, (HMENU)BUTTON_FILE,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 创建组合框
    hGroupBox = CreateWindowEx(
        0, L"BUTTON", L"复选框组合", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 50,
        150, 300, 200, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 创建复选框1
    CreateWindow(L"BUTTON", L"复选框1",
                 WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_GROUP, 90, 30, 120,
                 30, hGroupBox, (HMENU)CHECKBOX_GS,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 创建复选框2
    CreateWindow(L"BUTTON", L"复选框2", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 90,
                 70, 120, 30, hGroupBox, (HMENU)CHECKBOX_NX,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 创建复选框3
    CreateWindow(L"BUTTON", L"复选框3", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 90,
                 110, 120, 30, hGroupBox, (HMENU)CHECKBOX_DB,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 创建复选框4
    CreateWindow(L"BUTTON", L"复选框4", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 90,
                 150, 120, 30, hGroupBox, (HMENU)CHECKBOX_SafeSEH,
                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);

    // 设置所有复选框为选中状态且不可修改
    CheckDlgButton(hGroupBox, CHECKBOX_GS, BST_CHECKED); // 复选框1
    CheckDlgButton(hGroupBox, CHECKBOX_NX, BST_CHECKED); // 复选框2
    CheckDlgButton(hGroupBox, CHECKBOX_DB, BST_CHECKED); // 复选框3
    CheckDlgButton(hGroupBox, CHECKBOX_SafeSEH, BST_CHECKED); // 复选框4

    EnableWindow(GetDlgItem(hGroupBox, CHECKBOX_GS), FALSE);     // 禁用复选框1
    EnableWindow(GetDlgItem(hGroupBox, CHECKBOX_NX), FALSE);     // 禁用复选框2
    EnableWindow(GetDlgItem(hGroupBox, CHECKBOX_DB), FALSE);     // 禁用复选框3
    EnableWindow(GetDlgItem(hGroupBox, CHECKBOX_SafeSEH), FALSE); // 禁用复选框4
    }
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == BUTTON_DIR)
        { // 如果点击了按钮
            // 打开目录选择对话框
            BROWSEINFO bi = {0};
            bi.lpszTitle = L"请选择一个目录";

            // 目录选择对话框
            LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
            if (pidl != NULL)
            {
                // 获取目录路径
                TCHAR szPath[MAX_PATH];
                if (SHGetPathFromIDList(pidl, szPath))
                {
                    // 将路径显示到文本框
                    SetWindowText(hEdit1, szPath);
                }
                CoTaskMemFree(pidl);
            }
        }
        else if (LOWORD(wParam) == BUTTON_FILE)
        { // 如果点击了按钮
            // 打开文件选择对话框
            OPENFILENAME ofn;       // 文件选择对话框的结构体
            TCHAR szFile[MAX_PATH]; // 存放文件路径的缓冲区

            // 初始化 OPENFILENAME 结构体
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = L"所有 Excel 文件\0*.xlsx\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.lpstrTitle = L"选择一个文件";
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // 显示文件选择对话框
            if (GetOpenFileName(&ofn) == TRUE)
            {
                // 将选择的文件路径显示到文本框中
                SetWindowText(hEdit2, ofn.lpstrFile);
            }
        }
        return 0;
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      // All painting occurs here, between BeginPaint and EndPaint.

      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

      EndPaint(hwnd, &ps);
    }
      return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // 注册窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, L"Unicode 示例程序", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~ WS_THICKFRAME,
                               CW_USEDEFAULT, CW_USEDEFAULT, 550, 600, NULL, NULL, hInstance, NULL);

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
