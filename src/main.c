#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = TON,
            .jikaze = TON,
            .honbaCount = 0,
            .dora="1m",
            .uradora="3s",
            .handTile="1m1m2m2m3m3m5m5m6m6m7m7m9m",
            .groupTile={},
            .discardTile="2m3m4m5m3p4p5p6p2s3s4s5s",
            .currentPlayer=JICHA,
            .currentTile="9m",
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