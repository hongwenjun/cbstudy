#include <stdio.h>
#include "start_GuiLauncher.h"

// ************** 启动程序函数 **************** //
void  chdir_VirtualBox()
{
    chdir("C:\\Program Files\\Oracle\\VirtualBox\\");
}

void start_debian_VM_Headless(void)
{
    chdir_VirtualBox();
    char cmdline[] = "VBoxManage.exe  startvm  debian --type headless ";
    WinExec(cmdline, SW_HIDE);
}

void start_Arch_VM_Headless(void)
{
    chdir_VirtualBox();
    char cmdline[] = "VBoxManage.exe  startvm  ArchLinux --type headless ";
    WinExec(cmdline, SW_HIDE);
}

void stop_VM_Headless(void)
{
    chdir_VirtualBox();
    char cmdline[] = "VBoxManage.exe  controlvm  debian acpipowerbutton ";
    WinExec(cmdline, SW_HIDE);

    char cmdline2[] = "VBoxManage.exe  controlvm  ArchLinux acpipowerbutton ";
    WinExec(cmdline2, SW_HIDE);
}

//  注意 C:\\CodeBlocks\\codeblocks.exe  路径中 \ 要用转移字符 \\ 双反斜杠
void start_CodeBlocks(void)
{
    char app_cmd[] = "C:\\CodeBlocks\\codeblocks.exe";
    ShellExecuteA(NULL, NULL, app_cmd, NULL, NULL, SW_SHOW);
}

void start_VirtualBox(void)
{
    char app_cmd[] = "C:\\Program Files\\Oracle\\VirtualBox\\VirtualBox.exe";
    ShellExecuteA(NULL, NULL, app_cmd, NULL, NULL, SW_SHOW);
}

void start_git_bash(void)
{
    char app_cmd[] = "C:\\soft\\Git\\git-bash.exe";
    ShellExecuteA(NULL, NULL, app_cmd, NULL, NULL, SW_SHOW);
}

// *************  按钮选择对应程序 ************** //

void start_GuiLauncher(int app_id)
{
    printf("app_id: %d\n", app_id);

    switch (app_id) {

    case 1: start_CodeBlocks();
        break;
    case 2: start_git_bash();
        break;
    case 3: start_debian_VM_Headless();
        break;
    case 4: start_Arch_VM_Headless();
        break;
    case 5: start_VirtualBox();
        break;
    }
}
