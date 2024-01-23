#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = TON,
            .jikaze = NANN,
            .honbaCount = 1,
            .dora = "9p",
            .uradora = "5m",
            .handTile = "1m1m1m3m4m5m2s2s2s7s7s7s1z",
            .groupTile = {},
            .discardTile = "3z5z1z2m3p2m3s7s",
            .currentPlayer = KAMICHA,
            .currentTile = "1z",
            .remainTileCount = 37,
            .isRiichi = true,
            .isDoubleRiichi = false,
            .isIppatsu = true,
            .isRinshan = false,
    };
    Result const *result = majsa(&status);
    if (result != NULL)
        outputResultJson(*result);
    // OJ 会对比输出结果和标准结果，按照对比结果给出评分
    return 0;
}

void outputResultJson(Result result) {
    FILE *f = fopen("result.json", "w");
    fprintf(f, "{\"type\":%d,\"yaku\":[", result.type);
    for (int i = 0; i < 20; i++) {
        fprintf(f, "%d", result.yaku[i]);
        if (i < 19) {
            fprintf(f, ",");
        }
    }
    fprintf(f, "],\"han\":%d,\"fu\":%d,\"point\":[%d,%d,%d],\"machi\":%d,\"shanten\":%d}", result.han, result.fu,
            result.point[0], result.point[1], result.point[2], result.machi, result.shanten);
    fclose(f);
}