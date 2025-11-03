#include <iostream>
using namespace std;

int main() {
    int annee;

    cout << "Entrez une année : ";
    cin >> annee;

    // Règle pour déterminer si une année est bissextile :
    // - divisible par 4
    // - sauf si divisible par 100, sauf si divisible par 400
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        cout << annee << " est une année bissextile." << endl;
    } else {
        cout << annee << " n'est pas une année bissextile." << endl;
    }

    return 0;
}
