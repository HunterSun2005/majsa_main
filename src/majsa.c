#include "majsa.h"

Result *majsa(Status *status) {
    Result *result = malloc(sizeof(*result));  //初始化
    memset(result, 0, sizeof(*result));

    Possible *Possibles = isAgari(status);

    SortGroupTile(status, Possibles);  //排序副露牌

    for (int i = 0; i < 20; i++) {
        if (Possibles->Situations[i].Agari) {
            if (strstr(status->discardTile, status->currentTile) != NULL) {
                Possibles->Situations[i].result_type = FURITEN;
            } else {
                memcpy(Possibles->Situations[i].yaku, checkYaku(status, Possibles, i), sizeof(result->yaku));  //导入役种
                if (Possibles->Situations[i].yaku[0] == 0) {
                    Possibles->Situations[i].result_type = TENPAI;
                } else {
                    if (status->currentPlayer == JICHA) {
                        Possibles->Situations[i].result_type = TSUMO;
                    } else {
                        Possibles->Situations[i].result_type = RON;
                    }
                    Possibles->Situations[i].Han = calHan(status, Possibles->Situations[i].yaku, Possibles);
                    Possibles->Situations[i].Fu = calFu(status, Possibles->Situations[i].Han, Possibles, i);
                    Possibles->Situations[i].point = calPoint(
                            status, Possibles->Situations[i].Han, Possibles->Situations[i].Fu);
                }
            }
        }
    }

    int count_agari = 0;
    for (int i = 0; i < 30; i++) {
        if (Possibles->Situations[i].Agari &&
            (Possibles->Situations[i].result_type == TSUMO || Possibles->Situations[i].result_type == RON)) {
            count_agari++;      //记录有效情况次数
        }
    }

    if (count_agari >= 1) {
        int max = 0;
        for (int i = 0; i < 30; i++) {
            if (Possibles->Situations[i].point > Possibles->Situations[max].point) {
                max = i;
            }
        }
        memcpy(result->yaku, Possibles->Situations[max].yaku, sizeof(result->yaku));
        SortYaku(result->yaku);
        result->han = Possibles->Situations[max].Han;
        result->fu = Possibles->Situations[max].Fu;
        result->type = Possibles->Situations[max].result_type;
        if (status->jikaze == status->bakaze) {
            for (int i = 0; i < 3; i++) {
                result->point[i] = Possibles->Situations[max].point / 3;
            }
        } else {
            int d = (int) status->bakaze - (int) status->jikaze;
            if (d < 0) {
                d += 4;
            }
            result->point[3 - d] = Possibles->Situations[max].point / 2;
            for (int i = 0; i < 3; i++) {
                if (result->point[i] == 0) {
                    result->point[i] = Possibles->Situations[max].point / 4;
                }
            }
        }
        return result;
    }       //可以和牌
    else {
        DelCurrentTile(status, Possibles);  //去除当前牌
        int count_tenpai = 0;

        for (int i = 0; i < 30; i++) {
            if (Possibles->Situations[i].result_type == FURITEN) {
                result->type = FURITEN;
                count_tenpai++;
            } else if (Possibles->Situations[i].result_type == TENPAI) {
                result->type = TENPAI;
                count_tenpai++;
            }
        }

        if (count_tenpai <= 0) {
            int Machi = calMachi(status, Possibles->HandTiles);
            if (Machi >= 1) {
                result->type = TENPAI;
                result->machi = Machi;
            } else {
                result->type = NOTEN;
                result->shanten = getDistance(status, Possibles);    //计算向听数
                return result;
            }
        } else {
            int Machi = calMachi(status, Possibles->HandTiles);
            result->machi = Machi;
        }


        return result;
    }
}

void DelCurrentTile(Status *status, Possible *Possibles) {
    switch (status->currentTile[1]) {
        case 'm':
            Possibles->HandTiles.matrix[0][status->currentTile[0] - 48]--;
            Possibles->HandTiles.m_num--;
            break;
        case 'p':
            Possibles->HandTiles.matrix[1][status->currentTile[0] - 48]--;
            Possibles->HandTiles.p_num--;
            break;
        case 's':
            Possibles->HandTiles.matrix[2][status->currentTile[0] - 48]--;
            Possibles->HandTiles.s_num--;
            break;
        case 'z':
            Possibles->HandTiles.matrix[3][status->currentTile[0] - 48]--;
            Possibles->HandTiles.z_num--;
            break;
        default:;
    }
}