#ifndef RADIO_BUTTON_H_INCLUDED
#define RADIO_BUTTON_H_INCLUDED
#include <stdio.h>
#include <windows.h>
#include "resource.h"

//  �û���������ť ���� process_button
int process_button(HWND hwndDlg, WPARAM wParam);

static int rx = -1;
extern char buf[];

#endif // RADIO_BUTTON_H_INCLUDED

