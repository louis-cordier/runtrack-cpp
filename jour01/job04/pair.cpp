#include <iostream>
using namespace std;

int main() {
    int nombre;

    cout << "Entre un nombre entier : ";
    cin >> nombre;

    if (nombre % 2 == 0) {
        cout << nombre << " est pair." << endl;
    } else {
        cout << nombre << " est impair." << endl;
    }

    return 0;
}
