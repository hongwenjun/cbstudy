﻿#include "radio_button.h"
#include "start_GuiLauncher.h"
#include <mmsystem.h>


bool is_webp_format(const char *filename);

const char *hero[] = {
    "Null",
    "使用realesr-animevideov3-x2模型，极速对显卡没要求",
    "使用realesrgan-x4plus模型放大漫画,矢量LOGO标志效果好很多",
    "真实世界超分辨率模型DF2K, 提升分辨率在视觉上更加清晰和细腻",
    "手机拍照的文字稿件会有影子，图片一键漂白，方便打印或OCR",
    "把选择的图片转Webp格式，如果已经是Webp，则图片转换PNG"};

//  用户收音机按钮 函数 process_button
int process_button(HWND hwndDlg, WPARAM wParam) {
  rx = LOWORD(wParam) - RX_01 + 1;
  SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG), "");

  char hzzq[] = "C:\\app\\hzzq\\realesrgan-ncnn-vulkan.exe";
  char cmdline[MAX_PATH] = {0};
  char output[MAX_PATH] = {0};
  strcpy(output, buf);

  switch (rx) {
  case 1:
    strcat(output, "_2X.png -s 2");
    sprintf(cmdline, "%s -i %s -o %s", hzzq, buf, output);
    // hide_run_cmd(cmdline);
    ExecuteCommand(hwndDlg, cmdline);
    PlaySound(TEXT("SystemWelcome"), NULL, SND_ALIAS);
    break;

  case 2:
    SetWindowText(::GetDlgItem(hwndDlg, GET_FILE), "。。。画质增强运行中。。。");
    strcat(output, "_4x.png  -m models -n realesrgan-x4plus");
    sprintf(cmdline, "%s -i %s -o %s", hzzq, buf, output);
    ExecuteCommand(hwndDlg, cmdline);
    SetWindowText(::GetDlgItem(hwndDlg, GET_FILE), "^_^ 画质增强完成 ^_^");
    PlaySound(TEXT("SystemWelcome"), NULL, SND_ALIAS);
    break;

  case 3:
    SetWindowText(::GetDlgItem(hwndDlg, GET_FILE), "。。。画质增强运行中。。。");
    strcat(output, "_DF2K.png  -s 4 -m models-DF2K_JPEG -n x4");
    sprintf(cmdline, "%s -i %s -o %s", hzzq, buf, output);
    ExecuteCommand(hwndDlg, cmdline);
    SetWindowText(::GetDlgItem(hwndDlg, GET_FILE), "^_^ 画质增强完成 ^_^");
    PlaySound(TEXT("SystemWelcome"), NULL, SND_ALIAS);
    break;

  case 4: {
    strcpy(hzzq, "C:\\app\\hzzq\\LiApp.exe");
    sprintf(cmdline, "%s  %s", hzzq, buf);
    debug_flg = true;
    ExecuteCommand(hwndDlg, cmdline);
  } break;

  case 5: {
    strcpy(hzzq, "ffmpeg.exe");
    if (is_webp_format(buf)) {
      strcat(output, "_to.png");
    } else {
      strcat(output, "_new.webp");
    }
    sprintf(cmdline, "%s  -i %s %s -y", hzzq, buf, output);
    ExecuteCommand(hwndDlg, cmdline);
  } break;
  }

  SendMessage(::GetDlgItem(hwndDlg, EDIT_LOG),  EM_REPLACESEL, TRUE, (LPARAM)hero[rx]);

  return rx;
}

bool is_webp_format(const char *filename) {
  size_t len = strlen(filename);
  if (len < 5)
    return false;
  return strcmp(filename + len - 5, ".webp") == 0;
}