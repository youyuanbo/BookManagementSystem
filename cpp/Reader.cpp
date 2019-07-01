//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/Reader.h"

//无参构造
Reader::Reader() {

}

/**
 * 有参构造
 * @param id 读者id
 * @param name  读者姓名
 * @param password  读者密码
 */
Reader::Reader(string id, string name, string password) {

    this->id = id;
    this->name = name;
    this->password = password;
    //初始化图书容器
    ifstream readFile;
    readFile.open(BOOK_FILE, ios::in);  //读取文件
    Book book;
    while (readFile >> book.id && readFile >> book.bookName && readFile >> book.bookNum) {
        VCBook.push_back(book);
    }
    readFile.close();
}

//读者子菜单
void Reader::Menu() {
    cout << "\t\t欢迎读者：" << this->name << "  登录系统！" << endl;
    cout << "\t\t---------------------------------\n" << endl;
    cout << "\t\t|         1.查看已借图书           |\n" << endl;
    cout << "\t\t|         2.借书                  |\n" << endl;
    cout << "\t\t|         3.还书                  |\n" << endl;
    cout << "\t\t|         4.查询图书              |\n" << endl;
    cout << "\t\t|         5.查看所有图书           |\n" << endl;
    cout << "\t\t|         6.查看自己的借阅信息      |\n" << endl;
    cout << "\t\t|         0.注销登录              |\n" << endl;
    cout << "\t\t---------------------------------\n" << endl;
}


//借书
void Reader::borrowBook() {
    BorrowInformation borrowInformation;    //借阅记录信息类对象
    BookUtil bookUtil;
    string bookName;
    string status = "1";
    int flag = 0;
    cout << "请输入图书名称" << endl;
    cin >> bookName;

    //判断是否已经借阅此图书
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        //获取id
        string tempID = borrowInformation.borrowData[i]["ReaderID"];
        //获取借阅状态
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        //当图书名称、id相同，借阅状态为在借时，不能再借阅图书
        if ((borrowInformation.borrowData[i]["BookName"] == bookName) &&
                (tempID == this->id) && (tempStatus == 1)) {
            cout << "你已经借阅该图书" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    //借阅图书，当存在此图书，并且余量大于0时，才可以借阅此图书
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if ((bookBegin->bookName == bookName) && (bookBegin->bookNum > 0)) {
            ofstream write;
            write.open(BORROW_INFORMATION_FILE, ios::app);
            write << "ReaderID:" << this->id << "\t";
            write << "ReaderName:" << this->name << "\t";
            write << "Time:" << bookUtil.getTime() << "\t";
            write << "BookName:" << bookName << "\t";
            write << "Status:" << status << endl;
            write.close();
            //更改图书余量
            this->changeBookNum(bookName, 1);


            cout << "借书完成" << endl;
            flag = 1;
        }
    }
    if (flag == 0) {
        cout << "此书不存在或者余量为0" << endl;
    }
    system("pause");
    system("cls");
}

//查看在借的图书
void Reader::showOnBorrow() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "没有借阅记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        string tempID = borrowInformation.borrowData[i]["ReaderID"];
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        //当id匹配并且状态为在借时，显示此记录
        if ((this->id == tempID) && (1 == tempStatus)) {
            cout << "图书名称：" <<borrowInformation.borrowData[i]["BookName"] << "\t";
            cout << "借阅时间：" << borrowInformation.borrowData[i]["Time"] << endl;
        }
    }
    system("pause");
    system("cls");
    return;
}

//归还图书
void Reader::returnBook() {
    BorrowInformation borrowInformation;
    string bookName;

    cout << "请输入准备归还的图书名称: " << endl;
    cin>>bookName;
    //如果借阅记录文件中没有任何记录，直接退出
    if (borrowInformation.totalBorrowSize == 0){
        cout << "无任何借阅记录" << endl;
        return;
    }

    //归还图书，当读者id、图书名称都与节约记录文件中的数据匹配，并且借阅状态为在借，可以归还此图书
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        //获取图书名称
        string tempBookName = borrowInformation.borrowData[i]["BookName"];
        //获取读者id
        string tempId = borrowInformation.borrowData[i]["ReaderID"];
        //获取借阅状态
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        //验证
        if ((tempBookName == bookName) &&(tempId == this->id) && (tempStatus == 1)){
            //更改图书余量
            this->changeBookNum(bookName, 2);
            borrowInformation.borrowData[i]["Status"] = "0";
            borrowInformation.updateBorrowInformation();
            cout << "还书完成" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    cout << "你没有借阅此书" << endl;
    system("pause");
    system("cls");
    return;
}

//查看所有图书
void Reader::showAllBook() {

    if (VCBook.size() == 0){
        cout << "没有图书" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "名称\t" << "余量" << endl;
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        cout << "名称：" << bookBegin->bookName << "    ";
        cout << "余量：" << bookBegin->bookNum << endl;
    }
    system("pause");
    system("cls");
    return;
}

//查找图书
bool Reader::findBookByName() {

    string bookName;
    cout << "请输入图书名称：" << endl;
    cin >> bookName;
    //检测是否存在此书以及图书余量
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if ((bookBegin->bookName == bookName)) {
            cout << "名称：" << bookBegin->bookName << "    ";
            cout << "余量：" << bookBegin->bookNum << endl;
            system("pause");
            system("cls");
            return true;
        }
    }
    cout << "你查询的书名是：" << bookName <<"，该图书不存在" << endl;
    return false;

}

//查看自己的所有借阅信息
void Reader::showAllBorrowInfo() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "没有借阅记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "借书人姓名\t" << "图书名称\t" << "借阅时间\t" << "状态" << endl;
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        string tempID = borrowInformation.borrowData[i]["ReaderID"];
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());

        if (this->id == tempID ) {
            cout << "借书人姓名：" << this->name << "\t\t";
            cout << "图书名称：" << borrowInformation.borrowData[i]["BookName"] << "\t\t";
            cout << "借阅时间：" << borrowInformation.borrowData[i]["Time"] << "\t";
            cout << "状态：" ;
            if (tempStatus == 0){
                cout << "已归还" << endl;
            } else{
                cout << "在借" << endl;
            }
        }
    }
    system("pause");
    system("cls");
    return;
}

//更改图书余量，type：1，减少；2，增加
void Reader::changeBookNum(string bookName, int type) {
    fstream write;
    write.open(BOOK_FILE, ios::out);

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if ((bookBegin->bookName == bookName)) {
            if (type == 1) {
                bookBegin->bookNum--;
            }
            if (type == 2) {
                bookBegin->bookNum++;
            }
        }
    }

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        write << bookBegin->id << " ";
        write << bookBegin->bookName << " ";
        write << bookBegin->bookNum << endl;
    }
}

