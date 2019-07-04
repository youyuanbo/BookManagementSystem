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
    cout << "\t\t|         4.查找图书             |\n" << endl;
    cout << "\t\t|         5.查看所有图书          |\n" << endl;
    cout << "\t\t|         6.删除图书             |\n" << endl;
    cout << "\t\t|         7.查看借阅信息          |\n" << endl;
    cout << "\t\t|         8.图书排序             |\n" << endl;
    cout << "\t\t|         9.库存总量             |\n" << endl;
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
    readFile.close();
}

//添加读者
void Manager::addReader() {
    string fileName;    //定义输出文件名称
    string errorIdTip;    //id有重复提示
    ofstream output;    //输出文件流对象
    BookUtil bookUtil;

    fileName = READER_FILE;
    //利用追加的方式，写文件
    output.open(fileName, ios::out | ios::app);
    //定义属性
    string id = bookUtil.getId();
    string name;
    string password;

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
    cout << "借书号: " << reader.id << "    姓名：" << reader.name << "    密码：" << reader.password << endl;
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
    BookUtil bookUtil;

    fileName = BOOK_FILE;
    //利用追加的方式，写文件
    output.open(fileName, ios::out | ios::app);
    //定义属性
    string id = bookUtil.getId();
    string bookName;
    int bookNum;

    //输入图书名称
    cout << "请输入图书名称：" << endl;
    cin >> bookName;
    //输入图书数量
    cout << "请输入图书数量：" << endl;
    cin >> bookNum;

    //向文件中添加数据
    output << id << "\t" << bookName << "\t" << bookNum << endl;
    cout << "添加成功" << endl;
    system("pause");
    system("cls");
    //关闭文件
    output.close();
    this->initVector();
}

//输出图书信息
void printBook(Book &book) {
    cout << "图书名称: " << book.bookName << "    图书数量: " << book.bookNum << endl;
}

//查看图书
void Manager::showBooks() {
    for_each(VCBook.begin(), VCBook.end(), printBook);
    system("pause");
    system("cls");
}

//删除图书
void Manager::deleteBook() {
    string bookName;
    cout << "请输入要删除的图书名称：" << endl;
    cin >> bookName;
    int index = 0;
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if (bookName == bookBegin->bookName) {
            VCBook.erase(bookBegin);
            cout << "删除成功" << endl;

            ofstream write;
            write.open(BOOK_FILE, ios::out | ios::trunc);

            for (vector<Book>::iterator book = VCBook.begin(); book != VCBook.end(); book++) {
                write << book->id << "\t" << book->bookName << "\t" << book->bookNum << endl;
            }
            write.close();
            this->initVector();
            system("pause");
            system("cls");
            return;
        }
        index++;
    }
    cout << "图书不存在" << endl;
    system("pause");
    system("cls");
    return;
}

//查看所有借阅信息
void Manager::showAllBorrowInformation() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "没有借阅记录" << endl;
        system("pause");
        system("cls");
        return;
    }


    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        cout << "借书人姓名：" << borrowInformation.borrowData[i]["ReaderName"] << "  ";
        cout << "图书名称：" << borrowInformation.borrowData[i]["BookName"] << "  ";
        cout << "借阅时间：" << borrowInformation.borrowData[i]["Time"] << "  ";
        cout << "状态：";
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

//查询图书
void Manager::findBookByName() {

    //图书名称
    string bookName;
    cout << "请输入图书名称：" << endl;
    cin >> bookName;
    //检测是否存在此书以及图书余量
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        //是否存在图书
        if ((bookBegin->bookName == bookName)) {
            //输出图书的详细信息
            cout << "名称：" << bookBegin->bookName << "    ";
            cout << "余量：" << bookBegin->bookNum << endl;
            //结束程序
            system("pause");
            system("cls");
            return;
        }
    }
    //没有找到此图书，输出提示
    cout << "你查询的书名是：" << bookName << "，该图书不存在" << endl;
    system("pause");
    system("cls");
}

bool positiveBook(Book book1, Book book2) {

    return book1.bookNum > book2.bookNum;

}


void Manager::sortBook() {
    sort(VCBook.begin(), VCBook.end(), positiveBook);

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        cout << "名称：" << bookBegin->bookName << "    ";
        cout << "余量：" << bookBegin->bookNum << endl;
    }
    system("pause");
    system("cls");
}

void Manager::countAllBook() {

    int bookNums = 0;

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        bookNums += bookBegin->bookNum;
    }

    cout << "图书库存总量：" << bookNums << endl;
    system("pause");
    system("cls");
}




