package main

import (
	"fmt"
	"math"
)

// Исходная функция: f(x) = x * ln(x + 1) - 1
func f(x float64) float64 {
	return x * math.Log(x+1) - 1
}

// Метод половинного деления
func halfMethod(Left, Right, eps float64) float64 {
	k := 0
	var c float64

	// Проверка применимости
	if f(Left)*f(Right) >= 0 {
		fmt.Printf("Метод неприменим на интервале [%.6f, %.6f] — нет смены знака.\n", Left, Right)
		return math.NaN()
	}

	fmt.Println("╔════════════════════════════════════════════════╗")
	fmt.Println("║   N   ║     a_n    ║     b_n    ║   b_n - a_n  ║")
	fmt.Println("╠════════════════════════════════════════════════╣")

	for math.Abs(Right-Left) >= eps {
		c = (Left + Right) / 2.0
		fmt.Printf("║  %3d  ║ %10.6f ║ %10.6f ║ %12.6f ║\n", k, Left, Right, Right-Left)

		if f(Left)*f(c) < 0 {
			Right = c
		} else {
			Left = c
		}

		k++
	}

	fmt.Println("╚════════════════════════════════════════════════╝")
	return (Left + Right) / 2.0
}

func main() {
	const eps = 1e-4

	// Корень 1: положительный
	fmt.Println("\n=== Поиск положительного корня методом половинного деления ===")
	root_pos := halfMethod(1.0, 2.0, eps)
	if !math.IsNaN(root_pos) {
		fmt.Printf("Положительный корень: x ≈ %.6f\n", root_pos)
	}

	// Корень 2: отрицательный
	fmt.Println("\n=== Поиск отрицательного корня методом половинного деления ===")
	root_neg := halfMethod(-0.9, -0.5, eps) // заранее подобранный отрезок с f(a)·f(b) < 0
	if !math.IsNaN(root_neg) {
		fmt.Printf("Отрицательный корень: x ≈ %.6f\n", root_neg)
	}
}
