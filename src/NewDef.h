//
// Created by HP on 2024/1/13.
//

#pragma once

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
    Situation Situations[150];
    Hand HandTiles;
    Hand AllTiles;
    int HandGroupLen;  //手牌中的面子个数
};

typedef struct possible Possible;

struct count {
    int Shunzi;
    int Kezi;
    int Lianda;
    int Tiaoda;
    int Duizi;
};

typedef struct count countnumber;

struct situation_distance {
    bool valid;
    countnumber Count;
    int x;
};

typedef struct situation_distance Situation_D;

struct possible_distance {
    Situation_D Situations_D[150];
    Hand HandTiles;
};

typedef struct possible_distance Possible_D;

struct location {
    int a1, b1, a2, b2, a3, b3, a4, b4, a5, b5;
};

typedef struct location Location;
