#include "AgariChecker.h"

int CountSituation = 0;     //记录分组情况数

Possible *isAgari(Status *status) {
    CountSituation = 0;
    Possible *Possibles = malloc(sizeof(Possible));
    memset(Possibles, 0, sizeof(*Possibles));

    Possibles->HandTiles = Statistics(status);     //统计手中牌数
    Possibles->AllTiles = StatisticsAll(status);   //统计所有牌数

    Possibles->HandGroupLen = ((int) strlen(status->handTile) / 2 - 1) / 3;

    if (CheckKokushimusou(Possibles->HandTiles)) {
        Possibles->Situations[0].Agari = true;
        return Possibles;
    }

    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Possibles->HandTiles.matrix[i][j] >= 2) {
                Possibles->HandTiles.matrix[i][j] -= 2; //雀头

                Possibles->Situations[CountSituation].Jyantou[0] = (char) (j + 48);  //记录雀头
                switch (i) {
                    case 0:
                        Possibles->HandTiles.m_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 'm';
                        SeparateTile(Possibles->HandTiles, status, 0, Possibles);
                        Possibles->HandTiles.m_num += 2;
                        break;
                    case 1:
                        Possibles->HandTiles.p_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 'p';
                        SeparateTile(Possibles->HandTiles, status, 0, Possibles);
                        Possibles->HandTiles.p_num += 2;
                        break;
                    case 2:
                        Possibles->HandTiles.s_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 's';
                        SeparateTile(Possibles->HandTiles, status, 0, Possibles);
                        Possibles->HandTiles.s_num += 2;
                        break;
                    case 3:
                        Possibles->HandTiles.z_num -= 2;
                        Possibles->Situations[CountSituation].Jyantou[1] = 'z';
                        SeparateTile(Possibles->HandTiles, status, 0, Possibles);
                        Possibles->HandTiles.z_num += 2;
                        break;
                    default:;
                }

                Possibles->HandTiles.matrix[i][j] += 2;
            }
        }
    }

    if (CheckChiitoitsu(status, Possibles->HandTiles)) {
        Possibles->Situations[0].Agari = true;
        return Possibles;
    }

    return Possibles;
}

Possible *isTenpai(Status *status, Hand HandTiles) {
    CountSituation = 0;
    Possible *Tenpai_Possibles = malloc(sizeof(Possible));
    memset(Tenpai_Possibles, 0, sizeof(*Tenpai_Possibles));

    Tenpai_Possibles->HandTiles = HandTiles;     //导入听牌牌数

    Tenpai_Possibles->HandGroupLen = ((int) strlen(status->handTile) / 2 - 1) / 3;

    if (CheckKokushimusou(Tenpai_Possibles->HandTiles)) {
        Tenpai_Possibles->Situations[0].Agari = true;
        return Tenpai_Possibles;
    }

    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Tenpai_Possibles->HandTiles.matrix[i][j] >= 2) {
                Tenpai_Possibles->HandTiles.matrix[i][j] -= 2; //雀头

                Tenpai_Possibles->Situations[CountSituation].Jyantou[0] = (char) (j + 48);  //记录雀头
                switch (i) {
                    case 0:
                        Tenpai_Possibles->HandTiles.m_num -= 2;
                        Tenpai_Possibles->Situations[CountSituation].Jyantou[1] = 'm';
                        SeparateTile(Tenpai_Possibles->HandTiles, status, 0, Tenpai_Possibles);
                        Tenpai_Possibles->HandTiles.m_num += 2;
                        break;
                    case 1:
                        Tenpai_Possibles->HandTiles.p_num -= 2;
                        Tenpai_Possibles->Situations[CountSituation].Jyantou[1] = 'p';
                        SeparateTile(Tenpai_Possibles->HandTiles, status, 0, Tenpai_Possibles);
                        Tenpai_Possibles->HandTiles.p_num += 2;
                        break;
                    case 2:
                        Tenpai_Possibles->HandTiles.s_num -= 2;
                        Tenpai_Possibles->Situations[CountSituation].Jyantou[1] = 's';
                        SeparateTile(Tenpai_Possibles->HandTiles, status, 0, Tenpai_Possibles);
                        Tenpai_Possibles->HandTiles.s_num += 2;
                        break;
                    case 3:
                        Tenpai_Possibles->HandTiles.z_num -= 2;
                        Tenpai_Possibles->Situations[CountSituation].Jyantou[1] = 'z';
                        SeparateTile(Tenpai_Possibles->HandTiles, status, 0, Tenpai_Possibles);
                        Tenpai_Possibles->HandTiles.z_num += 2;
                        break;
                    default:;
                }

                Tenpai_Possibles->HandTiles.matrix[i][j] += 2;
            }
        }
    }

    if (CheckChiitoitsu(status, Tenpai_Possibles->HandTiles)) {
        Tenpai_Possibles->Situations[0].Agari = true;
        return Tenpai_Possibles;
    }

    return Tenpai_Possibles;
}

