#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

// ======== Vector2d ========
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

// ======== GameObject ========
class GameObject : public Vector2d {
protected:
    string name;
public:
    GameObject(string n, double x, double y) : Vector2d(x, y), name(std::move(n)) {}
    virtual void update() = 0;
    virtual void draw() const = 0;
    virtual bool isActive() const { return true; }
    string getName() const { return name; }
    virtual ~GameObject() = default;
};

// ======== Character ========
class Character : public GameObject {
protected:
    int health;
public:
    Character(string n, double x, double y, int hp)
        : GameObject(std::move(n), x, y), health(hp) {}
    void draw() const override {
        cout << name << " (" << health << " PV) à (" << x << ", " << y << ")" << endl;
    }
    bool isAlive() const { return health > 0; }
    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " subit " << dmg << " dégâts. PV restants : " << health << endl;
    }
    bool isActive() const override { return isAlive(); }
};

// ======== Interface Weapon ========
class Weapon {
public:
    virtual void attack(Character& target, const Character& attacker) const = 0;
    virtual string getName() const = 0;
    virtual ~Weapon() = default;
};

// ======== Armes concrètes ========
class Bow : public Weapon {
    int range = 4;
    int power = 1;
public:
    void attack(Character& target, const Character& attacker) const override {
        double d = attacker.distance(target);
        cout << "🏹  " << attacker.getName() << " tire une flèche sur " << target.getName()
             << " (distance " << d << ")" << endl;
        if (d <= range) target.takeDamage(power);
        else cout << "❌ Trop loin pour l’arc !" << endl;
    }
    string getName() const override { return "Arc"; }
};

class Spear : public Weapon {
    int range = 2;
    int power = 2;
public:
    void attack(Character& target, const Character& attacker) const override {
        double d = attacker.distance(target);
        cout << "🪶  " << attacker.getName() << " attaque à la lance " << target.getName()
             << " (distance " << d << ")" << endl;
        if (d <= range) target.takeDamage(power);
        else cout << "❌ Trop loin pour la lance !" << endl;
    }
    string getName() const override { return "Lance"; }
};

class Sword : public Weapon {
    int range = 1;
    int power = 4;
public:
    void attack(Character& target, const Character& attacker) const override {
        double d = attacker.distance(target);
        cout << "⚔️  " << attacker.getName() << " frappe " << target.getName()
             << " avec son épée (distance " << d << ")" << endl;
        if (d <= range) target.takeDamage(power);
        else cout << "❌ Hors de portée !" << endl;
    }
    string getName() const override { return "Épée"; }
};

// ======== Player ========
class Player : public Character {
private:
    vector<unique_ptr<Weapon>> arsenal;
    int currentWeaponIndex = 0;
public:
    Player(string n, double x, double y, int hp) : Character(n, x, y, hp) {
        arsenal.push_back(make_unique<Bow>());
        arsenal.push_back(make_unique<Spear>());
        arsenal.push_back(make_unique<Sword>());
    }

    void switchWeapon() {
        currentWeaponIndex = (currentWeaponIndex + 1) % arsenal.size();
        cout << "🔁 " << name << " équipe " << arsenal[currentWeaponIndex]->getName() << "." << endl;
    }

    void attack(Character& target) {
        arsenal[currentWeaponIndex]->attack(target, *this);
    }

    string getWeaponName() const {
        return arsenal[currentWeaponIndex]->getName();
    }

    void move(char dir) {
        switch (dir) {
            case 'z': y += 1; break;
            case 's': y -= 1; break;
            case 'q': x -= 1; break;
            case 'd': x += 1; break;
            default: cout << "❌ Commande invalide." << endl; return;
        }
        cout << "🏃 " << name << " se déplace vers (" << x << ", " << y << ")" << endl;
    }

    void update() override {
        // Le joueur ne bouge que sur commande
    }
};

