#include <iostream>
#include <memory>

// Classe abstraite Shape
class Shape {
public:
    virtual void draw() const = 0; // méthode pure (rend Shape abstraite)
    virtual ~Shape() = default;    // destructeur virtuel
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

// Template de fonction drawShape
template <typename T>
void drawShape(const T& shape) {
    static_assert(std::is_base_of<Shape, T>::value, 
                  "T doit dériver de Shape");
    shape.draw();
}

// Exemple d'utilisation
int main() {
    Circle c;
    Rectangle r;

    drawShape(c);
    drawShape(r);

    // Fonctionne aussi avec des pointeurs intelligents
    std::unique_ptr<Shape> s1 = std::make_unique<Circle>();
    std::unique_ptr<Shape> s2 = std::make_unique<Rectangle>();

    drawShape(*s1);
    drawShape(*s2);

    return 0;
}
