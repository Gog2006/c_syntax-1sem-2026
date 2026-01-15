/*
 * 08_recherche_dichotomique_recursivite.c
 * Exemples de recherche dichotomique et conversion itératif/récursif
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// 1. RECHERCHE DICHOTOMIQUE - VERSION ITÉRATIVE
// ============================================

int recherche_dichotomique_iterative(int tab[], int taille, int valeur) {
    int gauche = 0;
    int droite = taille - 1;
    
    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;  // Évite l'overflow
        
        if (tab[milieu] == valeur) {
            return milieu;  // Trouvé
        }
        
        if (tab[milieu] < valeur) {
            gauche = milieu + 1;  // Chercher dans la moitié droite
        } else {
            droite = milieu - 1;  // Chercher dans la moitié gauche
        }
    }
    
    return -1;  // Non trouvé
}

// ============================================
// 2. RECHERCHE DICHOTOMIQUE - VERSION RÉCURSIVE
// ============================================

int recherche_dichotomique_recursive(int tab[], int gauche, int droite, int valeur) {
    // Cas de base: intervalle vide
    if (gauche > droite) {
        return -1;
    }
    
    int milieu = gauche + (droite - gauche) / 2;
    
    if (tab[milieu] == valeur) {
        return milieu;
    }
    
    if (tab[milieu] < valeur) {
        // Chercher dans la moitié droite
        return recherche_dichotomique_recursive(tab, milieu + 1, droite, valeur);
    } else {
        // Chercher dans la moitié gauche
        return recherche_dichotomique_recursive(tab, gauche, milieu - 1, valeur);
    }
}

// Wrapper pour faciliter l'appel
int recherche_dichotomique_rec(int tab[], int taille, int valeur) {
    return recherche_dichotomique_recursive(tab, 0, taille - 1, valeur);
}

void test_recherche_dichotomique() {
    printf("=== TESTS RECHERCHE DICHOTOMIQUE ===\n");
    
    int tab[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int taille = 11;
    
    printf("Tableau: ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n\n");
    
    // Tests avec version itérative
    printf("Version itérative:\n");
    printf("Recherche 23: index %d\n", recherche_dichotomique_iterative(tab, taille, 23));
    printf("Recherche 45: index %d\n", recherche_dichotomique_iterative(tab, taille, 45));
    printf("Recherche 2: index %d\n", recherche_dichotomique_iterative(tab, taille, 2));
    printf("Recherche 78: index %d\n", recherche_dichotomique_iterative(tab, taille, 78));
    printf("Recherche 50 (absent): index %d\n", recherche_dichotomique_iterative(tab, taille, 50));
    
    // Tests avec version récursive
    printf("\nVersion récursive:\n");
    printf("Recherche 23: index %d\n", recherche_dichotomique_rec(tab, taille, 23));
    printf("Recherche 45: index %d\n", recherche_dichotomique_rec(tab, taille, 45));
    printf("Recherche 2: index %d\n", recherche_dichotomique_rec(tab, taille, 2));
    printf("Recherche 78: index %d\n", recherche_dichotomique_rec(tab, taille, 78));
    printf("Recherche 50 (absent): index %d\n", recherche_dichotomique_rec(tab, taille, 50));
}

// ============================================
// 3. FACTORIELLE - ITÉRATIVE VS RÉCURSIVE
// ============================================

// Version itérative
int factorielle_iterative(int n) {
    int resultat = 1;
    for (int i = 1; i <= n; i++) {
        resultat *= i;
    }
    return resultat;
}

// Version récursive
int factorielle_recursive(int n) {
    if (n <= 1) {
        return 1;  // Cas de base
    }
    return n * factorielle_recursive(n - 1);
}

void test_factorielle() {
    printf("\n=== FACTORIELLE ===\n");
    
    for (int i = 0; i <= 10; i++) {
        printf("Factorielle(%d) - Itératif: %d, Récursif: %d\n",
               i, factorielle_iterative(i), factorielle_recursive(i));
    }
}

// ============================================
// 4. FIBONACCI - ITÉRATIVE VS RÉCURSIVE
// ============================================

// Version itérative
int fibonacci_iteratif(int n) {
    if (n <= 1) return n;
    
    int fib_prev = 0;
    int fib_current = 1;
    
    for (int i = 2; i <= n; i++) {
        int fib_next = fib_prev + fib_current;
        fib_prev = fib_current;
        fib_current = fib_next;
    }
    
    return fib_current;
}

// Version récursive (simple mais inefficace)
int fibonacci_recursif(int n) {
    if (n <= 1) {
        return n;  // Cas de base
    }
    return fibonacci_recursif(n - 1) + fibonacci_recursif(n - 2);
}

void test_fibonacci() {
    printf("\n=== FIBONACCI ===\n");
    
    printf("Premiers nombres de Fibonacci:\n");
    for (int i = 0; i <= 15; i++) {
        printf("Fib(%d) - Itératif: %d, Récursif: %d\n",
               i, fibonacci_iteratif(i), fibonacci_recursif(i));
    }
}

// ============================================
// 5. PUISSANCE - ITÉRATIVE VS RÉCURSIVE
// ============================================

// Version itérative
int puissance_iterative(int base, int exposant) {
    int resultat = 1;
    for (int i = 0; i < exposant; i++) {
        resultat *= base;
    }
    return resultat;
}

// Version récursive
int puissance_recursive(int base, int exposant) {
    if (exposant == 0) {
        return 1;  // Cas de base
    }
    return base * puissance_recursive(base, exposant - 1);
}

void test_puissance() {
    printf("\n=== PUISSANCE ===\n");
    
    printf("2^10 - Itératif: %d, Récursif: %d\n",
           puissance_iterative(2, 10), puissance_recursive(2, 10));
    printf("3^5 - Itératif: %d, Récursif: %d\n",
           puissance_iterative(3, 5), puissance_recursive(3, 5));
    printf("5^3 - Itératif: %d, Récursif: %d\n",
           puissance_iterative(5, 3), puissance_recursive(5, 3));
}

// ============================================
// 6. SOMME D'UN TABLEAU - ITÉRATIVE VS RÉCURSIVE
// ============================================

// Version itérative
int somme_tableau_iteratif(int tab[], int taille) {
    int somme = 0;
    for (int i = 0; i < taille; i++) {
        somme += tab[i];
    }
    return somme;
}

// Version récursive
int somme_tableau_recursif(int tab[], int taille) {
    if (taille == 0) {
        return 0;  // Cas de base
    }
    return tab[taille - 1] + somme_tableau_recursif(tab, taille - 1);
}

void test_somme_tableau() {
    printf("\n=== SOMME TABLEAU ===\n");
    
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int taille = 10;
    
    printf("Tableau: ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    printf("Somme - Itératif: %d\n", somme_tableau_iteratif(tab, taille));
    printf("Somme - Récursif: %d\n", somme_tableau_recursif(tab, taille));
}

// ============================================
// 7. INVERSER UNE CHAÎNE - ITÉRATIVE VS RÉCURSIVE
// ============================================

// Version itérative
void inverser_chaine_iteratif(char str[]) {
    int debut = 0;
    int fin = 0;
    
    // Trouver la longueur
    while (str[fin] != '\0') {
        fin++;
    }
    fin--;
    
    // Échanger les caractères
    while (debut < fin) {
        char temp = str[debut];
        str[debut] = str[fin];
        str[fin] = temp;
        debut++;
        fin--;
    }
}

// Version récursive
void inverser_chaine_recursif_helper(char str[], int debut, int fin) {
    if (debut >= fin) {
        return;  // Cas de base
    }
    
    // Échanger
    char temp = str[debut];
    str[debut] = str[fin];
    str[fin] = temp;
    
    // Récursion
    inverser_chaine_recursif_helper(str, debut + 1, fin - 1);
}

void inverser_chaine_recursif(char str[]) {
    int fin = 0;
    while (str[fin] != '\0') {
        fin++;
    }
    inverser_chaine_recursif_helper(str, 0, fin - 1);
}

void test_inverser_chaine() {
    printf("\n=== INVERSER CHAÎNE ===\n");
    
    char str1[] = "Bonjour";
    char str2[] = "Bonjour";
    
    printf("Original: %s\n", str1);
    
    inverser_chaine_iteratif(str1);
    printf("Itératif: %s\n", str1);
    
    inverser_chaine_recursif(str2);
    printf("Récursif: %s\n", str2);
}

// ============================================
// 8. PGCD - ITÉRATIVE VS RÉCURSIVE (Algorithme d'Euclide)
// ============================================

// Version itérative
int pgcd_iteratif(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Version récursive
int pgcd_recursif(int a, int b) {
    if (b == 0) {
        return a;  // Cas de base
    }
    return pgcd_recursif(b, a % b);
}

void test_pgcd() {
    printf("\n=== PGCD (Plus Grand Commun Diviseur) ===\n");
    
    printf("PGCD(48, 18) - Itératif: %d, Récursif: %d\n",
           pgcd_iteratif(48, 18), pgcd_recursif(48, 18));
    printf("PGCD(100, 35) - Itératif: %d, Récursif: %d\n",
           pgcd_iteratif(100, 35), pgcd_recursif(100, 35));
    printf("PGCD(17, 19) - Itératif: %d, Récursif: %d\n",
           pgcd_iteratif(17, 19), pgcd_recursif(17, 19));
}

// ============================================
// 9. COMPTER CHIFFRES - ITÉRATIVE VS RÉCURSIVE
// ============================================

// Version itérative
int compter_chiffres_iteratif(int n) {
    if (n == 0) return 1;
    
    int count = 0;
    if (n < 0) n = -n;  // Valeur absolue
    
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

// Version récursive
int compter_chiffres_recursif(int n) {
    if (n == 0) {
        return 1;  // Cas spécial
    }
    if (n < 10 && n > -10) {
        return 1;  // Cas de base
    }
    return 1 + compter_chiffres_recursif(n / 10);
}

void test_compter_chiffres() {
    printf("\n=== COMPTER CHIFFRES ===\n");
    
    int nombres[] = {0, 7, 42, 123, 9876, 123456};
    
    for (int i = 0; i < 6; i++) {
        printf("Nombre: %d - Itératif: %d chiffres, Récursif: %d chiffres\n",
               nombres[i],
               compter_chiffres_iteratif(nombres[i]),
               compter_chiffres_recursif(nombres[i]));
    }
}

// ============================================
// 10. TOURS DE HANOÏ (RÉCURSIF UNIQUEMENT)
// ============================================

void tours_hanoi(int n, char source, char destination, char auxiliaire) {
    if (n == 1) {
        printf("Déplacer disque 1 de %c vers %c\n", source, destination);
        return;
    }
    
    // Déplacer n-1 disques de source vers auxiliaire
    tours_hanoi(n - 1, source, auxiliaire, destination);
    
    // Déplacer le disque n de source vers destination
    printf("Déplacer disque %d de %c vers %c\n", n, source, destination);
    
    // Déplacer n-1 disques d'auxiliaire vers destination
    tours_hanoi(n - 1, auxiliaire, destination, source);
}

void test_hanoi() {
    printf("\n=== TOURS DE HANOÏ ===\n");
    printf("Solution pour 3 disques:\n");
    tours_hanoi(3, 'A', 'C', 'B');
}

// ============================================
// 11. TRAÇAGE D'APPELS RÉCURSIFS
// ============================================

int factorielle_trace(int n, int niveau) {
    // Afficher l'entrée dans la fonction
    for (int i = 0; i < niveau; i++) printf("  ");
    printf("factorielle(%d) appelé\n", n);
    
    if (n <= 1) {
        for (int i = 0; i < niveau; i++) printf("  ");
        printf("factorielle(%d) retourne 1\n", n);
        return 1;
    }
    
    int resultat = n * factorielle_trace(n - 1, niveau + 1);
    
    // Afficher le retour
    for (int i = 0; i < niveau; i++) printf("  ");
    printf("factorielle(%d) retourne %d\n", n, resultat);
    
    return resultat;
}

void test_trace() {
    printf("\n=== TRAÇAGE APPELS RÉCURSIFS ===\n");
    printf("Traçage de factorielle(5):\n");
    factorielle_trace(5, 0);
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    test_recherche_dichotomique();
    test_factorielle();
    test_fibonacci();
    test_puissance();
    test_somme_tableau();
    test_inverser_chaine();
    test_pgcd();
    test_compter_chiffres();
    test_hanoi();
    test_trace();
    
    printf("\n=== TOUS LES TESTS TERMINÉS ===\n");
    
    return 0;
}
