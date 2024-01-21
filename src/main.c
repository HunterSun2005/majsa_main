#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = TON,
            .jikaze = TON,
            .honbaCount = 0,
            .dora="2z6z2z9s9s",
            .uradora="9s9s2z2z6z",
            .handTile="5z5z6z6z",
            .groupTile={{Ankan, "1z1z1z1z"}, {Ankan, "7z7z7z7z"}, {Ankan, "1s1s1s1s"}},
            .discardTile="1p2s3s4s5s",
            .currentPlayer=SHIMOCHA,
            .currentTile="5z",
            .remainTileCount=0,
            .isRiichi=false,
            .isDoubleRiichi=true,
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