#pragma once

#include "main.h"

struct AllHands {
    int matrix[4][10];
    int m_num;
    int p_num;
    int s_num;
    int z_num;
};

typedef struct AllHands AllHand;

Yaku *checkYaku(Status *status);    // 检测所满足的所有役种（若包含役满/两倍役种，则不返回其他非役满役种；注意其余役种替代关系）

AllHand StatisticsAll(Status *status);  //统计所有牌数

bool isMenzenchintsumo(Status *status);   //判断是否是门前清自摸和

bool isPinhu(Status *status);       //判断是否是平胡

bool isIipeikou(Status *status);    //判断是否是一杯口

bool isSanshokudoukou(Status *status);  //判断是否是三色同刻

bool isSankantsu(Status *status);   //判断是否是三杠子

bool isToitoihou(Status *status);   //判断是否是对对和

bool isSanankou(Status *status);    //判断是否是三杠子

bool isShousangen(Status *status);  //判断是否是小三元

bool isHonroutou(Status *status);   //判断是否是混老头

bool isChiitoitsu(Status *status);  //判断是否是七对子

bool isHonchantaiyaochuu(Status *status);   //判断是否是混全带幺九（门清）

bool isHonchantaiyaochuuF(Status *status);  //判断是否是混全带幺九（副露）

bool isIkkitsuukan(Status *status);     //判断是否是一气通贯（门清）

bool isIkkitsuukanF(Status *status);    //判断是否是一气通贯（副露）

bool isSanshokudoujun(Status *status);  //判断是否是三色同顺（门清）

bool isSanshokudoujunF(Status *status);  //判断是否是三色同顺（副露）

bool isRyanpeikou(Status *status);      //判断是否是两杯口

bool isJunchantaiyaochuu(Status *status);   //判断是否是纯全带幺九（门清）

bool isJunchantaiyaochuuF(Status *status);   //判断是否是纯全带幺九（副露）


bool isHonitsu(Status *status);     //判断是否是混一色（门清）

bool isHonitsuF(Status *status);    //判断是否是混一色（副露）