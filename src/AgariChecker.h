#pragma once
#include <stdbool.h>
#include "main.h"

bool isAgari(Status *status);  // 判断是否为和牌形，且无舍牌振听

bool isTenpai(Status *status);  // 判断是否为听牌形

int getDistance(Status *status);  // 获取听牌距离，即向听数