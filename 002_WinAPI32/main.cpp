#include "resource.h"
#include <commctrl.h>
#include <stdio.h>
#include <windows.h>


HINSTANCE hInst;
int rx = -1;

const char *hero[] = {
    "Null",
    "人类是奇幻角色扮演游戏《龙与地下城》中，玩家可扮演的一种种族。和其他种族相较之下，虽然人类的寿命较短。但也是所有龙"
    "与地下城的种族中，人口数量最多的。他们的多样性及雄心壮志使其颇有名声，虽然他们缺少其他种族的专精，但在许多领域仍能"
    "表现突出。人类的亚种包括神魔裔、神人，元素后裔与魔人，就和Vashar这个与卓尔精灵同意义的人类一样。",
    "人类是奇幻角色扮演游戏《龙与地下城》中，玩家可扮演的一种种族。和其他种族相较之下，虽然人类的寿命较短。但也是所有龙"
    "与地下城的种族中，人口数量最多的。他们的多样性及雄心壮志使其颇有名声，虽然他们缺少其他种族的专精，但在许多领域仍能"
    "表现突出。人类的亚种包括神魔裔、神人，元素后裔与魔人，就和Vashar这个与卓尔精灵同意义的人类一样。",
    "精灵经常出现在人类的居住地，虽然受到欢迎，但他们对此并不是很习惯。精灵以诗歌、舞蹈、说唱和魔法技巧而著称，崇尚自然"
    "单纯的美。但若森林家园受到威胁，精灵便会施展刀弓技巧和战略，显露武艺精湛的一面。",
    "矮人在奇幻文学题材中指的是最早出现在欧洲民间传奇的幻想矮小种族，自托尔金跟龙与地下城的创作延伸后，成为许多奇幻类型"
    "创作的题材人物。典型的奇幻矮人形象都是蓄长胡子且拿斧头，身材矮短而个性保守但善战的战士。 "
    "日尔曼民间传说中住在山间或矿井里的精灵，据说只有两岁孩子那样高，有时挺漂亮，但通常是拖着长胡子的驼背老头模样。",
    "亚瑟王英雄身份登场。他率领各部落在名为巴顿山之役的交战中一举击溃属于日耳曼民族一支的萨克森人，是中世纪英国著名的传"
    "奇人物。 "
    "但是亚瑟的形象却随着传说故事的演进而不断变化，最后演变成为统治不列颠之王，成为将兰斯洛特、崔斯坦等传说中骑士收于麾"
    "下的“圆桌骑士”首领，拥有至高荣誉的英雄"};

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
    case WM_INITDIALOG: {
    }
        return TRUE;

    case WM_CLOSE: {
        EndDialog(hwndDlg, 0);
    }
        return TRUE;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {

        //  用户收音机按钮
        case RX_01:
            rx = 1;
            break;
        case RX_02:
            rx = 2;
            break;
        case RX_03:
            rx = 3;
            break;
        case RX_04:
            rx = 4;
            break;
        case RX_05:
            rx = 5;
            break;

        //  用户按钮 命令
        case BT_OK: {
            if (rx != -1)
                printf("点击确认, 选择%d\n", rx);
            else
                printf("请选择英雄?\n", rx);

            SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG), hero[rx]);
        } break;
        case BT_CANCEL: {
            CheckRadioButton(hwndDlg, RX_01, RX_05, LOWORD(wParam));
            rx = -1;
            printf("点击取消\n");
            SetWindowText(::GetDlgItem(hwndDlg, EDIT_LOG), "取消选择英雄!");
        } break;
        case BT_QUIT: {
            printf("退出程序\n");
            EndDialog(hwndDlg, 0);
        } break;
        }
    }
        return TRUE;
    }

    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    hInst = hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
