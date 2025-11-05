class Projectile : public GameObject {
private:
int damage;
Vector2d direction;
Character* owner; // qui a tiré la flèche
public:
Projectile(double startX, double startY, double dx, double dy, int dmg, Character* o)
: GameObject(startX, startY), damage(dmg), direction(dx, dy), owner(o) {}

```
void update() override {
    // Déplacement de la flèche
    x += direction.getX();
    y += direction.getY();

    // Vérification collision avec les ennemis
    for(auto& obj : GameWorldSingleton::getInstance().getObjects()) {
        Character* target = dynamic_cast<Character*>(obj.get());
        if(target && target != owner && target->isAlive()) {
            if(static_cast<int>(x) == static_cast<int>(target->getX()) &&
               static_cast<int>(y) == static_cast<int>(target->getY())) {
                cout << "🏹 La flèche touche " << target->getName() << " pour " << damage << " dégâts!\n";
                target->takeDamage(damage);
                active = false;
                break;
            }
        }
    }
}

void draw() const override {
    if(active) cout << "➡ Projectile à (" << x << "," << y << ")\n";
}
```

};
