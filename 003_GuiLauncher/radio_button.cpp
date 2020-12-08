#include "radio_button.h"

const char* hero[] = { "Null",  "Alpine Linux是一个由社区开发的基于musl和BusyBox的Linux操作系统，该操作系统以安全为理念，面向x86路由器、防火墙、虚拟专用网、IP电话盒及服务器而设计。",
                       "git 发行版 git-for-windows，git-for-windows 使用 MSYS2 的工具链，但是在基本设置上沿袭了 msysgit 的设置，版本比 msysgit 新。",
                       "Debian是完全由自由软件组成的类UNIX操作系统，其包含的多数软件使用GNU通用公共许可协议授权，并由Debian计划的参与者组成团队对其进行打包、开发与维护。",
                       "Arch Linux是一款基于x86-64 架构的Linux发行版 。系统主要由自由和开源软件组成，支持社区参与。"
                       "系统设计以KISS原则为总体指导原则，注重代码正确、优雅和极简主义，期待用户愿意去理解系统的运作。Arch Linux 采用pacman作为默认的软件包管理器。",
                       "VirtualBox 是针对基于 x86 的系统的强大的跨平台虚拟化软件。 “跨平台”意味着它可以安装在 Windows、Linux、Mac OS X 和 Solaris x86 计算机上。"
                       "而“虚拟化软件”则意味着可以在同一台计算机上同时创建和运行多个虚拟机，并且这些虚拟机可以运行不同的操作系统。"
                     };

//  用户收音机按钮 函数 process_button
int process_button(HWND hwndDlg, WPARAM wParam)
{
    rx = LOWORD(wParam) - RX_01 + 1;
    SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG), hero[rx]);
    return rx ;
}
