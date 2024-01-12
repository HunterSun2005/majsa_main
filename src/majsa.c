#include "majsa.h"

Result *majsa(Status *status) {
    Result *result = malloc(20 * sizeof(*result));  //初始化
    memset(result, 0, sizeof(*result));

    Possible *Possibles = isAgari(status);

    if (Possibles->Situations[0].Agari) {
        memcpy(result->yaku, checkYaku(status, Possibles, 0), sizeof(result->yaku));  //导入役种
        if (strstr(status->discardTile, status->currentTile) != NULL) {
            result->type = FURITEN;
        } else if (result->yaku[0] == 0) {
            result->type = TENPAI;
        } else if (status->currentPlayer == JICHA) {
            result->type = TSUMO;
        } else {
            result->type = RON;
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