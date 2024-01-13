#include "AgariChecker.h"

int CountSituation = 0;     //记录分组情况数

Possible *isAgari(Status *status) {
    Hand temp;
    Possible *Possibles = malloc(sizeof(Possible));
    memset(Possibles, 0, sizeof(*Possibles));

    Possibles->HandTiles = Statistics(status);     //统计手中牌数
    Possibles->AllTiles = StatisticsAll(status);   //统计所有牌数

    Possibles->HandGroupLen = ((int) strlen(status->handTile) / 2 - 1) / 3;

    if (CheckKokushimusou(Possibles->HandTiles)) {
        Possibles->Situations[CountSituation].Agari = true;
        return Possibles;
    }

    if (CheckChiitoitsu(status, Possibles->HandTiles, Possibles)) {
        Possibles->Situations[CountSituation].Agari = true;
        return Possibles;
    }

    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Possibles->HandTiles.matrix[i][j] >= 2) {
                temp = Possibles->HandTiles;
                temp.matrix[i][j] -= 2; //雀头
                Possibles->Situations[CountSituation].Jyantou[0] = (char) (j + 48);  //记录雀头
                switch (i) {
                    case 0:
                        temp.m_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 'm';
                        break;
                    case 1:
                        temp.p_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 'p';
                        break;
                    case 2:
                        temp.s_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 's';
                        break;
                    case 3:
                        temp.z_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 'z';
                        break;
                    default:;
                }

                SeparateTile(temp, status, 0, Possibles, 0, 1, 0, 1);
            }
        }
    }
    return Possibles;
}

void SeparateTile(Hand Hands, Status *status, int count, Possible *Possibles, int a1, int b1, int a2, int b2) {
    count++;
    Hand temp;
    if (count > 5) {
        return;
    } else if ((Hands.m_num + Hands.p_num + Hands.s_num + Hands.z_num) == 0) {
        memcpy(&(Possibles->Situations[CountSituation + 1]), &(Possibles->Situations[CountSituation]), \
        sizeof(Situation));
        Possibles->Situations[CountSituation].Agari = true;
        CountSituation++;
        return;
    } else {
        for (int a = a1; a <= 3; a++) {
            for (int b = b1; b <= 9; b++) {
                if (Hands.matrix[a][b] >= 3) {
                    temp = Hands;
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].type = Koutsu;
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[0] = (char) (b + 48);
                    temp.matrix[a][b] -= 3;
                    switch (a) {
                        case 0:
                            temp.m_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'm';
                            break;
                        case 1:
                            temp.p_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'p';
                            break;
                        case 2:
                            temp.s_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 's';
                            break;
                        case 3:
                            temp.z_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'z';
                            break;
                        default:;
                    }  //记录牌数

                    SeparateTile(temp, status, count, Possibles, a, b, a2, b2);  //判断剩下的牌
                }
            }
        }   //刻子

        for (int a = a2; a <= 2; a++) {
            for (int b = b2; b <= 7; b++) {
                if (Hands.matrix[a][b] >= 1 && Hands.matrix[a][b + 1] >= 1 && Hands.matrix[a][b + 2] >= 1) {
                    temp = Hands;
                    temp.matrix[a][b]--;
                    temp.matrix[a][b + 1]--;
                    temp.matrix[a][b + 2]--;
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].type = Shuntsu;
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[0] = (char) (b + 48);
                    switch (a) {
                        case 0:
                            temp.m_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'm';
                            break;
                        case 1:
                            temp.p_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'p';
                            break;
                        case 2:
                            temp.s_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 's';
                            break;
                        default:;
                    }  //记录牌数

                    SeparateTile(temp, status, count, Possibles, a1, b1, a, b);    //判断剩下的牌
                }
            }
        }   //顺子
    }
}

Hand Statistics(Status *status) {
    Hand Hands;
    memset(&Hands, 0, sizeof(Hands));

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

Hand StatisticsAll(Status *status) {
    int HandGroupLen = ((int) strlen(status->handTile) / 2 - 1) / 3;
    Hand Hands;
    memset(&Hands, 0, sizeof(Hands));

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
    }   //当前控牌

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
    }   //手牌

    for (int i = 0; i < 4 - HandGroupLen; i++) {
        for (int j = 0; j <= 3 && status->groupTile[i].tile[2 * j + 1] != 0; j++) {
            switch (status->groupTile[i].tile[2 * j + 1]) {
                case 'm':
                    Hands.matrix[0][status->groupTile[i].tile[2 * j] - 48]++;
                    Hands.m_num++;
                    break;
                case 'p':
                    Hands.matrix[1][status->groupTile[i].tile[2 * j] - 48]++;
                    Hands.p_num++;
                    break;
                case 's':
                    Hands.matrix[2][status->groupTile[i].tile[2 * j] - 48]++;
                    Hands.s_num++;
                    break;
                case 'z':
                    Hands.matrix[3][status->groupTile[i].tile[2 * j] - 48]++;
                    Hands.z_num++;
                    break;
                default:;
            }
        }
    }   //副露牌

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

bool CheckChiitoitsu(Status *status, Hand Hands, Possible *Possibles) {
    if (isMenzenchinn(status, Possibles)) {
        for (int i = 0; i <= 3; i++) {
            for (int j = 1; j <= 9; j++) {
                if (Hands.matrix[i][j] != 0 && Hands.matrix[i][j] != 2) {
                    return false;
                }
            }
        }
        return true;
    } else return false;
}

bool isMenzenchinn(Status *status, Possible *Possibles) {
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type != Ankan) {
            return false;
        }
    }
    return true;
}
