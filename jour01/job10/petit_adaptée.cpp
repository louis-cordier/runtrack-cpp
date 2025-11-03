#include <iostream>
using namespace std;

// 🔹 Fonction qui trouve le plus petit élément d’un tableau de pointeurs d’entiers
int trouverMin(int** tableau, int taille) {
    int* ptr = tableau[0];  // Premier pointeur du tableau
    int min = *ptr;          // La valeur pointée devient le point de départ

    for (int i = 1; i < taille; i++) {
        if (*(tableau[i]) < min) {  // On compare la valeur pointée par chaque pointeur
            min = *(tableau[i]);
        }
    }

    return min;  // On renvoie le plus petit élément trouvé
}

int main() {
    // Création de variables entières
    int a = 42, b = 17, c = 8, d = 23, e = 56, f = 4;

    // Tableau de pointeurs vers ces entiers
    int* tableau[] = {&a, &b, &c, &d, &e, &f};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    cout << "Le plus petit élément du tableau de pointeurs est : "
         << trouverMin(tableau, taille) << endl;

    return 0;
}
