//
// Created by xiaoyou on 2019/6/8.
//
#pragma once
#ifndef BOOKMANAGEMENTSYSTEM_BORROWINFORMATION_H
#define BOOKMANAGEMENTSYSTEM_BORROWINFORMATION_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "GlobalFile.h"
using namespace std;
class BorrowInformation {
public:
    //构造函数
    BorrowInformation();

    //更新图书信息
    void updateBorrowInformation();

    //使用map来存储图书借阅信息
    map<int, map<string,string>> borrowData;

    //总的图书借阅信息
    int totalBorrowSize;
};


#endif //BOOKMANAGEMENTSYSTEM_BORROWINFORMATION_H
