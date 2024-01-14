//
// Created by HP on 2024/1/14.
//

#include "Sort.h"

void SortGroupTile(Status *status, Possible *Possibles) {
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        for (int j = 0; j < 4; j++) {
            if (status->groupTile[i].tile[2 * j] == '0' && status->groupTile[i].tile[2 * j + 1] != 0) {
                status->groupTile[i].tile[2 * j] = '5';
            }
        }
    }       //转换赤宝牌

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        SortTile(status->groupTile[i].tile);
    }

}

void SortTile(char *Sorted) {
    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j <= i && Sorted[2 * j + 2] != '\0'; j++) {
            if (comp(Sorted[2 * j + 1], Sorted[2 * j + 3]) > 0) {
                SwapTile(Sorted, 2 * j);
            }
        }
    }   //第一次排序

    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j <= i && Sorted[2 * j + 2] != '\0'; j++) {
            if (Sorted[2 * j + 1] == Sorted[2 * j + 3] && comp(Sorted[2 * j], Sorted[2 * j + 2]) > 0) {
                SwapTile(Sorted, 2 * j);
            }
        }
    }   //第二次排序

}

void SwapTile(char *Sorted, int a) {
    char temp = 0;

    temp = Sorted[a];
    Sorted[a] = Sorted[a + 2];
    Sorted[a + 2] = temp;

    temp = Sorted[a + 1];
    Sorted[a + 1] = Sorted[a + 3];
    Sorted[a + 3] = temp;
}

int comp(int a, int b) {
    if (a == b) {
        return 0;
    } else {
        return (a > b) - (a < b);
    }
}