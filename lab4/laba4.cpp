#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> 
using namespace std; 

// базовый класс ошибки
class ProgramError : public exception {
    string msg; // сообщение об ошибке
public:
    ProgramError(const string& message) : msg(message) {} // конструктор
    const char* what() const noexcept override { return msg.c_str(); } // метод what
};

// ошибка доступа к памяти
class MemoryAccessError : public ProgramError {
public:
    MemoryAccessError(const string& msg) : ProgramError(msg) {} // конструктор
};

// математическая ошибка
class MathError : public ProgramError {
public:
    MathError(const string& msg) : ProgramError(msg) {} // конструктор
};

// деление на ноль
class DivisionByZeroError : public MathError {
public:
    DivisionByZeroError(const string& msg) : MathError(msg) {} // конструктор
};

// переполнение
class OverflowError : public MathError {
public:
    OverflowError(const string& msg) : MathError(msg) {} // конструктор
};

// шаблонный класс для массива указателей
template<class T>
class PointerArray {
    vector<T*> arr; // вектор для хранения указателей
public:
    // деструктор освобождает память
    ~PointerArray() {
        for (auto ptr : arr) { // проходим по всем элементам
            delete ptr; // удаляем каждый объект
        }
    }
    
    // оператор [] с проверкой границ
    T*& operator[](int index) {
        if (index < 0 || index >= arr.size()) { // проверяем валидность индекса
            throw MemoryAccessError("неверный индекс: " + to_string(index)); // бросаем исключение
        }
        return arr[index]; // возвращаем указатель
    }
    
    // добавление элемента
    void add(T* item) {
        arr.push_back(item); // добавляем указатель в конец вектора
    }
    
    // получение размера
    int size() const {
        return arr.size(); // возвращаем размер массива
    }
};

class Number {
    int value;
public:
    Number(int v) : value(v) { // конструктор
        cout << "создан Number: " << value << endl;
    }
    ~Number() { // деструктор
        cout << "удален Number: " << value << endl;
    }
    void print() const { // метод печати
        cout << "Number: " << value << endl;
    }
    int getValue() const { return value; } // геттер для значения
};

// функции для демонстрации исключений
int safeDivide(int a, int b) {
    if (b == 0) throw DivisionByZeroError("деление на ноль"); // проверка деление на ноль
    return a / b; // возвращаем результат
}

int safeAdd(int a, int b) {
    if (a > 0 && b > INT_MAX - a) throw OverflowError("переполнение при сложении"); // проверка переполнения
    if (a < 0 && b < INT_MIN - a) throw OverflowError("переполнение при сложении"); // проверка переполнения
    return a + b; // возвращаем результат
}

int main() {

    // демонстрация исключений
    cout << "1. демонстрация исключений:" << endl; // заголовок раздела
    
    try {
        throw MemoryAccessError("ошибка доступа к памяти");
    } catch (const exception& e) {
        cout << "поймано: " << e.what() << endl; // обрабатываем исключение
    }
    
    try {
        safeDivide(10, 0); // вызываем деление на ноль
    } catch (const exception& e) {
        cout << "поймано: " << e.what() << endl; // обрабатываем исключение
    }
    
    try {
        safeAdd(INT_MAX, 1); // вызываем сложение с переполнением
    } catch (const exception& e) {
        cout << "поймано: " << e.what() << endl; // обрабатываем исключение
    }

    cout << "\n2. демонстрация с классом Number:" << endl;
    PointerArray<Number> numbers; // создаем массив указателей на Number
    
    numbers.add(new Number(10)); // добавляем первый объект
    numbers.add(new Number(20)); // добавляем второй объект
    numbers.add(new Number(30)); // добавляем третий объект
    
    cout << "\nиспользование оператора []:" << endl;
    for (int i = 0; i < numbers.size(); i++) { // проходим по всем элементам
        numbers[i]->print(); // вызываем метод print
    }
    
    // проверка выхода за границы
    cout << "\nпроверка выхода за границы:" << endl; 
    try {
        numbers[5]->print(); // пытаемся обратиться к несуществующему элементу
    } catch (const exception& e) {
        cout << "ошибка: " << e.what() << endl; // обрабатываем исключение
    }

    // демонстрация с int
    cout << "\n3. демонстрация с типом int:" << endl;
    PointerArray<int> ints; // создаем массив указателей на int
    
    ints.add(new int(100)); // добавляем первый int
    ints.add(new int(200)); // добавляем второй int
    
    cout << "значения: ";
    for (int i = 0; i < ints.size(); i++) { // проходим по всем элементам
        cout << *ints[i] << " "; // выводим значение
    }
    cout << endl;

    // демонстрация с string
    cout << "\n4. демонстрация с типом string:" << endl;
    PointerArray<string> strings; // создаем массив указателей на string
    
    strings.add(new string("Hello")); // добавляем первую строку
    strings.add(new string("World")); // добавляем вторую строку
    
    cout << "строки: ";
    for (int i = 0; i < strings.size(); i++) { // проходим по всем элементам
        cout << *strings[i] << " "; // выводим строку
    }
    cout << endl;
}