#pragma once
#include "main.h"

Yaku *checkYaku(Status *status);  // 检测所满足的所有役种（若包含役满/两倍役种，则不返回其他非役满役种；注意其余役种替代关系）