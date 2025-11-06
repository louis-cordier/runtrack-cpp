#include <iostream>

template <typename T>
class Box {
private:
    T value; // Élément stocké

public:
    // Constructeur
    Box(const T& v) : value(v) {}

    // Accesseur (getter)
    T get() const {
        return value;
    }

    // Mutateur (setter)
    void set(const T& v) {
        value = v;
    }

    // Méthode d'affichage (optionnelle)
    void print() const {
        std::cout << "Box contient : " << value << std::endl;
    }
};

// Exemple d'utilisation
int main() {
    Box<int> intBox(42);
    intBox.print();

    Box<std::string> strBox("Bonjour");
    strBox.print();

    // Modification du contenu
    strBox.set("Bonsoir");
    std::cout << "Nouveau contenu : " << strBox.get() << std::endl;

    return 0;
}
