//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/BorrowInformation.h"
/**
 * ͼ����ļ�¼
 */

 //���캯��
BorrowInformation::BorrowInformation() {
    //��ȡͼ�������Ϣ��¼�ļ�
    fstream read;
    read.open(BORROW_INFORMATION_FILE, ios::in);
    //��������ֶ�
    string ReaderID;    //����id
    string ReaderName;  //��������
    string Time;        //����ʱ��
    string BookName;    //ͼ������
    string Status;      //����״̬��1���ڽ裬0���ѹ黹
    this->totalBorrowSize = 0;  //��¼ͼ�������Ϣ����

    //��ȡ���ݣ��ָ��װ
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
 * ���½��ļ�¼�ļ�����
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
