#include <iostream>
using namespace std;

// 🔹 Fonction qui trouve le plus petit élément d’un tableau à l’aide de pointeurs
int trouverMin(int* tableau, int taille) {
    int* ptr = tableau;        // Pointeur vers le début du tableau
    int min = *ptr;            // Le premier élément comme point de départ

    for (int i = 1; i < taille; i++) {
        ptr++;                 // On avance le pointeur
        if (*ptr < min) {      // On compare la valeur pointée
            min = *ptr;
        }
    }

    return min;                // On renvoie le plus petit élément trouvé
}

int main() {
    int tableau[] = {42, 17, 8, 23, 56, 4};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    cout << "Le plus petit élément du tableau est : " 
         << trouverMin(tableau, taille) << endl;

    return 0;
}
