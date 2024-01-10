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

bool isAgari(Status *status);  // 判断是否为和牌形，且无舍牌振听

bool isTenpai(Status *status);  // 判断是否为听牌形

int getDistance(Status *status);  // 获取听牌距离，即向听数

bool SeparateTile(Hand Hands, Status *status, int count);  //递归分组

Hand Statistics(Status *status);  //统计牌数

bool CheckKokushimusou(Hand Hands);  //检查国士无双

bool CheckChiitoitsu(Hand Hands);  //检查七对子

