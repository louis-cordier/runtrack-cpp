#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

// Classe abstraite de base
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Classes dérivées
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Je dessine un cercle." << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Je dessine un rectangle." << std::endl;
    }
};

// Classe ShapeFactory
class ShapeFactory {
private:
    // Registre statique : associe un nom à une fonction de création
    static inline std::unordered_map<std::string, std::function<std::unique_ptr<Shape>()>> registry{};

public:
    // Méthode template pour enregistrer une nouvelle forme
    template <typename T>
    static void registerShape(const std::string& name) {
        static_assert(std::is_base_of<Shape, T>::value,
                      "T doit hériter de Shape");
        registry[name] = []() -> std::unique_ptr<Shape> {
            return std::make_unique<T>();
        };
    }

    // Crée une forme à partir de son nom
    static std::unique_ptr<Shape> createShape(const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end())
            return it->second();
        std::cerr << "Erreur : type de forme inconnu (" << name << ")" << std::endl;
        return nullptr;
    }
};

// Exemple d'utilisation
int main() {
    // Enregistrement des formes disponibles
    ShapeFactory::registerShape<Circle>("Circle");
    ShapeFactory::registerShape<Rectangle>("Rectangle");

    // Création dynamique
    auto shape1 = ShapeFactory::createShape("Circle");
    auto shape2 = ShapeFactory::createShape("Rectangle");
    auto shape3 = ShapeFactory::createShape("Triangle"); // Inconnu

    if (shape1) shape1->draw();
    if (shape2) shape2->draw();
    if (shape3) shape3->draw();

    return 0;
}
