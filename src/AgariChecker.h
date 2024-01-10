#pragma once

#include <stdbool.h>
#include "main.h"

struct Hands {
    int matrix[4][15];
    int m_num;
    int p_num;
    int s_num;
    int z_num;
};

typedef struct Hands Hand;

bool isAgari(Status *status);  // 判断是否为和牌形，且无舍牌振听

bool isTenpai(Status *status);  // 判断是否为听牌形

int getDistance(Status *status);  // 获取听牌距离，即向听数

bool SeparateTile(Hand Hands);  //递归分组

