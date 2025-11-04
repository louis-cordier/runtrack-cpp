//
// Created by louis on 04/11/2025.
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

class Aquatique {
protected:
    double vitesseNage;

public:
    Aquatique(double v = 1.0) : vitesseNage(v) {}
    virtual void nage() const = 0;
    void setVitesseNage(double v) { vitesseNage = v; }
    double getVitesseNage() const { return vitesseNage; }
};

class Terrestre {
protected:
    double vitesseMarche;

public:
    Terrestre(double v = 1.0) : vitesseMarche(v) {}
    virtual void marche() const = 0;
    void setVitesseMarche(double v) { vitesseMarche = v; }
    double getVitesseMarche() const { return vitesseMarche; }
};

class Pingouin : public Aquatique, public Terrestre, public std::enable_shared_from_this<Pingouin> {
private:
    std::string nom;
    double vitesseGlisse;

public:
    static std::vector<std::shared_ptr<Pingouin>> instances;

    Pingouin(const std::string& nom, double vNage, double vMarche, double vGlisse)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(vGlisse) {
        // shared_from_this() ne marche qu’après création par make_shared
    }

    static std::shared_ptr<Pingouin> creer(const std::string& nom, double vNage, double vMarche, double vGlisse) {
        auto p = std::shared_ptr<Pingouin>(new Pingouin(nom, vNage, vMarche, vGlisse));
        instances.push_back(p);
        return p;
    }

    ~Pingouin() {
        instances.erase(std::remove_if(instances.begin(), instances.end(),
            [&](const std::shared_ptr<Pingouin>& p) {
                return p.get() == this;
            }), instances.end());
    }

    void nage() const override {
        std::cout << nom << " nage a " << vitesseNage << " m/s." << std::endl;
    }

    void marche() const override {
        std::cout << nom << " marche a " << vitesseMarche << " m/s." << std::endl;
    }

    void setVitesseGlisse(double v) { vitesseGlisse = v; }
    double getVitesseGlisse() const { return vitesseGlisse; }

    double tempsParcoursPiste() const {
        if (vitesseGlisse <= 0 || vitesseMarche <= 0 || vitesseNage <= 0) return -1;

        double temps = 0;
        temps += 15.0 / vitesseGlisse;
        temps += 20.0 / vitesseMarche;
        temps += 50.0 / vitesseNage;
        temps += 15.0 / vitesseMarche;
        return temps;
    }

    static void afficherTempsParcoursTous() {
        std::cout << "\n=== Temps de parcours de tous les pingouins ===\n";
        for (const auto& p : instances) {
            std::cout << p->nom << " : " << p->tempsParcoursPiste() << " secondes" << std::endl;
        }
    }
};

// Initialisation du vecteur statique
std::vector<std::shared_ptr<Pingouin>> Pingouin::instances;

int main() {
    auto p1 = Pingouin::creer("Tux", 2.0, 1.2, 3.0);
    auto p2 = Pingouin::creer("Pingo", 1.8, 1.0, 2.5);

    p1->nage();
    p1->marche();

    p2->nage();
    p2->marche();

    Pingouin::afficherTempsParcoursTous();

    return 0;
}
