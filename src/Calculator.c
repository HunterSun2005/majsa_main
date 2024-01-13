#include "Calculator.h"

int calHan(Status *status, Yaku *yaku, Possible *Possibles) {
    int Han = 0;

    for (int i = 0; i < 20 && yaku[i] != 0; i++) {
        if (yaku[i] / 256 == 13) {
            Han += -1;
        } else if (yaku[i] / 256 == 15) {
            Han += -2;
        } else Han += (int) (yaku[i] / 256);
    }
    if (Han < 0) {
        return Han;
    }

    for (int i = 0; i <= 5 && status->dora[2 * i + 1] != 0; i++) {
        switch (status->dora[2 * i + 1]) {
            case 'm':
                Han += Possibles->AllTiles.matrix[0][status->dora[2 * i] - 48];
                break;
            case 'p':
                Han += Possibles->AllTiles.matrix[1][status->dora[2 * i] - 48];
                break;
            case 's':
                Han += Possibles->AllTiles.matrix[2][status->dora[2 * i] - 48];
                break;
            case 'z':
                Han += Possibles->AllTiles.matrix[3][status->dora[2 * i] - 48];
                break;
            default:;
        }
    }

    if (status->isRiichi == true) {
        for (int i = 0; i <= 5 && status->uradora[2 * i + 1] != 0; i++) {
            switch (status->uradora[2 * i + 1]) {
                case 'm':
                    Han += Possibles->AllTiles.matrix[0][status->uradora[2 * i] - 48];
                    break;
                case 'p':
                    Han += Possibles->AllTiles.matrix[1][status->uradora[2 * i] - 48];
                    break;
                case 's':
                    Han += Possibles->AllTiles.matrix[2][status->uradora[2 * i] - 48];
                    break;
                case 'z':
                    Han += Possibles->AllTiles.matrix[3][status->uradora[2 * i] - 48];
                    break;
                default:;
            }
        }
    }

    for (int i = 0; i <= 2; i++) {
        Han += Possibles->AllTiles.matrix[i][0];
    }

    return Han;
}

int calFu(Status *status, int Han, Possible *Possibles, int number) {
    int Fu = 20;
    if (Han < 0 || Han >= 13) {
        return 0;
    } else if (CheckChiitoitsu(status, Possibles->HandTiles, Possibles)) {
        return 25;
    } else if (isPinhu(status) && status->currentPlayer == JICHA) {
        return 20;
    } else {
        if (isMenzenchin(status)) {
            Fu += 10;
        }
        if (status->currentPlayer == JICHA) {
            Fu += 2;
        }

        {
            if (isDanqi(status, Possibles, number)) {
                Fu += 2;
            } else if (isBianzhang(status, Possibles, number)) {
                Fu += 2;
            } else if (isQianzhang(status, Possibles, number)) {
                Fu += 2;
            }
        }

        Fu += 2 * CountZZMK(status, Possibles, number);

        Fu += 4 * CountZZAK(status, Possibles, number);

        Fu += 8 * CountZZMG(status, Possibles, number);

        Fu += 16 * CountZZAG(status, Possibles, number);

        Fu += 4 * Count19MK(status, Possibles, number);

        Fu += 8 * Count19AK(status, Possibles, number);

        Fu += 16 * Count19MG(status, Possibles, number);

        Fu += 32 * Count19AG(status, Possibles, number);

        if (isLFQT(status, Possibles, number)) {
            Fu += 4;
        } else if (isYPQT(status, Possibles, number)) {
            Fu += 2;
        }

        if (isChi(status, Possibles) && Fu == 20) {
            return 30;
        }

        if (Fu % 10 != 0) {
            Fu -= Fu % 10;
            Fu += 10;
        }

        return Fu;
    }
}

