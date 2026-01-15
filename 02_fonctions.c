/*
 * 02_fonctions.c
 * Exemples de fonctions en C
 */

#include <stdio.h>

// ============================================
// 1. DÉCLARATION ET DÉFINITION
// ============================================

// Prototype (déclaration)
int addition(int a, int b);
void afficher_message(void);
double calculer_moyenne(int tab[], int taille);

// Définition
int addition(int a, int b) {
    return a + b;
}

void afficher_message(void) {
    printf("Fonction sans paramètre ni retour\n");
}

double calculer_moyenne(int tab[], int taille) {
    int somme = 0;
    for (int i = 0; i < taille; i++) {
        somme += tab[i];
    }
    return (double)somme / taille;
}

// ============================================
// 2. PASSAGE PAR VALEUR
// ============================================

void essai_modification_valeur(int x) {
    x = 100;  // Modifie seulement la copie locale
    printf("Dans la fonction: x = %d\n", x);
}

void test_passage_valeur() {
    int nombre = 42;
    printf("Avant: nombre = %d\n", nombre);
    essai_modification_valeur(nombre);
    printf("Après: nombre = %d\n", nombre);  // nombre vaut toujours 42
}

// ============================================
// 3. PASSAGE PAR RÉFÉRENCE (avec pointeur)
// ============================================

void modifier_avec_pointeur(int *x) {
    *x = 100;  // Modifie la valeur à l'adresse pointée
    printf("Dans la fonction: *x = %d\n", *x);
}

void test_passage_reference() {
    int nombre = 42;
    printf("Avant: nombre = %d\n", nombre);
    modifier_avec_pointeur(&nombre);  // Passage de l'adresse
    printf("Après: nombre = %d\n", nombre);  // nombre vaut maintenant 100
}

// ============================================
// 4. FONCTION SWAP (ÉCHANGE)
// ============================================

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void test_swap() {
    int x = 5, y = 10;
    printf("Avant swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("Après swap: x = %d, y = %d\n", x, y);
}

// ============================================
// 5. FONCTIONS AVEC TABLEAUX
// ============================================

// Le tableau est toujours passé par référence
void modifier_tableau(int tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        tab[i] *= 2;  // Double chaque élément
    }
}

void afficher_tableau(int tab[], int taille) {
    printf("[");
    for (int i = 0; i < taille; i++) {
        printf("%d", tab[i]);
        if (i < taille - 1) printf(", ");
    }
    printf("]\n");
}

int trouver_max(int tab[], int taille) {
    int max = tab[0];
    for (int i = 1; i < taille; i++) {
        if (tab[i] > max) {
            max = tab[i];
        }
    }
    return max;
}

int trouver_min(int tab[], int taille) {
    int min = tab[0];
    for (int i = 1; i < taille; i++) {
        if (tab[i] < min) {
            min = tab[i];
        }
    }
    return min;
}

int somme_tableau(int tab[], int taille) {
    int somme = 0;
    for (int i = 0; i < taille; i++) {
        somme += tab[i];
    }
    return somme;
}

void test_fonctions_tableaux() {
    int nombres[] = {5, 2, 8, 1, 9};
    int taille = 5;
    
    printf("Tableau initial: ");
    afficher_tableau(nombres, taille);
    
    printf("Max: %d\n", trouver_max(nombres, taille));
    printf("Min: %d\n", trouver_min(nombres, taille));
    printf("Somme: %d\n", somme_tableau(nombres, taille));
    printf("Moyenne: %.2f\n", calculer_moyenne(nombres, taille));
    
    modifier_tableau(nombres, taille);
    printf("Après modification: ");
    afficher_tableau(nombres, taille);
}

// ============================================
// 6. RECHERCHE LINÉAIRE
// ============================================

int recherche_lineaire(int tab[], int taille, int valeur) {
    for (int i = 0; i < taille; i++) {
        if (tab[i] == valeur) {
            return i;  // Retourne l'indice
        }
    }
    return -1;  // Non trouvé
}

void test_recherche() {
    int nombres[] = {10, 25, 30, 45, 50};
    int taille = 5;
    int recherche = 30;
    
    int index = recherche_lineaire(nombres, taille, recherche);
    if (index != -1) {
        printf("%d trouvé à l'indice %d\n", recherche, index);
    } else {
        printf("%d non trouvé\n", recherche);
    }
}

// ============================================
// 7. FONCTIONS RÉCURSIVES
// ============================================

int factorielle(int n) {
    if (n <= 1) {
        return 1;  // Cas de base
    }
    return n * factorielle(n - 1);  // Appel récursif
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;  // Cas de base
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int puissance(int base, int exposant) {
    if (exposant == 0) {
        return 1;
    }
    return base * puissance(base, exposant - 1);
}

void test_recursivite() {
    printf("Factorielle de 5: %d\n", factorielle(5));
    printf("Fibonacci(7): %d\n", fibonacci(7));
    printf("2^10: %d\n", puissance(2, 10));
}

// ============================================
// 8. FONCTIONS AVEC PLUSIEURS VALEURS DE RETOUR
// ============================================

// Utiliser des pointeurs pour retourner plusieurs valeurs
void min_max(int tab[], int taille, int *min, int *max) {
    *min = tab[0];
    *max = tab[0];
    
    for (int i = 1; i < taille; i++) {
        if (tab[i] < *min) *min = tab[i];
        if (tab[i] > *max) *max = tab[i];
    }
}

void test_min_max() {
    int nombres[] = {5, 2, 8, 1, 9};
    int min, max;
    
    min_max(nombres, 5, &min, &max);
    printf("Min: %d, Max: %d\n", min, max);
}

// ============================================
// 9. FONCTIONS VARIADIC (bonus)
// ============================================

#include <stdarg.h>

int somme_variable(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int somme = 0;
    for (int i = 0; i < count; i++) {
        somme += va_arg(args, int);
    }
    
    va_end(args);
    return somme;
}

void test_variadic() {
    printf("Somme(3, 5, 7): %d\n", somme_variable(3, 3, 5, 7));
    printf("Somme(10, 20, 30, 40): %d\n", somme_variable(4, 10, 20, 30, 40));
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    printf("=== PASSAGE PAR VALEUR ===\n");
    test_passage_valeur();
    
    printf("\n=== PASSAGE PAR RÉFÉRENCE ===\n");
    test_passage_reference();
    
    printf("\n=== FONCTION SWAP ===\n");
    test_swap();
    
    printf("\n=== FONCTIONS AVEC TABLEAUX ===\n");
    test_fonctions_tableaux();
    
    printf("\n=== RECHERCHE ===\n");
    test_recherche();
    
    printf("\n=== RÉCURSIVITÉ ===\n");
    test_recursivite();
    
    printf("\n=== MIN/MAX ===\n");
    test_min_max();
    
    printf("\n=== FONCTIONS VARIADIQUES ===\n");
    test_variadic();
    
    return 0;
}
