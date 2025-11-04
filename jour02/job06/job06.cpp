//
// Created by louis on 04/11/2025.
//
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <string>

class Aquatique {
protected:
    double vitesseNage;  // vitesse de nage en m/s
public:
    Aquatique(double v) : vitesseNage(v) {}
    virtual void nage() const {
        std::cout << "Je nage a " << vitesseNage << " m/s." << std::endl;
    }
    virtual void setVitesseNage(double v) { vitesseNage = v; }
};

class Terrestre {
protected:
    double vitesseMarche;  // vitesse de marche en m/s
public:
    Terrestre(double v) : vitesseMarche(v) {}
    virtual void marche() const {
        std::cout << "Je marche a " << vitesseMarche << " m/s." << std::endl;
    }
    virtual void setVitesseMarche(double v) { vitesseMarche = v; }
};

class Pingouin : public Aquatique, public Terrestre, public std::enable_shared_from_this<Pingouin> {
private:
    std::string nom;
    double vitesseGlisse; // vitesse de glisse sur la neige

public:
    // Constructeur
    Pingouin(const std::string& nom, double vNage, double vMarche, double vGlisse)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(vGlisse) {}

    // Constructeur de copie
    Pingouin(const Pingouin& other)
        : Aquatique(other.vitesseNage), Terrestre(other.vitesseMarche),
          nom(other.nom), vitesseGlisse(other.vitesseGlisse) {}

    ~Pingouin() {
        // Supprimer correctement le pingouin de la colonie
        colony.erase(std::remove_if(colony.begin(), colony.end(),
            [this](const std::shared_ptr<Pingouin>& p) { return p.get() == this; }),
            colony.end());
    }

    // Méthodes
    void nage() const override {
        std::cout << nom << " nage a " << vitesseNage << " m/s." << std::endl;
    }

    void marche() const override {
        std::cout << nom << " marche a " << vitesseMarche << " m/s." << std::endl;
    }

    void setVitesseNage(double v) { vitesseNage = v; trierColonie(); }
    void setVitesseMarche(double v) { vitesseMarche = v; trierColonie(); }
    void setVitesseGlisse(double v) { vitesseGlisse = v; trierColonie(); }

    double tempsParcoursPiste() const {
        if (vitesseGlisse <= 0 || vitesseMarche <= 0 || vitesseNage <= 0) return -1;

        double tempsGlisse = 15.0 / vitesseGlisse;
        double tempsMarche1 = 20.0 / vitesseMarche;
        double tempsNage = 50.0 / vitesseNage;
        double tempsMarche2 = 15.0 / vitesseMarche;

        return tempsGlisse + tempsMarche1 + tempsNage + tempsMarche2;
    }

    static void afficherTempsParcoursTous() {
        std::cout << "\n=== Temps de parcours de tous les pingouins (du plus rapide au plus lent) ===" << std::endl;
        for (const auto& p : colony) {
            std::cout << p->nom << " : " << p->tempsParcoursPiste() << " secondes" << std::endl;
        }
    }

    // Lieux de rencontre
    static void ajouterLieu(const std::string& lieu) {
        lieuxRencontre.push_back(lieu);
    }

    static void retirerLieu(const std::string& lieu) {
        lieuxRencontre.remove(lieu);
    }

    static void afficherLieux() {
        std::cout << "\nLieux de rencontre : ";
        if (lieuxRencontre.empty()) {
            std::cout << "aucun." << std::endl;
            return;
        }
        for (const auto& l : lieuxRencontre)
            std::cout << l << " ";
        std::cout << std::endl;
    }

    // Méthode pour trier la colonie des pingouins
    static void trierColonie() {
        std::sort(colony.begin(), colony.end(),
            [](const std::shared_ptr<Pingouin>& a, const std::shared_ptr<Pingouin>& b) {
                return a->tempsParcoursPiste() < b->tempsParcoursPiste();
            });
    }

    static std::vector<std::shared_ptr<Pingouin>> colony;
    static std::list<std::string> lieuxRencontre;
};

// Initialisation des membres statiques
std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;
std::list<std::string> Pingouin::lieuxRencontre;

int main() {
    // Ajout des lieux de rencontre
    Pingouin::ajouterLieu("lac");
    Pingouin::ajouterLieu("glacier");
    Pingouin::ajouterLieu("forêt");

    // Création de quelques pingouins en utilisant des shared_ptr
    auto p1 = std::make_shared<Pingouin>("Penguin1", 3.0, 5.0, 4.0);
    Pingouin::colony.push_back(p1);
    auto p2 = std::make_shared<Pingouin>("Penguin2", 4.0, 6.0, 3.5);
    Pingouin::colony.push_back(p2);
    auto p3 = std::make_shared<Pingouin>("Penguin3", 3.5, 4.5, 4.2);
    Pingouin::colony.push_back(p3);

    // Affichage des lieux de rencontre
    Pingouin::afficherLieux();

    // Affichage des temps de parcours de tous les pingouins avant le tri
    Pingouin::afficherTempsParcoursTous();

    // Trier la colonie par temps de parcours
    Pingouin::trierColonie();

    // Affichage des temps de parcours après le tri
    std::cout << "\nApres le tri des pingouins par temps de parcours :" << std::endl;
    Pingouin::afficherTempsParcoursTous();

    // Retirer un lieu de rencontre
    Pingouin::retirerLieu("forêt");

    // Affichage des lieux de rencontre après modification
    Pingouin::afficherLieux();

    return 0;
}
