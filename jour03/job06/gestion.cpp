#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
using namespace std;

// --- Classe Vector2d ---
class Vector2d {
protected:
    double x, y;
public:
    Vector2d(double xVal = 0, double yVal = 0) : x(xVal), y(yVal) {}
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    double distance(const Vector2d& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// --- Classe abstraite GameObject ---
class GameObject : public Vector2d {
protected:
    string name;
public:
    GameObject(string n, double xVal, double yVal)
        : Vector2d(xVal, yVal), name(std::move(n)) {}
    virtual void draw() const = 0;
    virtual void update() = 0;
    virtual ~GameObject() = default;
    string getName() const { return name; }
};

// --- Exemple d'objets dérivés ---
class Decor : public GameObject {
public:
    Decor(string name, double x, double y) : GameObject(name, x, y) {}
    void draw() const override {
        cout << "🌳 Décor \"" << name << "\" à (" << x << ", " << y << ")" << endl;
    }
    void update() override {
        // Les décors ne changent pas
    }
};

class Character : public GameObject {
protected:
    int health;
public:
    Character(string name, double x, double y, int hp)
        : GameObject(name, x, y), health(hp) {}
    void draw() const override {
        cout << "🧍 " << name << " (" << health << " PV) à (" << x << ", " << y << ")" << endl;
    }
    void update() override {
        // Comportement basique : se déplace légèrement
        x += 0.5;
        y += 0.2;
    }
};

// --- Le Container de tous les objets du jeu ---
class GameWorld {
private:
    vector<unique_ptr<GameObject>> objects;

public:
    // Ajouter un objet au monde
    template <typename T, typename... Args>
    T& addObject(Args&&... args) {
        // Crée un objet de type T et le stocke dans le vector
        auto obj = make_unique<T>(std::forward<Args>(args)...);
        T& ref = *obj; // Référence pour le retour
        objects.push_back(std::move(obj));
        return ref;
    }

    // Afficher tous les objets du monde
    void drawAll() const {
        cout << "\n--- Affichage du monde ---" << endl;
        for (const auto& obj : objects) {
            obj->draw();
        }
    }

    // Mettre à jour tous les objets
    void updateAll() {
        cout << "\n--- Mise à jour du monde ---" << endl;
        for (auto& obj : objects) {
            obj->update();
        }
    }
};

// --- Démonstration ---
int main() {
    GameWorld world;

    // Ajout d’objets variés
    world.addObject<Decor>("Arbre ancien", 4.0, 2.0);
    world.addObject<Character>("Aelwyn", 0.0, 0.0, 100);
    world.addObject<Character>("Goblin", 3.5, 0.0, 40);

    // Boucle de simulation
    for (int i = 1; i <= 3; ++i) {
        cout << "\n=== Tour " << i << " ===" << endl;
        world.drawAll();
        world.updateAll();
    }

    return 0;
}
