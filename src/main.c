#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = TON,
            .jikaze = TON,
            .honbaCount = 0,
            .dora="9p",
            .uradora="3s",
            .handTile="3p3p4p4p",
            .groupTile={{Koutsu, "8p8p8p"},
                        {Koutsu, "6p6p6p"},
                        {Koutsu, "7p7p7p"}},
            .discardTile="1s2s3s4s5s",
            .currentPlayer=KAMICHA,
            .currentTile="4p",
            .remainTileCount=18,
            .isRiichi=false,
            .isDoubleRiichi=false,
            .isIppatsu=false,
            .isRinshan=false,
    };
    Result *result = majsa(&status);
//    assert(result->type == TSUMO);
//    Yaku stdYaku[1] = {Kokushijuusanmenmachi};
//    assert(sizeof(result->yaku) == sizeof(stdYaku));
//    for (int i = 0; i < sizeof(result->yaku) / sizeof(result->yaku[0]); i++) {
//        assert(result->yaku[i] == stdYaku[i]);
//    }
//    assert(result->han == 26);
//    // assert(result->fu == 30);  // 国士无双，不考虑符数
//    assert(result->point[KAMICHA] == 32000);
//    assert(result->point[TOIMEN] == 32000);
//    assert(result->point[SHIMOCHA] == 32000);
//    // assert(result->machi == 13);  // 已和牌，不考虑面听数
//    // assert(result->shanten == 0);  // 已和牌，不考虑向听数
    return 0;
}