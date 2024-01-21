//
// Created by HP on 2024/1/14.
//

#pragma once

#include "main.h"
#include "NewDef.h"

void SortGroupTile(Status *status, Possible *Possibles);    //排序副露牌

void SortTile(char *Sorted);   //排序

void SwapTile(char *Sorted, int a);    //交换

int comp(int a, int b);    //比较

void SortYaku(Yaku *yaku);  //役种排序

void SwapYaku(Yaku *yaku, int a);   //役种比较
