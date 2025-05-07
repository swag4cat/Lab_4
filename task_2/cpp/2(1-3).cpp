#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0)));

    const int n = 20; // можно изменить в пределах [15, 30]
    const int m = 5;
    vector<int> arr1(n), arr2(m);

    // 1. Инициализация массивов случайными числами из [10, 30]
    for (int& x : arr1) x = rand() % 21 + 10;
    for (int& x : arr2) x = rand() % 21 + 10;

    cout << "Массив arr1: ";
    for (int x : arr1) cout << x << " ";
    cout << "\nМассив arr2: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n\n";

    // 2. Чётные элементы на нечётных индексах (индексация с 0)
    vector<int> evenOnOddIndices;
    for (int i = 1; i < n; i += 2) {
        if (arr1[i] % 2 == 0)
            evenOnOddIndices.push_back(arr1[i]);
    }

    cout << "Чётные элементы на нечётных позициях в arr1: ";
    if (evenOnOddIndices.empty()) {
        cout << "нет таких элементов.\n";
    } else {
        for (int x : evenOnOddIndices) cout << x << " ";
        cout << "\nКоличество: " << evenOnOddIndices.size() << "\n";
    }

    // 3. Подсчёт совпадений из arr2 в arr1
    map<int, int> freq;
    for (int x : arr1) freq[x]++;

    bool found = false;
    cout << "\nСовпадения элементов из arr2 в arr1:\n";
    for (int x : arr2) {
        if (freq[x] > 0) {
            cout << "Число " << x << " встречается " << freq[x] << " раз(а)\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Ни одно число из arr2 не встречается в arr1.\n";
    }

    return 0;
}
