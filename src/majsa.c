#include "majsa.h"

Result *majsa(Status *status) {
    Result *result = malloc(20 * sizeof(*result));  //初始化
    memset(result, 0, sizeof(*result));

    Possible *Possibles = isAgari(status);

    for (int i = 0; i < 20; i++) {
        if (Possibles->Situations[i].Agari) {
            if (strstr(status->discardTile, status->currentTile) != NULL) {
                result->type = FURITEN;
            } else {
                memcpy(Possibles->Situations[i].yaku, checkYaku(status, Possibles, i), sizeof(result->yaku));  //导入役种
                if (Possibles->Situations[i].yaku[0] == 0) {
                    result->type = TENPAI;
                } else {
                    if (status->currentPlayer == JICHA) {
                        result->type = TSUMO;
                    } else {
                        result->type = RON;
                    }
                    Possibles->Situations[i].Han = calHan(status, Possibles->Situations[i].yaku, Possibles);
                    Possibles->Situations[i].Fu = calFu(status, Possibles->Situations[i].Han, Possibles, i);
                    Possibles->Situations[i].point = calPoint(status, Possibles->Situations[i].Han, \
                        Possibles->Situations[i].Fu);
                }
            }
        }
    }
//    else {
//        if (isTenpai(status)) {
//            result->type = TENPAI;
//        }
//        else {
//            result->type = NOTEN;
//        }
//    }   //结果类型

    return result;
}