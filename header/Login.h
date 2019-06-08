//
// Created by xiaoyou on 2019/6/8.
//

#pragma once
#ifndef BOOKMANAGEMENTSYSTEM_LOGIN_H
#define BOOKMANAGEMENTSYSTEM_LOGIN_H

#include <iostream>
#include <string>
#include <fstream>
#include "Reader.h"
#include "Manager.h"
#include "Person.h"
#include "GlobalFile.h"

using namespace std;

class Login {

public:
    /**
     * 登录函数
     * @param fileName  文件名称
     * @param type 操作身份类型 1.学生 2.教师 3. 管理员
     */
    void loginIn(string fileName, int type);

    //管理员子菜单
    void managerMenu(Person *manager);

    //读者子菜单
    void readerMenu(Person *manager);

};


#endif //BOOKMANAGEMENTSYSTEM_LOGIN_H
