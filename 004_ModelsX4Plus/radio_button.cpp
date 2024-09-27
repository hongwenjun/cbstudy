#include "radio_button.h"
#include "start_GuiLauncher.h"

const char *hero[] = {
    "Null",
    "使用realesr-animevideov3-x2模型，极速对显卡没要求",
    "使用realesrgan-x4plus模型放大漫画,矢量LOGO标志效果好很多",
    "真实世界超分辨率模型DF2K, 提升图像的分辨率，使其在视觉上更加清晰和细腻",
    "手机拍照的文字稿件会有影子，图片一键漂白，方便打印或OCR",
    "把当前选择的图片文件转Webp格式，文件很小方便网络传输"};

//  用户收音机按钮 函数 process_button
int process_button(HWND hwndDlg, WPARAM wParam) {
  rx = LOWORD(wParam) - RX_01 + 1;
  SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG), hero[rx]);

  char hzzq[] = "C:\\app\\hzzq\\realesrgan-ncnn-vulkan.exe";
  char cmdline[MAX_PATH] = {0};
  char output[MAX_PATH] = {0};
  strcpy(output, buf);

  switch (rx) {
  case 1:
    strcat(output, "_2X.png");
    sprintf(cmdline, "%s -i %s -o %s", hzzq, buf, output);
    hide_run_cmd(cmdline);
    break;

  case 2:
    strcat(output, "_4x.png  -m models -n realesrgan-x4plus");
    sprintf(cmdline, "%s -i %s -o %s", hzzq, buf, output);
    hide_run_cmd(cmdline);
    break;

  case 3:
    strcat(output, "_DF2K.png  -s 4 -m models-DF2K_JPEG -n x4");
    sprintf(cmdline, "%s -i %s -o %s", hzzq, buf, output);
    hide_run_cmd(cmdline);
    break;
  }

  return rx;
}
