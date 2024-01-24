#include "YakuChecker.h"

Possible *Possibles;
int number;

Yaku *checkYaku(Status *status, Possible *possibles, int num) {
    Yaku *yaku = malloc(20 * sizeof(*yaku));
    memset(yaku, 0, 20 * sizeof(*yaku));

    Possibles = possibles;
    number = num;

    int count = 0;
    int yakuman = 0;

    if (status->bakaze == status->jikaze && status->discardTile[1] == 0) {
        yaku[count] = Tenhou;
        count++;
        yakuman++;
    }

    if (status->bakaze != status->jikaze && status->discardTile[1] == 0) {
        yaku[count] = Chihou;
        count++;
        yakuman++;
    }

    if (isDaisangen(status)) {
        yaku[count] = Daisangen;
        count++;
        yakuman++;
    }

    {
        if (isSuuankoutanki(status)) {
            yaku[count] = Suuankoutanki;
            count++;
            yakuman++;
        } else if (isSuuankou(status)) {
            yaku[count] = Suuankou;
            count++;
            yakuman++;
        }
    }

    if (isTsuuiisou(status)) {
        yaku[count] = Tsuuiisou;
        count++;
        yakuman++;
    }

    if (isRyuuiisou(status)) {
        yaku[count] = Ryuuiisou;
        count++;
        yakuman++;
    }

    if (isChinroutou(status)) {
        yaku[count] = Chinroutou;
        count++;
        yakuman++;
    }

    {
        if (isKokushijuusanmenmachi(status)) {
            yaku[count] = Kokushijuusanmenmachi;
            count++;
            yakuman++;
        } else if (isKokushimusou(status)) {
            yaku[count] = Kokushimusou;
            count++;
            yakuman++;
        }
    }

    {
        if (isDaisuushi(status)) {
            yaku[count] = Daisuushi;
            count++;
            yakuman++;
        } else if (isShousuushi(status)) {
            yaku[count] = Shousuushi;
            count++;
            yakuman++;
        }
    }

    {
        if (isChuurenkyuumenmachi(status)) {
            yaku[count] = Chuurenkyuumenmachi;
            count++;
            yakuman++;
        } else if (isChuurenpoutou(status)) {
            yaku[count] = Chuurenpoutou;
            count++;
            yakuman++;
        }
    }

    if (isSuukantsu(status)) {
        yaku[count] = Suukantsu;
        count++;
        yakuman++;
    }   //以上为役满及以上役种

    if (yakuman >= 1) {
        return yaku;
    }   //若有役满则不计其他役种

    if (status->isRiichi) {
        yaku[count] = Riichi;
        count++;
    }   //立直
    if (status->isIppatsu) {
        yaku[count] = Ippatsu;
        count++;
    }   //一发
    if (isMenzenchintsumo(status)) {
        yaku[count] = Menzenchintsumo;
        count++;
    }
    if (isTanyao(status)) {
        yaku[count] = Tanyao;
        count++;
    }
    if (Possibles->AllTiles.matrix[3][status->jikaze + 1] >= 3) {
        yaku[count] = YakuhaiJikaze;
        count++;
    }
    if (Possibles->AllTiles.matrix[3][status->bakaze + 1] >= 3) {
        yaku[count] = YakuhaiBakaze;
        count++;
    }
    if (Possibles->AllTiles.matrix[3][5] >= 3) {
        yaku[count] = YakuhaiHaku;
        count++;
    }
    if (Possibles->AllTiles.matrix[3][6] >= 3) {
        yaku[count] = YakuhaiHatsu;
        count++;
    }
    if (Possibles->AllTiles.matrix[3][7] >= 3) {
        yaku[count] = YakuhaiChun;
        count++;
    }
    if (isPinhu(status) && isMenzenchin(status)) {
        yaku[count] = Pinhu;
        count++;    //门前清限定
    }

    {
        if (isRyanpeikou(status) && isMenzenchin(status)) {
            yaku[count] = Ryanpeikou;
            count++;
        } else {
            if (isChiitoitsu(status) && isMenzenchin(status)) {
                yaku[count] = Chiitoitsu;
                count++;
            } else if (isIipeikou(status) && isMenzenchin(status)) {
                yaku[count] = Iipeikou;
                count++;    //门前清限定
            }
        }
    }

    if (status->isRinshan) {
        yaku[count] = Rinshankaihou;
        count++;
    }
    if (status->remainTileCount == 0 && status->currentPlayer == JICHA) {
        yaku[count] = Haiteiraoyue;
        count++;
    }
    if (status->remainTileCount == 0 && status->currentPlayer != JICHA) {
        yaku[count] = Houteiraoyui;
        count++;
    }
    if (status->isDoubleRiichi) {
        yaku[count] = doubleRiichi;
        count++;
    }
    if (isSanshokudoukou(status)) {
        yaku[count] = Sanshokudoukou;
        count++;
    }
    if (isSankantsu(status)) {
        yaku[count] = Sankantsu;
        count++;
    }
//    if (isToitoihou(status)) {
//        yaku[count] = Toitoihou;
//        count++;
//    }
//    if (isSanankou(status)) {
//        yaku[count] = Sanankou;
//        count++;
//    }
    if (isShousangen(status)) {
        yaku[count] = Shousangen;
        count++;
    }
    if (isHonroutou(status)) {
        yaku[count] = Honroutou;
        count++;
    }

    {
        if (isJunchantaiyaochuu(status)) {
            yaku[count] = Junchantaiyaochuu;
            count++;
        } else if (isJunchantaiyaochuuF(status)) {
            yaku[count] = JunchantaiyaochuuF;
            count++;
        } else if (isHonchantaiyaochuu(status)) {
            yaku[count] = Honchantaiyaochuu;
            count++;
        } else if (isHonchantaiyaochuuF(status)) {
            yaku[count] = HonchantaiyaochuuF;
            count++;
        }
    }

    {
        if (isIkkitsuukan(status)) {
            yaku[count] = Ikkitsuukan;
            count++;
        } else if (isIkkitsuukanF(status)) {
            yaku[count] = IkkitsuukanF;
            count++;
        }
    }

    {
        if (isSanshokudoujun(status)) {
            yaku[count] = Sanshokudoujun;
            count++;
        } else if (isSanshokudoujunF(status)) {
            yaku[count] = SanshokudoujunF;
            count++;
        }
    }

    {
        if (isChinitsu(status)) {
            yaku[count] = Chinitsu;
            count++;
        } else if (isChinitsuF(status)) {
            yaku[count] = ChinitsuF;
            count++;
        } else if (isHonitsu(status)) {
            yaku[count] = Honitsu;
            count++;
        } else if (isHonitsuF(status)) {
            yaku[count] = HonitsuF;
            count++;
        }
    }

    return yaku;
}

