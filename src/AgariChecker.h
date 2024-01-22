#pragma once

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"
#include "YakuChecker.h"
#include "NewDef.h"


Possible *isAgari(Status *status);  // 判断是否为和牌形，且无舍牌振听

Possible *isTenpai(Status *status, Hand HandTiles);  // 判断是否为听牌形

int getDistance(Status *status, Possible *Possibles);  // 获取听牌距离，即向听数

void SeparateTile(Hand Hands, Status *status, int count, Possible *Possibles, int a1, int b1, int a2, int b2);  //递归分组

Hand Statistics(Status *status);  //统计牌数

Hand StatisticsAll(Status *status);  //统计所有牌数

bool CheckKokushimusou(Hand Hands);  //检查国士无双

bool CheckChiitoitsu(Status *status, Hand Hands);  //检查七对子

void Separate(Possible_D *Possibles_D, countnumber counts);     //递推

bool Stop(Possible_D *Possibles_D);     //退出递推

int Shanten_ChChiitoitsu(Possible_D *Possibles_D);  //七对子向听数

int Shanten_Guo(Possible_D *Possibles_D);  //国士无双向听数

