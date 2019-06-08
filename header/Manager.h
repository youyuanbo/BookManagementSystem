//
// Created by xiaoyou on 2019/6/8.
//
#pragma once
#ifndef BOOKMANAGEMENTSYSTEM_MANAGER_H
#define BOOKMANAGEMENTSYSTEM_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Reader.h"
#include "Manager.h"
#include "Book.h"
#include "Person.h"
#include "GlobalFile.h"
using namespace std;

class Manager : public Person{
public:
    //无参构造
    Manager();

    //有参构造
    Manager(string name, string password);

    //显示菜单
    virtual void Menu();

    //添加账号
    void addReader();

    //查看账号
    void showReader();

    //查看图书信息
    void showBooks();

    //添加图书
    void addBook();

    //初始化容器
    void initVector();

    //检测读者是否重复
    bool checkReaderRepeat(int id);

    //检测读者是否重复
    bool checkBookRepeat(int id);

    //删除图书
    void deleteBook();

    //查看所有的借阅信息
    void showAllBorrowInformation();

    //属性：读者容器
    vector<Reader> VCReader;

    //属性：图书容器
    vector<Book> VCBook;

};


#endif //BOOKMANAGEMENTSYSTEM_MANAGER_H
