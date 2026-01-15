/*
 * 05_listes_chainees.c
 * Exemples complets de listes chaînées
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// 1. DÉFINITION DE LA STRUCTURE
// ============================================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// ============================================
// 2. CRÉER UN NOUVEAU NŒUD
// ============================================

Node* creer_noeud(int valeur) {
    Node *nouveau = (Node*)malloc(sizeof(Node));
    if (nouveau == NULL) {
        printf("Erreur d'allocation\n");
        return NULL;
    }
    nouveau->data = valeur;
    nouveau->next = NULL;
    return nouveau;
}

// ============================================
// 3. AFFICHER LA LISTE
// ============================================

void afficher_liste(Node *tete) {
    if (tete == NULL) {
        printf("Liste vide\n");
        return;
    }
    
    Node *current = tete;
    printf("Liste: ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// ============================================
// 4. INSERTION EN TÊTE
// ============================================

Node* inserer_tete(Node *tete, int valeur) {
    Node *nouveau = creer_noeud(valeur);
    if (nouveau == NULL) return tete;
    
    nouveau->next = tete;
    return nouveau;  // La nouvelle tête
}

void test_insertion_tete() {
    Node *liste = NULL;
    
    printf("=== INSERTION EN TÊTE ===\n");
    liste = inserer_tete(liste, 10);
    afficher_liste(liste);
    
    liste = inserer_tete(liste, 20);
    afficher_liste(liste);
    
    liste = inserer_tete(liste, 30);
    afficher_liste(liste);
    
    // Libérer (voir plus bas)
    while (liste != NULL) {
        Node *temp = liste;
        liste = liste->next;
        free(temp);
    }
}

// ============================================
// 5. INSERTION EN QUEUE
// ============================================

Node* inserer_queue(Node *tete, int valeur) {
    Node *nouveau = creer_noeud(valeur);
    if (nouveau == NULL) return tete;
    
    // Liste vide
    if (tete == NULL) {
        return nouveau;
    }
    
    // Trouver le dernier nœud
    Node *current = tete;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = nouveau;
    return tete;
}

void test_insertion_queue() {
    Node *liste = NULL;
    
    printf("\n=== INSERTION EN QUEUE ===\n");
    liste = inserer_queue(liste, 10);
    afficher_liste(liste);
    
    liste = inserer_queue(liste, 20);
    afficher_liste(liste);
    
    liste = inserer_queue(liste, 30);
    afficher_liste(liste);
    
    // Libérer
    while (liste != NULL) {
        Node *temp = liste;
        liste = liste->next;
        free(temp);
    }
}

// ============================================
// 6. INSERTION À UNE POSITION
// ============================================

Node* inserer_position(Node *tete, int valeur, int position) {
    // Position 0 = insertion en tête
    if (position == 0) {
        return inserer_tete(tete, valeur);
    }
    
    Node *nouveau = creer_noeud(valeur);
    if (nouveau == NULL) return tete;
    
    Node *current = tete;
    // Avancer jusqu'à position-1
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Position invalide\n");
        free(nouveau);
        return tete;
    }
    
    nouveau->next = current->next;
    current->next = nouveau;
    return tete;
}

void test_insertion_position() {
    Node *liste = NULL;
    
    printf("\n=== INSERTION À POSITION ===\n");
    liste = inserer_tete(liste, 10);
    liste = inserer_queue(liste, 30);
    afficher_liste(liste);  // 10 -> 30
    
    liste = inserer_position(liste, 20, 1);
    afficher_liste(liste);  // 10 -> 20 -> 30
    
    liste = inserer_position(liste, 5, 0);
    afficher_liste(liste);  // 5 -> 10 -> 20 -> 30
    
    // Libérer
    while (liste != NULL) {
        Node *temp = liste;
        liste = liste->next;
        free(temp);
    }
}

// ============================================
// 7. RECHERCHE
// ============================================

Node* rechercher(Node *tete, int valeur) {
    Node *current = tete;
    while (current != NULL) {
        if (current->data == valeur) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int rechercher_position(Node *tete, int valeur) {
    Node *current = tete;
    int position = 0;
    while (current != NULL) {
        if (current->data == valeur) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;  // Non trouvé
}

void test_recherche() {
    Node *liste = NULL;
    liste = inserer_queue(liste, 10);
    liste = inserer_queue(liste, 20);
    liste = inserer_queue(liste, 30);
    
    printf("\n=== RECHERCHE ===\n");
    afficher_liste(liste);
    
    Node *trouve = rechercher(liste, 20);
    if (trouve != NULL) {
        printf("20 trouvé dans la liste\n");
    }
    
    int pos = rechercher_position(liste, 30);
    if (pos != -1) {
        printf("30 trouvé à la position %d\n", pos);
    }
    
    if (rechercher(liste, 50) == NULL) {
        printf("50 n'est pas dans la liste\n");
    }
    
    // Libérer
    while (liste != NULL) {
        Node *temp = liste;
        liste = liste->next;
        free(temp);
    }
}

// ============================================
// 8. SUPPRESSION EN TÊTE
// ============================================

Node* supprimer_tete(Node *tete) {
    if (tete == NULL) {
        printf("Liste vide, impossible de supprimer\n");
        return NULL;
    }
    
    Node *nouvelle_tete = tete->next;
    free(tete);
    return nouvelle_tete;
}

// ============================================
// 9. SUPPRESSION D'UNE VALEUR
// ============================================

Node* supprimer_valeur(Node *tete, int valeur) {
    if (tete == NULL) {
        return NULL;
    }
    
    // Si c'est la tête
    if (tete->data == valeur) {
        Node *nouvelle_tete = tete->next;
        free(tete);
        return nouvelle_tete;
    }
    
    // Chercher le nœud précédent
    Node *current = tete;
    while (current->next != NULL && current->next->data != valeur) {
        current = current->next;
    }
    
    // Valeur non trouvée
    if (current->next == NULL) {
        printf("Valeur %d non trouvée\n", valeur);
        return tete;
    }
    
    // Supprimer le nœud
    Node *a_supprimer = current->next;
    current->next = a_supprimer->next;
    free(a_supprimer);
    
    return tete;
}

void test_suppression() {
    Node *liste = NULL;
    
    printf("\n=== SUPPRESSION ===\n");
    liste = inserer_queue(liste, 10);
    liste = inserer_queue(liste, 20);
    liste = inserer_queue(liste, 30);
    liste = inserer_queue(liste, 40);
    
    afficher_liste(liste);  // 10 -> 20 -> 30 -> 40
    
    liste = supprimer_valeur(liste, 20);
    afficher_liste(liste);  // 10 -> 30 -> 40
    
    liste = supprimer_tete(liste);
    afficher_liste(liste);  // 30 -> 40
    
    liste = supprimer_valeur(liste, 40);
    afficher_liste(liste);  // 30
    
    // Libérer
    while (liste != NULL) {
        Node *temp = liste;
        liste = liste->next;
        free(temp);
    }
}

// ============================================
// 10. COMPTER LES ÉLÉMENTS
// ============================================

int compter(Node *tete) {
    int count = 0;
    Node *current = tete;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Version récursive
int compter_recursif(Node *tete) {
    if (tete == NULL) {
        return 0;
    }
    return 1 + compter_recursif(tete->next);
}

// ============================================
// 11. LIBÉRER TOUTE LA LISTE
// ============================================

void liberer_liste(Node *tete) {
    Node *current = tete;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

// Version récursive
void liberer_liste_recursif(Node *tete) {
    if (tete == NULL) {
        return;
    }
    liberer_liste_recursif(tete->next);
    free(tete);
}

// ============================================
// 12. INVERSER LA LISTE
// ============================================

Node* inverser(Node *tete) {
    Node *precedent = NULL;
    Node *current = tete;
    Node *suivant = NULL;
    
    while (current != NULL) {
        suivant = current->next;  // Sauvegarder le suivant
        current->next = precedent;  // Inverser le lien
        precedent = current;  // Avancer precedent
        current = suivant;  // Avancer current
    }
    
    return precedent;  // Nouvelle tête
}

void test_inverser() {
    Node *liste = NULL;
    
    printf("\n=== INVERSER LA LISTE ===\n");
    liste = inserer_queue(liste, 10);
    liste = inserer_queue(liste, 20);
    liste = inserer_queue(liste, 30);
    liste = inserer_queue(liste, 40);
    
    printf("Avant inversion: ");
    afficher_liste(liste);
    
    liste = inverser(liste);
    
    printf("Après inversion: ");
    afficher_liste(liste);
    
    liberer_liste(liste);
}

// ============================================
// 13. FUSIONNER DEUX LISTES
// ============================================

Node* fusionner(Node *liste1, Node *liste2) {
    if (liste1 == NULL) return liste2;
    if (liste2 == NULL) return liste1;
    
    // Trouver la fin de liste1
    Node *current = liste1;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = liste2;
    return liste1;
}

void test_fusionner() {
    Node *liste1 = NULL;
    Node *liste2 = NULL;
    
    printf("\n=== FUSIONNER DEUX LISTES ===\n");
    
    liste1 = inserer_queue(liste1, 10);
    liste1 = inserer_queue(liste1, 20);
    
    liste2 = inserer_queue(liste2, 30);
    liste2 = inserer_queue(liste2, 40);
    
    printf("Liste 1: ");
    afficher_liste(liste1);
    printf("Liste 2: ");
    afficher_liste(liste2);
    
    liste1 = fusionner(liste1, liste2);
    
    printf("Liste fusionnée: ");
    afficher_liste(liste1);
    
    liberer_liste(liste1);
}

// ============================================
// 14. OBTENIR LE N-IÈME ÉLÉMENT
// ============================================

int obtenir_element(Node *tete, int index) {
    Node *current = tete;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Index invalide\n");
        return -1;
    }
    
    return current->data;
}

// ============================================
// 15. SOMME DES ÉLÉMENTS (RÉCURSIF)
// ============================================

int somme_recursif(Node *tete) {
    if (tete == NULL) {
        return 0;
    }
    return tete->data + somme_recursif(tete->next);
}

// ============================================
// 16. TESTS COMPLETS
// ============================================

void tests_utilitaires() {
    Node *liste = NULL;
    
    printf("\n=== FONCTIONS UTILITAIRES ===\n");
    
    liste = inserer_queue(liste, 5);
    liste = inserer_queue(liste, 10);
    liste = inserer_queue(liste, 15);
    liste = inserer_queue(liste, 20);
    
    afficher_liste(liste);
    
    printf("Nombre d'éléments: %d\n", compter(liste));
    printf("Nombre d'éléments (récursif): %d\n", compter_recursif(liste));
    
    printf("Élément à l'index 2: %d\n", obtenir_element(liste, 2));
    
    printf("Somme des éléments: %d\n", somme_recursif(liste));
    
    liberer_liste(liste);
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    test_insertion_tete();
    test_insertion_queue();
    test_insertion_position();
    test_recherche();
    test_suppression();
    test_inverser();
    test_fusionner();
    tests_utilitaires();
    
    printf("\n=== TOUS LES TESTS TERMINÉS ===\n");
    
    return 0;
}
