#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

// Функция сортировки цифр числа по возрастанию
int sortDigitsAscending(int number) {
    string s = to_string(number);
    sort(s.begin(), s.end());
    return stoi(s);
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    const int n = 10;
    vector<int> numbers(n);
    vector<int> transformed(n);

    // Заполняем массив случайными числами от 1000 до 9000
    for (int &num : numbers) {
        num = rand() % 8001 + 1000;
    }

    // Вывод исходного массива
    cout << "Исходный массив: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;

    // Сумма исходного массива
    int sumOriginal = 0;
    for (int num : numbers) sumOriginal += num;
    cout << "Сумма исходного массива: " << sumOriginal << endl;

    // Преобразование элементов: сортировка цифр в числе
    for (int i = 0; i < n; ++i) {
        transformed[i] = sortDigitsAscending(numbers[i]);
    }

    // Сортировка массива по возрастанию
    sort(transformed.begin(), transformed.end());

    // Вывод преобразованного и отсортированного массива
    cout << "Преобразованный и отсортированный массив: ";
    for (int num : transformed) cout << num << " ";
    cout << endl;

    // Сумма преобразованного массива
    int sumTransformed = 0;
    for (int num : transformed) sumTransformed += num;
    cout << "Сумма преобразованного массива: " << sumTransformed << endl;

    // Сравнение сумм
    if (sumOriginal == sumTransformed)
        cout << "Суммы массивов равны." << endl;
    else
        cout << "Суммы массивов не равны." << endl;

    return 0;
}
