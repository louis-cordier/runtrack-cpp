#include <iostream>
#include <cmath>   // pour sqrt() et pow()
using namespace std;

class Vector2d {
private:
    double x;
    double y;

public:
    // --- Constructeurs ---
    Vector2d() : x(0.0), y(0.0) {}
    Vector2d(double xVal, double yVal) : x(xVal), y(yVal) {}

    // --- Accesseurs (getters) ---
    double getX() const { return x; }
    double getY() const { return y; }

    // --- Mutateurs (setters) ---
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    // --- Surcharge de l’opérateur + (addition de vecteurs) ---
    Vector2d operator+(const Vector2d& autre) const {
        return Vector2d(x + autre.x, y + autre.y);
    }

    // --- Surcharge de l’opérateur - (soustraction de vecteurs) ---
    Vector2d operator-(const Vector2d& autre) const {
        return Vector2d(x - autre.x, y - autre.y);
    }

    // --- Méthode distance() ---
    double distance(const Vector2d& autre) const {
        return sqrt(pow(x - autre.x, 2) + pow(y - autre.y, 2));
    }

    // --- Méthode d'affichage (facultative, pour le confort du héros) ---
    void afficher() const {
        cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    // Création de deux vecteurs
    Vector2d v1(3.0, 4.0);
    Vector2d v2(7.0, 1.0);

    // Affichage des vecteurs
    cout << "Vecteur v1 : "; v1.afficher(); cout << endl;
    cout << "Vecteur v2 : "; v2.afficher(); cout << endl;

    // Addition et soustraction
    Vector2d somme = v1 + v2;
    Vector2d difference = v1 - v2;

    cout << "\nSomme (v1 + v2) : "; somme.afficher(); cout << endl;
    cout << "Difference (v1 - v2) : "; difference.afficher(); cout << endl;

    // Distance entre les deux vecteurs
    cout << "\nDistance entre v1 et v2 : " << v1.distance(v2) << endl;

    return 0;
}
