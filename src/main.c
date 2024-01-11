#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = TON,
            .jikaze = TON,
            .honbaCount = 0,
            .dora="1m",
            .uradora="3s",
            .handTile="1m9m1p9p1s9s1z2z3z4z5z6z7z",
            .groupTile={},
            .discardTile="2m3m4m5m3p4p5p6p2s3s4s5s",
            .currentPlayer=JICHA,
            .currentTile="1z",
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
    printf("%d\n", result->type);
    for (int i = 0; i < 20 && result->yaku[i] != 0; i++) {
        printf("%x ", result->yaku[i]);
    }
    return 0;
}