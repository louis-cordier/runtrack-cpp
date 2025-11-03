#include <iostream>
using namespace std;

int main() {
    int n;           // Variable pour lire chaque nombre
    double somme = 0; // Variable pour accumuler la somme (et calculer la moyenne)

    cout << "Entre 5 entiers :" << endl;

    for (int i = 1; i <= 5; i++) {
        cin >> n;         // Lire un nombre
        somme += n;       // L'ajouter à la somme
    }

    cout << "La moyenne est : " << somme / 5 << endl;

    return 0;
}
