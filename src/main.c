#include "main.h"
#include "majsa.h"

int main() {
    Status status = {
            .bakaze = NANN,
            .jikaze = PEI,
            .honbaCount = 1,
            .dora = "2m",
            .uradora = "6m",
            .handTile = "0m6m7m8m8m9m9m",
            .groupTile = {{.type = Koutsu, .tile = "1m1m1m"},
                          {.type = Koutsu, .tile = "7z7z7z"}},
            .discardTile = "8s9s9s2z3m",
            .currentPlayer = SHIMOCHA,
            .currentTile = "9m",
            .remainTileCount = 53,
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