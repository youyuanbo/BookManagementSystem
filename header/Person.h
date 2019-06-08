//
// Created by xiaoyou on 2019/6/8.
//
#pragma once
#ifndef BOOKMANAGEMENTSYSTEM_IDENTITY_H
#define BOOKMANAGEMENTSYSTEM_IDENTITY_H

#include <string>

using namespace std;
class Person {

public:
    virtual void Menu() = 0;

    string name;
    string password;
};


#endif //BOOKMANAGEMENTSYSTEM_IDENTITY_H
