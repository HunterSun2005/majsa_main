#pragma once

#include <stdbool.h>
#include "main.h"

struct Hands {
    int matrix[4][10];
    int m_num;
    int p_num;
    int s_num;
    int z_num;
};

typedef struct Hands Hand;

struct situation {
    bool Agari;     //是否为和牌型
    char Jyantou[4];   //雀头
    Group HandGroupTile[6];     //手牌中的面子
};

typedef struct situation Situation;

struct possible {
    Situation Situations[100];
    Hand HandTiles;
    Hand AllTiles;
    int HandGroupLen;  //手牌中的面子个数
};

typedef struct possible Possible;

Possible *isAgari(Status *status);  // 判断是否为和牌形，且无舍牌振听

bool isTenpai(Status *status);  // 判断是否为听牌形

int getDistance(Status *status);  // 获取听牌距离，即向听数

void SeparateTile(Hand Hands, Status *status, int count, Possible *Possibles);  //递归分组

Hand Statistics(Status *status);  //统计牌数

Hand StatisticsAll(Status *status);  //统计所有牌数

bool CheckKokushimusou(Hand Hands);  //检查国士无双

bool CheckChiitoitsu(Hand Hands);  //检查七对子