bool isTanyao(Status *status) {
    if (Possibles->AllTiles.matrix[0][1] == 0 && Possibles->AllTiles.matrix[0][9] == 0 &&
        Possibles->AllTiles.matrix[1][1] == 0 && Possibles->AllTiles.matrix[1][9] == 0 &&
        Possibles->AllTiles.matrix[2][1] == 0 && Possibles->AllTiles.matrix[2][9] == 0 &&
        Possibles->AllTiles.matrix[3][1] == 0 && Possibles->AllTiles.matrix[3][2] == 0 &&
        Possibles->AllTiles.matrix[3][3] == 0 && Possibles->AllTiles.matrix[3][4] == 0 &&
        Possibles->AllTiles.matrix[3][5] == 0 && Possibles->AllTiles.matrix[3][6] == 0 &&
        Possibles->AllTiles.matrix[3][7] == 0) {
        return true;
    } else return false;

}

bool isMenzenchin(Status *status) {
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type != Ankan) {
            return false;
        }
    }
    return true;
}

bool isMenzenchintsumo(Status *status) {
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type != Ankan) {
            return false;
        }
    }
    if (status->currentPlayer == JICHA) {
        return true;
    } else return false;

}

bool isPinhu(Status *status) {
    if (Possibles->Situations[number].Jyantou[1] != 'z' ||
        (Possibles->Situations[number].Jyantou[1] == 'z' && Possibles->Situations[number].Jyantou[0] - 48 != 5 &&
         Possibles->Situations[number].Jyantou[0] - 48 != 6 && Possibles->Situations[number].Jyantou[0] - 48 != 7 &&
         Possibles->Situations[number].Jyantou[0] - 48 != status->jikaze + 1 &&
         Possibles->Situations[number].Jyantou[0] - 48 != status->bakaze + 1)) {
        if (Possibles->HandGroupLen != 4) {
            return false;
        }

        for (int i = 0; i < 4; i++) {
            if (Possibles->Situations[number].HandGroupTile[i].type != Shuntsu) {
                return false;
            }
        }

        if (status->currentTile[0] == Possibles->Situations[number].Jyantou[0] &&
            status->currentTile[1] == Possibles->Situations[number].Jyantou[1]) {
            return false;
        }

        for (int i = 0; i < 4; i++) {
            if (Possibles->Situations[number].HandGroupTile[i].tile[1] == status->currentTile[1]) {
                if (Possibles->Situations[number].HandGroupTile[i].tile[0] == status->currentTile[0] ||
                    Possibles->Situations[number].HandGroupTile[i].tile[0] == status->currentTile[0] - 2) {
                    if (Possibles->Situations[number].HandGroupTile[i].tile[0] == '1') {
                        if (status->currentTile[0] != '3') {
                            return true;
                        }
                    } else if (Possibles->Situations[number].HandGroupTile[i].tile[0] == '7') {
                        if (status->currentTile[0] != '7') {
                            return true;
                        }
                    } else return true;
                }
            }
        }       //只能两面听

        return false;
    } else return false;
}

