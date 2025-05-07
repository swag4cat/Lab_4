#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

char getRandomChar() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
    return chars[rand() % chars.size()];
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    const int n = 10; // можно выбрать любое значение
    vector<char> symbols(n);

    // Заполняем массив случайными символами
    for (char &c : symbols) {
        c = getRandomChar();
    }

    // Вывод начального массива
    cout << "Исходный массив: [";
    for (int i = 0; i < n; ++i) {
        cout << symbols[i];
        if (i != n - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Сдвиг влево на 1, первый элемент — в конец
    char first = symbols[0];
    for (int i = 1; i < n; ++i) {
        symbols[i - 1] = symbols[i];
    }
    symbols[n - 1] = first;

    // Вывод модифицированного массива
    cout << "Модифицированный массив: [";
    for (int i = 0; i < n; ++i) {
        cout << symbols[i];
        if (i != n - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
