#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Исходная функция
double f(double x) {
    return x * log(x + 1) - 1;
}

// Первая производная
double df(double x) {
    return log(x + 1) + x / (x + 1);
}

// Вторая производная
double ddf(double x) {
    return 1.0 / (x + 1) + 1.0 / ((x + 1) * (x + 1));
}

// Метод Ньютона
double NewtonMethod(double x, double eps) {
    int k = 0;
    double prevX = x - 2 * eps;

    // Проверка условия сходимости
    if (f(x) * ddf(x) <= 0) {
        cout << "Условие сходимости нарушено при x0 = " << x << ". Попробуйте другое приближение.\n";
        return NAN;
    }

    cout << "╔═════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║   N   ║         x_n           ║         x_(n+1)       ║    x_(n+1) - x_n    ║\n";
    cout << "╠═════════════════════════════════════════════════════════════════════════════╣\n";

    while (fabs(x - prevX) > eps) {
        prevX = x;
        x = x - f(x) / df(x);
        cout << fixed << setprecision(6)
        << "║  " << setw(3) << k << "  ║\t"
        << prevX << "\t║\t" << x << "\t║\t"
        << fabs(x - prevX) << "      ║" << "\n";
        ++k;
    }

    cout << "╚═════════════════════════════════════════════════════════════════════════════╝\n";
    return x;
}

int main() {
    double eps = 1e-4;

    cout << "\n=== Поиск положительного корня ===\n";
    double x0_pos = 1.5;
    double root_pos = NewtonMethod(x0_pos, eps);
    if (!isnan(root_pos))
        cout << "\nПоложительный корень (Ньютон): x ≈ " << setprecision(6) << root_pos << "\n";

    cout << "\n=== Поиск отрицательного корня ===\n";
    double x0_neg = -0.8;
    double root_neg = NewtonMethod(x0_neg, eps);
    if (!isnan(root_neg))
        cout << "\nОтрицательный корень (Ньютон): x ≈ " << setprecision(6) << root_neg << "\n";

    return 0;
}
