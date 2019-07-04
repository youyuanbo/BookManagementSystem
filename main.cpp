#include <iostream>
#include <string>
#include "header/Login.h"
#include "header/GlobalFile.h"
using namespace std;


int main() {

    char select;

    Login login;

    while (true){
        cout<<"========欢迎来到图书管理系统=========="<<endl;
        cout<<"\t\t------------------------------\n"<<endl;
        cout<<"\t\t|            1.读者            |\n"<<endl;
        cout<<"\t\t|            2.管理员          |\n"<<endl;
        cout<<"\t\t|            0.退出            |\n"<<endl;
        cout<<"\t\t------------------------------\n"<<endl;
        cout<<"请输入你的选择: ";
        cin>>select;
        cout << endl;

        switch (select){
            case '1':
                login.loginIn(READER_FILE, 1);
                break;
            case '2':
                login.loginIn(ADMIN_FILE, 2);
                break;
            case '0':
                cout << "欢迎下次使用" << endl;
                system("pause");
                return 0;
            default:
                cout<<"输入有误，请重新输入"<<endl;
                system("pause");
                system("cls");
                break;
        }
    }
}