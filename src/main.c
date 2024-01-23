#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = NANN,
            .jikaze = SHAA,
            .honbaCount = 1,
            .dora = "0p",
            .uradora = "4p",
            .handTile = "3m4m5m6p6p4s4s0s5s6s9s9s9s",
            .groupTile = {},
            .discardTile = "5z3z7z7m",
            .currentPlayer = KAMICHA,
            .currentTile = "9p",
            .remainTileCount = 50,
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