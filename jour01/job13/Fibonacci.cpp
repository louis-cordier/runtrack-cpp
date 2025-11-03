#include <iostream>
#include <cstdint>
using namespace std;

// 🔹 Fonction constexpr pour calculer le N-ième terme de Fibonacci à la compilation
constexpr uint64_t fibonacci(unsigned int N) {
    return (N == 0) ? 0 :
           (N == 1) ? 1 :
           fibonacci(N - 1) + fibonacci(N - 2);
}

// 🔹 Fonction qui retourne vrai si le nombre de bits à 1 est pair
bool hasEvenOnes(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;   // Ajoute 1 si le dernier bit est 1
        n >>= 1;          // Décale à droite
    }
    return (count % 2 == 0);
}

int main() {
    // Afficher les 10 premiers termes de la suite de Fibonacci
    cout << "Les 10 premiers termes de la suite de Fibonacci : ";
    for (unsigned int i = 0; i < 10; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;

    // Tester la fonction de parité des bits à 1
    uint32_t testNumber;
    cout << "Entrez un entier non signé pour tester la parité des bits à 1 : ";
    cin >> testNumber;

    if (hasEvenOnes(testNumber)) {
        cout << "Le nombre de bits à 1 est pair." << endl;
    } else {
        cout << "Le nombre de bits à 1 est impair." << endl;
    }

    return 0;
}
