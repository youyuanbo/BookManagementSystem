//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/Manager.h"

/**
 * 管理员类
 */

Manager::Manager() {

}

/**
 * 有参构造函数
 * @param name  姓名
 * @param password  密码
 */
Manager::Manager(string name, string password) {
    this->name = name;
    this->password = password;
    this->initVector();

}

//管理员菜单
void Manager::Menu() {
    cout << "\t\t欢迎管理员：" << this->name << "登录系统！" << endl;
    cout << "\t\t---------------------------------\n" << endl;
    cout << "\t\t|         1.添加账号             |\n" << endl;
    cout << "\t\t|         2.查看账号             |\n" << endl;
    cout << "\t\t|         3.添加图书             |\n" << endl;
    cout << "\t\t|         4.查看图书             |\n" << endl;
    cout << "\t\t|         5.删除图书             |\n" << endl;
    cout << "\t\t|         6.查看借阅信息          |\n" << endl;
    cout << "\t\t|         0.注销登录             |\n" << endl;
    cout << "\t\t---------------------------------\n" << endl;
}

//初始化容器
void Manager::initVector() {
    //确保容器中没有数据
    this->VCReader.clear();
    this->VCBook.clear();

    //读取读者信息
    ifstream readFile;
    readFile.open(READER_FILE, ios::in);
    if (!readFile.is_open()) {
        cout << "读者文件读取失败" << endl;
        return;
    }
    Reader reader;  //读取信息
    while (readFile >> reader.id && readFile >> reader.name && readFile >> reader.password) {
        VCReader.push_back(reader);
    }
    cout << "当前读者数量：" << VCReader.size() << endl;
    readFile.close();


    //初始化图书信息
    readFile.open(BOOK_FILE, ios::in);
    if (!readFile.is_open()) {
        cout << "图书信息文件打开失败" << endl;
    }
    Book book;
    while (readFile >> book.id && readFile >> book.bookName && readFile >> book.bookNum) {
        VCBook.push_back(book);
    }
    cout << "当前图书数量：" << VCBook.size() << endl;
    readFile.close();
}

//添加读者
void Manager::addReader() {
    string fileName;    //定义输出文件名称
    string errorIdTip;    //id有重复提示
    ofstream output;    //输出文件流对象

    fileName = READER_FILE;
    //利用追加的方式，写文件
    output.open(fileName, ios::out | ios::app);
    //定义属性
    int id;
    string name;
    string password;
    cout << "请输入id: " << endl;
    while (true) {
        cin >> id;
        bool result = this->checkReaderRepeat(id);
        if (result) {    //有重复
            cout << "读者id重复，请重新输入：" << endl;
        } else {
            //没有重复，直接退出
            break;
        }
    }

    //输入姓名
    cout << "请输入姓名：" << endl;
    cin >> name;
    //输入密码
    cout << "请输入密码：" << endl;
    cin >> password;

    //向文件中添加数据
    output << id << " " << name << " " << password << endl;
    cout << "添加成功" << endl;
    system("pause");
    system("cls");

    output.close();
    this->initVector();
}

//输出读者信息
void printReader(Reader &reader) {
    cout << "借书号: " << reader.id << "\t姓名：" << reader.name << "\t密码：" << reader.password << endl;
}

//查看读者信息
void Manager::showReader() {
    cout << "所有的读者信息：" << endl;
    for_each(VCReader.begin(), VCReader.end(), printReader);

    system("pause");
    system("cls");
}

//添加图书
void Manager::addBook() {
    string fileName;    //定义输出文件名称
    ofstream output;    //输出文件流对象

    fileName = BOOK_FILE;
    //利用追加的方式，写文件
    output.open(fileName, ios::out | ios::app);
    //定义属性
    int id;
    string bookName;
    int bookNum;
    cout << "请输入图书id: " << endl;
    while (true) {
        cin >> id;
        bool result = this->checkBookRepeat(id);
        if (result) {    //有重复
            cout << "图书id重复，请重新输入：" << endl;
        } else {
            //没有重复，直接退出
            break;
        }
    }

    //输入图书名称
    cout << "请输入图书名称：" << endl;
    cin >> bookName;
    //输入图书数量
    cout << "请输入图书数量：" << endl;
    cin >> bookNum;

    //向文件中添加数据
    output << id << " " << bookName << " " << bookNum << endl;
    cout << "添加成功" << endl;
    system("pause");
    system("cls");
    //关闭文件
    output.close();
    this->initVector();
}

//输出图书信息
void printBook(Book &book) {
    cout << book.bookName << "\t\t" << book.bookNum << endl;
}

//查看图书
void Manager::showBooks() {
    cout << "所有图书信息" << endl;
    cout << "图书名称\t" << "图书数量\t" <<  endl;
    for_each(VCBook.begin(), VCBook.end(), printBook);
    system("pause");
    system("cls");
}

//检测读者id是否重复
bool Manager::checkReaderRepeat(int id) {
    //检测读者id是否重复
    for (vector<Reader>::iterator readerBegin = VCReader.begin(); readerBegin != VCReader.end(); readerBegin++) {
        if (id == readerBegin->id) {
            return true;
        }
    }
    return false;
}

//检测图书id是否重复
bool Manager::checkBookRepeat(int id) {

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if (id == bookBegin->id) {
            return true;
        }
    }
    return false;
}

//删除图书
void Manager::deleteBook() {
    string bookName;
    cout << "请输入要删除的图书名称：" << endl;
    cin >> bookName;
    cout << "正在完善中，请等候" << endl;
    system("pause");
    system("cls");
    return;
}

void Manager::showAllBorrowInformation() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "没有借阅记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "借书人姓名\t" << "图书名称\t" << "借阅时间\t" << "状态" << endl;
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        cout << borrowInformation.borrowData[i]["ReaderName"] << "\t\t";
        cout << borrowInformation.borrowData[i]["BookName"] << "\t\t";
        cout << borrowInformation.borrowData[i]["Time"] << "\t";
        if (tempStatus == 0) {
            cout << "已归还" << endl;
        } else {
            cout << "在借" << endl;
        }

    }
    system("pause");
    system("cls");
    return;
}


