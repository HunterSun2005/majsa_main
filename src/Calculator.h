#pragma once

#include <math.h>
#include "main.h"
#include "YakuChecker.h"
#include "NewDef.h"

int calHan(Status *status, Yaku *yaku, Possible *Possibles);  // 计算番数

int calFu(Status *status, Possible *Possibles, int number);  // 计算符数

int calPoint(Status *status, int Han, int Fu);  // 计算点数

Tenpai calMachi(Status *status, Hand HandTiles, Hand AllTiles);  // 计算面听数

bool isChi(Status *status, Possible *Possibles);    //是否吃牌

int MarkMK(Status *status, Possible *Possibles, int number);   //标记明刻(杠子)

bool isYPQT(Status *status, Possible *Possibles, int number);      //是否是役牌雀头

bool isLFQT(Status *status, Possible *Possibles, int number);      //是否是连风雀头

bool isDanqi(Status *status, Possible *Possibles, int number);     //是否是单骑听牌

bool isBianzhang(Status *status, Possible *Possibles, int number); //是否是边张听牌

bool isQianzhang(Status *status, Possible *Possibles, int number); //是否是嵌张听牌

int CountZZMK(Status *status, Possible *Possibles, int number);      //是否是中张明刻

int CountZZAK(Status *status, Possible *Possibles, int number);      //是否是中张暗刻

int CountZZMG(Status *status, Possible *Possibles, int number);      //是否是中张明杠

int CountZZAG(Status *status, Possible *Possibles, int number);      //是否是中张暗杠

int Count19MK(Status *status, Possible *Possibles, int number);      //是否是幺九明刻

int Count19AK(Status *status, Possible *Possibles, int number);      //是否是幺九暗刻

int Count19MG(Status *status, Possible *Possibles, int number);      //是否是幺九明杠

int Count19AG(Status *status, Possible *Possibles, int number);      //是否是幺九暗杠

Hand *AllTilesOnDesk(Status *status);   //计算牌桌上所有牌

void DelCurrentTile(Status *status, Possible *Possibles);   //去除当前牌