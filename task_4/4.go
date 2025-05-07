package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Генерация случайных предпочтений избирателя (перестановка кандидатов)
func generatePermutation(n int, rng *rand.Rand) []int {
	perm := make([]int, n)
	for i := 0; i < n; i++ {
		perm[i] = i
	}
	rng.Shuffle(n, func(i, j int) {
		perm[i], perm[j] = perm[j], perm[i]
	})
	return perm
}

// Метод Борда
func bordaWinner(preferences [][]int, numCandidates int) int {
	scores := make([]int, numCandidates)

	for _, pref := range preferences {
		for i := 0; i < numCandidates; i++ {
			scores[pref[i]] += numCandidates - 1 - i
		}
	}

	maxScore := -1
	winner := 0
	fmt.Println("\nБаллы по методу Борда:")
	for i := 0; i < numCandidates; i++ {
		fmt.Printf("Кандидат %d: %d баллов\n", i+1, scores[i])
		if scores[i] > maxScore {
			maxScore = scores[i]
			winner = i
		}
	}

	return winner
}

// Метод Кондорсе
func condorcetWinner(preferences [][]int, numCandidates int) int {
	wins := make([][]int, numCandidates)
	for i := range wins {
		wins[i] = make([]int, numCandidates)
	}

	for _, pref := range preferences {
		for i := 0; i < numCandidates; i++ {
			for j := i + 1; j < numCandidates; j++ {
				candA := pref[i]
				candB := pref[j]
				wins[candA][candB]++
			}
		}
	}

	// Проверка на Кондорсе-победителя
	for i := 0; i < numCandidates; i++ {
		isWinner := true
		for j := 0; j < numCandidates; j++ {
			if i == j {
				continue
			}
			if wins[i][j] <= len(preferences)/2 {
				isWinner = false
				break
			}
		}
		if isWinner {
			return i
		}
	}

	return -1 // Кондорсе-победителя нет
}

func main() {
	rand.Seed(time.Now().UnixNano())
	rng := rand.New(rand.NewSource(time.Now().UnixNano()))

	var numCandidates, numVoters int
	fmt.Print("Введите количество кандидатов: ")
	fmt.Scan(&numCandidates)
	fmt.Print("Введите количество избирателей: ")
	fmt.Scan(&numVoters)

	preferences := make([][]int, numVoters)

	for i := 0; i < numVoters; i++ {
		perm := generatePermutation(numCandidates, rng)
		preferences[i] = perm
	}

	// Вывод предпочтений
	fmt.Println("\nПредпочтения избирателей:")
	for i := 0; i < numVoters; i++ {
		fmt.Printf("Избиратель %d: ", i+1)
		for _, j := range preferences[i] {
			fmt.Printf("%d ", j+1)
		}
		fmt.Println()
	}

	borda := bordaWinner(preferences, numCandidates)
	condorcet := condorcetWinner(preferences, numCandidates)

	fmt.Printf("\nПобедитель по методу Борда: Кандидат %d\n", borda+1)
	if condorcet != -1 {
		fmt.Printf("Победитель по методу Кондорсе: Кандидат %d\n", condorcet+1)
	} else {
		fmt.Println("Победитель по методу Кондорсе: не существует (нет универсального победителя)")
	}

	if condorcet != -1 && borda != condorcet {
		fmt.Println("\nВнимание: методы Борда и Кондорсе дали разных победителей.")
	}
}
