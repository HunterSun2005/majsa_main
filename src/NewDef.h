//
// Created by HP on 2024/1/13.
//

#ifndef MAJSA_MAIN_NEWDEF_H
#define MAJSA_MAIN_NEWDEF_H

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
    Yaku yaku[20];
    int Han;
    int Fu;
    int point;
    ResultType result_type;
};

typedef struct situation Situation;

struct possible {
    Situation Situations[30];
    Hand HandTiles;
    Hand AllTiles;
    int HandGroupLen;  //手牌中的面子个数
};

typedef struct possible Possible;

#endif //MAJSA_MAIN_NEWDEF_H
