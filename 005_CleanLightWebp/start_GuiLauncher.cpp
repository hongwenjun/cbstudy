#include "start_GuiLauncher.h"
#include "resource.h"
#include <stdio.h>

int hide_run_cmd(char *cmdline)
{
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
    CreateProcess(NULL, (LPSTR)cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
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
wchar_t *charToWCHAR(wchar_t *wch, const char *czs)
{
    MultiByteToWideChar(CP_ACP, 0, czs, -1, wch, MAX_PATH); // czs 转换到宽字节wch
    return wch;
}
char *WCHARTochar(char *czs, const wchar_t *wch)
{
    WideCharToMultiByte(CP_ACP, 0, wch, -1, czs, MAX_PATH, NULL, NULL);
    return czs;
}

void ExecuteCommand(HWND hwnd, const char *command)
{
    if (debug_flg) {
        hide_run_cmd((LPSTR)command);
        return;
    }

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    HANDLE hReadPipe, hWritePipe;
    CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.wShowWindow = SW_HIDE; // 隐藏命令行窗口

    if (CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(hWritePipe);

        char buffer[64];
        DWORD bytesRead;
        HWND hOutput = GetDlgItem(hwnd, EDIT_LOG);
        while (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';

            // 将输出逐行添加到文本框
            char *line = strtok(buffer, "\r\n");
            while (line != NULL) {
                SendMessage(hOutput, EM_REPLACESEL, TRUE, (LPARAM)line);
                SendMessage(hOutput, EM_REPLACESEL, TRUE, (LPARAM) "\r\n"); // 添加换行
                line = strtok(NULL, "\r\n");
            }
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        MessageBox(hwnd, "CreateProcess failed.", "Error", MB_OK | MB_ICONERROR);
    }

    CloseHandle(hReadPipe);
}