void SeparateTile(Hand Hands, Status *status, int count, Possible *Possibles) {
    count++;
    if (CountSituation >= SIZEOFPOSSIBLE) {
        return;
    }
    if (count > 5) {
        return;
    } else if (count == Possibles->HandGroupLen + 1) {
        memcpy(&(Possibles->Situations[CountSituation + 1]), &(Possibles->Situations[CountSituation]), \
        sizeof(Situation));
        Possibles->Situations[CountSituation].Agari = true;
        CountSituation++;
        return;
    } else {
        for (int a = 0; a <= 3; a++) {
            for (int b = 1; b <= 9; b++) {
                if (Hands.matrix[a][b] >= 3) {
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].type = Koutsu;
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[0] = (char) (b + 48);
                    Hands.matrix[a][b] -= 3;

                    switch (a) {
                        case 0:
                            Hands.m_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'm';
                            SeparateTile(Hands, status, count, Possibles);  //判断剩下的牌
                            Hands.m_num += 3;
                            break;
                        case 1:
                            Hands.p_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'p';
                            SeparateTile(Hands, status, count, Possibles);  //判断剩下的牌
                            Hands.p_num += 3;
                            break;
                        case 2:
                            Hands.s_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 's';
                            SeparateTile(Hands, status, count, Possibles);  //判断剩下的牌
                            Hands.s_num += 3;
                            break;
                        case 3:
                            Hands.z_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'z';
                            SeparateTile(Hands, status, count, Possibles);  //判断剩下的牌
                            Hands.z_num += 3;
                            break;
                        default:;
                    }  //记录牌数

                    Hands.matrix[a][b] += 3;
                }
            }
        }   //刻子

        for (int a = 0; a <= 2; a++) {
            for (int b = 1; b <= 7; b++) {
                if (Hands.matrix[a][b] >= 1 && Hands.matrix[a][b + 1] >= 1 && Hands.matrix[a][b + 2] >= 1) {
                    Hands.matrix[a][b]--;
                    Hands.matrix[a][b + 1]--;
                    Hands.matrix[a][b + 2]--;

                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].type = Shuntsu;
                    Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[0] = (char) (b + 48);
                    switch (a) {
                        case 0:
                            Hands.m_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'm';
                            SeparateTile(Hands, status, count, Possibles);    //判断剩下的牌
                            Hands.m_num += 3;
                            break;
                        case 1:
                            Hands.p_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 'p';
                            SeparateTile(Hands, status, count, Possibles);    //判断剩下的牌
                            Hands.p_num += 3;
                            break;
                        case 2:
                            Hands.s_num -= 3;
                            Possibles->Situations[CountSituation].HandGroupTile[count - 1].tile[1] = 's';
                            SeparateTile(Hands, status, count, Possibles);    //判断剩下的牌
                            Hands.s_num += 3;
                            break;
                        default:;
                    }  //记录牌数

                    Hands.matrix[a][b]++;
                    Hands.matrix[a][b + 1]++;
                    Hands.matrix[a][b + 2]++;
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

bool CheckChiitoitsu(Status *status, Hand Hands) {
    if (strlen(status->handTile) == 26) {
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

int getDistance(Possible *Possibles) {
    int m;
    int d;
    int c;
    int q;
    int distance = 6;
    CountSituation = 0;

    countnumber counts = {};
    memset(&counts, 0, sizeof(countnumber));
    Possible_D *Possibles_D = malloc(sizeof(Possible_D));
    memset(Possibles_D, 0, sizeof(*Possibles_D));

    Possibles_D->HandTiles = Possibles->HandTiles;

    Separate(Possibles_D, counts);  //递归

    for (int i = 0; i < SIZEOFPOSSIBLE_D; i++) {
        if (Possibles_D->Situations_D[i].valid) {
            m = Possibles_D->Situations_D[i].Count.Shunzi + Possibles_D->Situations_D[i].Count.Kezi;
            d = Possibles_D->Situations_D[i].Count.Lianda + Possibles_D->Situations_D[i].Count.Tiaoda +
                Possibles_D->Situations_D[i].Count.Duizi;

            if (m + d <= 5) {
                c = 0;
            } else c = m + d - 5;

            if (m + d <= 4) {
                q = 1;
            } else if (Possibles_D->Situations_D[i].Count.Duizi >= 1) {
                q = 1;
            } else q = 0;

            Possibles_D->Situations_D[i].x = 9 - 2 * m - d + c - q;
        }
    }

    for (int i = 0; i < SIZEOFPOSSIBLE_D; i++) {
        if (Possibles_D->Situations_D[i].valid && Possibles_D->Situations_D[i].x < distance) {
            distance = Possibles_D->Situations_D[i].x;
        }
    }

    int qi_distance = Shanten_ChChiitoitsu(Possibles_D);

    int guo_distance = Shanten_Guo(Possibles_D);

    if (qi_distance < distance) distance = qi_distance;

    if (guo_distance < distance) distance = guo_distance;

    free(Possibles_D);
    return distance;
}

void Separate(Possible_D *Possibles_D, countnumber counts) {
    if (CountSituation >= SIZEOFPOSSIBLE_D) {
        return;
    }
    if (Stop(Possibles_D)) {
        memcpy(&(Possibles_D->Situations_D[CountSituation].Count), &counts, sizeof(countnumber));
        Possibles_D->Situations_D[CountSituation].valid = true;
        CountSituation++;
        return;
    }

    for (int a = 0; a <= 2; a++) {
        for (int b = 1; b <= 8; b++) {
            if (Possibles_D->HandTiles.matrix[a][b] >= 1 && Possibles_D->HandTiles.matrix[a][b + 1] >= 1) {
                Possibles_D->HandTiles.matrix[a][b] -= 1;
                Possibles_D->HandTiles.matrix[a][b + 1] -= 1;
                counts.Lianda++;
                Separate(Possibles_D, counts);
                counts.Lianda--;
                Possibles_D->HandTiles.matrix[a][b] += 1;
                Possibles_D->HandTiles.matrix[a][b + 1] += 1;
            }
        }
    }   //连搭

    for (int a = 0; a <= 2; a++) {
        for (int b = 1; b <= 7; b++) {
            if (Possibles_D->HandTiles.matrix[a][b] >= 1 && Possibles_D->HandTiles.matrix[a][b + 2] >= 1) {
                Possibles_D->HandTiles.matrix[a][b] -= 1;
                Possibles_D->HandTiles.matrix[a][b + 2] -= 1;
                counts.Tiaoda++;
                Separate(Possibles_D, counts);
                counts.Tiaoda--;
                Possibles_D->HandTiles.matrix[a][b] += 1;
                Possibles_D->HandTiles.matrix[a][b + 2] += 1;
            }
        }
    }   //跳搭

    for (int a = 0; a <= 3; a++) {
        for (int b = 1; b <= 9; b++) {
            if (a == 3 && b >= 8) {
                break;
            }

            if (Possibles_D->HandTiles.matrix[a][b] >= 2) {
                Possibles_D->HandTiles.matrix[a][b] -= 2;
                counts.Duizi++;
                Separate(Possibles_D, counts);
                counts.Duizi--;
                Possibles_D->HandTiles.matrix[a][b] += 2;
            }
        }
    }   //对子

    for (int a = 0; a <= 3; a++) {
        for (int b = 1; b <= 9; b++) {
            if (a == 3 && b >= 8) {
                break;
            }

            if (Possibles_D->HandTiles.matrix[a][b] >= 3) {
                Possibles_D->HandTiles.matrix[a][b] -= 3;
                counts.Kezi++;
                Separate(Possibles_D, counts);
                counts.Kezi--;
                Possibles_D->HandTiles.matrix[a][b] += 3;
            }
        }
    }   //刻子

    for (int a = 0; a <= 2; a++) {
        for (int b = 1; b <= 7; b++) {
            if (Possibles_D->HandTiles.matrix[a][b] >= 1 && Possibles_D->HandTiles.matrix[a][b + 1] >= 1 &&
                Possibles_D->HandTiles.matrix[a][b + 2] >= 1) {
                Possibles_D->HandTiles.matrix[a][b] -= 1;
                Possibles_D->HandTiles.matrix[a][b + 1] -= 1;
                Possibles_D->HandTiles.matrix[a][b + 2] -= 1;
                counts.Shunzi++;
                Separate(Possibles_D, counts);
                counts.Shunzi--;
                Possibles_D->HandTiles.matrix[a][b] += 1;
                Possibles_D->HandTiles.matrix[a][b + 1] += 1;
                Possibles_D->HandTiles.matrix[a][b + 2] += 1;
            }
        }
    }   //顺子
}

bool Stop(Possible_D *Possibles_D) {
    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i == 3 && j >= 8) {
                break;
            }

            if (Possibles_D->HandTiles.matrix[i][j] > 1) {
                return false;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        for (int j = 1; j <= 7; j++) {
            if (Possibles_D->HandTiles.matrix[i][j] == 0) continue;
            else if (Possibles_D->HandTiles.matrix[i][j] >= 1) {
                if (Possibles_D->HandTiles.matrix[i][j + 1] >= 1 || Possibles_D->HandTiles.matrix[i][j + 2] >= 1) {
                    return false;
                }
            }
        }
        if (Possibles_D->HandTiles.matrix[i][8] >= 1 && Possibles_D->HandTiles.matrix[i][9] >= 1) {
            return false;
        }
    }

    for (int i = 0; i <= 2; i++) {
        if (Possibles_D->HandTiles.matrix[i][8] >= 1 && Possibles_D->HandTiles.matrix[i][9] >= 1) {
            return false;
        }
    }

    return true;
}

int Shanten_ChChiitoitsu(Possible_D *Possibles_D) {
    int distance = 6;
    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i == 3 && j >= 8) break;

            if (Possibles_D->HandTiles.matrix[i][j] >= 2) {
                distance--;
            }
        }
    }

    return distance;
}

int Shanten_Guo(Possible_D *Possibles_D) {
    int distance = 12;

    if (Possibles_D->HandTiles.matrix[0][1] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[0][9] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[1][1] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[1][9] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[2][1] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[2][9] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][1] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][2] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][3] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][4] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][5] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][6] >= 1) distance--;
    if (Possibles_D->HandTiles.matrix[3][7] >= 1) distance--;

    return distance;
}

