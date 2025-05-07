package main

import (
	"fmt"
	"math"
)

// φ1(x) для положительного корня
func phiPositive(x float64) float64 {
	return 1.0 / math.Log(x+1)
}

func dphiPositive(x float64) float64 {
	return -1.0 / ((x + 1) * math.Pow(math.Log(x+1), 2)) // производная φ1(x)
}

// φ2(x) для отрицательного корня
func phiNegative(x float64) float64 {
	return math.Exp(1.0/x) - 1
}

func dphiNegative(x float64) float64 {
	return -math.Exp(1.0/x) / (x * x) // производная φ2(x)
}

func iterationMethod(x0, eps float64, phi, dphi func(float64) float64) float64 {
	k := 0
	prevX := x0 - 2*eps

	if math.Abs(dphi(x0)) >= 1 {
		fmt.Println("Метод не сходится при данном x0. Попробуйте другое начальное приближение.")
		return 0.0
	}

	fmt.Println("╔════════════════════════════════════════════════════════════════════════════╗")
	fmt.Println("║   N   ║         x_n           ║       x_(n+1)         ║   x_(n+1) - x_n    ║")
	fmt.Println("╠════════════════════════════════════════════════════════════════════════════╣")

	for math.Abs(x0-prevX) >= eps {
		prevX = x0
		x0 = phi(prevX)

		fmt.Printf("║  %3d  ║\t%.6f\t║\t%.6f\t║\t%.6f     ║\n", k, prevX, x0, math.Abs(x0-prevX))

		k++
	}

	fmt.Println("╚════════════════════════════════════════════════════════════════════════════╝")
	return x0
}

func main() {
	eps := 1e-4

	fmt.Println("\n=== Поиск положительного корня ===")
	x0Pos := 1.5
	rootPos := iterationMethod(x0Pos, eps, phiPositive, dphiPositive)
	fmt.Printf("\nПоложительный корень: x ≈ %.6f\n", rootPos)

	fmt.Println("\n=== Поиск отрицательного корня ===")
	x0Neg := -0.5
	rootNeg := iterationMethod(x0Neg, eps, phiNegative, dphiNegative)
	fmt.Printf("\nОтрицательный корень: x ≈ %.6f\n", rootNeg)
}