bool isIipeikou(Status *status) {
    if (Possibles->HandGroupLen >= 2) {
        int count = 0;
        int matrix[4][10] = {0};

        for (int i = 0; i < Possibles->HandGroupLen; i++) {
            if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu) {
                switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                    case 'm':
                        matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    case 'p':
                        matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    case 's':
                        matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    case 'z':
                        matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    default:;
                }
            }
        }

        for (int i = 0; i <= 2; i++) {
            matrix[i][5] += matrix[i][0];
        }  //转换赤宝牌

        for (int i = 0; i <= 2; i++) {
            for (int j = 1; j <= 7; j++) {
                if (matrix[i][j] >= 2) {
                    count++;
                }
            }
        }

        if (count >= 1) {
            return true;
        } else return false;
    } else return false;
}

bool isSanshokudoukou(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Koutsu || status->groupTile[i].type == Kantsu ||
            status->groupTile[i].type == Ankan) {
            switch (status->groupTile[i].tile[1]) {
                case 'm':
                    matrix[0][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][status->groupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    for (int i = 1; i <= 9; i++) {
        if (matrix[0][i] >= 1 && matrix[1][i] >= 1 && matrix[2][i] >= 1) {
            return true;
        }
    }

    return false;
}

bool isSankantsu(Status *status) {
    int K_num = 0;

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Kantsu || status->groupTile[i].type == Ankan) {
            K_num++;
        }
    }

    if (K_num == 3) {
        return true;
    } else return false;
}

bool isToitoihou(Status *status) {
    int K_num = 0;

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu ||
            Possibles->Situations[number].HandGroupTile[i].type == Kantsu ||
            Possibles->Situations[number].HandGroupTile[i].type == Ankan) {
            K_num++;
        }
    }

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Koutsu || status->groupTile[i].type == Kantsu ||
            status->groupTile[i].type == Ankan) {
            K_num++;
        }
    }

    if (K_num == 4) {
        return true;
    } else return false;
}

bool isSanankou(Status *status) {
    int K_num = 0;

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu ||
            Possibles->Situations[number].HandGroupTile[i].type == Kantsu ||
            Possibles->Situations[number].HandGroupTile[i].type == Ankan) {
            K_num++;
        }
    }

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Ankan) {
            K_num++;
        }
    }

    if (status->currentPlayer != JICHA) {
        switch (status->currentTile[1]) {
            case 'm':
                if (Possibles->AllTiles.matrix[0][status->currentTile[0] - 48] == 3) {
                    K_num--;
                }
                break;
            case 'p':
                if (Possibles->AllTiles.matrix[1][status->currentTile[0] - 48] == 3) {
                    K_num--;
                }
                break;
            case 's':
                if (Possibles->AllTiles.matrix[2][status->currentTile[0] - 48] == 3) {
                    K_num--;
                }
                break;
            case 'z':
                if (Possibles->AllTiles.matrix[3][status->currentTile[0] - 48] == 3) {
                    K_num--;
                }
                break;
            default:;
        }
    }

    if (K_num == 3) {
        return true;
    } else return false;
}

