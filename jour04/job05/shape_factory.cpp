#include <iostream>
#include <memory>
#include <string>

// Classe abstraite Shape
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Classe dérivée Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Je dessine un cercle." << std::endl;
    }
};

// Classe dérivée Rectangle
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Je dessine un rectangle." << std::endl;
    }
};

// Classe ShapeFactory
class ShapeFactory {
public:
    // Méthode statique qui crée une forme selon un nom
    static std::unique_ptr<Shape> createShape(const std::string& type) {
        if (type == "circle" || type == "Circle") {
            return std::make_unique<Circle>();
        }
        else if (type == "rectangle" || type == "Rectangle") {
            return std::make_unique<Rectangle>();
        }
        else {
            std::cerr << "Erreur : type de forme inconnu (" << type << ")" << std::endl;
            return nullptr;
        }
    }
};

// Exemple d'utilisation
int main() {
    auto shape1 = ShapeFactory::createShape("Circle");
    auto shape2 = ShapeFactory::createShape("Rectangle");
    auto shape3 = ShapeFactory::createShape("Triangle"); // Type inconnu

    if (shape1) shape1->draw();
    if (shape2) shape2->draw();
    if (shape3) shape3->draw(); // Ne fera rien (nullptr)

    return 0;
}
