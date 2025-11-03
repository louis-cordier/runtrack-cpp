#include <iostream>
using namespace std;

// 🔹 Fonction pour échanger deux entiers à l'aide de références
void swapValues(int& a, int& b) {
    int temp = a;  // Sauvegarde temporaire de la valeur de a
    a = b;         // a prend la valeur de b
    b = temp;      // b prend l'ancienne valeur de a
}

int main() {
    int x = 10, y = 20;

    cout << "Avant l'échange : x = " << x << ", y = " << y << endl;

    swapValues(x, y);  // Appel de la fonction d'échange

    cout << "Après l'échange : x = " << x << ", y = " << y << endl;

    return 0;
}
