//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/BorrowInformation.h"
/**
 * 图书借阅记录
 */

 //构造函数
BorrowInformation::BorrowInformation() {
    //读取图书借阅信息记录文件
    fstream read;
    read.open(BORROW_INFORMATION_FILE, ios::in);
    //定义相关字段
    string ReaderID;    //读者id
    string ReaderName;  //读者姓名
    string Time;        //借阅时间
    string BookName;    //图书名称
    string Status;      //借阅状态，1：在借，0：已归还
    this->totalBorrowSize = 0;  //记录图书借阅信息总数

    //读取数据，分割，封装
    while (read >> ReaderID && read >> ReaderName && read >> Time && read >> BookName && read >> Status){
        string key;
        string value;

        map<string, string> map;
        //split ReaderID
        int position = ReaderID.find(":");
        if (position != -1){
            key = ReaderID.substr(0, position);
            value = ReaderID.substr(position+1, ReaderID.size() - position - 1);
            map.insert(make_pair(key, value));
        }

        //split readName
        position = ReaderName.find(":");
        if (position != -1){
            key = ReaderName.substr(0, position);
            value = ReaderName.substr(position+1, ReaderName.size() - position - 1);
            map.insert(make_pair(key, value));
        }

        //split Time
        position = Time.find(":");
        if (position != -1){
            key = Time.substr(0, position);
            value = Time.substr(position + 1, Time.size() - position - 1);
            map.insert(make_pair(key, value));
        }

        //split BookName
        position = BookName.find(":");
        if (position != -1){
            key = BookName.substr(0, position);
            value = BookName.substr(position + 1,  BookName.size() - position - 1);
            map.insert(make_pair(key, value));
        }

        //split Status
        position = Status.find(":");
        if (position != -1){
            key = Status.substr(0, position);
            value = Status.substr(position + 1, Status.size() - position - 1);
            map.insert(make_pair(key, value));
        }
        this->borrowData.insert(make_pair(this->totalBorrowSize, map));
        this->totalBorrowSize++;
    }
    read.close();
}

/**
 * 更新借阅记录文件内容
 */
void BorrowInformation::updateBorrowInformation() {
    if (this->totalBorrowSize == 0){
        return;
    }

    ofstream write;
    write.open(BORROW_INFORMATION_FILE, ios::out | ios::trunc);

    for (int i = 0; i < this->totalBorrowSize; i++) {
        write << "ReaderID:" << this->borrowData[i]["ReaderID"] << " ";
        write << "ReaderName:" << this->borrowData[i]["ReaderName"] << " ";
        write << "Time:" << this->borrowData[i]["Time"] << " ";
        write << "BookName:" << this->borrowData[i]["BookName"] << " ";
        write << "Status:" << this->borrowData[i]["Status"] << endl;
    }
    write.close();
}
