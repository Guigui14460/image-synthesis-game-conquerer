# Equipe

- Développeur 1 : LEMAIRE Raphaëlle
- Développeur 2 : LETELLIER Guillaume


# Présentation du jeu
Réalisation d'un jeu de combat/course entre deux vaisseaux.

**But :** arriver sur une planète pour la conquérir.

**Gameplay :** double scène 3D (split de l'écran de rendu)

**Contrôles :**
- Joueur 1 : touches Z,Q,S,D pour les déplacements, Ctrl gauche pour tirer, Shift gauche pour accélérer et Tab pour changer d'armement.
- Joueur 2 : touches directionnelles pour se déplacer, Ctrl droit pour tirer, Shift droit pour accélérer et Entrée pour changer d'armement.


# Description détaillée
Jeu en un contre un consistant à aller se battre pour la conquête d'une nouvelle planète pour les colonies représentées par les deux joueurs. Au départ, il n'y a pas de planète et quelques secondes après, la localisation apparaît à l'écran.

Les joueurs peuvent gagner de plusieurs manières :
- soit ils arrivent en premier sur la planète
    - s'ils y sont depuis assez longtemps, la planète pourra repousser la puissance de frappe de l'autre joueur
    - sinon l'autre joueur pourra détruire le vaisseau ennemi
- soit ils se combattent et le dernier vaisseau en vie gagne la nouvelle planète

(image de fin avec des vaisseaux alliés aux couleurs du vainqueur qui arrivent pour établir la colonie)

Pour les combats, ils peuvent se battre avec des lasers (type star wars) comme tirs classiques, des missiles, des leurres pour contrer des missiles. Etant dans l'espace, ils peuvent utiliser l'environnement pour se cacher et surprendre l'ennemi (s'il est considéré caché, le joueur n'apparaîtra plus à l'écran de l'autre joueur)

Pour éviter que le jeu dure trop longtemps, un minuteur sera affiché et les joueurs perdront tous les deux car invasion par une autre armée (si les deux joueurs sont en vie, ou que le chronomètre est terminé).

# Aspects techniques
* rendu de texte à l'écran
* détection de collision
* chargement de modèles 3D
* overlay 2D au-dessus d'un monde 3D
