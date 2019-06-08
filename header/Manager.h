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
    //�޲ι���
    Manager();

    //�вι���
    Manager(string name, string password);

    //��ʾ�˵�
    virtual void Menu();

    //����˺�
    void addReader();

    //�鿴�˺�
    void showReader();

    //�鿴ͼ����Ϣ
    void showBooks();

    //���ͼ��
    void addBook();

    //��ʼ������
    void initVector();

    //�������Ƿ��ظ�
    bool checkReaderRepeat(int id);

    //�������Ƿ��ظ�
    bool checkBookRepeat(int id);

    //ɾ��ͼ��
    void deleteBook();

    //�鿴���еĽ�����Ϣ
    void showAllBorrowInformation();

    //���ԣ���������
    vector<Reader> VCReader;

    //���ԣ�ͼ������
    vector<Book> VCBook;

};


#endif //BOOKMANAGEMENTSYSTEM_MANAGER_H
