#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// Тип стратегии
typedef bool (*Strategy)(int, const vector<bool>&, const vector<bool>&);

// Стратегия 1: Обидчивый — предаёт, если противник предавал более 50% раз
bool grudger(int round, const vector<bool>& self, const vector<bool>& enemy) {
    if (round == 0) return true;
    int betrayals = 0;
    for (bool e : enemy) {
        if (!e) ++betrayals;
    }
    return betrayals <= round / 2;
}

// Стратегия 2: Всегда предаёт
bool alwaysBetray(int round, const vector<bool>& self, const vector<bool>& enemy) {
    return false;
}

// Стратегия 3: Случайная стратегия
bool randomBetrayer(int round, const vector<bool>& self, const vector<bool>& enemy) {
    static mt19937 rng(static_cast<unsigned>(time(0))); // Используем текущее время для seed
    uniform_int_distribution<int> dist(0, 1);
    return dist(rng) == 1; // true = сотрудничество, false = предательство
}

// Игровая сессия
void playGame(Strategy strat1, Strategy strat2, const string& name1, const string& name2) {
    static mt19937 rng(static_cast<unsigned>(time(0))); // Общий rng для всех игр
    uniform_int_distribution<int> dist(100, 200);
    int rounds = dist(rng);

    vector<bool> moves1, moves2;
    int score1 = 0, score2 = 0;

    for (int i = 0; i < rounds; ++i) {
        bool move1 = strat1(i, moves1, moves2);
        bool move2 = strat2(i, moves2, moves1);

        moves1.push_back(move1);
        moves2.push_back(move2);

        if (move1 && move2) {
            score1 += 24;
            score2 += 24;
        } else if (!move1 && !move2) {
            score1 += 4;
            score2 += 4;
        } else if (move1 && !move2) {
            score1 += 0;
            score2 += 20;
        } else { // !move1 && move2
            score1 += 20;
            score2 += 0;
        }
    }

    cout << "\nИгра:\n" << name1 << " против " << name2 << " — Раундов: " << rounds << "\n";
    cout << name1 << " набрал: " << score1 << " очков\n";
    cout << name2 << " набрал: " << score2 << " очков\n";
    if (score1 > score2)
        cout << "Победил: " << name1 << "\n";
    else if (score2 > score1)
        cout << "Победил: " << name2 << "\n";
    else
        cout << "Ничья!\n";
}

int main() {
    // Инициализация генератора случайных чисел для main
    srand(static_cast<unsigned>(time(0)));

    playGame(grudger, alwaysBetray, "|Обидчивый|", "|Всегда предаёт|");
    playGame(grudger, randomBetrayer, "|Обидчивый|", "|Случайный предатель|");
    playGame(alwaysBetray, randomBetrayer, "|Всегда предаёт|", "|Случайный предатель|");

    return 0;
}
