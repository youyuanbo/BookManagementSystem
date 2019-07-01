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
    //�޲ι���
    Reader();

    //�вι���
    Reader(string id, string name, string password);

    //�˵�
    virtual void Menu();


    //����
    void borrowBook();

    //����ͼ������
    void changeBookNum(string bookName, int type);

    //�鿴���ڽ��ĵ�ͼ��
    void showOnBorrow();

    //�鿴�ѹ黹��ͼ��
    void showAllBorrowInfo();

    //����
    void returnBook();

    //��ѯͼ��
    bool findBookByName();

    //�鿴���е�ͼ��
    void showAllBook();

    //�����
    string id;

    //ͼ������
    vector<Book> VCBook;


};


#endif //BOOKMANAGEMENTSYSTEM_READER_H