bool isShousangen(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Koutsu || status->groupTile[i].type == Kantsu ||
            status->groupTile[i].type == Ankan) {
            switch (status->groupTile[i].tile[1]) {
                case 'm':
                    matrix[0][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][status->groupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    if (Possibles->Situations[number].Jyantou[1] == 'z') {
        if (Possibles->Situations[number].Jyantou[0] == '5' && matrix[3][6] >= 1 && matrix[3][7] >= 1) {
            return true;
        } else if (matrix[3][5] >= 1 && Possibles->Situations[number].Jyantou[0] == '6' && matrix[3][7] >= 1) {
            return true;
        } else if (matrix[3][5] >= 1 && matrix[3][6] >= 1 && Possibles->Situations[number].Jyantou[0] == '7') {
            return true;
        }
    }

    return false;
}

bool isHonroutou(Status *status) {
    for (int i = 0; i <= 2; i++) {
        for (int j = 2; j <= 8; j++) {
            if (Possibles->AllTiles.matrix[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool isChiitoitsu(Status *status) {
    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Possibles->AllTiles.matrix[i][j] != 0 && Possibles->AllTiles.matrix[i][j] != 2) {
                return false;
            }
        }
    }
    return true;
}

bool isHonchantaiyaochuu(Status *status) {
    if ((Possibles->Situations[number].Jyantou[1] == 'z') ||
        ((Possibles->Situations[number].Jyantou[0] == '1' || Possibles->Situations[number].Jyantou[0] == '9') &&
         (Possibles->Situations[number].Jyantou[1] == 'm' || Possibles->Situations[number].Jyantou[0] == 'p' ||
          Possibles->Situations[number].Jyantou[0] == 's'))) {
        if (isToitoihou(status) == false) {
            for (int i = 0; i < Possibles->HandGroupLen; i++) {
                if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
                    (Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                     Possibles->Situations[number].HandGroupTile[i].tile[0] != '7')) {
                    return false;
                } else if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
                    if (Possibles->Situations[number].HandGroupTile[i].tile[1] == 'm' ||
                        Possibles->Situations[number].HandGroupTile[i].tile[1] == 'p' ||
                        Possibles->Situations[number].HandGroupTile[i].tile[1] == 's') {
                        if (Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                            Possibles->Situations[number].HandGroupTile[i].tile[0] != '9') {
                            return false;
                        }
                    }
                }
            }
            for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
                if (status->groupTile[i].type != Ankan) {
                    return false;
                } else if (status->groupTile[i].tile[1] == 'm' || status->groupTile[i].tile[1] == 'p' ||
                           status->groupTile[i].tile[1] == 's') {
                    if (status->groupTile[i].tile[0] != '1' && status->groupTile[i].tile[0] != '9') {
                        return false;
                    }
                }
            }

            return true;
        }
    }
    return false;
}

bool isHonchantaiyaochuuF(Status *status) {
    if ((Possibles->Situations[number].Jyantou[1] == 'z') ||
        ((Possibles->Situations[number].Jyantou[0] == '1' || Possibles->Situations[number].Jyantou[0] == '9') &&
         (Possibles->Situations[number].Jyantou[1] == 'm' || Possibles->Situations[number].Jyantou[0] == 'p' ||
          Possibles->Situations[number].Jyantou[0] == 's'))) {
        if (isToitoihou(status) == false) {
            for (int i = 0; i < Possibles->HandGroupLen; i++) {
                if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] != '7') {
                    return false;
                } else if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
                    if (Possibles->Situations[number].HandGroupTile[i].tile[1] == 'm' ||
                        Possibles->Situations[number].HandGroupTile[i].tile[1] == 'p' ||
                        Possibles->Situations[number].HandGroupTile[i].tile[1] == 's') {
                        if (Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                            Possibles->Situations[number].HandGroupTile[i].tile[0] != '9') {
                            return false;
                        }
                    }
                }
            }
            for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
                if (status->groupTile[i].type == Shuntsu && status->groupTile[i].tile[0] != '1' &&
                    status->groupTile[i].tile[0] != '7') {
                    return false;
                } else if (status->groupTile[i].type == Ankan || status->groupTile[i].type == Koutsu ||
                           status->groupTile[i].type == Kantsu) {
                    if (status->groupTile[i].tile[1] == 'm' || status->groupTile[i].tile[1] == 'p' ||
                        status->groupTile[i].tile[1] == 's') {
                        if (status->groupTile[i].tile[0] != '1' && status->groupTile[i].tile[0] != '9') {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
    }
    return false;
}

bool isIkkitsuukan(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    for (int i = 0; i <= 2; i++) {
        if (matrix[i][1] >= 1 && matrix[i][4] >= 1 && matrix[i][7] >= 1) {
            return true;
        }
    }

    return false;
}

bool isIkkitsuukanF(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Shuntsu) {
            switch (status->groupTile[i].tile[1]) {
                case 'm':
                    matrix[0][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][status->groupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    for (int i = 0; i <= 2; i++) {
        if (matrix[i][1] >= 1 && matrix[i][4] >= 1 && matrix[i][7] >= 1) {
            return true;
        }
    }

    return false;
}

bool isSanshokudoujun(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    for (int i = 1; i <= 7; i++) {
        if (matrix[0][i] >= 1 && matrix[1][i] >= 1 && matrix[2][i] >= 1) {
            return true;
        }
    }
    return false;
}

bool isSanshokudoujunF(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Shuntsu) {
            switch (status->groupTile[i].tile[1]) {
                case 'm':
                    matrix[0][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][status->groupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    for (int i = 1; i <= 7; i++) {
        if (matrix[0][i] >= 1 && matrix[1][i] >= 1 && matrix[2][i] >= 1) {
            return true;
        }
    }
    return false;
}

bool isRyanpeikou(Status *status) {
    if (Possibles->HandGroupLen == 4) {
        int count = 0;
        int matrix[4][10] = {0};

        for (int i = 0; i < Possibles->HandGroupLen; i++) {
            if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu) {
                switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                    case 'm':
                        matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    case 'p':
                        matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    case 's':
                        matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    case 'z':
                        matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                        break;
                    default:;
                }
            }
        }

        for (int i = 0; i <= 2; i++) {
            matrix[i][5] += matrix[i][0];
        }  //转换赤宝牌

        for (int i = 0; i <= 2; i++) {
            for (int j = 1; j <= 7; j++) {
                if (matrix[i][j] >= 4) {
                    count += 2;
                } else if (matrix[i][j] >= 2) {
                    count++;
                }
            }
        }

        if (count >= 2) {
            return true;
        } else return false;
    } else return false;
}

bool isJunchantaiyaochuu(Status *status) {
    if ((Possibles->Situations[number].Jyantou[0] == '1' || Possibles->Situations[number].Jyantou[0] == '9') &&
        (Possibles->Situations[number].Jyantou[1] == 'm' || Possibles->Situations[number].Jyantou[0] == 'p' ||
         Possibles->Situations[number].Jyantou[0] == 's')) {
        if (isToitoihou(status) == false) {
            for (int i = 0; i < Possibles->HandGroupLen; i++) {
                if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] != '7') {
                    return false;
                } else if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
                    if (Possibles->Situations[number].HandGroupTile[i].tile[1] == 'z') {
                        return false;
                    } else if (Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                               Possibles->Situations[number].HandGroupTile[i].tile[0] != '9') {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
                if (status->groupTile[i].type != Ankan) {
                    return false;
                } else {
                    if (status->groupTile[i].tile[1] == 'z') {
                        return false;
                    } else if (status->groupTile[i].tile[0] != '1' && status->groupTile[i].tile[0] != '9') {
                        return false;
                    }
                }
            }

            return true;
        }
    }
    return false;
}

bool isJunchantaiyaochuuF(Status *status) {
    if ((Possibles->Situations[number].Jyantou[0] == '1' || Possibles->Situations[number].Jyantou[0] == '9') &&
        (Possibles->Situations[number].Jyantou[1] == 'm' || Possibles->Situations[number].Jyantou[0] == 'p' ||
         Possibles->Situations[number].Jyantou[0] == 's')) {
        if (isToitoihou(status) == false) {
            for (int i = 0; i < Possibles->HandGroupLen; i++) {
                if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] != '7') {
                    return false;
                } else if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
                    if (Possibles->Situations[number].HandGroupTile[i].tile[1] == 'z') {
                        return false;
                    } else if (Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
                               Possibles->Situations[number].HandGroupTile[i].tile[0] != '9') {
                        return false;
                    }
                }
            }
            for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
                if (status->groupTile[i].type == Shuntsu && status->groupTile[i].tile[0] != '1' &&
                    status->groupTile[i].tile[0] != '7') {
                    return false;
                } else if (status->groupTile[i].type == Ankan || status->groupTile[i].type == Koutsu ||
                           status->groupTile[i].type == Kantsu) {
                    if (status->groupTile[i].tile[1] == 'z') {
                        return false;
                    } else if (status->groupTile[i].tile[0] != '1' && status->groupTile[i].tile[0] != '9') {
                        return false;
                    }
                }
            }

            return true;
        }
    }
    return false;
}

