#include "YakuChecker.h"

extern char Pair[4];
extern Group HandGroupTile[6];
AllHand Hands;
int HandGroupLen;

Yaku *checkYaku(Status *status) {
    Yaku *yaku = malloc(20 * sizeof(*yaku));
    int count = 0;
    Hands = StatisticsAll(status);
    HandGroupLen = ((int) strlen(status->handTile) - 1) / 3;

    if (status->isRiichi) {
        yaku[count] = Riichi;
        count++;
    }   //立直
    if (status->isIppatsu) {
        yaku[count] = Ippatsu;
        count++;
    }   //一发
    if (strlen(status->handTile) == 26 && status->currentPlayer == JICHA) {
        yaku[count] = Menzenchintsumo;
        count++;
    }
    if (Hands.matrix[0][1] == 0 && Hands.matrix[0][9] == 0 && Hands.matrix[1][1] == 0 && Hands.matrix[1][9] == 0 &&
        Hands.matrix[2][1] && Hands.matrix[2][9] && Hands.z_num == 0) {
        yaku[count] = Tanyao;
        count++;
    }
    if (Hands.matrix[3][status->jikaze + 1] >= 3) {
        yaku[count] = YakuhaiJikaze;
        count++;
    }
    if (Hands.matrix[3][status->bakaze + 1] >= 3) {
        yaku[count] = YakuhaiBakaze;
        count++;
    }
    if (Hands.matrix[3][5] >= 3) {
        yaku[count] = YakuhaiHaku;
        count++;
    }
    if (Hands.matrix[3][6] >= 3) {
        yaku[count] = YakuhaiHatsu;
        count++;
    }
    if (Hands.matrix[3][7] >= 3) {
        yaku[count] = YakuhaiChun;
        count++;
    }
    if (isPinhu(status)) {
        yaku[count] = Pinhu;
        count++;
    }
    if (isIipeikou(status)) {
        yaku[count] = Iipeikou;
        count++;
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
    if (isToitoihou(status)) {
        yaku[count] = Toitoihou;
        count++;
    }
    if (isSanankou(status)) {
        yaku[count] = Sanankou;
        count++;
    }
    if (isShousangen(status)) {
        yaku[count] = Shousangen;
        count++;
    }
    if (isHonroutou(status)) {
        yaku[count] = Honroutou;
        count++;
    }
    if (isChiitoitsu(status)) {
        yaku[count] = Chiitoitsu;
        count++;
    }

    {
        if (isHonchantaiyaochuu(status)) {
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
        if (isHonitsu(status)) {
            yaku[count] = Honitsu;
            count++;
        } else if (isHonitsuF(status)) {
            yaku[count] = HonitsuF;
            count++;
        }
    }


    return yaku;
}

AllHand StatisticsAll(Status *status) {
    AllHand hands = {
            .matrix = {0},
            .m_num = 0,
            .p_num = 0,
            .s_num = 0,
            .z_num = 0,
    };

    switch (status->currentTile[1]) {
        case 'm':
            hands.matrix[0][status->currentTile[0] - 48]++;
            hands.m_num++;
            break;
        case 'p':
            hands.matrix[1][status->currentTile[0] - 48]++;
            hands.p_num++;
            break;
        case 's':
            hands.matrix[2][status->currentTile[0] - 48]++;
            hands.s_num++;
            break;
        case 'z':
            hands.matrix[3][status->currentTile[0] - 48]++;
            hands.z_num++;
            break;
        default:;
    }   //当前控牌

    for (int i = 0; i < 15 && status->handTile[2 * i] != '\0'; i++) {
        switch (status->handTile[2 * i + 1]) {
            case 'm':
                hands.matrix[0][status->handTile[2 * i] - 48]++;
                hands.m_num++;
                break;
            case 'p':
                hands.matrix[1][status->handTile[2 * i] - 48]++;
                hands.p_num++;
                break;
            case 's':
                hands.matrix[2][status->handTile[2 * i] - 48]++;
                hands.s_num++;
                break;
            case 'z':
                hands.matrix[3][status->handTile[2 * i] - 48]++;
                hands.z_num++;
                break;
            default:;
        }
    }   //手牌

    for (int i = 0; i < 19; i++) {
        for (int j = 0; j <= 10 && status->groupTile[i].tile[2 * j + 1] != 0; j++) {
            switch (status->groupTile[i].tile[2 * j + 1]) {
                case 'm':
                    hands.matrix[0][status->groupTile[i].tile[2 * j] - 48]++;
                    hands.m_num++;
                    break;
                case 'p':
                    hands.matrix[1][status->groupTile[i].tile[2 * j] - 48]++;
                    hands.p_num++;
                    break;
                case 's':
                    hands.matrix[2][status->groupTile[i].tile[2 * j] - 48]++;
                    hands.s_num++;
                    break;
                case 'z':
                    hands.matrix[3][status->groupTile[i].tile[2 * j] - 48]++;
                    hands.z_num++;
                    break;
                default:;
            }
        }
    }   //副露牌

    for (int i = 0; i <= 2; i++) {
        hands.matrix[i][5] += hands.matrix[i][0];
    }  //转换赤宝牌

    return hands;
}

bool isPinhu(Status *status) {
    if (Pair[1] != 'z') {
        for (int i = 0; i < HandGroupLen; i++) {
            if (HandGroupTile[i].type != Shuntsu || HandGroupTile[i].tile[1] == 'z') {
                return false;
            }
        }
        for (int i = 0; i < 4 - HandGroupLen; i++) {
            if (status->groupTile[i].type != Shuntsu || status->groupTile[i].tile[1] == 'z') {
                return false;
            }
        }
        return true;
    } else return false;
}

bool isIipeikou(Status *status) {
    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Shuntsu) {
            for (int j = i + 1; j < HandGroupLen; j++) {
                if (HandGroupTile[j].type == Shuntsu && HandGroupTile[i].tile[0] == HandGroupTile[j].tile[0] &&
                    HandGroupTile[i].tile[1] == HandGroupTile[j].tile[1]) {
                    return true;
                }
                for (int k = 0; k < 4 - HandGroupLen; k++) {
                    if (HandGroupTile[k].type == Shuntsu && HandGroupTile[i].tile[0] == HandGroupTile[k].tile[0] &&
                        HandGroupTile[i].tile[1] == HandGroupTile[k].tile[1]) {
                        return true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4 - HandGroupLen; i++) {
        if (status->groupTile[i].type == Shuntsu) {
            for (int j = i + 1; j < 4 - HandGroupLen; j++) {
                if (status->groupTile[j].type == Shuntsu &&
                    status->groupTile[i].tile[0] == status->groupTile[j].tile[0] &&
                    status->groupTile[i].tile[1] == status->groupTile[j].tile[1]) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool isSanshokudoukou(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Koutsu || HandGroupTile[i].type == Kantsu) {
            switch (HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - HandGroupLen; i++) {
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
        if (matrix[0][i] == 1 && matrix[1][i] == 1 && matrix[2][i] == 1) {
            return true;
        }
    }

    return false;
}

bool isSankantsu(Status *status) {
    int K_num = 0;

    for (int i = 0; i < 4 - HandGroupLen; i++) {
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

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Koutsu || HandGroupTile[i].type == Kantsu ||
            HandGroupTile[i].type == Ankan) {
            K_num++;
        }
    }

    for (int i = 0; i < 4 - HandGroupLen; i++) {
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

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Koutsu || HandGroupTile[i].type == Kantsu ||
            HandGroupTile[i].type == Ankan) {
            K_num++;
        }
    }

    for (int i = 0; i < 4 - HandGroupLen; i++) {
        if (status->groupTile[i].type == Ankan) {
            K_num++;
        }
    }

    if (K_num == 3) {
        return true;
    } else return false;
}

bool isShousangen(Status *status) {
    int San_num = 0;
    if (Pair[1] == 'z') {
        if (Pair[0] == '5') {
            for (int i = 0; i < HandGroupLen; i++) {
                if (HandGroupTile[i].type == Koutsu || HandGroupTile[i].type == Kantsu ||
                    HandGroupTile[i].type == Ankan) {
                    if (HandGroupTile[i].tile[1] == 'z') {
                        if (HandGroupTile[i].tile[0] == '5' || HandGroupTile[i].tile[0] == '6' ||
                            HandGroupTile[i].tile[0] == '7') {
                            San_num++;
                        }
                    }
                }
            }

            for (int i = 0; i < 4 - HandGroupLen; i++) {
                if (status->groupTile[i].type == Koutsu || status->groupTile[i].type == Kantsu ||
                    status->groupTile[i].type == Ankan) {
                    if (status->groupTile[i].tile[1] == 'z') {
                        if (status->groupTile[i].tile[0] == '5' || status->groupTile[i].tile[0] == '6' ||
                            status->groupTile[i].tile[0] == '7') {
                            San_num++;
                        }
                    }
                }
            }
        }

        if (San_num == 2) {
            return true;
        } else return false;
    } else return false;
}

bool isHonroutou(Status *status) {
    for (int i = 0; i <= 2; i++) {
        for (int j = 2; j <= 8; j++) {
            if (Hands.matrix[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool isChiitoitsu(Status *status) {
    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Hands.matrix[i][j] != 0 && Hands.matrix[i][j] != 2) {
                return false;
            }
        }
    }
    return true;
}

bool isHonchantaiyaochuu(Status *status) {
    if ((Pair[1] == 'z') ||
        ((Pair[0] == '1' || Pair[0] == '9') && (Pair[1] == 'm' || Pair[0] == 'p' || Pair[0] == 's'))) {
        if (isToitoihou(status) == false) {
            for (int i = 0; i < HandGroupLen; i++) {
                if (HandGroupTile[i].type == Shuntsu &&
                    (HandGroupTile[i].tile[0] != '1' && HandGroupTile[i].tile[0] != '7')) {
                    return false;
                } else if (HandGroupTile[i].type == Koutsu) {
                    if (HandGroupTile[i].tile[1] == 'm' || HandGroupTile[i].tile[1] == 'p' ||
                        HandGroupTile[i].tile[1] == 's') {
                        if (HandGroupTile[i].tile[0] != '1' && HandGroupTile[i].tile[0] != '9') {
                            return false;
                        }
                    }
                }
            }
            for (int i = 0; i < 4 - HandGroupLen; i++) {
                if (status->groupTile[i].type == Koutsu || status->groupTile[i].type == Kantsu ||
                    status->groupTile[i].type == Shuntsu) {
                    return false;
                } else if (status->groupTile[i].type == Ankan) {
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

bool isHonchantaiyaochuuF(Status *status) {
    if ((Pair[1] == 'z') ||
        ((Pair[0] == '1' || Pair[0] == '9') && (Pair[1] == 'm' || Pair[0] == 'p' || Pair[0] == 's'))) {
        if (isToitoihou(status) == false) {
            for (int i = 0; i < HandGroupLen; i++) {
                if (HandGroupTile[i].type == Shuntsu && HandGroupTile[i].tile[0] != '1' && \
                    HandGroupTile[i].tile[0] != '7') {
                    return false;
                } else if (HandGroupTile[i].type == Koutsu) {
                    if (HandGroupTile[i].tile[1] == 'm' || HandGroupTile[i].tile[1] == 'p' || \
                        HandGroupTile[i].tile[1] == 's') {
                        if (HandGroupTile[i].tile[0] != '1' && HandGroupTile[i].tile[0] != '9') {
                            return false;
                        }
                    }
                }
            }
            for (int i = 0; i < 4 - HandGroupLen; i++) {
                if (status->groupTile[i].type == Shuntsu && status->groupTile[i].tile[0] != '1' && \
                    status->groupTile[i].tile[0] != '7') {
                    return false;
                } else if (status->groupTile[i].type == Ankan || status->groupTile[i].type == Koutsu || \
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

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Shuntsu) {
            switch (HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][HandGroupTile[i].tile[0] - 48]++;
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

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Shuntsu) {
            switch (HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - HandGroupLen; i++) {
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

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Shuntsu) {
            switch (HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - HandGroupLen; i++) {
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

bool isSanshokudoujunF(Status *status) {
    int matrix[4][10] = {0};

    for (int i = 0; i < HandGroupLen; i++) {
        if (HandGroupTile[i].type == Shuntsu) {
            switch (HandGroupTile[i].tile[1]) {
                case 'm':
                    matrix[0][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'p':
                    matrix[1][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 's':
                    matrix[2][HandGroupTile[i].tile[0] - 48]++;
                    break;
                case 'z':
                    matrix[3][HandGroupTile[i].tile[0] - 48]++;
                    break;
                default:;
            }
        }
    }
    for (int i = 0; i < 4 - HandGroupLen; i++) {
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

bool isHonitsu(Status *status) {
    if ((Hands.z_num + Hands.m_num == 14) || (Hands.z_num + Hands.p_num == 14) || (Hands.z_num + Hands.s_num == 14)) {
        for (int i = 0; i < 4 - HandGroupLen; i++) {
            if (status->groupTile[i].type != Ankan) {
                return false;
            }
        }
        return true;
    } else return false;
}

bool isHonitsuF(Status *status) {
    if ((Hands.z_num + Hands.m_num == 14) || (Hands.z_num + Hands.p_num == 14) || (Hands.z_num + Hands.s_num == 14)) {
        return true;
    } else return false;
}