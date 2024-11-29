#include <commctrl.h>
#include <stdio.h>
#include <windows.h>


#include "radio_button.h"
#include "resource.h"
#include "start_GuiLauncher.h"


HINSTANCE hInst;
HICON g_hIcon;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
    case WM_INITDIALOG: {
        // 大图标：按下alt+tab键切换窗口时对应的图标
        // 小图标：就是窗口左上角对应的那个图标
        ::SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)g_hIcon);
        ::SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)g_hIcon);
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

        //  用户按钮 命令
        case BT_OK: {
            if (rx != -1) {
                start_GuiLauncher(rx);
                EndDialog(hwndDlg, 0);

            } else {
                SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG),
                              ":: 蘭雅sRGB 龙芯2F服务器\thttps://262235.xyz \n"
                              "提供编程和电脑应用视频教程，工具和源代码 ,C, C++, Programming, Source Code, Video");
            }
        } break;

        case BT_CANCEL: {
            CheckRadioButton(hwndDlg, RX_01, RX_05, LOWORD(wParam));
            rx = -1;
            printf("点击取消\n");
            SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG), "取消选择英雄!");
        } break;

        case BT_QUIT: {
            stop_VM_Headless();
        } break;
        }
    }
        return TRUE;
    }

    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInst = hInstance;

    // 从资源中加载BMP文件和图标，这些工作也可以在WM_INITDIALOG消息中进行
    g_hIcon = ::LoadIcon(hInst, (LPCTSTR)IDI_ICON1);

    InitCommonControls();

    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
