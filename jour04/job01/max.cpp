#include <iostream>

// Définition du template
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// Exemple d'utilisation
int main() {
    std::cout << "max(3, 7) = " << max(3, 7) << std::endl;
    std::cout << "max(3.14, 2.71) = " << max(3.14, 2.71) << std::endl;
    std::cout << "max('b', 'a') = " << max('b', 'a') << std::endl;
    std::cout << "max(std::string(\"chat\"), std::string(\"chien\")) = "
              << max(std::string("chat"), std::string("chien")) << std::endl;
    return 0;
}
