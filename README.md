# Guide des exemples de code C

## Contenu des fichiers

1. **01_syntaxe_base.c** - Syntaxe de base, types, opérateurs, structures de contrôle
2. **02_fonctions.c** - Fonctions, passage par valeur/référence, tableaux
3. **03_pointeurs_allocation.c** - Pointeurs, malloc, calloc, realloc, free
4. **04_structures_chaines.c** - Structures, chaînes de caractères, fichiers
5. **05_listes_chainees.c** - Listes chaînées complètes
6. **06_piles_files.c** - Piles (LIFO) et Files (FIFO)
7. **07_arbres_binaires.c** - Arbres binaires de recherche
8. **08_recherche_recursivite.c** - Recherche dichotomique et récursivité
9. **09_types_generiques.c** - Types génériques avec void*

## Compilation et exécution

### Compiler un fichier:
```bash
gcc -Wall -Wextra -o programme 01_syntaxe_base.c
```

### Exécuter:
```bash
./programme
```

### Compiler avec débogage:
```bash
gcc -Wall -Wextra -g -o programme 01_syntaxe_base.c
```

### Vérifier les fuites mémoire avec valgrind:
```bash
valgrind --leak-check=full ./programme
```

## Compilation de tous les fichiers

```bash
# Compiler tous les fichiers
gcc -Wall -Wextra -o syntaxe 01_syntaxe_base.c
gcc -Wall -Wextra -o fonctions 02_fonctions.c
gcc -Wall -Wextra -o pointeurs 03_pointeurs_allocation.c
gcc -Wall -Wextra -o structures 04_structures_chaines.c
gcc -Wall -Wextra -o listes 05_listes_chainees.c
gcc -Wall -Wextra -o piles_files 06_piles_files.c
gcc -Wall -Wextra -o arbres 07_arbres_binaires.c
gcc -Wall -Wextra -o recherche 08_recherche_recursivite.c
gcc -Wall -Wextra -o generiques 09_types_generiques.c
```

## Ordre d'étude recommandé

### Jour 1 (8-10h)
1. **01_syntaxe_base.c** - Revoir les bases rapidement (1-2h)
2. **02_fonctions.c** - Maîtriser les fonctions (1-2h)
3. **03_pointeurs_allocation.c** - CRUCIAL - Pointeurs et mémoire (4-5h)

### Jour 2 (8-10h)
4. **04_structures_chaines.c** - Structures et chaînes (2-3h)
5. **05_listes_chainees.c** - TRÈS IMPORTANT - Listes chaînées (5-6h)

### Jour 3 (8-10h)
6. **06_piles_files.c** - Piles et files (3-4h)
7. **07_arbres_binaires.c** - Arbres binaires (4-5h)

### Jour 4 (8-10h)
8. **08_recherche_recursivite.c** - Recherche dichotomique et récursivité (3-4h)
9. **09_types_generiques.c** - Types génériques (2-3h)
10. **Révision et exercices** - Pratique intensive (3-4h)

## Points critiques à maîtriser absolument

### Pointeurs
- Différence entre `&` et `*`
- Arithmétique des pointeurs
- Passage par référence
- Ne jamais déréférencer NULL

### Allocation dynamique
- `malloc` / `calloc` / `realloc` / `free`
- Toujours `free` ce qui est `malloc`
- Vérifier si `malloc` retourne NULL
- Ne pas utiliser après `free`

### Listes chaînées
- Insertion en tête, queue, position
- Suppression
- Ne jamais perdre la tête de liste
- Libérer toute la mémoire

### Arbres binaires
- Parcours: préfixe, infixe, postfixe
- Insertion et recherche dans ABR
- Libération (parcours postfixe)

### Recherche dichotomique
- Version itérative (IMPORTANT)
- Version récursive
- Tableau doit être trié

## Pièges classiques à éviter

1. **Déréférencement de NULL**
   ```c
   int *p = NULL;
   *p = 42;  // CRASH!
   ```

2. **Oubli de free (fuite mémoire)**
   ```c
   int *p = malloc(sizeof(int));
   // ... utilisation ...
   // Oubli de free(p);
   ```

3. **Double free**
   ```c
   free(p);
   free(p);  // ERREUR!
   ```

4. **Utiliser après free**
   ```c
   free(p);
   *p = 42;  // Comportement indéfini!
   ```

5. **Perdre la tête de liste**
   ```c
   Node *liste = ...;
   liste = liste->next;  // Tête originale perdue!
   ```

6. **Oublier '\0' dans les chaînes**
   ```c
   char str[5];
   str[0] = 'A';
   // Oublier str[1] = '\0';
   ```

## Tests avec valgrind

Pour chaque programme utilisant malloc:
```bash
gcc -g -o programme fichier.c
valgrind --leak-check=full --show-leak-kinds=all ./programme
```

Résultat attendu:
```
All heap blocks were freed -- no leaks are possible
```

## Exercices de traçage

Pour bien comprendre, tracez sur papier:
- L'état de la pile et du tas
- Les valeurs des variables
- Les appels de fonctions
- Les structures de données (listes, arbres)

## Bonnes pratiques

1. **Toujours vérifier les allocations**
   ```c
   int *p = malloc(sizeof(int));
   if (p == NULL) {
       // Gérer l'erreur
       return;
   }
   ```

2. **Initialiser les pointeurs**
   ```c
   int *p = NULL;
   ```

3. **Mettre à NULL après free**
   ```c
   free(p);
   p = NULL;
   ```

4. **Compiler avec warnings**
   ```bash
   gcc -Wall -Wextra -Werror
   ```

## Ressources supplémentaires

- Dessiner les structures de données sur papier
- Écrire du code à la main avant de taper
- Faire des exercices sans regarder les corrections
- Expliquer le code à voix haute

