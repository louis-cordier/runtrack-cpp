#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// --- Classe de base Vector2d ---
class Vector2d {
protected:
    double x, y;

public:
    Vector2d() : x(0.0), y(0.0) {}
    Vector2d(double xVal, double yVal) : x(xVal), y(yVal) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    Vector2d operator+(const Vector2d& autre) const {
        return Vector2d(x + autre.x, y + autre.y);
    }

    Vector2d operator-(const Vector2d& autre) const {
        return Vector2d(x - autre.x, y - autre.y);
    }

    double distance(const Vector2d& autre) const {
        return sqrt(pow(x - autre.x, 2) + pow(y - autre.y, 2));
    }
};

// --- Classe abstraite GameObject ---
class GameObject : public Vector2d {
public:
    GameObject() : Vector2d() {}
    GameObject(double xVal, double yVal) : Vector2d(xVal, yVal) {}

    virtual void draw() const = 0;   // Méthode pure virtuelle
    virtual void update() = 0;       // Méthode pure virtuelle

    virtual ~GameObject() = default;
};

// --- Classe Decor ---
class Decor : public GameObject {
private:
    string name;

public:
    Decor(string decorName, double xVal, double yVal)
        : GameObject(xVal, yVal), name(decorName) {}

    void draw() const override {
        cout << "Décor \"" << name << "\" affiché à la position ("
             << x << ", " << y << ")" << endl;
    }

    void update() override {
        // Les décors ne bougent pas
        cout << "Décor \"" << name << "\" reste immobile." << endl;
    }
};

// --- Classe Character ---
class Character : public GameObject {
private:
    string name;
    int health;

public:
    Character(string charName, double xVal, double yVal, int hp)
        : GameObject(xVal, yVal), name(charName), health(hp) {}

    void draw() const override {
        cout << "Personnage \"" << name << "\" (" << health << " PV)"
             << " à la position (" << x << ", " << y << ")" << endl;
    }

    void update() override {
        // Exemple simple : le personnage se déplace un peu
        x += 0.5;
        y += 0.2;
        cout << name << " avance vers (" << x << ", " << y << ")" << endl;
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
    }
};

// --- Fonction principale ---
int main() {
    Decor arbre("Arbre magique", 5.0, 8.0);
    Character heros("Aelwyn", 2.0, 3.0, 100);

    cout << "--- État initial ---" << endl;
    arbre.draw();
    heros.draw();

    cout << "\n--- Mise à jour du monde ---" << endl;
    arbre.update();
    heros.update();

    cout << "\n--- État après mise à jour ---" << endl;
    arbre.draw();
    heros.draw();

    // Test de la méthode isAlive()
    heros.takeDamage(110);
    cout << "\n" << heros.isAlive()
         ? "Le héros est encore vivant." : "Le héros est tombé au combat." << endl ;

    return 0;
}
