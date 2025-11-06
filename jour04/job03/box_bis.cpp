#include <iostream>
#include <string>

// Version générique de Box
template <typename T>
class Box {
private:
    T value;

public:
    Box(const T& v) : value(v) {}

    T get() const { return value; }
    void set(const T& v) { value = v; }

    void print() const {
        std::cout << "Box contient : " << value << std::endl;
    }
};

// Spécialisation pour les pointeurs
template <typename T>
class Box<T*> {
private:
    T* ptr;

public:
    Box(T* p) : ptr(p) {}

    // Accéder au pointeur
    T* get() const { return ptr; }

    // Accéder à la valeur pointée
    T& getValue() const { return *ptr; }

    void set(T* p) { ptr = p; }

    void print() const {
        if (ptr)
            std::cout << "Box pointe vers : " << *ptr << std::endl;
        else
            std::cout << "Box ne contient pas de pointeur valide." << std::endl;
    }
};

// Exemple d'utilisation
int main() {
    int a = 10;
    Box<int*> ptrBox(&a);
    ptrBox.print();

    std::cout << "Valeur pointée : " << ptrBox.getValue() << std::endl;

    // Modification via la box
    ptrBox.getValue() = 99;
    std::cout << "Nouvelle valeur de a : " << a << std::endl;

    std::string str = "Bonjour";
    Box<std::string*> strBox(&str);
    strBox.print();

    return 0;
}
