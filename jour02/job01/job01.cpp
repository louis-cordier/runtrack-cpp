//
// Created by louis on 04/11/2025.
//
#include <iostream>
#include <string>

// Classe de base Aquatique
class Aquatique {
protected:
    double vitesseNage; // m/s

public:
    Aquatique(double vNage = 0.0) : vitesseNage(vNage) {}

    virtual void nage() const {
        std::cout << "Je nage a " << vitesseNage << " m/s." << std::endl;
    }

    virtual ~Aquatique() {}
};

// Classe de base Terrestre
class Terrestre {
protected:
    double vitesseMarche; // m/s

public:
    Terrestre(double vMarche = 0.0) : vitesseMarche(vMarche) {}

    virtual void marche() const {
        std::cout << "Je marche a " << vitesseMarche << " m/s." << std::endl;
    }

    virtual ~Terrestre() {}
};

// Classe Pingouin qui hérite de Aquatique et Terrestre
class Pingouin : public Aquatique, public Terrestre {
private:
    std::string nom;

public:
    Pingouin(const std::string& nom, double vNage, double vMarche)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom) {}

    void sePresenter() const {
        std::cout << "Bonjour, je suis un pingouin et je m'appelle " << nom << "." << std::endl;
    }

    // Redéfinir les méthodes nage() et marche() si nécessaire
    void nage() const override {
        std::cout << nom << " nage a " << vitesseNage << " m/s." << std::endl;
    }

    void marche() const override {
        std::cout << nom << " marche a " << vitesseMarche << " m/s." << std::endl;
    }
};

int main() {
    Pingouin p("Pingu", 2.5, 1.2);
    p.sePresenter();
    p.nage();
    p.marche();

    return 0;
}
