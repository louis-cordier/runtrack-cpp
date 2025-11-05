& player->distance(*e) <= 1.5) {
player->attack(*e);
break;
}
}
}
else if(cmd=='w') player->switchWeapon();
else cout << "❌ Commande inconnue\n";

```
    // Tour des ennemis
    for(auto& obj : world.getObjects()) {
        Enemy* e = dynamic_cast<Enemy*>(obj.get());
        if(e && e->isActive()) e->moveTowards(*player, world.getObjects());
    }

    // Nettoyage des objets inactifs
    world.cleanup();
    cout << "----------------------------\n";
}

cout << "💀 Le joueur est mort. Fin du jeu.\n";
return 0;
```

}
