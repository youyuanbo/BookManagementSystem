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
    //���캯��
    BorrowInformation();

    //����ͼ����Ϣ
    void updateBorrowInformation();

    //ʹ��map���洢ͼ�������Ϣ
    map<int, map<string,string>> borrowData;

    //�ܵ�ͼ�������Ϣ
    int totalBorrowSize;
};


#endif //BOOKMANAGEMENTSYSTEM_BORROWINFORMATION_H
