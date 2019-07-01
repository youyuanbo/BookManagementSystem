//
// Created by xiaoyou on 2019/6/8.
//
#pragma once
#ifndef BOOKMANAGEMENTSYSTEM_READER_H
#define BOOKMANAGEMENTSYSTEM_READER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "GlobalFile.h"
#include "Book.h"
#include "Person.h"
#include "BorrowInformation.h"
#include "BookUtil.h"

using namespace std;

class Reader : public Person{
public:
    //无参构造
    Reader();

    //有参构造
    Reader(string id, string name, string password);

    //菜单
    virtual void Menu();


    //借书
    void borrowBook();

    //更改图书数量
    void changeBookNum(string bookName, int type);

    //查看正在借阅的图书
    void showOnBorrow();

    //查看已归还的图书
    void showAllBorrowInfo();

    //还书
    void returnBook();

    //查询图书
    bool findBookByName();

    //查看所有的图书
    void showAllBook();

    //借书号
    string id;

    //图书容器
    vector<Book> VCBook;


};


#endif //BOOKMANAGEMENTSYSTEM_READER_H
