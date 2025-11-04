//
// Created by louis on 04/11/2025.
//
#include <iostream>
#include <string>

// Classe de base Aquatique
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

// Classe de base Terrestre
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

// Classe Pingouin qui hérite de Aquatique et Terrestre
class Pingouin : public Aquatique, public Terrestre {
private:
    std::string nom;
    double vitesseGlisse;

public:
    // Constructeur
    Pingouin(const std::string& nom, double vNage, double vMarche, double vGlisse)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(vGlisse) {}

    // Constructeur de copie
    Pingouin(const Pingouin& autre)
        : Aquatique(autre.vitesseNage),
          Terrestre(autre.vitesseMarche),
          nom(autre.nom),
          vitesseGlisse(autre.vitesseGlisse) {}

    // Méthode de présentation
    void sePresenter() const {
        std::cout << "Bonjour, je suis un pingouin et je m'appelle " << nom << "." << std::endl;
    }

    // Redéfinition des méthodes de déplacement
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

int main() {
    Pingouin p1("Pingu", 2.5, 1.2, 3.0);
    p1.sePresenter();
    p1.nage();
    p1.marche();
    p1.glisse();

    std::cout << "\nCreation d'un pingouin clone...\n";
    Pingouin p2 = p1;
    p2.setVitesseGlisse(4.5); // On change la vitesse de glisse pour le second
    p2.sePresenter();
    p2.glisse();

    return 0;
}
