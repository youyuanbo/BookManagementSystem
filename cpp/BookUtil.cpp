//
// Created by youyuanbo on 2019/7/1.
//

#include "../header/BookUtil.h"

string BookUtil::getId() {

    string id;

    int year;   //��
    int month;  //��
    int day;    //��
    time_t time1 = time(NULL);
    tm *currentTime = localtime(&time1);
    year = currentTime->tm_year + 1900;
    month = currentTime->tm_mon + 1;
    day = currentTime->tm_mday;

    default_random_engine engine(time(0));
    uniform_int_distribution<unsigned > uniform(10000, 100000);
    int num = uniform(engine);

    id = to_string(year) + to_string(month) + to_string(day) + to_string(num);

    return id;
}


//��ȡ��ǰϵͳʱ��
string BookUtil::getTime() {
    int year;   //��
    int month;  //��
    int day;    //��
    time_t time1 = time(NULL);
    tm *currentTime = localtime(&time1);
    year = currentTime->tm_year + 1900;
    month = currentTime->tm_mon + 1;
    day = currentTime->tm_mday;
    string timeStr = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
    return timeStr;
}

