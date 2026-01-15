/*
 * 01_syntaxe_base.c
 * Exemples de syntaxe de base en C
 */

#include <stdio.h>

// ============================================
// 1. TYPES DE BASE ET PRINTF/SCANF
// ============================================

void exemples_types_base() {
    // Déclaration et initialisation
    int entier = 42;
    float flottant = 3.14f;
    double double_precision = 3.14159265359;
    char caractere = 'A';
    char chaine[50] = "Bonjour";
    
    // Affichage avec printf
    printf("Entier: %d\n", entier);
    printf("Flottant: %f\n", flottant);
    printf("Double: %.10f\n", double_precision);
    printf("Caractère: %c\n", caractere);
    printf("Chaîne: %s\n", chaine);
    printf("Adresse: %p\n", (void*)&entier);
    printf("Hexadécimal: %x\n", entier);
    printf("Octal: %o\n", entier);
    
    // Lecture avec scanf
    int nombre;
    printf("Entrez un nombre: ");
    scanf("%d", &nombre);  // ATTENTION: & obligatoire pour scanf
    printf("Vous avez entré: %d\n", nombre);
}

// ============================================
// 2. OPÉRATEURS
// ============================================

void exemples_operateurs() {
    int a = 10, b = 3;
    
    // Arithmétiques
    printf("Addition: %d + %d = %d\n", a, b, a + b);
    printf("Soustraction: %d - %d = %d\n", a, b, a - b);
    printf("Multiplication: %d * %d = %d\n", a, b, a * b);
    printf("Division: %d / %d = %d\n", a, b, a / b);
    printf("Modulo: %d %% %d = %d\n", a, b, a % b);
    
    // Incrémentation
    int c = 5;
    printf("c = %d\n", c);
    printf("c++ = %d\n", c++);  // Post-incrémentation: affiche 5, puis c=6
    printf("c = %d\n", c);
    printf("++c = %d\n", ++c);  // Pré-incrémentation: c=7, puis affiche 7
    
    // Logiques
    int x = 1, y = 0;
    printf("ET logique: %d && %d = %d\n", x, y, x && y);
    printf("OU logique: %d || %d = %d\n", x, y, x || y);
    printf("NON logique: !%d = %d\n", x, !x);
    
    // Comparaison
    printf("%d == %d: %d\n", a, b, a == b);
    printf("%d != %d: %d\n", a, b, a != b);
    printf("%d > %d: %d\n", a, b, a > b);
    printf("%d < %d: %d\n", a, b, a < b);
    printf("%d >= %d: %d\n", a, b, a >= b);
    printf("%d <= %d: %d\n", a, b, a <= b);
}

// ============================================
// 3. STRUCTURES DE CONTRÔLE
// ============================================

void exemple_if() {
    int age = 18;
    
    if (age < 18) {
        printf("Mineur\n");
    } else if (age == 18) {
        printf("Tout juste majeur\n");
    } else {
        printf("Majeur\n");
    }
    
    // Opérateur ternaire
    char *statut = (age >= 18) ? "Majeur" : "Mineur";
    printf("Statut: %s\n", statut);
}

void exemple_switch() {
    int choix = 2;
    
    switch (choix) {
        case 1:
            printf("Option 1\n");
            break;
        case 2:
            printf("Option 2\n");
            break;
        case 3:
            printf("Option 3\n");
            break;
        default:
            printf("Option invalide\n");
            break;
    }
}

void exemple_boucles() {
    // Boucle for
    printf("Boucle for:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Boucle while
    printf("Boucle while:\n");
    int j = 0;
    while (j < 5) {
        printf("%d ", j);
        j++;
    }
    printf("\n");
    
    // Boucle do-while (exécutée au moins une fois)
    printf("Boucle do-while:\n");
    int k = 0;
    do {
        printf("%d ", k);
        k++;
    } while (k < 5);
    printf("\n");
    
    // Break et continue
    printf("Avec break (s'arrête à 3):\n");
    for (int i = 0; i < 10; i++) {
        if (i == 3) break;
        printf("%d ", i);
    }
    printf("\n");
    
    printf("Avec continue (saute 3):\n");
    for (int i = 0; i < 5; i++) {
        if (i == 3) continue;
        printf("%d ", i);
    }
    printf("\n");
}

// ============================================
// 4. TABLEAUX
// ============================================

void exemple_tableaux() {
    // Tableau 1D
    int nombres[5] = {10, 20, 30, 40, 50};
    
    printf("Parcours avec for:\n");
    for (int i = 0; i < 5; i++) {
        printf("nombres[%d] = %d\n", i, nombres[i]);
    }
    
    // Initialisation partielle
    int tab[10] = {1, 2, 3};  // Reste initialisé à 0
    
    // Tableau 2D (matrice)
    int matrice[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("\nMatrice 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    printf("=== TYPES DE BASE ===\n");
    exemples_types_base();
    
    printf("\n=== OPÉRATEURS ===\n");
    exemples_operateurs();
    
    printf("\n=== IF ===\n");
    exemple_if();
    
    printf("\n=== SWITCH ===\n");
    exemple_switch();
    
    printf("\n=== BOUCLES ===\n");
    exemple_boucles();
    
    printf("\n=== TABLEAUX ===\n");
    exemple_tableaux();
    
    return 0;
}
