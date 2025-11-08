/*
#include <iostream>
#include <string>
using namespace std;

class publication {
public:
    string title;
    float price;
    
    void getdata() {
        cout << "введите название: ";
        getline(cin, title); // читаем всю строку с пробелами
        cout << "введите цену: ";
        cin >> price;
    }
    
    void putdata() {
        cout << "название: " << title << endl;
        cout << "цена: " << price << " руб." << endl;
    }
};

class Book : public publication {
public:
    int pages;
    void getdata() {
        publication::getdata();
        cout << "введите количество страниц: ";
        cin >> pages;
        cin.ignore(); // очищаем /n после ввода числа чтоб все работало корректно
    }
    
    void putdata() {
        publication::putdata();
        cout << "страниц: " << pages << endl;
    }
};

class Tape : public publication {
public:
    float time;
    void getdata() {
        publication::getdata();
        cout << "введите время записи (минуты): ";
        cin >> time;
        cin.ignore(); // очищаем /n после ввода числа чтоб все работало корректно
    }
    
    void putdata() {
        publication::putdata();
        cout << "время записи: " << time << " минут" << endl;
    }
};

int main() {
    Book book; // создаем объект книги
    Tape tape; // создаем объект аудиозаписи
    cout << "ввод данных о книге:" << endl;
    book.getdata(); // вводим данные книги
    cout << endl << "ввод данных о аудиозаписи:" << endl;
    tape.getdata(); // вводим данные аудиозаписи
    cout << endl << "информация о книге:" << endl;
    book.putdata(); // выводим информацию о книге
    cout << endl << "информация об аудиозаписи:" << endl;
    tape.putdata(); // выводим информацию об аудиозаписи
}
*/

#include <iostream>
#include <string>
using namespace std;

class sales {
public:
    float salesarr[3]; // массив продаж за 3 месяца
    void getsalesdata() {
        cout << "введите продажи за последние 3 месяца:" << endl;
        for(int i = 0; i < 3; i++) {
            cout << "месяц " << i+1 << ": ";
            cin >> salesarr[i]; // вводим продажи за каждый месяц
        }
    }
    
    void putsalesdata() {
        cout << "продажи за 3 месяца: ";
        for(int i = 0; i < 3; i++) {
            cout << salesarr[i] << " "; // выводим продажи
        }
        cout << "руб." << endl;
    }
};

class publication {
public:
    string title;
    float price;
    void getdata() {
        cout << "введите название: ";
        getline(cin, title);
        cout << "введите цену: ";
        cin >> price;
    }
    
    void putdata() {
        cout << "название: " << title << endl;
        cout << "цена: " << price << " руб." << endl;
    }
};

class Book : public publication, public sales {
public:
    int pages;
    void getdata() {
        publication::getdata();
        sales::getsalesdata();
        cout << "введите количество страниц: ";
        cin >> pages;
        cin.ignore(); // очищаем /n после ввода числа чтоб все работало корректно
    }
    
    void putdata() {
        publication::putdata();
        sales::putsalesdata();
        cout << "страниц: " << pages << endl;
    }
};

class Tape : public publication, public sales {
public:
    float time;
    void getdata() {
        publication::getdata();
        sales::getsalesdata();
        cout << "введите время записи (минуты): ";
        cin >> time;
        cin.ignore(); // очищаем /n после ввода числа чтоб все работало корректно
    }
    
    void putdata() {
        publication::putdata();
        sales::putsalesdata();
        cout << "время записи: " << time << " минут" << endl;
    }
};

int main() {
    Book book;
    Tape tape;
    cout << "ввод данных о книге:" << endl;
    book.getdata(); // вводим данные книги
    cout << endl << "ввод данных о аудиозаписи:" << endl;
    tape.getdata(); // вводим данные аудиозаписи
    cout << endl << "информация о книге:" << endl;
    book.putdata(); // выводим информацию о книге
    cout << endl << "информация об аудиозаписи:" << endl;
    tape.putdata(); // выводим информацию об аудиозаписи
}