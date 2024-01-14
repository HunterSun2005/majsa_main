//
// Created by HP on 2024/1/14.
//

#ifndef MAJSA_MAIN_SORT_H
#define MAJSA_MAIN_SORT_H

#include "main.h"
#include "NewDef.h"

void SortGroupTile(Status *status, Possible *Possibles);    //排序副露牌

void SortTile(char *Sorted);   //排序

void SwapTile(char *Sorted, int a);    //交换

int comp(int a, int b);    //比较

#endif //MAJSA_MAIN_SORT_H