int calPoint(Status *status, int Han, int Fu) {
    int point = 0;
    if (status->bakaze == status->jikaze) {
        if (Han == -1) {
            return 48000;
        }
        if (Han == -2) {
            return 96000;
        }

        point = 6 * Fu * (int) pow(2, Han + 2);
        if (Han < 6) {
            if (point <= 12000) {
                return point;
            } else return 12000;
        } else if (Han == 6 || Han == 7) {
            return 18000;
        } else if (Han == 8 || Han == 9 || Han == 10) {
            return 24000;
        } else if (Han == 11 || Han == 12) {
            return 36000;
        } else if (Han > 12) {
            return 48000;
        }
        return -1;
    } else {
        if (Han == -1) {
            return 32000;
        }
        if (Han == -2) {
            return 64000;
        }

        point = 4 * Fu * (int) pow(2, Han + 2);
        if (Han < 6) {
            if (point <= 8000) {
                return point;
            } else return 8000;
        } else if (Han == 6 || Han == 7) {
            return 12000;
        } else if (Han == 8 || Han == 9 || Han == 10) {
            return 16000;
        } else if (Han == 11 || Han == 12) {
            return 24000;
        } else if (Han > 12) {
            return 32000;
        }
        return -1;
    }
}

bool isChi(Status *status, Possible *Possibles) {
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Shuntsu) {
            return true;
        }
    }
    return false;
}

int MarkMK(Status *status, Possible *Possibles, int number) {
    int count = 0;
    if (status->currentPlayer != JICHA) {
        for (int i = 0; i < Possibles->HandGroupLen; i++) {
            if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu &&
                Possibles->Situations[number].HandGroupTile[i].tile[0] == status->currentTile[0] &&
                Possibles->Situations[number].HandGroupTile[i].tile[1] == status->currentTile[1]) {
                switch (status->currentTile[1]) {
                    case 'm':
                        if (Possibles->HandTiles.matrix[0][status->currentTile[0] - 48] == 3) {
                            count++;
                        }
                        break;
                    case 'p':
                        if (Possibles->HandTiles.matrix[1][status->currentTile[0] - 48] == 3) {
                            count++;
                        }
                        break;
                    case 's':
                        if (Possibles->HandTiles.matrix[2][status->currentTile[0] - 48] == 3) {
                            count++;
                        }
                        break;
                    default:;
                }
            }
        }
    }
    return count;
}

bool isDanqi(Status *status, Possible *Possibles, int number) {
    if (status->currentTile[0] == Possibles->Situations[number].Jyantou[0] &&
        status->currentTile[1] == Possibles->Situations[number].Jyantou[1]) {
        return true;
    } else return false;
}

bool isBianzhang(Status *status, Possible *Possibles, int number) {
    if (status->currentTile[1] != 'z' && (status->currentTile[0] == '3' || status->currentTile[0] == '7')) {
        for (int i = 0; i < Possibles->HandGroupLen; i++) {
            if (status->currentTile[0] == '3') {
                if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] == '1' &&
                    status->currentTile[1] == Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                    return true;
                }
            } else if (status->currentTile[0] == '7') {
                if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
                    Possibles->Situations[number].HandGroupTile[i].tile[0] == '7' &&
                    status->currentTile[1] == Possibles->Situations[number].HandGroupTile[i].tile[1]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isQianzhang(Status *status, Possible *Possibles, int number) {
    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Shuntsu &&
            status->currentTile[0] - 1 == Possibles->Situations[number].HandGroupTile[i].tile[0] &&
            status->currentTile[1] == Possibles->Situations[number].HandGroupTile[i].tile[1]) {
            return true;
        }
    }
    return false;
}

int CountZZMK(Status *status, Possible *Possibles, int number) {
    int count = 0;
    if (status->currentPlayer != JICHA) {
        if (status->currentTile[0] != '1' &&
            status->currentTile[0] != '9' &&
            status->currentTile[1] != 'z') {
            for (int i = 0; i < Possibles->HandGroupLen; i++) {
                count += MarkMK(status, Possibles, number);
            }
        }
    }       //荣和形成的明刻

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Koutsu &&
            status->groupTile[i].tile[0] != '1' &&
            status->groupTile[i].tile[0] != '9' &&
            status->groupTile[i].tile[1] != 'z') {
            count++;
        }
    }
    return count;
}

