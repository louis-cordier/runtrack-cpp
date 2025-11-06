#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

// Classe de base Enemy
class Enemy {
public:
    virtual void attack() const = 0;
    virtual ~Enemy() = default;
};

// Classes dérivées
class Goblin : public Enemy {
public:
    void attack() const override {
        std::cout << "Goblin attaque avec sa dague !" << std::endl;
    }
};

class Ogre : public Enemy {
public:
    void attack() const override {
        std::cout << "Ogre attaque avec sa massue !" << std::endl;
    }
};

class Dragon : public Enemy {
public:
    void attack() const override {
        std::cout << "Dragon crache du feu !" << std::endl;
    }
};

// Classe EnemyFactory
class EnemyFactory {
private:
    // Map : string -> fonction qui renvoie un pointeur unique vers Enemy
    std::unordered_map<std::string, std::function<std::unique_ptr<Enemy>()>> registry;

public:
    // Constructeur : initialise la map avec les types d'ennemis disponibles
    EnemyFactory() {
        registry["Goblin"] = []() { return std::make_unique<Goblin>(); };
        registry["Ogre"] = []() { return std::make_unique<Ogre>(); };
        registry["Dragon"] = []() { return std::make_unique<Dragon>(); };
    }

    // Méthode pour créer un ennemi selon son type
    std::unique_ptr<Enemy> createEnemy(const std::string& type) const {
        auto it = registry.find(type);
        if (it != registry.end()) {
            return it->second(); // Appelle la fonction de création
        } else {
            std::cerr << "Erreur : type d'ennemi inconnu (" << type << ")" << std::endl;
            return nullptr;
        }
    }
};

// Exemple d'utilisation
int main() {
    EnemyFactory factory;

    auto e1 = factory.createEnemy("Goblin");
    auto e2 = factory.createEnemy("Ogre");
    auto e3 = factory.createEnemy("Dragon");
    auto e4 = factory.createEnemy("Zombie"); // Type inconnu

    if (e1) e1->attack();
    if (e2) e2->attack();
    if (e3) e3->attack();
    if (e4) e4->attack(); // Ne fera rien

    return 0;
}
