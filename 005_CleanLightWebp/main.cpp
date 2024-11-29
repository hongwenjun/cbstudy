#include <stdio.h>
#include <wchar.h>
#include <windows.h>

#include "radio_button.h"
#include "resource.h"
#include "start_GuiLauncher.h"
#include <commctrl.h>

HINSTANCE hInst;
HICON g_hIcon;
wchar_t wbuf[BUFSIZ];
char buf[BUFSIZ] = {0};
bool debug_flg = false; // 调试->高级模式

int GetImageFileName(HWND hWnd, char *szFile);
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg) {
    case WM_INITDIALOG: {
        // 大图标：按下alt+tab键切换窗口时对应的图标
        // 小图标：就是窗口左上角对应的那个图标
        ::SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)g_hIcon);
        ::SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)g_hIcon);

        SetWindowTextW(::GetDlgItem(hwndDlg, EDIT_LOG), wbuf);
    }
        return TRUE;

    case WM_CLOSE: {
        EndDialog(hwndDlg, 0);
    }
        return TRUE;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {

        //  用户收音机按钮处理
        case RX_01:
        case RX_02:
        case RX_03:
        case RX_04:
        case RX_05:
            rx = process_button(hwndDlg, wParam);
            break;

        case GET_FILE: {
            GetImageFileName(hwndDlg, buf);
            charToWCHAR(wbuf, buf);
            SetWindowTextW(::GetDlgItem(hwndDlg, EDIT_LOG), wbuf);
        } break;

        case DEBUG_FLG: {
            if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, DEBUG_FLG))
                debug_flg = true;
            else
                debug_flg = false;
        } break;
        }
    }
        return TRUE;
    }

    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

    // 获取命令行参数
    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    wcscpy(wbuf, argv[0]);
    if (2 == argc) {
        wcscpy(wbuf, argv[1]);
        WCHARTochar(buf, wbuf);
    }

    // 释放内存
    LocalFree(argv);

    hInst = hInstance;

    // 从资源中加载BMP文件和图标，这些工作也可以在WM_INITDIALOG消息中进行
    g_hIcon = ::LoadIcon(hInst, (LPCTSTR)IDI_ICON1);

    InitCommonControls();

    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}

// 选择一个图片文件
int GetImageFileName(HWND hWnd, char *szFile)
{
    OPENFILENAME ofn; // common dialog box structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 260; // 本来sizeof(szFile);
    ofn.lpstrFilter = "图片文件(*.png;*.jpg;*.jpeg;*.gif;*.bmp;*.tif;*.webp)\0"
                      "*.png;*.jpg;*.jpeg;*.gif;*.bmp;*.tif;*.webp\0"
                      "所有文件(*.*)\0"
                      "*.*\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    if (GetOpenFileName(&ofn)) {
        return lstrlen(szFile);
    }
    else {
        // 处理错误或用户取消的情况
        return 0; // 用户取消或发生错误
    }
}
