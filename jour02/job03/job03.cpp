//
// Created by louis on 04/11/2025.
//
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Aquatique {
protected:
    double vitesseNage;

public:
    Aquatique(double vNage = 0.0) : vitesseNage(vNage) {}
    virtual void nage() const {
        std::cout << "Je nage a " << vitesseNage << " m/s." << std::endl;
    }
    virtual ~Aquatique() {}
};

class Terrestre {
protected:
    double vitesseMarche;

public:
    Terrestre(double vMarche = 0.0) : vitesseMarche(vMarche) {}
    virtual void marche() const {
        std::cout << "Je marche a " << vitesseMarche << " m/s." << std::endl;
    }
    virtual ~Terrestre() {}
};

class Pingouin : public Aquatique, public Terrestre, public std::enable_shared_from_this<Pingouin> {
private:
    std::string nom;
    double vitesseGlisse;

    // Constructeur privé : on force l'utilisation de la méthode de fabrique
    Pingouin(const std::string& nom, double vNage, double vMarche, double vGlisse)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(vGlisse) {}

public:
    // Vecteur statique contenant tous les pingouins instanciés
    static std::vector<std::shared_ptr<Pingouin>> instances;

    // Méthode de fabrique
    static std::shared_ptr<Pingouin> creer(const std::string& nom, double vNage, double vMarche, double vGlisse) {
        std::shared_ptr<Pingouin> pingouin(new Pingouin(nom, vNage, vMarche, vGlisse));
        instances.push_back(pingouin);
        return pingouin;
    }

    // Destructeur : suppression du shared_ptr courant du vecteur
    ~Pingouin() {
        auto it = std::remove_if(instances.begin(), instances.end(),
                                 [this](const std::shared_ptr<Pingouin>& ptr) {
                                     return ptr.get() == this;
                                 });
        instances.erase(it, instances.end());
        std::cout << "Pingouin " << nom << " detruit et retire du registre.\n";
    }

    void sePresenter() const {
        std::cout << "Bonjour, je suis un pingouin et je m'appelle " << nom << "." << std::endl;
    }

    void nage() const override {
        std::cout << nom << " nage a " << vitesseNage << " m/s." << std::endl;
    }

    void marche() const override {
        std::cout << nom << " marche a " << vitesseMarche << " m/s." << std::endl;
    }

    void glisse() const {
        std::cout << nom << " glisse a " << vitesseGlisse << " m/s." << std::endl;
    }

    // Méthodes pour modifier les vitesses
    void setVitesseNage(double v) { vitesseNage = v; }
    void setVitesseMarche(double v) { vitesseMarche = v; }
    void setVitesseGlisse(double v) { vitesseGlisse = v; }
};

// Définition du vecteur statique
std::vector<std::shared_ptr<Pingouin>> Pingouin::instances;

// === Exemple d'utilisation ===

int main() {
    {
        auto p1 = Pingouin::creer("Pingu", 2.5, 1.2, 3.0);
        auto p2 = Pingouin::creer("Tux", 2.0, 1.0, 2.8);

        std::cout << "\nListe actuelle des pingouins (" << Pingouin::instances.size() << "):\n";
        for (const auto& pingouin : Pingouin::instances) {
            pingouin->sePresenter();
        }
    } // À la sortie du bloc, p1 et p2 sont détruits

    std::cout << "\nApres destruction automatique, pingouins restants : "
              << Pingouin::instances.size() << std::endl;

    return 0;
}
