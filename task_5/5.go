package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Тип стратегии
type Strategy func(int, []bool, []bool) bool

// Стратегия 1: Обидчивый — предаёт, если противник предавал более 50% раз
func grudger(round int, self []bool, enemy []bool) bool {
	if round == 0 {
		return true
	}
	betrayals := 0
	for _, e := range enemy {
		if !e {
			betrayals++
		}
	}
	return betrayals <= round/2
}

// Стратегия 2: Всегда предаёт
func alwaysBetray(round int, self []bool, enemy []bool) bool {
	return false
}

// Стратегия 3: Случайная стратегия
func randomBetrayer(round int, self []bool, enemy []bool) bool {
	return rand.Intn(2) == 1 // true = сотрудничество, false = предательство
}

// Игровая сессия
func playGame(strat1 Strategy, strat2 Strategy, name1 string, name2 string) {
	rand.Seed(time.Now().UnixNano())
	rounds := rand.Intn(101) + 100 // 100-200 раундов

	moves1 := make([]bool, 0, rounds)
	moves2 := make([]bool, 0, rounds)
	score1, score2 := 0, 0

	for i := 0; i < rounds; i++ {
		move1 := strat1(i, moves1, moves2)
		move2 := strat2(i, moves2, moves1)

		moves1 = append(moves1, move1)
		moves2 = append(moves2, move2)

		if move1 && move2 {
			score1 += 24
			score2 += 24
		} else if !move1 && !move2 {
			score1 += 4
			score2 += 4
		} else if move1 && !move2 {
			score1 += 0
			score2 += 20
		} else { // !move1 && move2
			score1 += 20
			score2 += 0
		}
	}

	fmt.Printf("\nИгра:\n%s против %s — Раундов: %d\n", name1, name2, rounds)
	fmt.Printf("%s набрал: %d очков\n", name1, score1)
	fmt.Printf("%s набрал: %d очков\n", name2, score2)
	if score1 > score2 {
		fmt.Printf("Победил: %s\n", name1)
	} else if score2 > score1 {
		fmt.Printf("Победил: %s\n", name2)
	} else {
		fmt.Println("Ничья!")
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	playGame(grudger, alwaysBetray, "|Обидчивый|", "|Всегда предаёт|")
	playGame(grudger, randomBetrayer, "|Обидчивый|", "|Случайный предатель|")
	playGame(alwaysBetray, randomBetrayer, "|Всегда предаёт|", "|Случайный предатель|")
}
