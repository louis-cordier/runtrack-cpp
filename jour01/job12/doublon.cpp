#include <iostream>
using namespace std;

// 🔹 Fonction pour doubler chaque élément et retourner la somme
int doubleArray(int* tableau, int taille) {
    int somme = 0;
    int* ptr = tableau;  // Pointeur vers le début du tableau

    for (int i = 0; i < taille; i++) {
        *ptr = *ptr * 2;  // Double la valeur pointée
        somme += *ptr;    // Ajoute au total
        ptr++;            // Passe à l'élément suivant
    }

    return somme;
}

// 🔹 Fonction pour afficher le tableau
void printArray(int* tableau, int taille) {
    for (int i = 0; i < taille; i++) {
        cout << tableau[i] << " ";
    }
    cout << endl;
}

int main() {
    int tableau[] = {1, 2, 3, 4, 5};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    int somme = doubleArray(tableau, taille);  // Double les éléments et calcule la somme

    cout << "Tableau après doublement : ";
    printArray(tableau, taille);

    cout << "Somme des éléments doublés : " << somme << endl;

    return 0;
}
