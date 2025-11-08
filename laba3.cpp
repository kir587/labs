/*
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// базовый класс - деталь
class detail {
protected:
    string name; // название детали
    double weight; // вес детали
    
    // защищенный конструктор - запрещает прямое создание
    detail(string n, double w) : name(n), weight(w) {}
    
public:
    // виртуальный деструктор для корректного удаления
    virtual ~detail() {}
    
    // виртуальный метод показа информации
    virtual void show() {
        cout << "деталь: " << name << ", вес: " << weight << " кг" << endl; // вывод информации о детали
    }
    
    // объявление дружественной шаблонной функции
    template<typename type, typename... args>
    friend type* create(args... arguments);
};

// производный класс - сборка
class assembly : public detail {
private:
    vector<detail*> parts; // вектор для хранения компонентов сборки
    
protected:
    // защищенный конструктор сборки
    assembly(string n, double w) : detail(n, w) {}
    
public:
    // метод добавления детали в сборку
    void addpart(detail* part) {
        parts.push_back(part); // добавляем указатель в вектор
    }
    
    // переопределенный метод показа информации
    void show() override {
        cout << "сборка: " << name << endl; // вывод названия сборки
        cout << "  составные части:" << endl; // заголовок списка компонентов
        for (auto part : parts) { // цикл по всем компонентам
            cout << "    "; // отступ для выравнивания
            part->show(); // вызов метода show для компонента
        }
    }
    
    // объявление дружественной функции в производном классе
    template<typename type, typename... args>
    friend type* create(args... arguments);
};

// шаблонная функция для создания объектов
template<typename type, typename... args>
type* create(args... arguments) {
    return new type(arguments...); // создаем объект через new
}

int main() {
    vector<detail*> storage; // вектор для хранения всех объектов
    
    // создаем детали через дружественную функцию
    detail* bolt = create<detail>("болт", 0.1); // создаем болт
    detail* nut = create<detail>("гайка", 0.05); // создаем гайку
    detail* gear1 = create<detail>("шестерня", 0.5); // создаем первую шестерню для двигателя
    detail* gear2 = create<detail>("шестерня", 0.5); // создаем вторую шестерню для механизма
    
    // создаем сборки через дружественную функцию
    assembly* engine = create<assembly>("двигатель", 10.0); // создаем двигатель
    assembly* mechanism = create<assembly>("механизм", 5.0); // создаем механизм
    
    // добавляем детали в двигатель
    engine->addpart(bolt); // добавляем болт в двигатель
    engine->addpart(gear1); // добавляем первую шестерню в двигатель
    
    // добавляем детали в механизм
    mechanism->addpart(nut); // добавляем гайку в механизм
    mechanism->addpart(gear2); // добавляем вторую шестерню в механизм
    
    // сохраняем все объекты в хранилище
    storage.push_back(bolt); // сохраняем болт
    storage.push_back(nut); // сохраняем гайку
    storage.push_back(gear1); // сохраняем первую шестерню
    storage.push_back(gear2); // сохраняем вторую шестерню
    storage.push_back(engine); // сохраняем двигатель
    storage.push_back(mechanism); // сохраняем механизм
    
    // выводим информацию о всех объектах
    for (auto item : storage) { // цикл по всем объектам
        item->show(); // вызов виртуального метода show
        cout << endl; // пустая строка между объектами
    }
    
    // освобождаем память
    for (auto item : storage) { // цикл по всем объектам
        delete item; // удаляем объект
    }
}
*/



#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// базовый класс
class base {
protected:
    int value; // целочисленное значение

    // защищенный конструктор
    base(int v) : value(v) {}

public:
    // виртуальный деструктор
    virtual ~base() {}

    // виртуальный метод клонирования для создания копий
    virtual base* clone() const {
        return new base(*this); // создаем копию базового класса
    }

    // виртуальный метод для демонстрации поведения
    virtual void show() const {
        cout << "базовый класс, значение: " << value << endl; // вывод информации базового класса
    }

    // виртуальный метод для вычисления
    virtual int calculate() const {
        return value; // возвращаем просто значение
    }

    // дружественная функция для создания объектов
    template<typename t, typename... a>
    friend t* create(a... args);
};

// производный класс
class derived : public base {
private:
    int extra; // дополнительное значение

protected:
    // защищенный конструктор
    derived(int v, int e) : base(v), extra(e) {}

public:
    // переопределенный метод клонирования
    base* clone() const override {
        return new derived(*this); // создаем копию производного класса
    }

    // переопределенный метод show
    void show() const override {
        cout << "производный класс, значение: " << value << ", дополнительно: " << extra << endl; // вывод расширенной информации
    }

    // переопределенный метод calculate
    int calculate() const override {
        return value * extra; // возвращаем произведение значений
    }

    // дружественная функция
    template<typename t, typename... a>
    friend t* create(a... args);
};

// шаблонная функция для создания объектов
template<typename t, typename... a>
t* create(a... args) {
    return new t(args...); // создаем объект динамически
}

// функция для добавления копии объекта в хранилище
void add(vector<base*>& storage, const base& obj) {
    storage.push_back(obj.clone()); // создаем копию и добавляем в вектор
}

int main() {
    srand(time(0)); // инициализация генератора случайных чисел
    vector<base*> storage; // общее хранилище для объектов

    // цикл случайного создания объектов
    for (int i = 0; i < 6; i++) {
        base* original = nullptr; // указатель на оригинальный объект
        
        if (rand() % 2 == 0) { // случайное число четное
            original = create<base>(rand() % 100); // создаем базовый объект
            cout << "создан оригинал базового класса" << endl; // сообщение о создании
        } else { // случайное число нечетное
            original = create<derived>(rand() % 100, rand() % 10 + 1); // создаем производный объект
            cout << "создан оригинал производного класса" << endl; // сообщение о создании
        }
        
        add(storage, *original); // передаем копию объекта в функцию add
        delete original; // удаляем оригинальный объект
    }

    // показываем разницу в поведении объектов из хранилища
    for (size_t i = 0; i < storage.size(); i++) {
        cout << "объект " << i + 1 << " из хранилища: "; // номер объекта
        storage[i]->show(); // демонстрация поведения show
        cout << "результат вычисления: " << storage[i]->calculate() << endl; // демонстрация поведения calculate
    }
    // освобождаем все ресурсы
    for (auto obj : storage) { // цикл по всем объектам в хранилище
        delete obj; // удаляем объект
    }
    storage.clear(); // очищаем вектор
} 
