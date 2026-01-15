/*
 * 03_pointeurs_allocation.c
 * Exemples de pointeurs et allocation dynamique
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. BASES DES POINTEURS
// ============================================

void exemples_pointeurs_base() {
    int x = 42;
    int *ptr;  // Déclaration d'un pointeur vers un int
    
    ptr = &x;  // ptr contient l'adresse de x
    
    printf("Valeur de x: %d\n", x);
    printf("Adresse de x: %p\n", (void*)&x);
    printf("Valeur de ptr (adresse): %p\n", (void*)ptr);
    printf("Valeur pointée par ptr: %d\n", *ptr);
    
    // Modification via pointeur
    *ptr = 100;
    printf("Après *ptr = 100, x vaut: %d\n", x);
}

// ============================================
// 2. ARITHMÉTIQUE DES POINTEURS
// ============================================

void arithmetique_pointeurs() {
    int tab[5] = {10, 20, 30, 40, 50};
    int *ptr = tab;  // ptr pointe sur le premier élément
    
    printf("Parcours avec arithmétique de pointeurs:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }
    
    // Équivalent avec notation tableau
    printf("\nÉquivalent avec notation tableau:\n");
    for (int i = 0; i < 5; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    
    // Incrémenter le pointeur
    printf("\nIncrémenter le pointeur:\n");
    ptr = tab;
    for (int i = 0; i < 5; i++) {
        printf("*ptr = %d\n", *ptr);
        ptr++;  // Avance au prochain élément
    }
}

// ============================================
// 3. POINTEURS ET FONCTIONS
// ============================================

void incrementer(int *p) {
    (*p)++;  // Parenthèses importantes!
}

void doubler_elements(int *tab, int taille) {
    for (int i = 0; i < taille; i++) {
        *(tab + i) *= 2;
        // Équivalent: tab[i] *= 2;
    }
}

void test_pointeurs_fonctions() {
    int x = 5;
    printf("Avant: x = %d\n", x);
    incrementer(&x);
    printf("Après: x = %d\n", x);
    
    int tab[] = {1, 2, 3, 4, 5};
    printf("\nAvant doublement: ");
    for (int i = 0; i < 5; i++) printf("%d ", tab[i]);
    
    doubler_elements(tab, 5);
    printf("\nAprès doublement: ");
    for (int i = 0; i < 5; i++) printf("%d ", tab[i]);
    printf("\n");
}

// ============================================
// 4. MALLOC - ALLOCATION DYNAMIQUE
// ============================================

void exemple_malloc_simple() {
    // Allouer un entier
    int *p = (int*)malloc(sizeof(int));
    if (p == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    *p = 42;
    printf("Valeur allouée: %d\n", *p);
    
    free(p);  // TOUJOURS libérer la mémoire
    p = NULL; // Bonne pratique
}

void exemple_malloc_tableau() {
    int taille = 5;
    
    // Allouer un tableau dynamique
    int *tab = (int*)malloc(taille * sizeof(int));
    if (tab == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    // Utilisation
    for (int i = 0; i < taille; i++) {
        tab[i] = i * 10;
    }
    
    printf("Tableau dynamique: ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    free(tab);  // Libérer
    tab = NULL;
}

// ============================================
// 5. CALLOC - ALLOCATION INITIALISÉE À 0
// ============================================

void exemple_calloc() {
    int taille = 5;
    
    // calloc initialise à 0
    int *tab = (int*)calloc(taille, sizeof(int));
    if (tab == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    printf("Tableau avec calloc (initialisé à 0): ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    free(tab);
}

// ============================================
// 6. REALLOC - REDIMENSIONNEMENT
// ============================================

void exemple_realloc() {
    int *tab = (int*)malloc(3 * sizeof(int));
    if (tab == NULL) return;
    
    // Remplir le tableau initial
    for (int i = 0; i < 3; i++) {
        tab[i] = i + 1;
    }
    
    printf("Tableau initial (taille 3): ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    // Redimensionner à 5 éléments
    int *nouveau_tab = (int*)realloc(tab, 5 * sizeof(int));
    if (nouveau_tab == NULL) {
        free(tab);
        return;
    }
    tab = nouveau_tab;
    
    // Ajouter de nouveaux éléments
    tab[3] = 4;
    tab[4] = 5;
    
    printf("Tableau agrandi (taille 5): ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    free(tab);
}

// ============================================
// 7. FONCTION RETOURNANT UN POINTEUR
// ============================================

int* creer_tableau(int taille) {
    int *tab = (int*)malloc(taille * sizeof(int));
    if (tab == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < taille; i++) {
        tab[i] = i * i;  // Carrés
    }
    
    return tab;
}

void test_fonction_retour_pointeur() {
    int *tab = creer_tableau(5);
    if (tab == NULL) {
        printf("Erreur de création\n");
        return;
    }
    
    printf("Tableau créé par fonction: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    free(tab);  // L'appelant doit libérer
}

// ============================================
// 8. TABLEAUX 2D DYNAMIQUES
// ============================================

int** creer_matrice(int lignes, int colonnes) {
    // Allouer le tableau de pointeurs
    int **matrice = (int**)malloc(lignes * sizeof(int*));
    if (matrice == NULL) return NULL;
    
    // Allouer chaque ligne
    for (int i = 0; i < lignes; i++) {
        matrice[i] = (int*)malloc(colonnes * sizeof(int));
        if (matrice[i] == NULL) {
            // Libérer ce qui a déjà été alloué
            for (int j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            return NULL;
        }
    }
    
    return matrice;
}

void liberer_matrice(int **matrice, int lignes) {
    for (int i = 0; i < lignes; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

void test_matrice_dynamique() {
    int lignes = 3, colonnes = 4;
    int **matrice = creer_matrice(lignes, colonnes);
    if (matrice == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    // Remplir la matrice
    int valeur = 1;
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            matrice[i][j] = valeur++;
        }
    }
    
    // Afficher
    printf("Matrice dynamique %dx%d:\n", lignes, colonnes);
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    liberer_matrice(matrice, lignes);
}

// ============================================
// 9. POINTEURS DE POINTEURS
// ============================================

void modifier_pointeur(int **pp, int nouvelle_valeur) {
    // Créer une nouvelle allocation
    *pp = (int*)malloc(sizeof(int));
    if (*pp != NULL) {
        **pp = nouvelle_valeur;
    }
}

void test_pointeur_de_pointeur() {
    int *p = NULL;
    
    modifier_pointeur(&p, 999);
    
    if (p != NULL) {
        printf("Valeur via pointeur de pointeur: %d\n", *p);
        free(p);
    }
}

// ============================================
// 10. ERREURS COURANTES À ÉVITER
// ============================================

void erreurs_courantes() {
    // ERREUR 1: Déréférencement de NULL
    /*
    int *p = NULL;
    *p = 42;  // CRASH!
    */
    
    // ERREUR 2: Oublier free (fuite mémoire)
    /*
    int *p = (int*)malloc(sizeof(int));
    // ... utilisation ...
    // Oubli de free(p);
    */
    
    // ERREUR 3: Double free
    /*
    int *p = (int*)malloc(sizeof(int));
    free(p);
    free(p);  // ERREUR!
    */
    
    // ERREUR 4: Utiliser après free
    /*
    int *p = (int*)malloc(sizeof(int));
    *p = 42;
    free(p);
    printf("%d\n", *p);  // Comportement indéfini!
    */
    
    // ERREUR 5: Retourner un pointeur vers variable locale
    /*
    int* mauvaise_fonction() {
        int x = 42;
        return &x;  // ERREUR: x n'existe plus après le retour
    }
    */
    
    printf("Voir les commentaires pour les erreurs courantes\n");
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    printf("=== BASES DES POINTEURS ===\n");
    exemples_pointeurs_base();
    
    printf("\n=== ARITHMÉTIQUE DES POINTEURS ===\n");
    arithmetique_pointeurs();
    
    printf("\n=== POINTEURS ET FONCTIONS ===\n");
    test_pointeurs_fonctions();
    
    printf("\n=== MALLOC ===\n");
    exemple_malloc_simple();
    exemple_malloc_tableau();
    
    printf("\n=== CALLOC ===\n");
    exemple_calloc();
    
    printf("\n=== REALLOC ===\n");
    exemple_realloc();
    
    printf("\n=== FONCTION RETOURNANT POINTEUR ===\n");
    test_fonction_retour_pointeur();
    
    printf("\n=== MATRICE DYNAMIQUE ===\n");
    test_matrice_dynamique();
    
    printf("\n=== POINTEUR DE POINTEUR ===\n");
    test_pointeur_de_pointeur();
    
    printf("\n=== ERREURS COURANTES ===\n");
    erreurs_courantes();
    
    return 0;
}
