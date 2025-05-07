package main

import (
	"fmt"
	"math/rand"
	"time"
)

func getRandomChar() byte {
	const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()"
	return chars[rand.Intn(len(chars))]
}

func main() {
	rand.Seed(time.Now().UnixNano())

	const n = 10 // можно выбрать любое значение
	symbols := make([]byte, n)

	// Заполняем массив случайными символами
	for i := range symbols {
		symbols[i] = getRandomChar()
	}

	// Вывод начального массива
	fmt.Print("Исходный массив: [")
	for i := 0; i < n; i++ {
		fmt.Printf("%c", symbols[i])
		if i != n-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")

	// Сдвиг влево на 1, первый элемент — в конец
	first := symbols[0]
	copy(symbols[:n-1], symbols[1:])
	symbols[n-1] = first

	// Вывод модифицированного массива
	fmt.Print("Модифицированный массив: [")
	for i := 0; i < n; i++ {
		fmt.Printf("%c", symbols[i])
		if i != n-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}
