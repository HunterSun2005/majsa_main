#pragma once

#include "main.h"
#include "AgariChecker.h"
#include "NewDef.h"

Yaku *checkYaku(Status *status, Possible *possibles, int num);    // 检测所满足的所有役种（若包含役满/两倍役种，则不返回其他非役满役种；注意其余役种替代关系）

bool isMenzenchin(Status *status);  //判断是否是门前清

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

bool isChinitsu(Status *status);    //判断是否是清一色（门清）

bool isChinitsuF(Status *status);   //判断是否是清一色（副露）

bool isDaisangen(Status *status);   //判断是否是大三元

bool isSuuankou(Status *status);    //判断是否是四暗刻

bool isTsuuiisou(Status *status);   //判断是否是字一色

bool isRyuuiisou(Status *status);   //判断是否是绿一色

bool isChinroutou(Status *status);   //判断是否是清老头

bool isKokushimusou(Status *status);   //判断是否是国士无双

bool isShousuushi(Status *status);   //判断是否是小四喜

bool isSuukantsu(Status *status);   //判断是否是四杠子

bool isChuurenpoutou(Status *status);   //判断是否是九莲宝灯

bool isSuuankoutanki(Status *status);   //判断是否是四暗刻单骑

bool isKokushijuusanmenmachi(Status *status);   //判断是否是国士无双十三面

bool isChuurenkyuumenmachi(Status *status);     //判断是否是纯正九莲宝灯

bool isDaisuushi(Status *status);     //判断是否是大四喜
