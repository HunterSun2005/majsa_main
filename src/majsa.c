#include "majsa.h"

char Pair[4] = {0};
Group HandGroupTile[6] = {};

Result *majsa(Status *status) {
    Result *result = malloc(20 * sizeof(*result));  //初始化

    if (isAgari(status)) {
        memcpy(result->yaku, checkYaku(status), sizeof(result->yaku));  //导入役种
        if (strstr(status->discardTile, status->currentTile) != NULL) {
            result->type = FURITEN;
        } else if (result->yaku[0] == 0x000) {
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