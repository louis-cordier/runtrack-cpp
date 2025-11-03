#include <iostream>
using namespace std;

int main() {
    double prixHT, kilos, tva, prixTTC;

    cout << "=== Calcul du prix TTC des carottes ===" << endl;

    // Saisie des données
    cout << "Entrez le prix HT d'un kilo de carottes (€) : ";
    cin >> prixHT;

    cout << "Entrez le nombre de kilos : ";
    cin >> kilos;

    cout << "Entrez le taux de TVA (%) : ";
    cin >> tva;

    // Calcul du prix TTC
    prixTTC = prixHT * kilos * (1 + tva / 100);

    // Affichage du résultat
    cout << "\nLe prix TTC pour " << kilos << " kg de carottes est de : " 
         << prixTTC << " €" << endl;

    return 0;
}
