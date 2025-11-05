#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
using namespace std;

// --- Classe Vector2d ---
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
protected:
    string name;
    int health;

public:
    Character(string charName, double xVal, double yVal, int hp)
        : GameObject(xVal, yVal), name(charName), health(hp) {}

    void draw() const override {
        cout << name << " (" << health << " PV) à (" << x << ", " << y << ")" << endl;
    }

    virtual void update() override {}

    bool isAlive() const { return health > 0; }

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

// --- Implémentations concrètes des armes ---
class Bow : public Weapon {
    int range = 4;
    int power = 1;
public:
    void attack(Character& target, const Character& attacker) const override {
        double d = attacker.distance(target);
        cout << "🏹 " << attacker.getName() << " tire sur " << target.getName()
             << " (distance: " << d << ")" << endl;
        if (d <= range) target.takeDamage(power);
        else cout << "La cible est trop loin pour l'arc !" << endl;
    }
};

class Spear : public Weapon {
    int range = 2;
    int power = 2;
public:
    void attack(Character& target, const Character& attacker) const override {
        double d = attacker.distance(target);
        cout << "🪶 " << attacker.getName() << " attaque " << target.getName()
             << " à la lance (distance: " << d << ")" << endl;
        if (d <= range) target.takeDamage(power);
        else cout << "Trop loin pour la lance !" << endl;
    }
};

class Sword : public Weapon {
    int range = 1;
    int power = 4;
public:
    void attack(Character& target, const Character& attacker) const override {
        double d = attacker.distance(target);
        cout << "⚔️ " << attacker.getName() << " frappe " << target.getName()
             << " avec son épée (distance: " << d << ")" << endl;
        if (d <= range) target.takeDamage(power);
        else cout << "L'ennemi est hors de portée !" << endl;
    }
};

// --- Classe Player ---
class Player : public Character {
private:
    vector<unique_ptr<Weapon>> arsenal;
    int currentWeaponIndex;

public:
    Player(string name, double x, double y, int hp)
        : Character(name, x, y, hp), currentWeaponIndex(0) {
        // Initialise les armes du joueur
        arsenal.push_back(make_unique<Bow>());
        arsenal.push_back(make_unique<Spear>());
        arsenal.push_back(make_unique<Sword>());
    }

    Weapon* getCurrentWeapon() const {
        return arsenal[currentWeaponIndex].get();
    }

    void switchWeapon() {
        currentWeaponIndex = (currentWeaponIndex + 1) % arsenal.size();
        cout << name << " change d’arme !" << endl;
    }

    void attack(Character& target) {
        getCurrentWeapon()->attack(target, *this);
    }

    void update() override {
        cout << "🎯 " << name << " se prépare à attaquer..." << endl;
    }
};

// --- Classe Enemy ---
class Enemy : public Character {
public:
    Enemy(string name, double x, double y, int hp)
        : Character(name, x, y, hp) {}

    void update(Player& player) {
        double d = distance(player);
        if (d > 1.0) {
            // Se rapproche du joueur
            double dx = player.getX() - x;
            double dy = player.getY() - y;
            double len = sqrt(dx*dx + dy*dy);
            x += (dx / len) * 0.5;
            y += (dy / len) * 0.5;
            cout << name << " s’approche du joueur (" << x << ", " << y << ")" << endl;
        } else {
            // Attaque le joueur
            cout << "💥 " << name << " attaque " << player.getName() << " au corps à corps !" << endl;
            player.takeDamage(2);
        }
    }

    void update() override {} // pour respecter GameObject, inutilisé ici
};

// --- Démonstration ---
int main() {
    Player hero("Aelwyn", 0, 0, 20);
    Enemy goblin("Goblin", 3, 0, 8);

    cout << "\n--- Début de la bataille ---" << endl;
    hero.draw();
    goblin.draw();

    for (int tour = 1; tour <= 5 && goblin.isAlive() && hero.isAlive(); ++tour) {
        cout << "\n=== Tour " << tour << " ===" << endl;

        // Le joueur attaque
        hero.attack(goblin);
        if (!goblin.isAlive()) break;

        // Le joueur change d’arme
        hero.switchWeapon();

        // L’ennemi réagit
        goblin.update(hero);
    }

    cout << "\n--- Fin du combat ---" << endl;
    hero.draw();
    goblin.draw();
    return 0;
}
