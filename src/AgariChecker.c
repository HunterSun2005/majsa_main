#include "AgariChecker.h"

extern char Pair[4];
extern Group HandGroupTile[6];

bool isAgari(Status *status) {
    Hand Hands = Statistics(status);  //统计牌数
    Hand temp;

    if (CheckKokushimusou(Hands)) {
        return true;
    }

    if (CheckChiitoitsu(Hands)) {
        return true;
    }

    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Hands.matrix[i][j] >= 2) {
                temp = Hands;
                temp.matrix[i][j] -= 2; //雀头
                Pair[0] = (char) (j + 48);  //记录雀头
                switch (i) {
                    case 0:
                        temp.m_num -= 2;
                        Pair[1] = 'm';
                        break;
                    case 1:
                        temp.p_num -= 2;
                        Pair[1] = 'p';
                        break;
                    case 2:
                        temp.s_num -= 2;
                        Pair[1] = 's';
                        break;
                    case 3:
                        temp.z_num -= 2;
                        Pair[1] = 'z';
                        break;
                    default:;
                }
                if (SeparateTile(temp, status, 0) == 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool SeparateTile(Hand Hands, Status *status, int count) {
    count++;
    Hand temp;
    if (Hands.m_num + Hands.p_num + Hands.s_num + Hands.z_num == 0) {
        return true;
    } else {
        for (int a = 0; a <= 3; a++) {
            for (int b = 1; b <= 9; b++) {
                if (Hands.matrix[a][b] >= 3) {
                    temp = Hands;
                    HandGroupTile[count - 1].type = Koutsu;
                    HandGroupTile[count - 1].tile[0] = (char) (b + 48);
                    temp.matrix[a][b] -= 3;
                    switch (a) {
                        case 0:
                            temp.m_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 'm';
                            break;
                        case 1:
                            temp.p_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 'p';
                            break;
                        case 2:
                            temp.s_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 's';
                            break;
                        case 3:
                            temp.z_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 'z';
                            break;
                        default:;
                    }  //记录牌数

                    if (SeparateTile(temp, status, count) == 1) {
                        return true;
                    }  //判断剩下的牌
                }
            }
        }   //刻子

        for (int a = 0; a <= 2; a++) {
            for (int b = 1; b <= 7; b++) {
                if (Hands.matrix[a][b] >= 1 && Hands.matrix[a][b + 1] >= 1 && Hands.matrix[a][b + 2] >= 1) {
                    temp = Hands;
                    temp.matrix[a][b]--;
                    temp.matrix[a][b + 1]--;
                    temp.matrix[a][b + 2]--;
                    HandGroupTile[count - 1].type = Shuntsu;
                    HandGroupTile[count - 1].tile[0] = (char) (b + 48);
                    switch (a) {
                        case 0:
                            temp.m_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 'm';
                            break;
                        case 1:
                            temp.p_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 'p';
                            break;
                        case 2:
                            temp.s_num -= 3;
                            HandGroupTile[count - 1].tile[1] = 's';
                            break;
                        default:;
                    }  //记录牌数
                    if (SeparateTile(temp, status, count) == 1) {
                        return true;
                    }  //判断剩下的牌
                }
            }
        }   //顺子

        return false;
    }
}

Hand Statistics(Status *status) {
    Hand Hands = {
            .matrix = {0},
            .m_num = 0,
            .p_num = 0,
            .s_num = 0,
            .z_num = 0,
    };

    switch (status->currentTile[1]) {
        case 'm':
            Hands.matrix[0][status->currentTile[0] - 48]++;
            Hands.m_num++;
            break;
        case 'p':
            Hands.matrix[1][status->currentTile[0] - 48]++;
            Hands.p_num++;
            break;
        case 's':
            Hands.matrix[2][status->currentTile[0] - 48]++;
            Hands.s_num++;
            break;
        case 'z':
            Hands.matrix[3][status->currentTile[0] - 48]++;
            Hands.z_num++;
            break;
        default:;
    }

    for (int i = 0; i < 15 && status->handTile[2 * i] != '\0'; i++) {
        switch (status->handTile[2 * i + 1]) {
            case 'm':
                Hands.matrix[0][status->handTile[2 * i] - 48]++;
                Hands.m_num++;
                break;
            case 'p':
                Hands.matrix[1][status->handTile[2 * i] - 48]++;
                Hands.p_num++;
                break;
            case 's':
                Hands.matrix[2][status->handTile[2 * i] - 48]++;
                Hands.s_num++;
                break;
            case 'z':
                Hands.matrix[3][status->handTile[2 * i] - 48]++;
                Hands.z_num++;
                break;
            default:;
        }
    }

    for (int i = 0; i <= 2; i++) {
        Hands.matrix[i][5] += Hands.matrix[i][0];
    }  //转换赤宝牌

    return Hands;
}

bool CheckKokushimusou(Hand Hands) {
    if (Hands.matrix[0][1] >= 1 && Hands.matrix[0][9] >= 1 && Hands.matrix[1][1] >= 1 && Hands.matrix[1][9] >= 1 &&
        Hands.matrix[2][1] >= 1 && Hands.matrix[2][9] >= 1 && Hands.matrix[3][1] >= 1 && Hands.matrix[3][2] >= 1 &&
        Hands.matrix[3][3] >= 1 && Hands.matrix[3][4] >= 1 && Hands.matrix[3][5] >= 1 && Hands.matrix[3][6] >= 1 &&
        Hands.matrix[3][7] >= 1) {
        return true;
    } else return false;
}

bool CheckChiitoitsu(Hand Hands) {
    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Hands.matrix[i][j] != 0 && Hands.matrix[i][j] != 2) {
                return false;
            }
        }
    }
    return true;
}
