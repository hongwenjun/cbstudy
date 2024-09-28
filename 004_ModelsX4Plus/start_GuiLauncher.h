#ifndef START_GUILAUNCHER_H_INCLUDED
#define START_GUILAUNCHER_H_INCLUDED

#include <windows.h>

extern bool debug_flg;

// *************  按钮选择对应程序 ************** //

void start_GuiLauncher(int app_id);
void stop_VM_Headless(void);

int hide_run_cmd(char *cmdline);
wchar_t *charToWCHAR(wchar_t *wch, const char *czs);
char *WCHARTochar(char *czs, const wchar_t *wch);

#endif // START_GUILAUNCHER_H_INCLUDED