int CountZZAK(Status *status, Possible *Possibles, int number) {
    int count = 0;
    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu &&
            Possibles->Situations[number].HandGroupTile[i].tile[0] != '1' &&
            Possibles->Situations[number].HandGroupTile[i].tile[0] != '9' &&
            Possibles->Situations[number].HandGroupTile[i].tile[1] != 'z') {
            count++;
        }
    }
    return count;
}

int CountZZMG(Status *status, Possible *Possibles, int number) {
    int count = 0;
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Kantsu && status->groupTile[i].tile[0] != '1' &&
            status->groupTile[i].tile[0] != '9' && status->groupTile[i].tile[1] != 'z') {
            count++;
        }
    }
    return count;
}

int CountZZAG(Status *status, Possible *Possibles, int number) {
    int count = 0;
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Ankan && status->groupTile[i].tile[0] != '1' &&
            status->groupTile[i].tile[0] != '9' && status->groupTile[i].tile[1] != 'z') {
            count++;
        }
    }
    return count;
}

int Count19MK(Status *status, Possible *Possibles, int number) {
    int count = 0;
    if (status->currentPlayer != JICHA) {
        if (status->currentTile[0] == '1' ||
            status->currentTile[0] == '9' ||
            status->currentTile[1] == 'z') {
            for (int i = 0; i < Possibles->HandGroupLen; i++) {
                count += MarkMK(status, Possibles, number);
            }
        }
    }       //荣和形成的明刻

    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Koutsu &&
            (status->groupTile[i].tile[0] == '1' || \
            status->groupTile[i].tile[0] == '9' || \
            status->groupTile[i].tile[1] == 'z')) {
            count++;
        }
    }
    return count;
}

int Count19AK(Status *status, Possible *Possibles, int number) {
    int count = 0;
    for (int i = 0; i < Possibles->HandGroupLen; i++) {
        if (Possibles->Situations[number].HandGroupTile[i].type == Koutsu &&
            (Possibles->Situations[number].HandGroupTile[i].tile[0] == '1' || \
            Possibles->Situations[number].HandGroupTile[i].tile[0] == '9' || \
            Possibles->Situations[number].HandGroupTile[i].tile[1] == 'z')) {
            count++;
        }
    }
    return count;
}

int Count19MG(Status *status, Possible *Possibles, int number) {
    int count = 0;
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Kantsu && \
        (status->groupTile[i].tile[0] == '1' || \
        status->groupTile[i].tile[0] == '9' || \
        status->groupTile[i].tile[1] == 'z')) {
            count++;
        }
    }
    return count;
}

int Count19AG(Status *status, Possible *Possibles, int number) {
    int count = 0;
    for (int i = 0; i < 4 - Possibles->HandGroupLen; i++) {
        if (status->groupTile[i].type == Ankan && \
        (status->groupTile[i].tile[0] == '1' || \
        status->groupTile[i].tile[0] == '9' || \
        status->groupTile[i].tile[1] == 'z')) {
            count++;
        }
    }
    return count;
}

bool isYPQT(Status *status, Possible *Possibles, int number) {
    if (Possibles->Situations[number].Jyantou[1] == 'z' && Possibles->Situations[number].Jyantou[0] >= '5' &&
        Possibles->Situations[number].Jyantou[0] <= '7') {
        return true;
    } else if (Possibles->Situations[number].Jyantou[1] == 'z' && (
            Possibles->Situations[number].Jyantou[0] - 48 == status->bakaze + 1 ||
            Possibles->Situations[number].Jyantou[0] - 48 == status->jikaze + 1)) {
        return true;
    } else return false;
}

bool isLFQT(Status *status, Possible *Possibles, int number) {
    if (status->bakaze == status->jikaze && Possibles->Situations[number].Jyantou[1] == 'z' &&
        Possibles->Situations[number].Jyantou[0] - 48 == status->bakaze + 1) {
        return true;
    } else return false;
}