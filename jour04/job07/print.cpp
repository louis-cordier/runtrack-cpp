#include <iostream>

// Fonction template variadique
template <typename... Args>
void print(const Args&... args) {
    // Utilisation d’un "fold expression" (C++17)
    ((std::cout << args << ", "), ...);
    std::cout << "\b\b " << std::endl; // Supprime la dernière virgule et espace
}

// Variante plus propre avec gestion manuelle du séparateur
template <typename T, typename... Args>
void print_v2(const T& first, const Args&... rest) {
    std::cout << first;
    ((std::cout << ", " << rest), ...);
    std::cout << std::endl;
}

// Exemple d’utilisation
int main() {
    print(1, 2, 3, 4, 5);
    print("Bonjour", 42, 3.14, 'A');
    print_v2("Hello", "world", 2025, 3.14159);

    return 0;
}
