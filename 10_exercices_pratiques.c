/*
 * 10_exercices_pratiques.c
 * Exercices pratiques avec solutions commentées
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// EXERCICE 1: Inverser un tableau
// ============================================

void inverser_tableau(int tab[], int taille) {
    int debut = 0;
    int fin = taille - 1;
    
    while (debut < fin) {
        // Échanger les éléments
        int temp = tab[debut];
        tab[debut] = tab[fin];
        tab[fin] = temp;
        
        debut++;
        fin--;
    }
}

void test_exercice1() {
    printf("=== EXERCICE 1: INVERSER TABLEAU ===\n");
    int tab[] = {1, 2, 3, 4, 5};
    int taille = 5;
    
    printf("Avant: ");
    for (int i = 0; i < taille; i++) printf("%d ", tab[i]);
    printf("\n");
    
    inverser_tableau(tab, taille);
    
    printf("Après: ");
    for (int i = 0; i < taille; i++) printf("%d ", tab[i]);
    printf("\n");
}

// ============================================
// EXERCICE 2: Compter les occurrences d'un élément
// ============================================

int compter_occurrences(int tab[], int taille, int valeur) {
    int count = 0;
    for (int i = 0; i < taille; i++) {
        if (tab[i] == valeur) {
            count++;
        }
    }
    return count;
}

void test_exercice2() {
    printf("\n=== EXERCICE 2: COMPTER OCCURRENCES ===\n");
    int tab[] = {1, 2, 3, 2, 4, 2, 5};
    int taille = 7;
    
    printf("Tableau: ");
    for (int i = 0; i < taille; i++) printf("%d ", tab[i]);
    printf("\n");
    
    printf("Occurrences de 2: %d\n", compter_occurrences(tab, taille, 2));
    printf("Occurrences de 5: %d\n", compter_occurrences(tab, taille, 5));
}

// ============================================
// EXERCICE 3: Fusionner deux tableaux triés
// ============================================

int* fusionner_tableaux_tries(int tab1[], int taille1, int tab2[], int taille2) {
    int *resultat = (int*)malloc((taille1 + taille2) * sizeof(int));
    if (resultat == NULL) return NULL;
    
    int i = 0, j = 0, k = 0;
    
    // Fusionner tant qu'il reste des éléments dans les deux tableaux
    while (i < taille1 && j < taille2) {
        if (tab1[i] <= tab2[j]) {
            resultat[k++] = tab1[i++];
        } else {
            resultat[k++] = tab2[j++];
        }
    }
    
    // Copier les éléments restants de tab1
    while (i < taille1) {
        resultat[k++] = tab1[i++];
    }
    
    // Copier les éléments restants de tab2
    while (j < taille2) {
        resultat[k++] = tab2[j++];
    }
    
    return resultat;
}

void test_exercice3() {
    printf("\n=== EXERCICE 3: FUSIONNER TABLEAUX TRIÉS ===\n");
    int tab1[] = {1, 3, 5, 7};
    int tab2[] = {2, 4, 6, 8, 10};
    int taille1 = 4, taille2 = 5;
    
    int *resultat = fusionner_tableaux_tries(tab1, taille1, tab2, taille2);
    
    printf("Résultat: ");
    for (int i = 0; i < taille1 + taille2; i++) {
        printf("%d ", resultat[i]);
    }
    printf("\n");
    
    free(resultat);
}

// ============================================
// EXERCICE 4: Vérifier si un tableau est trié
// ============================================

int est_trie(int tab[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        if (tab[i] > tab[i + 1]) {
            return 0;  // Non trié
        }
    }
    return 1;  // Trié
}

void test_exercice4() {
    printf("\n=== EXERCICE 4: VÉRIFIER SI TRIÉ ===\n");
    int tab1[] = {1, 2, 3, 4, 5};
    int tab2[] = {1, 3, 2, 4, 5};
    
    printf("Tab1 trié? %s\n", est_trie(tab1, 5) ? "Oui" : "Non");
    printf("Tab2 trié? %s\n", est_trie(tab2, 5) ? "Oui" : "Non");
}

// ============================================
// EXERCICE 5: Supprimer les doublons d'une liste
// ============================================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* creer_noeud(int valeur) {
    Node *nouveau = (Node*)malloc(sizeof(Node));
    if (nouveau == NULL) return NULL;
    nouveau->data = valeur;
    nouveau->next = NULL;
    return nouveau;
}

Node* inserer_queue(Node *tete, int valeur) {
    Node *nouveau = creer_noeud(valeur);
    if (nouveau == NULL) return tete;
    
    if (tete == NULL) return nouveau;
    
    Node *current = tete;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = nouveau;
    return tete;
}

void afficher_liste(Node *tete) {
    Node *current = tete;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Node* supprimer_doublons(Node *tete) {
    if (tete == NULL) return NULL;
    
    Node *current = tete;
    
    while (current != NULL) {
        Node *runner = current;
        
        // Chercher et supprimer les doublons
        while (runner->next != NULL) {
            if (runner->next->data == current->data) {
                Node *temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        
        current = current->next;
    }
    
    return tete;
}

void liberer_liste(Node *tete) {
    while (tete != NULL) {
        Node *temp = tete;
        tete = tete->next;
        free(temp);
    }
}

void test_exercice5() {
    printf("\n=== EXERCICE 5: SUPPRIMER DOUBLONS ===\n");
    Node *liste = NULL;
    
    liste = inserer_queue(liste, 1);
    liste = inserer_queue(liste, 2);
    liste = inserer_queue(liste, 2);
    liste = inserer_queue(liste, 3);
    liste = inserer_queue(liste, 1);
    liste = inserer_queue(liste, 4);
    
    printf("Avant: ");
    afficher_liste(liste);
    
    liste = supprimer_doublons(liste);
    
    printf("Après: ");
    afficher_liste(liste);
    
    liberer_liste(liste);
}

// ============================================
// EXERCICE 6: Trouver le milieu d'une liste
// ============================================

Node* trouver_milieu(Node *tete) {
    if (tete == NULL) return NULL;
    
    Node *lent = tete;
    Node *rapide = tete;
    
    // Technique du pointeur lent/rapide
    while (rapide->next != NULL && rapide->next->next != NULL) {
        lent = lent->next;
        rapide = rapide->next->next;
    }
    
    return lent;
}

void test_exercice6() {
    printf("\n=== EXERCICE 6: TROUVER MILIEU LISTE ===\n");
    Node *liste = NULL;
    
    for (int i = 1; i <= 7; i++) {
        liste = inserer_queue(liste, i * 10);
    }
    
    printf("Liste: ");
    afficher_liste(liste);
    
    Node *milieu = trouver_milieu(liste);
    printf("Élément du milieu: %d\n", milieu->data);
    
    liberer_liste(liste);
}

// ============================================
// EXERCICE 7: Détecter un cycle dans une liste
// ============================================

int detecter_cycle(Node *tete) {
    if (tete == NULL) return 0;
    
    Node *lent = tete;
    Node *rapide = tete;
    
    while (rapide != NULL && rapide->next != NULL) {
        lent = lent->next;
        rapide = rapide->next->next;
        
        if (lent == rapide) {
            return 1;  // Cycle détecté
        }
    }
    
    return 0;  // Pas de cycle
}

void test_exercice7() {
    printf("\n=== EXERCICE 7: DÉTECTER CYCLE ===\n");
    
    // Liste sans cycle
    Node *liste1 = NULL;
    for (int i = 1; i <= 5; i++) {
        liste1 = inserer_queue(liste1, i);
    }
    printf("Liste sans cycle: %s\n", detecter_cycle(liste1) ? "Cycle" : "Pas de cycle");
    
    // Liste avec cycle
    Node *liste2 = creer_noeud(1);
    liste2->next = creer_noeud(2);
    liste2->next->next = creer_noeud(3);
    liste2->next->next->next = creer_noeud(4);
    liste2->next->next->next->next = liste2->next;  // Créer un cycle
    
    printf("Liste avec cycle: %s\n", detecter_cycle(liste2) ? "Cycle" : "Pas de cycle");
    
    // Nettoyage (attention au cycle!)
    liberer_liste(liste1);
    // Ne pas libérer liste2 car elle a un cycle
}

// ============================================
// EXERCICE 8: Vérifier si un arbre est équilibré
// ============================================

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* creer_noeud_arbre(int valeur) {
    TreeNode *nouveau = (TreeNode*)malloc(sizeof(TreeNode));
    if (nouveau == NULL) return NULL;
    nouveau->data = valeur;
    nouveau->left = NULL;
    nouveau->right = NULL;
    return nouveau;
}

int hauteur_arbre(TreeNode *racine) {
    if (racine == NULL) return 0;
    
    int h_gauche = hauteur_arbre(racine->left);
    int h_droite = hauteur_arbre(racine->right);
    
    return 1 + (h_gauche > h_droite ? h_gauche : h_droite);
}

int est_equilibre(TreeNode *racine) {
    if (racine == NULL) return 1;
    
    int h_gauche = hauteur_arbre(racine->left);
    int h_droite = hauteur_arbre(racine->right);
    
    int diff = h_gauche - h_droite;
    if (diff < 0) diff = -diff;
    
    if (diff > 1) return 0;
    
    return est_equilibre(racine->left) && est_equilibre(racine->right);
}

void liberer_arbre(TreeNode *racine) {
    if (racine == NULL) return;
    liberer_arbre(racine->left);
    liberer_arbre(racine->right);
    free(racine);
}

void test_exercice8() {
    printf("\n=== EXERCICE 8: ARBRE ÉQUILIBRÉ ===\n");
    
    // Arbre équilibré
    TreeNode *arbre1 = creer_noeud_arbre(1);
    arbre1->left = creer_noeud_arbre(2);
    arbre1->right = creer_noeud_arbre(3);
    arbre1->left->left = creer_noeud_arbre(4);
    
    printf("Arbre 1 équilibré? %s\n", est_equilibre(arbre1) ? "Oui" : "Non");
    
    // Arbre non équilibré
    TreeNode *arbre2 = creer_noeud_arbre(1);
    arbre2->left = creer_noeud_arbre(2);
    arbre2->left->left = creer_noeud_arbre(3);
    arbre2->left->left->left = creer_noeud_arbre(4);
    
    printf("Arbre 2 équilibré? %s\n", est_equilibre(arbre2) ? "Oui" : "Non");
    
    liberer_arbre(arbre1);
    liberer_arbre(arbre2);
}

// ============================================
// EXERCICE 9: Palindrome
// ============================================

int est_palindrome(char str[]) {
    int debut = 0;
    int fin = 0;
    
    // Trouver la longueur
    while (str[fin] != '\0') {
        fin++;
    }
    fin--;
    
    while (debut < fin) {
        if (str[debut] != str[fin]) {
            return 0;
        }
        debut++;
        fin--;
    }
    
    return 1;
}

void test_exercice9() {
    printf("\n=== EXERCICE 9: PALINDROME ===\n");
    
    char *tests[] = {"radar", "bonjour", "kayak", "hello", "level"};
    
    for (int i = 0; i < 5; i++) {
        printf("%s: %s\n", tests[i], 
               est_palindrome(tests[i]) ? "Palindrome" : "Pas palindrome");
    }
}

// ============================================
// EXERCICE 10: Rotation d'un tableau
// ============================================

void rotation_droite(int tab[], int taille, int k) {
    k = k % taille;  // Au cas où k > taille
    
    // Inverser tout le tableau
    inverser_tableau(tab, taille);
    
    // Inverser les k premiers éléments
    int debut = 0, fin = k - 1;
    while (debut < fin) {
        int temp = tab[debut];
        tab[debut] = tab[fin];
        tab[fin] = temp;
        debut++;
        fin--;
    }
    
    // Inverser le reste
    debut = k;
    fin = taille - 1;
    while (debut < fin) {
        int temp = tab[debut];
        tab[debut] = tab[fin];
        tab[fin] = temp;
        debut++;
        fin--;
    }
}

void test_exercice10() {
    printf("\n=== EXERCICE 10: ROTATION TABLEAU ===\n");
    int tab[] = {1, 2, 3, 4, 5, 6, 7};
    int taille = 7;
    
    printf("Avant rotation: ");
    for (int i = 0; i < taille; i++) printf("%d ", tab[i]);
    printf("\n");
    
    rotation_droite(tab, taille, 3);
    
    printf("Après rotation de 3: ");
    for (int i = 0; i < taille; i++) printf("%d ", tab[i]);
    printf("\n");
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    test_exercice1();
    test_exercice2();
    test_exercice3();
    test_exercice4();
    test_exercice5();
    test_exercice6();
    test_exercice7();
    test_exercice8();
    test_exercice9();
    test_exercice10();
    
    printf("\n=== TOUS LES EXERCICES TERMINÉS ===\n");
    
    return 0;
}
