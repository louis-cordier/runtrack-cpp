#include <iostream>
using namespace std;

int main() {
    int nombre, inverse = 0;

    cout << "Entrez un nombre à inverser : ";
    cin >> nombre;

    while (nombre != 0) {
        int chiffre = nombre % 10;        // Extraire le dernier chiffre
        inverse = inverse * 10 + chiffre; // Ajouter le chiffre à l'inverse
        nombre = nombre / 10;             // Supprimer le dernier chiffre
    }

    cout << "Le nombre inversé est : " << inverse << endl;

    return 0;
}
