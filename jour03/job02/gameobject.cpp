#include <iostream>
#include <cmath>
using namespace std;

// 🔹 Classe de base Vector2d (comme précédemment)
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

// 🔸 Classe abstraite GameObject, héritant de Vector2d
class GameObject : public Vector2d {
public:
    GameObject() : Vector2d() {}
    GameObject(double xVal, double yVal) : Vector2d(xVal, yVal) {}

    // Méthodes virtuelles pures → classe abstraite
    virtual void draw() const = 0;
    virtual void update() = 0;

    virtual ~GameObject() = default; // Bon réflexe : destructeur virtuel
};

// 🔹 Exemple de classe concrète : un personnage dans le jeu
class Player : public GameObject {
private:
    string name;

public:
    Player(string playerName, double xVal, double yVal)
        : GameObject(xVal, yVal), name(playerName) {}

    // Implémentation de draw()
    void draw() const override {
        cout << "Affichage du joueur \"" << name 
             << "\" à la position (" << x << ", " << y << ")" << endl;
    }

    // Implémentation de update()
    void update() override {
        x += 1.0;
        y += 0.5;
        cout << name << " se déplace vers (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Player hero("Aelwyn", 2.0, 3.0);

    hero.draw();     // Affiche la position initiale
    hero.update();   // Met à jour la position
    hero.draw();     // Affiche la nouvelle position

    return 0;
}
