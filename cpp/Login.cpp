//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/Login.h"

/**
 * 登录类
 * @param fileName  需要操作的文件名称
 * @param type  人员类型，1：读者，2：管理员
 */
void Login::loginIn(string fileName, int type) {
    //父类指针，用于指向子类对象
    Person *person = NULL;

    //读文件
    ifstream readFile;
    readFile.open(fileName, ios::in);

    //判断文件是否存在
    if (!readFile.is_open()){
        cout << "文件不存在" << endl;
        readFile.close();
        return;
    }

    //准备接收用户信息
    int id = 0;

    string name;

    string password;

    if (type == 1){
        cout << "请输入你的借书证号：" << endl;
        cin>>id;
    }

    cout << "请输入你的姓名：" << endl;
    cin>>name;

    cout << "请输入你的密码：" << endl;
    cin>>password;

    if (type == 1){
        //读者身份验证
        int fId;    //从文佳中读取的ID
        string fName;   //从文件中读取的name
        string fPassword;   //从文件中读取的password

        while (readFile >> fId && readFile >> fName && readFile >> fPassword){
            if(fId == id && fName == name && fPassword == password){
                cout << "读者登录验证成功。" << endl;
                system("pause");
                system("cls");
                person = new Reader(id, name, password);
                //进入读者子菜单
                this->readerMenu(person);
                return;
            }
        }
    }  else if (type == 2){
        //管理员身份验证
        string fName;   //从文件中读取的name
        string fPassword;   //从文件中读取的password

        while (readFile >> fName && readFile >> fPassword){
            if(fName == name && fPassword == password){
                cout << "管理员登录验证成功。" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, password);

                //进入管理员子菜单
                this->managerMenu(person);
                return;
            }
        }
    }

    cout << "验证失败" << endl;
    system("pause");
    system("cls");
    return;
}

//进入管理员子菜单界面
void Login::managerMenu(Person *person) {
    while (true){

        //调用管理员子菜单
        person->Menu();

        //将父类指针转为子类指针
        Manager *manager = (Manager*) person;

        //定义用户选项
        int select = 0;
        cout << "请选择：" << endl;
        cin>>select;
        switch (select){
            case 1: //添加读者
                manager->addReader();
                break;
            case 2: //显示读者信息
                manager->showReader();
                break;
            case 3: //添加图书
                manager->addBook();
                break;
            case 4: //查看图书
                manager->showBooks();
                break;
            case 5: //删除图书
                manager->deleteBook();
                break;
            case 6: //查看所有的借阅信息
                manager->showAllBorrowInformation();
                break;
            case 0:
                delete manager;
                cout << "注销成功" << endl;
                system("pause");
                system("cls");
                return;
            default:
                cout << "输入有误，请重新输入" << endl;
        }
    }
}

//读者子菜单
void Login::readerMenu(Person *person) {
    Reader *reader = (Reader *) person;
    while (true){
        //调用读者子菜单
        person->Menu();
        int select;
        cout << "请输入你的选择" << endl;
        cin>>select;

        switch (select){
            case 1: //查看正在借阅的图书信息
                reader->showOnBorrow();
                break;
            case 2: //借阅图书
                reader->borrowBook();
                break;
            case 3: //还书
                reader->returnBook();
                break;
            case 4: //查询图书
                reader->findBookByName();
                break;
            case 5: //查看所有图书
                reader->showAllBook();
                break;
            case 6: //查看所有图书
                reader->showAllBorrowInf();
                break;
            case 0: //注销登录
                delete person;
                cout << "注销成功" << endl;
                system("pause");
                system("cls");
                return;
            default:
                cout << "输入有误，请重新输入" << endl;
        }
    }

}
