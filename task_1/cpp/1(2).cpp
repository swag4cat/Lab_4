#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// φ1(x) для положительного корня
double phi_positive(double x) {
    return 1.0 / log(x + 1);
}

double dphi_positive(double x) {
    return -1.0 / ((x + 1) * pow(log(x + 1), 2)); // производная φ1(x)
}

// φ2(x) для отрицательного корня
double phi_negative(double x) {
    return exp(1.0 / x) - 1;
}

double dphi_negative(double x) {
    return -exp(1.0 / x) / (x * x); // производная φ2(x)
}

double iterationMethod(double x0, double eps,
                       double (*phi)(double), double (*dphi)(double)) {
    int k = 0;
    double prevX = x0 - 2 * eps;

    if (fabs(dphi(x0)) >= 1) {
        cout << "Метод не сходится при данном x0. Попробуйте другое начальное приближение." << endl;
        return 0.0;
    }

    cout << "╔════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║   N   ║         x_n           ║       x_(n+1)         ║   x_(n+1) - x_n    ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════╣\n";

    while (fabs(x0 - prevX) >= eps) {
        prevX = x0;
        x0 = phi(prevX);

        cout << fixed << setprecision(6)
        << "║  " << setw(3) << k << "  ║\t"
        << prevX << "\t║\t" << x0 << "\t║\t"
        << fabs(x0 - prevX) << "     ║" << "\n";

        ++k;
    }

    cout << "╚════════════════════════════════════════════════════════════════════════════╝\n";
    return x0;
                       }

                       int main() {
                           double eps = 1e-4;

                           cout << "\n=== Поиск положительного корня ===\n";
                           double x0_pos = 1.5;
                           double root_pos = iterationMethod(x0_pos, eps, phi_positive, dphi_positive);
                           cout << "\nПоложительный корень: x ≈ " << root_pos << "\n";

                           cout << "\n=== Поиск отрицательного корня ===\n";
                           double x0_neg = -0.5;
                           double root_neg = iterationMethod(x0_neg, eps, phi_negative, dphi_negative);
                           cout << "\nОтрицательный корень: x ≈ " << root_neg << "\n";

                           return 0;
                       }
