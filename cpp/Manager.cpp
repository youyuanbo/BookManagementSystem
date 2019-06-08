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
    cout << "\t\t|         4.�鿴ͼ��             |\n" << endl;
    cout << "\t\t|         5.ɾ��ͼ��             |\n" << endl;
    cout << "\t\t|         6.�鿴������Ϣ          |\n" << endl;
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
    cout << "��ǰ����������" << VCReader.size() << endl;
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
    cout << "��ǰͼ��������" << VCBook.size() << endl;
    readFile.close();
}

//��Ӷ���
void Manager::addReader() {
    string fileName;    //��������ļ�����
    string errorIdTip;    //id���ظ���ʾ
    ofstream output;    //����ļ�������

    fileName = READER_FILE;
    //����׷�ӵķ�ʽ��д�ļ�
    output.open(fileName, ios::out | ios::app);
    //��������
    int id;
    string name;
    string password;
    cout << "������id: " << endl;
    while (true) {
        cin >> id;
        bool result = this->checkReaderRepeat(id);
        if (result) {    //���ظ�
            cout << "����id�ظ������������룺" << endl;
        } else {
            //û���ظ���ֱ���˳�
            break;
        }
    }

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
    cout << "�����: " << reader.id << "\t������" << reader.name << "\t���룺" << reader.password << endl;
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

    fileName = BOOK_FILE;
    //����׷�ӵķ�ʽ��д�ļ�
    output.open(fileName, ios::out | ios::app);
    //��������
    int id;
    string bookName;
    int bookNum;
    cout << "������ͼ��id: " << endl;
    while (true) {
        cin >> id;
        bool result = this->checkBookRepeat(id);
        if (result) {    //���ظ�
            cout << "ͼ��id�ظ������������룺" << endl;
        } else {
            //û���ظ���ֱ���˳�
            break;
        }
    }

    //����ͼ������
    cout << "������ͼ�����ƣ�" << endl;
    cin >> bookName;
    //����ͼ������
    cout << "������ͼ��������" << endl;
    cin >> bookNum;

    //���ļ����������
    output << id << " " << bookName << " " << bookNum << endl;
    cout << "��ӳɹ�" << endl;
    system("pause");
    system("cls");
    //�ر��ļ�
    output.close();
    this->initVector();
}

//���ͼ����Ϣ
void printBook(Book &book) {
    cout << book.bookName << "\t\t" << book.bookNum << endl;
}

//�鿴ͼ��
void Manager::showBooks() {
    cout << "����ͼ����Ϣ" << endl;
    cout << "ͼ������\t" << "ͼ������\t" <<  endl;
    for_each(VCBook.begin(), VCBook.end(), printBook);
    system("pause");
    system("cls");
}

//������id�Ƿ��ظ�
bool Manager::checkReaderRepeat(int id) {
    //������id�Ƿ��ظ�
    for (vector<Reader>::iterator readerBegin = VCReader.begin(); readerBegin != VCReader.end(); readerBegin++) {
        if (id == readerBegin->id) {
            return true;
        }
    }
    return false;
}

//���ͼ��id�Ƿ��ظ�
bool Manager::checkBookRepeat(int id) {

    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if (id == bookBegin->id) {
            return true;
        }
    }
    return false;
}

//ɾ��ͼ��
void Manager::deleteBook() {
    string bookName;
    cout << "������Ҫɾ����ͼ�����ƣ�" << endl;
    cin >> bookName;
    cout << "���������У���Ⱥ�" << endl;
    system("pause");
    system("cls");
    return;
}

void Manager::showAllBorrowInformation() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "û�н��ļ�¼" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "����������\t" << "ͼ������\t" << "����ʱ��\t" << "״̬" << endl;
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        cout << borrowInformation.borrowData[i]["ReaderName"] << "\t\t";
        cout << borrowInformation.borrowData[i]["BookName"] << "\t\t";
        cout << borrowInformation.borrowData[i]["Time"] << "\t";
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


