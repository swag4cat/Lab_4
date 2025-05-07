#include <iostream>
#include <cstdint>

using namespace std;

class Xorshift128 {
private:
    uint32_t x, y, z, w;

public:
    Xorshift128(uint32_t seed = 88675123) {
        // Инициализация стартовыми значениями
        x = seed;
        y = seed << 13;
        z = (seed >> 9) ^ 0xDEADBEEF;
        w = (seed << 7) ^ 0x12345678;
    }

    uint32_t next() {
        uint32_t t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w = w ^ (w >> 19) ^ (t ^ (t >> 8));
        return w;
    }

    // Функция для генерации вещественного числа от 0 до 1
    double nextDouble() {
        return static_cast<double>(next()) / static_cast<double>(UINT32_MAX);
    }
};

int main() {
    Xorshift128 rng;

    cout << "Генерация 10 псевдослучайных чисел:\n";
    for (int i = 0; i < 10; ++i) {
        cout << rng.next() << " ";
    }

    cout << "\n\nГенерация 10 псевдослучайных вещественных чисел [0; 1):\n";
    for (int i = 0; i < 10; ++i) {
        cout << rng.nextDouble() << " ";
    }

    return 0;
}
