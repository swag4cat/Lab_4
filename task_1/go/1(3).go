package main

import (
	"fmt"
	"math"
)

// Исходная функция
func f(x float64) float64 {
	return x * math.Log(x+1) - 1
}

// Первая производная
func df(x float64) float64 {
	return math.Log(x+1) + x/(x+1)
}

// Вторая производная
func ddf(x float64) float64 {
	return 1.0/(x+1) + 1.0/((x+1)*(x+1))
}

// Метод Ньютона
func NewtonMethod(x, eps float64) float64 {
	k := 0
	prevX := x - 2*eps

	// Проверка условия сходимости
	if f(x)*ddf(x) <= 0 {
		fmt.Printf("Условие сходимости нарушено при x0 = %.6f. Попробуйте другое приближение.\n", x)
		return math.NaN()
	}

	fmt.Println("╔═════════════════════════════════════════════════════════════════════════════╗")
	fmt.Println("║   N   ║         x_n           ║         x_(n+1)       ║    x_(n+1) - x_n    ║")
	fmt.Println("╠═════════════════════════════════════════════════════════════════════════════╣")

	for math.Abs(x-prevX) > eps {
		prevX = x
		x = x - f(x)/df(x)
		fmt.Printf("║  %3d  ║\t%.6f\t║\t%.6f\t║\t%.6f      ║\n", k, prevX, x, math.Abs(x-prevX))
		k++
	}

	fmt.Println("╚═════════════════════════════════════════════════════════════════════════════╝")
	return x
}

func main() {
	eps := 1e-4

	fmt.Println("\n=== Поиск положительного корня ===")
	x0Pos := 1.5
	rootPos := NewtonMethod(x0Pos, eps)
	if !math.IsNaN(rootPos) {
		fmt.Printf("\nПоложительный корень (Ньютон): x ≈ %.6f\n", rootPos)
	}

	fmt.Println("\n=== Поиск отрицательного корня ===")
	x0Neg := -0.8
	rootNeg := NewtonMethod(x0Neg, eps)
	if !math.IsNaN(rootNeg) {
		fmt.Printf("\nОтрицательный корень (Ньютон): x ≈ %.6f\n", rootNeg)
	}
}
