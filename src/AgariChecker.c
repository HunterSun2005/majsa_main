#include "AgariChecker.h"

bool SeparateTile(Hand Hands) {
    if (Hands.m_num + Hands.p_num + Hands.s_num + Hands.z_num == 0) {
        return true;
    } else {
        for (int a = 0; a <= 3; a++) {
            for (int b = 1; b <= 9; b++) {
                if (Hands.matrix[a][b] >= 3) {
                    Hands.matrix[a][b] -= 3;
                    switch (a) {
                        case 0:
                            Hands.m_num -= 3;
                            break;
                        case 1:
                            Hands.p_num -= 3;
                            break;
                        case 2:
                            Hands.s_num -= 3;
                            break;
                        case 3:
                            Hands.z_num -= 3;
                            break;
                        default:;
                    }
                    if (SeparateTile(Hands) == 1) {
                        return true;
                    }
                }
            }
        }   //刻子

        for (int a = 0; a <= 2; a++) {
            for (int b = 1; b <= 7; b++) {
                if (Hands.matrix[a][b] >= 1 && Hands.matrix[a][b + 1] >= 1 && Hands.matrix[a][b + 2] >= 1) {
                    Hands.matrix[a][b]--;
                    Hands.matrix[a][b + 1]--;
                    Hands.matrix[a][b + 2]--;
                    if (SeparateTile(Hands) == 1) {
                        return true;
                    }
                }
            }
        }   //顺子

        return false;
    }
}

bool isAgari(Status *status) {
    Hand temp;

    Hand Hands = {
            .matrix = {0},
            .m_num = 0,
            .p_num = 0,
            .s_num = 0,
            .z_num = 0,
    };

    if (status->currentTile[1] == 'm') {
        Hands.matrix[0][status->currentTile[0]]++;
        Hands.m_num++;
    } else if (status->currentTile[1] == 'p') {
        Hands.matrix[1][status->currentTile[0]]++;
        Hands.p_num++;
    } else if (status->handTile[1] == 's') {
        Hands.matrix[2][status->currentTile[0]]++;
        Hands.s_num++;
    } else if (status->handTile[1] == 'z') {
        Hands.matrix[3][status->currentTile[0]]++;
        Hands.z_num++;
    }

    for (int i = 0; i < 15 && status->handTile[2 * i] != '\0'; i++) {
        if (status->handTile[2 * i + 1] == 'm') {
            Hands.matrix[0][status->handTile[2 * i]]++;
            Hands.m_num++;
        } else if (status->handTile[2 * i + 1] == 'p') {
            Hands.matrix[1][status->handTile[2 * i]]++;
            Hands.p_num++;
        } else if (status->handTile[2 * i + 1] == 's') {
            Hands.matrix[2][status->handTile[2 * i]]++;
            Hands.s_num++;
        } else if (status->handTile[2 * i + 1] == 'z') {
            Hands.matrix[3][status->handTile[2 * i]]++;
            Hands.z_num++;
        }

        switch (status->handTile[2 * i + 1]) {
            case 'm':
                Hands.matrix[0][status->handTile[2 * i]]++;
                Hands.m_num++;
                break;
            case 'p':
                Hands.matrix[1][status->handTile[2 * i]]++;
                Hands.p_num++;
                break;
            case 's':
                Hands.matrix[2][status->handTile[2 * i]]++;
                Hands.s_num++;
                break;
            case 'z':
                Hands.matrix[3][status->handTile[2 * i]]++;
                Hands.z_num++;
                break;
            default:;
        }
    }


    for (int i = 0; i <= 3; i++) {
        Hands.matrix[i][5] += Hands.matrix[i][0];
        Hands.matrix[i][0] = 0;
    }

    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Hands.matrix[i][j] >= 2) {
                temp = Hands;
                temp.matrix[i][j] -= 2; //雀头
                if (SeparateTile(temp) == 1) {
                    return true;
                }
            }
        }
    }

    return false;
}
