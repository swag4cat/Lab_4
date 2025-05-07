package main

import (
	"fmt"
	"math/rand"
	"sort"
	"strconv"
	"strings"
	"time"
)

// Функция сортировки цифр числа по возрастанию
func sortDigitsAscending(number int) int {
	s := strconv.Itoa(number)
	digits := strings.Split(s, "")
	sort.Strings(digits)
	sorted := strings.Join(digits, "")
	result, _ := strconv.Atoi(sorted)
	return result
}

func main() {
	rand.Seed(time.Now().UnixNano())

	const n = 10
	numbers := make([]int, n)
	transformed := make([]int, n)

	// Заполняем массив случайными числами от 1000 до 9000
	for i := range numbers {
		numbers[i] = rand.Intn(8001) + 1000
	}

	// Вывод исходного массива
	fmt.Print("Исходный массив: ")
	for _, num := range numbers {
		fmt.Printf("%d ", num)
	}
	fmt.Println()

	// Сумма исходного массива
	sumOriginal := 0
	for _, num := range numbers {
		sumOriginal += num
	}
	fmt.Printf("Сумма исходного массива: %d\n", sumOriginal)

	// Преобразование элементов: сортировка цифр в числе
	for i := 0; i < n; i++ {
		transformed[i] = sortDigitsAscending(numbers[i])
	}

	// Сортировка массива по возрастанию
	sort.Ints(transformed)

	// Вывод преобразованного и отсортированного массива
	fmt.Print("Преобразованный и отсортированный массив: ")
	for _, num := range transformed {
		fmt.Printf("%d ", num)
	}
	fmt.Println()

	// Сумма преобразованного массива
	sumTransformed := 0
	for _, num := range transformed {
		sumTransformed += num
	}
	fmt.Printf("Сумма преобразованного массива: %d\n", sumTransformed)

	// Сравнение сумм
	if sumOriginal == sumTransformed {
		fmt.Println("Суммы массивов равны.")
	} else {
		fmt.Println("Суммы массивов не равны.")
	}
}
