#include "start_GuiLauncher.h"
#include <stdio.h>

int hide_run_cmd(char *cmdline) {
  SetConsoleTitle(cmdline);
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);

  // 后台隐藏
  si.dwFlags = STARTF_USESHOWWINDOW;
  si.wShowWindow = SW_HIDE;

  if (debug_flg) {
    si.wShowWindow = SW_SHOW;
  }

  ZeroMemory(&pi, sizeof(pi));
  // Start the child process.
  CreateProcess(NULL, TEXT(cmdline), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
  // Wait until child process exits.
  WaitForSingleObject(pi.hProcess, INFINITE);
  // Get the return value of the child process
  DWORD ret;
  GetExitCodeProcess(pi.hProcess, &ret);
  //    if (!ret) {
  //        // .....
  //    }
  // Close process and thread handles.
  //    CloseHandle(pi.hProcess);
  //    CloseHandle(pi.hThread);
  return ret;
}

// 路径转宽字节
wchar_t *charToWCHAR(wchar_t *wch, const char *czs) {
  MultiByteToWideChar(CP_ACP, 0, czs, -1, wch, MAX_PATH); // czs 转换到宽字节wch
  return wch;
}
char *WCHARTochar(char *czs, const wchar_t *wch) {
  WideCharToMultiByte(CP_ACP, 0, wch, -1, czs, MAX_PATH, NULL, NULL);
  return czs;
}
