#include <iostream>
#include <string>
#include "header/Login.h"
#include "header/GlobalFile.h"
using namespace std;


int main() {

    char select;

    Login login;

    while (true){
        cout<<"========��ӭ����ͼ�����ϵͳ=========="<<endl;
        cout<<"\t\t------------------------------\n"<<endl;
        cout<<"\t\t|            1.����            |\n"<<endl;
        cout<<"\t\t|            2.����Ա          |\n"<<endl;
        cout<<"\t\t|            0.�˳�            |\n"<<endl;
        cout<<"\t\t------------------------------\n"<<endl;
        cout<<"���������ѡ��: ";
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
                cout << "��ӭ�´�ʹ��" << endl;
                system("pause");
                return 0;
            default:
                cout<<"������������������"<<endl;
                system("pause");
                system("cls");
                break;
        }
    }
}