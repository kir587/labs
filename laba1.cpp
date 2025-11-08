/*#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    int n;
    
    //флаг
    bool success = true;
    
    //ввод размера и проверка
    cout << "введите размер массива: ";
    if (!(cin >> n) || n <= 0) {
        cout << "введите еще раз" << endl;
        success = false;
    }
    
    int* array = 0;
    if (success) {
        //выделение памяти
        array = new int[n];
    }
    
    if (success) {
        //заполнение массива
        cout << "введите " << n << " целых чисел:" << endl;
        for (int i = 0; i < n; i++) {
            if (!(cin >> array[i])) {
                cout << "введите еще раз" << endl;
                success = false;
                break;
            }
        }
    }
    
    if (success) {
        //адрес начала массива
        cout << "\nадрес начала массива: " << array << endl;
        for (int i = 0; i < n; i++) {
            uintptr_t distance = reinterpret_cast<uintptr_t>(&array[i]) - reinterpret_cast<uintptr_t>(array);
            cout << "индекс - " << i << ", значение - " << array[i] 
                 << ", адрес - " << &array[i] << " расстояние - " << distance << " байт" << endl;
        }
    }
    
    //освобождение памяти
    if (array != 0) {
        delete[] array;
    }
}*/

#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    int n;
    
    //флаг
    bool success = true;
    
    //ввод размера и проверка
    cout << "введите размер массива: ";
    if (!(cin >> n) || n <= 0) {
        cout << "введите еще раз" << endl;
        success = false;
    }
    
    double* array = 0;
    if (success) {
        //выделение памяти
        array = new double[n];
    }
    
    if (success) {
        //заполнение массива
        cout << "введите " << n << " чисел типа double:" << endl;
        for (int i = 0; i < n; i++) {
            if (!(cin >> array[i])) {
                cout << "введите еще раз" << endl;
                success = false;
                break;
            }
        }
    }
    
    if (success) {
        //адрес начала массива
        cout << "\nадрес начала массива: " << array << endl;
        for (int i = 0; i < n; i++) {
            //вычисляем расстояние от начала в байтах
            uintptr_t distance = reinterpret_cast<uintptr_t>(&array[i]) - reinterpret_cast<uintptr_t>(array);
            cout << "индекс - " << i << ", значение - " << array[i] 
                 << ", адрес - " << &array[i] 
                 << ", расстояние - " << distance << " байт" << endl;
        }
    }
    
    //освобождение памяти
    if (array != 0) {
        delete[] array;
    }
}