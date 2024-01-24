#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = TON,
            .jikaze = TON,
            .honbaCount = 0,
            .dora = "1m",
            .uradora = "3s",
            .handTile = "1m1m2m2m3m3p3p4p4p5p5p6p6p",
            .groupTile = {},
            .discardTile = "2m3m4m5m3p4p5p6p2s3s4s5s",
            .currentPlayer = JICHA,
            .currentTile = "3m",
            .remainTileCount = 18,
            .isRiichi = false,
            .isDoubleRiichi = false,
            .isIppatsu = false,
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