bool isHonitsu(Status *status) {
    if ((Possibles->AllTiles.z_num + Possibles->AllTiles.m_num >= 14 && Possibles->AllTiles.p_num == 0 &&
         Possibles->AllTiles.s_num == 0) ||
        (Possibles->AllTiles.z_num + Possibles->AllTiles.p_num >= 14 && Possibles->AllTiles.m_num == 0 &&
         Possibles->AllTiles.s_num == 0) ||
        (Possibles->AllTiles.z_num + Possibles->AllTiles.s_num >= 14 && Possibles->AllTiles.m_num == 0 &&
         Possibles->AllTiles.p_num == 0)) {
        for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
            if (status->groupTile[i].type != Ankan) {
                return false;
            }
        }
        return true;
    } else return false;
}

bool isHonitsuF(Status *status) {
    if ((Possibles->AllTiles.z_num + Possibles->AllTiles.m_num >= 14 && Possibles->AllTiles.p_num == 0 &&
         Possibles->AllTiles.s_num == 0) ||
        (Possibles->AllTiles.z_num + Possibles->AllTiles.p_num >= 14 && Possibles->AllTiles.m_num == 0 &&
         Possibles->AllTiles.s_num == 0) ||
        (Possibles->AllTiles.z_num + Possibles->AllTiles.s_num >= 14 && Possibles->AllTiles.m_num == 0 &&
         Possibles->AllTiles.p_num == 0)) {
        return true;
    } else return false;
}

