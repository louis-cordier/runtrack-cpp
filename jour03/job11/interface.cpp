#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Taille de la grille de jeu
const int WIDTH = 20;
const int HEIGHT = 10;

class Vector2d {
public:
double x, y;
Vector2d(double _x=0, double _y=0) : x(_x), y(_y) {}
};

class GameObject {
public:
Vector2d pos;
bool active = true;
GameObject(double x=0, double y=0) : pos(x, y) {}
virtual void update() = 0;
virtual void draw() const = 0;
virtual ~GameObject() {}
};

// Exemple simplifié pour l’interface
void drawGameWorld(const vector<shared_ptr<GameObject>>& objects) {
char grid[HEIGHT][WIDTH];

```
// Initialisation
for(int i=0;i<HEIGHT;i++)
    for(int j=0;j<WIDTH;j++)
        grid[i][j] = '.';

// Placer les objets sur la grille
for(const auto& obj : objects) {
    int gx = static_cast<int>(obj->pos.x);
    int gy = static_cast<int>(obj->pos.y);
    if(gx >=0 && gx < WIDTH && gy >=0 && gy < HEIGHT) {
        char symbol = '?';
        // Identifier le type via dynamic_cast
        if(dynamic_cast<class Player*>(obj.get())) symbol = 'P';
        else if(dynamic_cast<class Enemy*>(obj.get())) symbol = 'E';
        else if(dynamic_cast<class Projectile*>(obj.get())) symbol = '*';
        else symbol = 'O';
        grid[gy][gx] = symbol;
    }
}

// Affichage de la grille
for(int i=0;i<HEIGHT;i++) {
    for(int j=0;j<WIDTH;j++)
        cout << grid[i][j];
    cout << "\n";
}
cout << "Légende : P=Player, E=Enemy, *=Projectile, O=Autre\n";
```

}

// Dans la boucle principale
/*
while(gameRunning) {
// update() des objets
for(auto& obj : objects) obj->update();

```
// afficher la grille
drawGameWorld(objects);

// demander action joueur
char cmd;
cout << "Déplacer (z/q/s/d), attaquer (a), changer arme (w) : ";
cin >> cmd;

// gérer commandes
```

}
*/
