//
// Created by xiaoyou on 2019/6/8.
//

#include "../header/Reader.h"

//�޲ι���
Reader::Reader() {

}

/**
 * �вι���
 * @param id ����id
 * @param name  ��������
 * @param password  ��������
 */
Reader::Reader(int id, string name, string password) {

    this->id = id;
    this->name = name;
    this->password = password;
    //��ʼ��ͼ������
    ifstream readFile;
    readFile.open(BOOK_FILE, ios::in);  //��ȡ�ļ�
    Book book;
    while (readFile >> book.id && readFile >> book.bookName && readFile >> book.bookNum) {
        VCBook.push_back(book);
    }
    readFile.close();
}

//�����Ӳ˵�
void Reader::Menu() {
    cout << "\t\t��ӭ���ߣ�" << this->name << "  ��¼ϵͳ��" << endl;
    cout << "\t\t---------------------------------\n" << endl;
    cout << "\t\t|         1.�鿴�ѽ�ͼ��           |\n" << endl;
    cout << "\t\t|         2.����                  |\n" << endl;
    cout << "\t\t|         3.����                  |\n" << endl;
    cout << "\t\t|         4.��ѯͼ��               |\n" << endl;
    cout << "\t\t|         5.�鿴����ͼ��           |\n" << endl;
    cout << "\t\t|         6.�鿴���н�����Ϣ        |\n" << endl;
    cout << "\t\t|         0.ע����¼               |\n" << endl;
    cout << "\t\t---------------------------------\n" << endl;
}

//��ȡ��ǰϵͳʱ��
string Reader::getTime() {
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

//����
void Reader::borrowBook() {
    BorrowInformation borrowInformation;    //���ļ�¼��Ϣ�����
    string bookName;
    string status = "1";
    int flag = 0;
    cout << "������ͼ������" << endl;
    cin >> bookName;

    //�ж��Ƿ��Ѿ����Ĵ�ͼ��
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        //��ȡid
        int tempID = atoi(borrowInformation.borrowData[i]["ReaderID"].c_str()) ;
        //��ȡ����״̬
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        //��ͼ�����ơ�id��ͬ������״̬Ϊ�ڽ�ʱ�������ٽ���ͼ��
        if ((borrowInformation.borrowData[i]["BookName"] == bookName) &&
                (tempID == this->id) && (tempStatus == 1)) {
            cout << "���Ѿ����ĸ�ͼ��" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    //����ͼ�飬�����ڴ�ͼ�飬������������0ʱ���ſ��Խ��Ĵ�ͼ��
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if ((bookBegin->bookName == bookName) && (bookBegin->bookNum > 0)) {
            ofstream write;
            write.open(BORROW_INFORMATION_FILE, ios::app);
            write << "ReaderID:" << this->id << "\t";
            write << "ReaderName:" << this->name << "\t";
            write << "Time:" << this->getTime() << "\t";
            write << "BookName:" << bookName << "\t";
            write << "Status:" << status << endl;
            write.close();
            //����ͼ������
            this->changeBookNum(bookName, 1);


            cout << "�������" << endl;
            flag = 1;
        }
    }
    if (flag == 0) {
        cout << "���鲻���ڻ�������Ϊ0" << endl;
    }
    system("pause");
    system("cls");
}

//�鿴�ڽ��ͼ��
void Reader::showOnBorrow() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "û�н��ļ�¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "ͼ������\t" << "����ʱ��" << endl;
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        int tempID = atoi(borrowInformation.borrowData[i]["ReaderID"].c_str());
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        //��idƥ�䲢��״̬Ϊ�ڽ�ʱ����ʾ�˼�¼
        if ((this->id == tempID) && (1 == tempStatus)) {
            cout << borrowInformation.borrowData[i]["BookName"] << "\t\t";
            cout << borrowInformation.borrowData[i]["Time"] << endl;
        }
    }
    system("pause");
    system("cls");
    return;
}

//�黹ͼ��
void Reader::returnBook() {
    BorrowInformation borrowInformation;
    string bookName;

    cout << "������׼���黹��ͼ������: " << endl;
    cin>>bookName;
    //������ļ�¼�ļ���û���κμ�¼��ֱ���˳�
    if (borrowInformation.totalBorrowSize == 0){
        cout << "���κν��ļ�¼" << endl;
        return;
    }

    //�黹ͼ�飬������id��ͼ�����ƶ����Լ��¼�ļ��е�����ƥ�䣬���ҽ���״̬Ϊ�ڽ裬���Թ黹��ͼ��
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        //��ȡͼ������
        string tempBookName = borrowInformation.borrowData[i]["BookName"];
        //��ȡ����id
        int tempId = atoi(borrowInformation.borrowData[i]["ReaderID"].c_str());
        //��ȡ����ת̨
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());
        //��֤
        if ((tempBookName == bookName) &&(tempId == this->id) && (tempStatus == 1)){
            //����ͼ������
            this->changeBookNum(bookName, 2);
            borrowInformation.borrowData[i]["Status"] = "0";
            borrowInformation.updateBorrowInformation();
            cout << "�������" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    cout << "��û�н��Ĵ���" << endl;
    system("pause");
    system("cls");
    return;
}

//�鿴����ͼ��
void Reader::showAllBook() {

    if (VCBook.size() == 0){
        cout << "û��ͼ��" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "����\t" << "����" << endl;
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        cout << bookBegin->bookName << "\t";
        cout << bookBegin->bookNum << endl;
    }
    system("pause");
    system("cls");
    return;
}

//����ͼ��
bool Reader::findBookByName() {

    string bookName;
    cout << "������ͼ�����ƣ�" << endl;
    cin >> bookName;
    //����Ƿ���ڴ����Լ�ͼ������
    for (vector<Book>::iterator bookBegin = VCBook.begin(); bookBegin != VCBook.end(); bookBegin++) {
        if ((bookBegin->bookName == bookName)) {
            cout << "����" << "  ����" << endl;
            cout << bookBegin->bookName << "  ";
            cout << bookBegin->bookNum << endl;
            system("pause");
            system("cls");
            return true;
        }
    }
    return false;

}

//�鿴�Լ������н�����Ϣ
void Reader::showAllBorrowInf() {
    BorrowInformation borrowInformation;
    if (borrowInformation.totalBorrowSize == 0) {
        cout << "û�н��ļ�¼" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "����������\t" << "ͼ������\t" << "����ʱ��\t" << "״̬" << endl;
    for (int i = 0; i < borrowInformation.totalBorrowSize; i++) {
        int tempID = atoi(borrowInformation.borrowData[i]["ReaderID"].c_str());
        int tempStatus = atoi(borrowInformation.borrowData[i]["Status"].c_str());

        if (this->id == tempID ) {
            cout << this->name << "\t\t";
            cout << borrowInformation.borrowData[i]["BookName"] << "\t\t";
            cout << borrowInformation.borrowData[i]["Time"] << "\t";
            if (tempStatus == 0){
                cout << "�ѹ黹" << endl;
            } else{
                cout << "�ڽ�" << endl;
            }
        }
    }
    system("pause");
    system("cls");
    return;
}

//����ͼ��������type��1�����٣�2������
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