bool isChinitsu(Status *status) {
    if ((Possibles->AllTiles.m_num >= 14 && Possibles->AllTiles.p_num == 0 && Possibles->AllTiles.s_num == 0 &&
         Possibles->AllTiles.z_num == 0) ||
        (Possibles->AllTiles.p_num >= 14 && Possibles->AllTiles.m_num == 0 && Possibles->AllTiles.s_num == 0 &&
         Possibles->AllTiles.z_num == 0) ||
        (Possibles->AllTiles.s_num >= 14 && Possibles->AllTiles.m_num == 0 && Possibles->AllTiles.p_num == 0 &&
         Possibles->AllTiles.z_num == 0)) {
        for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
            if (status->groupTile[i].type != Ankan) {
                return false;
            }
        }
        return true;
    } else return false;
}

bool isChinitsuF(Status *status) {
    if ((Possibles->AllTiles.m_num >= 14 && Possibles->AllTiles.p_num == 0 && Possibles->AllTiles.s_num == 0 &&
         Possibles->AllTiles.z_num == 0) ||
        (Possibles->AllTiles.p_num >= 14 && Possibles->AllTiles.m_num == 0 && Possibles->AllTiles.s_num == 0 &&
         Possibles->AllTiles.z_num == 0) ||
        (Possibles->AllTiles.s_num >= 14 && Possibles->AllTiles.m_num == 0 && Possibles->AllTiles.p_num == 0 &&
         Possibles->AllTiles.z_num == 0)) {
        return true;
    } else return false;
}

