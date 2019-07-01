//
// Created by youyuanbo on 2019/7/1.
//

#ifndef BOOKMANAGEMENTSYSTEM_BOOKUTIL_H
#define BOOKMANAGEMENTSYSTEM_BOOKUTIL_H

#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include "BorrowInformation.h"

using namespace std;

class BookUtil {
public:
    string getId();

    //取得当前系统时间
    string getTime();



};


#endif //BOOKMANAGEMENTSYSTEM_BOOKUTIL_H
