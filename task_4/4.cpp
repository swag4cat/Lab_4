#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

// Генерация случайных предпочтений избирателя (перестановка кандидатов)
vector<int> generatePermutation(int n, mt19937& rng) {
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i;
    shuffle(perm.begin(), perm.end(), rng);
    return perm;
}

// Метод Борда
int bordaWinner(const vector<vector<int>>& preferences, int numCandidates) {
    vector<int> scores(numCandidates, 0);

    for (const auto& pref : preferences) {
        for (int i = 0; i < numCandidates; ++i) {
            scores[pref[i]] += numCandidates - 1 - i;
        }
    }

    int winner = max_element(scores.begin(), scores.end()) - scores.begin();
    cout << "\nБаллы по методу Борда:\n";
    for (int i = 0; i < numCandidates; ++i) {
        cout << "Кандидат " << i + 1 << ": " << scores[i] << " баллов\n";
    }

    return winner;
}

// Метод Кондорсе
int condorcetWinner(const vector<vector<int>>& preferences, int numCandidates) {
    vector<vector<int>> wins(numCandidates, vector<int>(numCandidates, 0));

    for (const auto& pref : preferences) {
        for (int i = 0; i < numCandidates; ++i) {
            for (int j = i + 1; j < numCandidates; ++j) {
                int candA = pref[i];
                int candB = pref[j];
                wins[candA][candB]++;
            }
        }
    }

    // Проверка на Кондорсе-победителя
    for (int i = 0; i < numCandidates; ++i) {
        bool isWinner = true;
        for (int j = 0; j < numCandidates; ++j) {
            if (i == j) continue;
            if (wins[i][j] <= preferences.size() / 2) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) return i;
    }

    return -1; // Кондорсе-победителя нет
}

int main() {
    setlocale(LC_ALL, "Russian");
    mt19937 rng(time(0));

    int numCandidates, numVoters;
    cout << "Введите количество кандидатов: ";
    cin >> numCandidates;
    cout << "Введите количество избирателей: ";
    cin >> numVoters;

    vector<vector<int>> preferences;

    for (int i = 0; i < numVoters; ++i) {
        vector<int> perm = generatePermutation(numCandidates, rng);
        preferences.push_back(perm);
    }

    // Вывод предпочтений
    cout << "\nПредпочтения избирателей:\n";
    for (int i = 0; i < numVoters; ++i) {
        cout << "Избиратель " << i + 1 << ": ";
        for (int j : preferences[i]) {
            cout << j + 1 << " ";
        }
        cout << endl;
    }

    int borda = bordaWinner(preferences, numCandidates);
    int condorcet = condorcetWinner(preferences, numCandidates);

    cout << "\nПобедитель по методу Борда: Кандидат " << borda + 1 << endl;
    if (condorcet != -1)
        cout << "Победитель по методу Кондорсе: Кандидат " << condorcet + 1 << endl;
    else
        cout << "Победитель по методу Кондорсе: не существует (нет универсального победителя)\n";

    if (condorcet != -1 && borda != condorcet)
        cout << "\nВнимание: методы Борда и Кондорсе дали разных победителей.\n";

    return 0;
}