// ======== Enemy ========
class Enemy : public Character {
public:
    Enemy(string n, double x, double y, int hp) : Character(n, x, y, hp) {}
    void update(Player& player) {
        double d = distance(player);
        if (d > 1.0) {
            double dx = player.getX() - x;
            double dy = player.getY() - y;
            double len = sqrt(dx*dx + dy*dy);
            x += (dx / len) * 0.5;
            y += (dy / len) * 0.5;
            cout << name << " s’approche du joueur (" << x << ", " << y << ")" << endl;
        } else {
            cout << "💥 " << name << " attaque " << player.getName() << " !" << endl;
            player.takeDamage(2);
        }
    }
    void update() override {} // inutilisé ici
};

// ======== GameWorld ========
class GameWorld {
private:
    vector<unique_ptr<GameObject>> objects;
public:
    template<typename T, typename... Args>
    T& addObject(Args&&... args) {
        auto obj = make_unique<T>(std::forward<Args>(args)...);
        T& ref = *obj;
        objects.push_back(std::move(obj));
        return ref;
    }

    void drawAll() const {
        for (const auto& obj : objects)
            obj->draw();
    }

    void cleanup() {
        objects.erase(
            remove_if(objects.begin(), objects.end(),
                      [](const unique_ptr<GameObject>& obj) { return !obj->isActive(); }),
            objects.end());
    }

    vector<unique_ptr<GameObject>>& getObjects() { return objects; }
};

// ======== Main ========
int main() {
    GameWorld world;
    Player& hero = world.addObject<Player>("Aelwyn", 0, 0, 20);
    world.addObject<Enemy>("Goblin", 3, 0, 8);
    world.addObject<Enemy>("Orc", 5, 2, 12);

    cout << "\n=== 🌍 Début de la partie interactive ===" << endl;

    bool running = true;
    int turn = 1;

    while (running) {
        cout << "\n=== 🕒 Tour " << turn++ << " ===" << endl;
        world.drawAll();

        // --- Action du joueur ---
        cout << "\n⚔️  Que voulez-vous faire ?\n";
        cout << "[A] Attaquer  [M] Changer d’arme  [D] Se déplacer  [P] Passer le tour\n> ";

        char action;
        cin >> action;
        action = tolower(action);

        if (action == 'a') {
            cout << "👉 Choisissez un ennemi à attaquer :" << endl;
            vector<Enemy*> targets;
            int i = 1;
            for (auto& obj : world.getObjects()) {
                if (Enemy* e = dynamic_cast<Enemy*>(obj.get())) {
                    if (e->isAlive()) {
                        cout << i << ". " << e->getName() << " (" << e->getX() << ", " << e->getY() << ")" << endl;
                        targets.push_back(e);
                        i++;
                    }
                }
            }
            if (targets.empty()) {
                cout << "Aucun ennemi à attaquer !" << endl;
            } else {
                int choice;
                cin >> choice;
                if (choice >= 1 && choice <= (int)targets.size()) {
                    hero.attack(*targets[choice - 1]);
                } else {
                    cout << "Choix invalide." << endl;
                }
            }
        } 
        else if (action == 'm') {
            hero.switchWeapon();
        } 
        else if (action == 'd') {
            cout << "Déplacez-vous : (z=haut, s=bas, q=gauche, d=droite)\n> ";
            char dir;
            cin >> dir;
            hero.move(dir);
        } 
        else if (action == 'p') {
            cout << "⏸️  Vous passez votre tour." << endl;
        } 
        else {
            cout << "❌ Action invalide." << endl;
        }

        // --- Réaction des ennemis ---
        for (auto& obj : world.getObjects()) {
            if (Enemy* e = dynamic_cast<Enemy*>(obj.get())) {
                if (e->isAlive()) e->update(hero);
            }
        }

        // --- Nettoyage ---
        world.cleanup();

        // --- Conditions de victoire/défaite ---
        bool anyEnemyAlive = false;
        for (const auto& obj : world.getObjects())
            if (dynamic_cast<Enemy*>(obj.get())) anyEnemyAlive = true;

        if (!hero.isAlive()) {
            cout << "\n💀 Le joueur est mort... GAME OVER." << endl;
            running = false;
        } else if (!anyEnemyAlive) {
            cout << "\n🏆 Tous les ennemis ont été vaincus ! VICTOIRE !" << endl;
            running = false;
        }
    }

    cout << "\n=== 🎮 Fin du jeu ===" << endl;
    return 0;
}
