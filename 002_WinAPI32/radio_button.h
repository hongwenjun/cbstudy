#ifndef RADIO_BUTTON_H_INCLUDED
#define RADIO_BUTTON_H_INCLUDED
#include <stdio.h>
#include <windows.h>
#include "resource.h"

//  用户收音机按钮 函数 process_button
int process_button(HWND hwndDlg, WPARAM wParam);

static int rx = -1;

#endif // RADIO_BUTTON_H_INCLUDED

