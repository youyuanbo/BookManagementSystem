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
     * ��¼����
     * @param fileName  �ļ�����
     * @param type ����������� 1.ѧ�� 2.��ʦ 3. ����Ա
     */
    void loginIn(string fileName, int type);

    //����Ա�Ӳ˵�
    void managerMenu(Person *manager);

    //�����Ӳ˵�
    void readerMenu(Person *manager);

};


#endif //BOOKMANAGEMENTSYSTEM_LOGIN_H
