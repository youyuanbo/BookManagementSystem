//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/Manager.h"

/**
 * ����Ա��
 */

Manager::Manager() {

}

/**
 * �вι��캯��
 * @param name  ����
 * @param password  ����
 */
Manager::Manager(string name, string password) {
    this->name = name;
    this->password = password;
    this->initVector();

}

//����Ա�˵�
void Manager::Menu() {
    cout << "\t\t��ӭ����Ա��" << this->name << "��¼ϵͳ��" << endl;
    cout << "\t\t---------------------------------\n" << endl;
    cout << "\t\t|         1.����˺�             |\n" << endl;
    cout << "\t\t|         2.�鿴�˺�             |\n" << endl;
    cout << "\t\t|         3.���ͼ��             |\n" << endl;
    cout << "\t\t|         4.����ͼ��             |\n" << endl;
    cout << "\t\t|         5.�鿴����ͼ��          |\n" << endl;
    cout << "\t\t|         6.ɾ��ͼ��             |\n" << endl;
    cout << "\t\t|         7.�鿴������Ϣ          |\n" << endl;
    cout << "\t\t|         8.ͼ������             |\n" << endl;
    cout << "\t\t|         9.�������             |\n" << endl;
    cout << "\t\t|         0.ע����¼             |\n" << endl;
    cout << "\t\t---------------------------------\n" << endl;
}

//��ʼ������
void Manager::initVector() {
    //ȷ��������û������
    this->VCReader.clear();
    this->VCBook.clear();

    //��ȡ������Ϣ
    ifstream readFile;
    readFile.open(READER_FILE, ios::in);
    if (!readFile.is_open()) {
        cout << "�����ļ���ȡʧ��" << endl;
        return;
    }
    Reader reader;  //��ȡ��Ϣ
    while (readFile >> reader.id && readFile >> reader.name && readFile >> reader.password) {
        VCReader.push_back(reader);
    }
    readFile.close();


    //��ʼ��ͼ����Ϣ
    readFile.open(BOOK_FILE, ios::in);
    if (!readFile.is_open()) {
        cout << "ͼ����Ϣ�ļ���ʧ��" << endl;
    }
    Book book;
    while (readFile >> book.id && readFile >> book.bookName && readFile >> book.bookNum) {
        VCBook.push_back(book);
    }
    readFile.close();
}

//��Ӷ���
void Manager::addReader() {
    string fileName;    //��������ļ�����
    string errorIdTip;    //id���ظ���ʾ
    ofstream output;    //����ļ�������
    BookUtil bookUtil;

    fileName = READER_FILE;
    //����׷�ӵķ�ʽ��д�ļ�
    output.open(fileName, ios::out | ios::app);
    //��������
    string id = bookUtil.getId();
    string name;
    string password;

    //��������
    cout << "������������" << endl;
    cin >> name;
    //��������
    cout << "���������룺" << endl;
    cin >> password;

    //���ļ����������
    output << id << " " << name << " " << password << endl;
    cout << "��ӳɹ�" << endl;
    system("pause");
    system("cls");

    output.close();
    this->initVector();
}

//���������Ϣ
void printReader(Reader &reader) {
    cout << "�����: " << reader.id << "    ������" << reader.name << "    ���룺" << reader.password << endl;
}

//�鿴������Ϣ
void Manager::showReader() {
    cout << "���еĶ�����Ϣ��" << endl;
    for_each(VCReader.begin(), VCReader.end(), printReader);

    system("pause");
    system("cls");
}

//���ͼ��
void Manager::addBook() {
    string fileName;    //��������ļ�����
    ofstream output;    //����ļ�������
    BookUtil bookUtil;

    fileName = BOOK_FILE;
    //����׷�ӵķ�ʽ��д�ļ�
    output.open(fileName, ios::out | ios::app);
    //��������
    string id = bookUtil.getId();
    string bookName;
    int bookNum;

    //����ͼ������
    cout << "������ͼ�����ƣ�" << endl;
    cin >> bookName;
    //����ͼ������
    cout << "������ͼ��������" << endl;
    cin >> bookNum;

    //���ļ����������
    output << id << "\t" << bookName << "\t" << bookNum << endl;
    cout << "��ӳɹ�" << endl;
    system("pause");
    system("cls");
    //�ر��ļ�
    output.close();
    this->initVector();
}

//���ͼ����Ϣ
void printBook(Book &book) {
    cout << "ͼ������: " << book.bookName << "    ͼ������: " << book.bookNum << endl;
}

//�鿴ͼ��
void Manager::showBooks() {
    for_each(VCBook.begin(), VCBook.end(), printBook);
    system("pause");
    system("cls");
}

//ɾ��ͼ��
void Manager::deleteBook() {
    string bookName;
    cout << "������Ҫɾ����ͼ�����ƣ�" << endl;
    cin >> bookName;
    int index = 0;
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if (bookName == bookBegin->bookName) {
            VCBook.erase(bookBegin);
            cout << "ɾ���ɹ�" << endl;

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
    cout << "ͼ�鲻����" << endl;
    system("pause");
    system("cls");
    return;
}

//�鿴���н�����Ϣ
void Manager::showAllBorrowInformation() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "û�н��ļ�¼" << endl;
        system("pause");
        system("cls");
        return;
    }


    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        cout << "������������" << borrowInformation.borrowData[i]["ReaderName"] << "  ";
        cout << "ͼ�����ƣ�" << borrowInformation.borrowData[i]["BookName"] << "  ";
        cout << "����ʱ�䣺" << borrowInformation.borrowData[i]["Time"] << "  ";
        cout << "״̬��";
        if (tempStatus == 0) {
            cout << "�ѹ黹" << endl;
        } else {
            cout << "�ڽ�" << endl;
        }

    }
    system("pause");
    system("cls");
    return;
}

//��ѯͼ��
void Manager::findBookByName() {

    //ͼ������
    string bookName;
    cout << "������ͼ�����ƣ�" << endl;
    cin >> bookName;
    //����Ƿ���ڴ����Լ�ͼ������
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        //�Ƿ����ͼ��
        if ((bookBegin->bookName == bookName)) {
            //���ͼ�����ϸ��Ϣ
            cout << "���ƣ�" << bookBegin->bookName << "    ";
            cout << "������" << bookBegin->bookNum << endl;
            //��������
            system("pause");
            system("cls");
            return;
        }
    }
    //û���ҵ���ͼ�飬�����ʾ
    cout << "���ѯ�������ǣ�" << bookName << "����ͼ�鲻����" << endl;
    system("pause");
    system("cls");
}

bool positiveBook(Book book1, Book book2) {

    return book1.bookNum > book2.bookNum;

}


void Manager::sortBook() {
    sort(VCBook.begin(), VCBook.end(), positiveBook);

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        cout << "���ƣ�" << bookBegin->bookName << "    ";
        cout << "������" << bookBegin->bookNum << endl;
    }
    system("pause");
    system("cls");
}

void Manager::countAllBook() {

    int bookNums = 0;

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        bookNums += bookBegin->bookNum;
    }

    cout << "ͼ����������" << bookNums << endl;
    system("pause");
    system("cls");
}




