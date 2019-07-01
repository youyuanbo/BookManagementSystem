//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/Login.h"

/**
 * ��¼��
 * @param fileName  ��Ҫ�������ļ�����
 * @param type  ��Ա���ͣ�1�����ߣ�2������Ա
 */
void Login::loginIn(string fileName, int type) {
    //����ָ�룬����ָ���������
    Person *person = NULL;

    //���ļ�
    ifstream readFile;
    readFile.open(fileName, ios::in);

    //�ж��ļ��Ƿ����
    if (!readFile.is_open()){
        cout << "�ļ�������" << endl;
        readFile.close();
        return;
    }

    //׼�������û���Ϣ

    string name;

    string password;

    cout << "���������������" << endl;
    cin>>name;

    cout << "������������룺" << endl;
    cin>>password;

    if (type == 1){
        //���������֤
        string fId;    //���ļ��ж�ȡ��ID
        string fName;   //���ļ��ж�ȡ��name
        string fPassword;   //���ļ��ж�ȡ��password

        while (readFile >> fId && readFile >> fName && readFile >> fPassword){
            if( fName == name && fPassword == password){
                cout << "���ߵ�¼��֤�ɹ���" << endl;
                system("pause");
                system("cls");
                person = new Reader(fId,name, password);
                //��������Ӳ˵�
                this->readerMenu(person);
                return;
            }
        }
    }  else if (type == 2){
        //����Ա�����֤
        string fName;   //���ļ��ж�ȡ��name
        string fPassword;   //���ļ��ж�ȡ��password

        while (readFile >> fName && readFile >> fPassword){
            if(fName == name && fPassword == password){
                cout << "����Ա��¼��֤�ɹ���" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, password);

                //�������Ա�Ӳ˵�
                this->managerMenu(person);
                return;
            }
        }
    }

    cout << "��֤ʧ��" << endl;
    system("pause");
    system("cls");
    return;
}

//�������Ա�Ӳ˵�����
void Login::managerMenu(Person *person) {
    while (true){

        //���ù���Ա�Ӳ˵�
        person->Menu();

        //������ָ��תΪ����ָ��
        Manager *manager = (Manager*) person;

        //�����û�ѡ��
        char select = '0';
        cout << "��ѡ��" << endl;
        cin>>select;
        switch (select){
            case '1': //��Ӷ���
                manager->addReader();
                break;
            case '2': //��ʾ������Ϣ
                manager->showReader();
                break;
            case '3': //���ͼ��
                manager->addBook();
                break;
            case '4': //����ͼ��
                manager->findBookByName();
                break;
            case '5': //�鿴����ͼ��
                manager->showBooks();
                break;
            case '6': //ɾ��ͼ��
                manager->deleteBook();
                break;
            case '7': //ɾ��ͼ��
                manager->showAllBorrowInformation();
                break;
            case '8': //����
                manager->sortBook();
                break;
            case '9': //�������
                manager->countAllBook();
                break;
            case '0':
                delete manager;
                cout << "ע���ɹ�" << endl;
                system("pause");
                system("cls");
                return;
            default:
                cout << "������������������" << endl;
        }
    }
}

//�����Ӳ˵�
void Login::readerMenu(Person *person) {
    Reader *reader = (Reader *) person;
    while (true){
        //���ö����Ӳ˵�
        person->Menu();
        char select;
        cout << "���������ѡ��" << endl;
        cin>>select;

        switch (select){
            case '1': //�鿴���ڽ��ĵ�ͼ����Ϣ
                reader->showOnBorrow();
                break;
            case '2': //����ͼ��
                reader->borrowBook();
                break;
            case '3': //����
                reader->returnBook();
                break;
            case '4': //��ѯͼ��
                reader->findBookByName();
                break;
            case '5': //�鿴����ͼ��
                reader->showAllBook();
                break;
            case '6': //�鿴����ͼ��
                reader->showAllBorrowInfo();
                break;
            case '0': //ע����¼
                delete person;
                cout << "ע���ɹ�" << endl;
                system("pause");
                system("cls");
                return;
            default:
                cout << "������������������" << endl;
        }
    }

}
