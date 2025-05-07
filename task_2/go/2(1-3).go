package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())

	const n = 20 // можно изменить в пределах [15, 30]
	const m = 5
	arr1 := make([]int, n)
	arr2 := make([]int, m)

	// 1. Инициализация массивов случайными числами из [10, 30]
	for i := range arr1 {
		arr1[i] = rand.Intn(21) + 10
	}
	for i := range arr2 {
		arr2[i] = rand.Intn(21) + 10
	}

	fmt.Print("Массив arr1: ")
	for _, x := range arr1 {
		fmt.Printf("%d ", x)
	}
	fmt.Print("\nМассив arr2: ")
	for _, x := range arr2 {
		fmt.Printf("%d ", x)
	}
	fmt.Println("\n")

	// 2. Чётные элементы на нечётных индексах (индексация с 0)
	var evenOnOddIndices []int
	for i := 1; i < n; i += 2 {
		if arr1[i]%2 == 0 {
			evenOnOddIndices = append(evenOnOddIndices, arr1[i])
		}
	}

	fmt.Print("Чётные элементы на нечётных позициях в arr1: ")
	if len(evenOnOddIndices) == 0 {
		fmt.Println("нет таких элементов.")
	} else {
		for _, x := range evenOnOddIndices {
			fmt.Printf("%d ", x)
		}
		fmt.Printf("\nКоличество: %d\n", len(evenOnOddIndices))
	}

	// 3. Подсчёт совпадений из arr2 в arr1
	freq := make(map[int]int)
	for _, x := range arr1 {
		freq[x]++
	}

	found := false
	fmt.Println("\nСовпадения элементов из arr2 в arr1:")
	for _, x := range arr2 {
		if count, exists := freq[x]; exists && count > 0 {
			fmt.Printf("Число %d встречается %d раз(а)\n", x, count)
			found = true
		}
	}

	if !found {
		fmt.Println("Ни одно число из arr2 не встречается в arr1.")
	}
}
