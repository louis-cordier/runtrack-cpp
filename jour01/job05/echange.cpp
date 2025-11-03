#include <iostream>
using namespace std;

int main() {
    int n, m, temp;

    // Saisie des deux entiers
    cout << "Entre la valeur de n : ";
    cin >> n;

    cout << "Entre la valeur de m : ";
    cin >> m;

    // Affichage avant l'échange
    cout << "\nAvant l'échange : n = " << n << ", m = " << m << endl;

    // Échange des valeurs à l'aide d'une variable temporaire
    temp = n;
    n = m;
    m = temp;

    // Affichage après l'échange
    cout << "Après l'échange : n = " << n << ", m = " << m << endl;

    return 0;
}
