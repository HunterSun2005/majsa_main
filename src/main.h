#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef enum {
  TON,   // 东风
  NANN,   // 南风，由于 NAN 与 math.h 库冲突，改为 NANN
  SHAA,  // 西风
  PEI    // 北风
} KazeType;

typedef enum {
  JICHA = -1,   // 自家
  KAMICHA = 0,  // 上家
  TOIMEN = 1,   // 对家
  SHIMOCHA = 2  // 下家
} Player;

typedef enum {
  Shuntsu,  // 顺子
  Koutsu,   // 刻子
  Kantsu,   // 杠子
  Ankan     // 暗杠
} GroupType;

typedef struct group {
  GroupType type;
  char tile[10];
} Group;

typedef enum {
  RON,      // 荣和
  TSUMO,    // 自摸
  TENPAI,   // 听牌
  FURITEN,  // 振听
  NOTEN,    // 不听
} ResultType;

/**
 * 役种以三位 16 进制数做编号
 * 第一位为番数 (役满记 d, 两倍役满记 f, 食下役按照应有的番数算)
 * 第二位:
 *    0=非食下役/食下役的门清版
 *    1=门清限定
 *    2=食下役的非门清版
 * 第三位为编号
 */

typedef enum {
  Riichi = 0x110,           // 立直
  Ippatsu = 0x111,          // 一发
  Menzenchintsumo = 0x112,  // 门前清自摸和
  Tanyao = 0x100,           // 断幺九
  YakuhaiJikaze = 0x101,    // 自风
  YakuhaiBakaze = 0x102,    // 场风
  YakuhaiHaku = 0x103,      // 白
  YakuhaiHatsu = 0x104,     // 发
  YakuhaiChun = 0x105,      // 中
  Pinhu = 0x113,            // 平和
  Iipeikou = 0x114,         // 一杯口
  Chankan = 0x106,          // 抢杠（排除）
  Rinshankaihou = 0x107,    // 岭上开花
  Haiteiraoyue = 0x108,     // 海底摸月
  Houteiraoyui = 0x109,     // 河底捞鱼

  doubleRiichi = 0x210,    // 两立直
  Sanshokudoukou = 0x200,  // 三色同刻
  Sankantsu = 0x201,       // 三杠子
  Toitoihou = 0x202,       // 对对和
  Sanankou = 0x203,        // 三暗刻
  Shousangen = 0x204,      // 小三元
  Honroutou = 0x205,       // 混老头
  Chiitoitsu = 0x211,      // 七对子

  Honchantaiyaochuu = 0x206,   // 混全带幺九（门清）
  HonchantaiyaochuuF = 0x126,  // 混全带幺九（副露）
  Ikkitsuukan = 0x207,         // 一气通贯（门清）
  IkkitsuukanF = 0x127,        // 一气通贯（副露）
  Sanshokudoujun = 0x208,      // 三色同顺（门清）
  SanshokudoujunF = 0x128,     // 三色同顺（副露）

  Ryanpeikou = 0x310,          // 两杯口
  Junchantaiyaochuu = 0x300,   // 纯全带幺九（门清）
  JunchantaiyaochuuF = 0x220,  // 纯全带幺九（副露）
  Honitsu = 0x301,             // 混一色（门清）
  HonitsuF = 0x221,            // 混一色（副露）

  Nagashimangan = 0x500,  // 流局满贯（排除）
  Chinitsu = 0x600,       // 清一色（门清）
  ChinitsuF = 0x520,      // 清一色（副露）

  Tenhou = 0xd00,         // 天和
  Chihou = 0xd01,         // 地和
  Daisangen = 0xd02,      // 大三元
  Suuankou = 0xd10,       // 四暗刻
  Tsuuiisou = 0xd03,      // 字一色
  Ryuuiisou = 0xd04,      // 绿一色
  Chinroutou = 0xd05,     // 清老头
  Kokushimusou = 0xd11,   // 国士无双
  Shousuushi = 0xd06,     // 小四喜
  Suukantsu = 0xd07,      // 四杠子
  Chuurenpoutou = 0xd12,  // 九莲宝灯

  Suuankoutanki = 0xf10,          // 四暗刻单骑
  Kokushijuusanmenmachi = 0xf11,  // 国士无双十三面
  Chuurenkyuumenmachi = 0xf12,    // 纯正九莲宝灯
  Daisuushi = 0xf00,              // 大四喜
} Yaku;

struct status {
  KazeType bakaze;       // 场风
  KazeType jikaze;       // 自风
  int honbaCount;        // 本场棒数
  char dora[12];         // 宝牌指示牌
  char uradora[12];      // 里宝牌指示牌
  char handTile[30];     // 自家手牌
  Group groupTile[30];   // 自家副露区（包括暗杠）
  char discardTile[60];  // 自家弃牌区（包含被别家副露掉的牌）
  Player currentPlayer;  // 当前控牌玩家
  char currentTile[2];   // 当前控牌
  int remainTileCount;   // 牌山剩余牌数
  bool isRiichi;         // 是否已立直
  bool isDoubleRiichi;   // 是否为两立直
  bool isIppatsu;        // 是否为一发
  bool isRinshan;        // 是否为岭上牌
};

typedef struct status Status;

struct result {
  ResultType type;  // 结果类型
  Yaku yaku[20];    // 役种，排除古役、抢杠与流局满贯
  int han;          // 番数，约定役满役种得到的番数为负数，X倍役满即为 -X，以此与累计役满区分
  int fu;           // 符数，国士无双时符数无意义
  int point[3];     // 点数，三家各自要给自家的点数，不考虑包牌，下标为 0=上家，1=对家，2=下家
  int machi;        // 面听数
  int shanten;      // 向听数
};

typedef struct result Result;

void outputResultJson(Result result);
