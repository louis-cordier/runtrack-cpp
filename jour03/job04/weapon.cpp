#include <iostream>
#include <string>
#include <cmath>
#include <vector>
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

    virtual void draw() const = 0;
    virtual void update() = 0;

    virtual ~GameObject() = default;
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
        // Exemple simple de déplacement
        x += 0.5;
        y += 0.2;
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
        cout << name << " subit " << amount << " dégâts. PV restants : " << health << endl;
    }

    string getName() const { return name; }
};

// --- Interface Weapon ---
class Weapon {
public:
    virtual void attack(Character& target, const Character& attacker) const = 0;
    virtual ~Weapon() = default;
};

// --- Classe Bow ---
class Bow : public Weapon {
private:
    int range;
    int power;
public:
    Bow() : range(4), power(1) {}

    void attack(Character& target, const Character& attacker) const override {
        double distance = attacker.distance(target);
        cout << "🏹 " << attacker.getName() << " tire une flèche sur " << target.getName()
             << " (distance: " << distance << ")" << endl;

        if (distance <= range) {
            target.takeDamage(power);
        } else {
            cout << "La cible est trop loin pour l’arc !" << endl;
        }
    }
};

// --- Classe Spear ---
class Spear : public Weapon {
private:
    int range;
    int power;
public:
    Spear() : range(2), power(2) {}

    void attack(Character& target, const Character& attacker) const override {
        double distance = attacker.distance(target);
        cout << "🪶 " << attacker.getName() << " lance sa lance vers " << target.getName()
             << " (distance: " << distance << ")" << endl;

        if (distance <= range) {
            target.takeDamage(power);
        } else {
            cout << "La cible est hors de portée de la lance !" << endl;
        }
    }
};

// --- Classe Sword ---
class Sword : public Weapon {
private:
    int range;
    int power;
public:
    Sword() : range(1), power(4) {}

    void attack(Character& target, const Character& attacker) const override {
        double distance = attacker.distance(target);
        cout << "⚔️ " << attacker.getName() << " attaque " << target.getName()
             << " avec son épée (distance: " << distance << ")" << endl;

        if (distance <= range) {
            target.takeDamage(power);
        } else {
            cout << "L’ennemi est trop loin pour être touché à l’épée !" << endl;
        }
    }
};

// --- Démonstration ---
int main() {
    Character hero("Aelwyn", 0, 0, 10);
    Character enemy("Gorak", 3, 0, 8);

    Bow bow;
    Spear spear;
    Sword sword;

    cout << "\n--- Début du combat ---" << endl;
    hero.draw();
    enemy.draw();

    cout << "\n>>> Test du Bow" << endl;
    bow.attack(enemy, hero);

    cout << "\n>>> Test du Spear" << endl;
    spear.attack(enemy, hero);

    cout << "\n>>> Test du Sword" << endl;
    sword.attack(enemy, hero);

    return 0;
}
