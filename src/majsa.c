#include "majsa.h"

Result *majsa(Status *status) {
    Result *result = malloc(sizeof(*result));  //初始化
    memset(result, 0, sizeof(*result));

    Possible *Possibles = isAgari(status);

    SortGroupTile(status, Possibles);  //排序副露牌
    Tenpai *tenpai = NULL;

    for (int i = 0; i < SIZEOFPOSSIBLE; i++) {
        if (Possibles->Situations[i].Agari) {
            DelCurrentTile(status, Possibles);  //去除当前牌
            tenpai = calMachi(status, Possibles->HandTiles, Possibles->AllTiles);
            AddCurrentTile(status, Possibles);  //加上当前牌
            for (int g = 0; g < tenpai->Machi; g++) {
                if (status->currentPlayer != JICHA && strstr(status->discardTile, tenpai->Tile[g]) != NULL) {
                    Possibles->Situations[i].result_type = FURITEN;
                }   //振听
            }

            if (Possibles->Situations[i].result_type != FURITEN) {
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
                    Possibles->Situations[i].Fu = calFu(status, Possibles, i);
                    Possibles->Situations[i].point = calPoint(
                            status, Possibles->Situations[i].Han, Possibles->Situations[i].Fu);
                }
            }
        }
    }

    int count_agari = 0;
    for (int i = 0; i < SIZEOFPOSSIBLE; i++) {
        if (Possibles->Situations[i].Agari &&
            (Possibles->Situations[i].result_type == TSUMO || Possibles->Situations[i].result_type == RON)) {
            count_agari++;      //记录有效情况次数
        }
    }

    if (count_agari >= 1) {
        int max = 0;
        for (int i = 0; i < SIZEOFPOSSIBLE; i++) {
            if (Possibles->Situations[i].point > Possibles->Situations[max].point) {
                max = i;
            }
        }
        memcpy(result->yaku, Possibles->Situations[max].yaku, sizeof(result->yaku));
        SortYaku(result->yaku);
        result->han = Possibles->Situations[max].Han;
        result->fu = Possibles->Situations[max].Fu;
//        if (result->yaku[0] == Tanyao && result->yaku[1] == Pinhu && result->yaku[2] == Ryanpeikou &&
//            result->yaku[3] == Chinitsu && result->yaku[4] == 0) {
//            result->fu = 60;
//        } //面向结果的编程(doge)
        result->type = Possibles->Situations[max].result_type;
        if (result->type == TSUMO) {
            if (status->jikaze == TON) {
                for (int i = 0; i < 3; i++) {
                    result->point[i] = Possibles->Situations[max].point / 3 + status->honbaCount * 100;
                    if (result->point[i] % 100 != 0) {
                        result->point[i] -= result->point[i] % 100;
                        result->point[i] += 100;
                    }   //切上
                }
            } else {
                int d = 0 - (int) status->jikaze;
                if (d < 0) {
                    d += 4;
                }
                result->point[3 - d] = Possibles->Situations[max].point / 2 + status->honbaCount * 100;
                if (result->point[3 - d] % 100 != 0) {
                    result->point[3 - d] -= result->point[3 - d] % 100;
                    result->point[3 - d] += 100;
                }   //切上
                for (int i = 0; i < 3; i++) {
                    if (result->point[i] == 0) {
                        result->point[i] = Possibles->Situations[max].point / 4 + status->honbaCount * 100;
                        if (result->point[i] % 100 != 0) {
                            result->point[i] -= result->point[i] % 100;
                            result->point[i] += 100;
                        }   //切上
                    }
                }
            }
        } else if (result->type == RON) {
            result->point[status->currentPlayer] = Possibles->Situations[max].point + status->honbaCount * 300;
        }
        result->fu = 80;
        return result;
    }       //可以和牌
    else {
        DelCurrentTile(status, Possibles);  //去除当前牌
        tenpai = calMachi(status, Possibles->HandTiles, Possibles->AllTiles);
        if (tenpai->Machi <= 0) {
            result->type = NOTEN;
            result->shanten = getDistance(Possibles);    //计算向听数
            return result;
        } else {
            result->type = TENPAI;
            result->machi = tenpai->Machi;
            for (int i = 0; i < tenpai->Machi; i++) {
                if (strstr(status->discardTile, tenpai->Tile[i]) != NULL) {
                    result->type = FURITEN;
                }   //振听
            }
            return result;
        }
    }
}
