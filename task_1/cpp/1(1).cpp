#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Исходная функция: f(x) = x * ln(x + 1) - 1
double f(double x) {
    return x * log(x + 1) - 1;
}

// Метод половинного деления
double halfMethod(double Left, double Right, double eps) {
    int k = 0;
    double c;

    // Проверка применимости
    if (f(Left) * f(Right) >= 0) {
        cout << "Метод неприменим на интервале [" << Left << ", " << Right << "] — нет смены знака.\n";
        return NAN;
    }

    cout << "╔════════════════════════════════════════════════╗" << endl;
    cout << "║   N   ║     a_n    ║     b_n    ║   b_n - a_n  ║" << endl;
    cout << "╠════════════════════════════════════════════════╣" << endl;

    while (fabs(Right - Left) >= eps) {
        c = (Left + Right) / 2.0;
        cout << fixed << setprecision(6)
        << "║  " << setw(3) << k << "  ║ "
        << setw(10) << Left << " ║ "
        << setw(10) << Right << " ║ "
        << setw(12) << Right - Left << " ║" << endl;

        if (f(Left) * f(c) < 0)
            Right = c;
        else
            Left = c;

        ++k;
    }

    cout << "╚════════════════════════════════════════════════╝" << endl;
    return (Left + Right) / 2.0;
}

int main() {
    const double eps = 1e-4;

    // Корень 1: положительный
    cout << "\n=== Поиск положительного корня методом половинного деления ===\n";
    double root_pos = halfMethod(1.0, 2.0, eps);
    if (!isnan(root_pos))
        cout << "Положительный корень: x ≈ " << setprecision(6) << root_pos << endl;

    // Корень 2: отрицательный
    cout << "\n=== Поиск отрицательного корня методом половинного деления ===\n";
    double root_neg = halfMethod(-0.9, -0.5, eps);  // заранее подобранный отрезок с f(a)·f(b) < 0
    if (!isnan(root_neg))
        cout << "Отрицательный корень: x ≈ " << setprecision(6) << root_neg << endl;

    return 0;
}