bool isDaisangen(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
            switch (Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][Possibles->Situations[number].HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Koutsu || status->groupTile[i].type == Kantsu ||
            status->groupTile[i].type == Ankan) {
            switch (status->groupTile[i].tile[1]) {
                case 'm':
                    matrix[0][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][status->groupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][status->groupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        matrix[i][5] += matrix[i][0];
    }  //转换赤宝牌

    if (matrix[3][5] >= 1 && matrix[3][6] >= 1 && matrix[3][7] >= 1) {
        return true;
    }
    return false;
}

bool isSuuankou(Status *status) {
    int count = 0;

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
            count++;
        }
    }
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Ankan) {
            count++;
        }
    }

    if (count == 4 && status->currentPlayer == JICHA) {
        return true;
    }
    return false;
}

bool isTsuuiisou(Status *status) {
    if (Possibles->AllTiles.z_num >= 14 && Possibles->AllTiles.m_num == 0 && Possibles->AllTiles.p_num == 0 &&
        Possibles->AllTiles.s_num == 0) {
        return true;
    } else return false;
}

bool isRyuuiisou(Status *status) {
    if (Possibles->AllTiles.matrix[2][2] + Possibles->AllTiles.matrix[2][3] + Possibles->AllTiles.matrix[2][4] +
        Possibles->AllTiles.matrix[2][6] + Possibles->AllTiles.matrix[2][8] +
        Possibles->AllTiles.matrix[3][6] ==
        Possibles->AllTiles.m_num + Possibles->AllTiles.p_num + Possibles->AllTiles.s_num + Possibles->AllTiles.z_num) {
        return true;
    } else return false;
}

bool isChinroutou(Status *status) {
    if (Possibles->AllTiles.matrix[0][1] + Possibles->AllTiles.matrix[0][9] + Possibles->AllTiles.matrix[1][1] +
        Possibles->AllTiles.matrix[1][9] + Possibles->AllTiles.matrix[2][1] +
        Possibles->AllTiles.matrix[2][9] ==
        Possibles->AllTiles.m_num + Possibles->AllTiles.p_num + Possibles->AllTiles.s_num + Possibles->AllTiles.z_num) {
        return true;
    } else return false;
}

bool isKokushimusou(Status *status) {
    if (Possibles->AllTiles.matrix[0][1] >= 1 && Possibles->AllTiles.matrix[0][9] >= 1 &&
        Possibles->AllTiles.matrix[1][1] >= 1 && Possibles->AllTiles.matrix[1][9] >= 1 &&
        Possibles->AllTiles.matrix[2][1] >= 1 && Possibles->AllTiles.matrix[2][9] >= 1 &&
        Possibles->AllTiles.matrix[3][1] >= 1 && Possibles->AllTiles.matrix[3][2] >= 1 &&
        Possibles->AllTiles.matrix[3][3] >= 1 && Possibles->AllTiles.matrix[3][4] >= 1 &&
        Possibles->AllTiles.matrix[3][5] >= 1 && Possibles->AllTiles.matrix[3][6] >= 1 &&
        Possibles->AllTiles.matrix[3][7] >= 1) {
        return true;
    } else return false;
}

bool isKokushijuusanmenmachi(Status *status) {
    if (isKokushimusou(status)) {
        switch (status->currentTile[1]) {
            case 'm':
                if (Possibles->AllTiles.matrix[0][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            case 'p':
                if (Possibles->AllTiles.matrix[1][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            case 's':
                if (Possibles->AllTiles.matrix[2][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            case 'z':
                if (Possibles->AllTiles.matrix[3][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            default:;
        }
        return false;
    } else return false;
}

bool isShousuushi(Status *status) {
    if (Possibles->AllTiles.matrix[3][1] >= 2 && Possibles->AllTiles.matrix[3][2] >= 3 &&
        Possibles->AllTiles.matrix[3][3] >= 3 &&
        Possibles->AllTiles.matrix[3][4] >= 3) {
        return true;
    } else if (Possibles->AllTiles.matrix[3][1] >= 3 && Possibles->AllTiles.matrix[3][2] >= 2 &&
               Possibles->AllTiles.matrix[3][3] >= 3 &&
               Possibles->AllTiles.matrix[3][4] >= 3) {
        return true;
    } else if (Possibles->AllTiles.matrix[3][1] >= 3 && Possibles->AllTiles.matrix[3][2] >= 3 &&
               Possibles->AllTiles.matrix[3][3] >= 2 &&
               Possibles->AllTiles.matrix[3][4] >= 3) {
        return true;
    } else if (Possibles->AllTiles.matrix[3][1] >= 3 && Possibles->AllTiles.matrix[3][2] >= 3 &&
               Possibles->AllTiles.matrix[3][3] >= 3 &&
               Possibles->AllTiles.matrix[3][4] >= 2) {
        return true;
    } else return false;
}

bool isDaisuushi(Status *status) {
    if (Possibles->AllTiles.matrix[3][1] >= 3 && Possibles->AllTiles.matrix[3][2] >= 3 &&
        Possibles->AllTiles.matrix[3][3] >= 3 &&
        Possibles->AllTiles.matrix[3][4] >= 3) {
        return true;
    } else return false;
}

bool isSuukantsu(Status *status) {
    if (Possibles->HandGroupLen == 0) {
        for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
            if (status->groupTile[i].type != Ankan && status->groupTile[i].type != Kantsu) {
                return false;
            }
        }
        return true;
    } else return false;
}

bool isChuurenpoutou(Status *status) {
    for (int i = 0; i < 3; i++) {
        if (isMenzenchin(status) &&
            Possibles->AllTiles.matrix[i][1] >= 3 && Possibles->AllTiles.matrix[i][9] >= 3 &&
            Possibles->AllTiles.matrix[i][2] >= 1 && Possibles->AllTiles.matrix[i][3] >= 1 &&
            Possibles->AllTiles.matrix[i][4] >= 1 && Possibles->AllTiles.matrix[i][5] >= 1 &&
            Possibles->AllTiles.matrix[i][6] >= 1 && Possibles->AllTiles.matrix[i][7] >= 1 &&
            Possibles->AllTiles.matrix[i][8] >= 1) {
            return true;
        }
    }
    return false;
}

bool isChuurenkyuumenmachi(Status *status) {
    for (int i = 0; i < 3; i++) {
        if (isMenzenchin(status) &&
            Possibles->AllTiles.matrix[i][1] >= 3 && Possibles->AllTiles.matrix[i][9] >= 3 &&
            Possibles->AllTiles.matrix[i][2] >= 1 && Possibles->AllTiles.matrix[i][3] >= 1 &&
            Possibles->AllTiles.matrix[i][4] >= 1 && Possibles->AllTiles.matrix[i][5] >= 1 &&
            Possibles->AllTiles.matrix[i][6] >= 1 && Possibles->AllTiles.matrix[i][7] >= 1 &&
            Possibles->AllTiles.matrix[i][8] >= 1) {
            switch (status->currentTile[1]) {
                case 'm':
                    if (Possibles->AllTiles.matrix[0][status->currentTile[0] - 48] == 2 ||
                        Possibles->AllTiles.matrix[0][status->currentTile[0] - 48] == 4) {
                        return true;
                    }
                    break;
                case 'p':
                    if (Possibles->AllTiles.matrix[1][status->currentTile[0] - 48] == 2 ||
                        Possibles->AllTiles.matrix[1][status->currentTile[0] - 48] == 4) {
                        return true;
                    }
                    break;
                case 's':
                    if (Possibles->AllTiles.matrix[2][status->currentTile[0] - 48] == 2 ||
                        Possibles->AllTiles.matrix[2][status->currentTile[0] - 48] == 4) {
                        return true;
                    }
                    break;
                default:;
            }
        }
    }
    return false;
}

bool isSuuankoutanki(Status *status) {
    int count = 0;

    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu) {
            count++;
        }
    }
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Ankan) {
            count++;
        }
    }

    if (count == 4) {
        switch (status->currentTile[1]) {
            case 'm':
                if (Possibles->AllTiles.matrix[0][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            case 'p':
                if (Possibles->AllTiles.matrix[1][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            case 's':
                if (Possibles->AllTiles.matrix[2][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            case 'z':
                if (Possibles->AllTiles.matrix[3][status->currentTile[0] - 48] == 2) {
                    return true;
                }
                break;
            default:;
        }
    }
    return false;
}