/*
 * 07_arbres_binaires.c
 * Exemples complets d'arbres binaires de recherche
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// 1. DÉFINITION DE LA STRUCTURE
// ============================================

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// ============================================
// 2. CRÉER UN NOUVEAU NŒUD
// ============================================

TreeNode* creer_noeud(int valeur) {
    TreeNode *nouveau = (TreeNode*)malloc(sizeof(TreeNode));
    if (nouveau == NULL) {
        printf("Erreur d'allocation\n");
        return NULL;
    }
    nouveau->data = valeur;
    nouveau->left = NULL;
    nouveau->right = NULL;
    return nouveau;
}

// ============================================
// 3. INSERTION DANS UN ARBRE BINAIRE DE RECHERCHE
// ============================================

TreeNode* inserer(TreeNode *racine, int valeur) {
    // Cas de base: arbre vide
    if (racine == NULL) {
        return creer_noeud(valeur);
    }
    
    // Insertion récursive
    if (valeur < racine->data) {
        racine->left = inserer(racine->left, valeur);
    } else if (valeur > racine->data) {
        racine->right = inserer(racine->right, valeur);
    }
    // Si valeur == racine->data, on ne fait rien (pas de doublons)
    
    return racine;
}

// ============================================
// 4. RECHERCHE DANS UN ARBRE BINAIRE DE RECHERCHE
// ============================================

// Version récursive
TreeNode* rechercher(TreeNode *racine, int valeur) {
    // Cas de base
    if (racine == NULL || racine->data == valeur) {
        return racine;
    }
    
    // Recherche récursive
    if (valeur < racine->data) {
        return rechercher(racine->left, valeur);
    } else {
        return rechercher(racine->right, valeur);
    }
}

// Version itérative
TreeNode* rechercher_iteratif(TreeNode *racine, int valeur) {
    TreeNode *current = racine;
    
    while (current != NULL && current->data != valeur) {
        if (valeur < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return current;
}

void test_recherche() {
    printf("=== TESTS RECHERCHE ===\n");
    
    TreeNode *arbre = NULL;
    int valeurs[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int i = 0; i < 7; i++) {
        arbre = inserer(arbre, valeurs[i]);
    }
    
    TreeNode *trouve = rechercher(arbre, 40);
    if (trouve != NULL) {
        printf("40 trouvé dans l'arbre\n");
    } else {
        printf("40 non trouvé\n");
    }
    
    trouve = rechercher_iteratif(arbre, 25);
    if (trouve != NULL) {
        printf("25 trouvé dans l'arbre\n");
    } else {
        printf("25 non trouvé\n");
    }
    
    // Libération (voir plus bas)
}

// ============================================
// 5. PARCOURS PRÉFIXE (Préordre)
// ============================================
// Racine -> Gauche -> Droite

void parcours_prefixe(TreeNode *racine) {
    if (racine == NULL) {
        return;
    }
    
    printf("%d ", racine->data);
    parcours_prefixe(racine->left);
    parcours_prefixe(racine->right);
}

// ============================================
// 6. PARCOURS INFIXE (Inordre)
// ============================================
// Gauche -> Racine -> Droite
// Donne les éléments triés pour un ABR

void parcours_infixe(TreeNode *racine) {
    if (racine == NULL) {
        return;
    }
    
    parcours_infixe(racine->left);
    printf("%d ", racine->data);
    parcours_infixe(racine->right);
}

// ============================================
// 7. PARCOURS POSTFIXE (Postordre)
// ============================================
// Gauche -> Droite -> Racine

void parcours_postfixe(TreeNode *racine) {
    if (racine == NULL) {
        return;
    }
    
    parcours_postfixe(racine->left);
    parcours_postfixe(racine->right);
    printf("%d ", racine->data);
}

void test_parcours() {
    printf("\n=== TESTS PARCOURS ===\n");
    
    TreeNode *arbre = NULL;
    int valeurs[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int i = 0; i < 7; i++) {
        arbre = inserer(arbre, valeurs[i]);
    }
    
    /*
    Structure de l'arbre:
            50
           /  \
          30   70
         / \   / \
        20 40 60 80
    */
    
    printf("Parcours préfixe: ");
    parcours_prefixe(arbre);
    printf("\n");
    
    printf("Parcours infixe (trié): ");
    parcours_infixe(arbre);
    printf("\n");
    
    printf("Parcours postfixe: ");
    parcours_postfixe(arbre);
    printf("\n");
}

// ============================================
// 8. CALCULER LA HAUTEUR
// ============================================

int hauteur(TreeNode *racine) {
    if (racine == NULL) {
        return 0;
    }
    
    int hauteur_gauche = hauteur(racine->left);
    int hauteur_droite = hauteur(racine->right);
    
    // Hauteur = 1 + max(hauteur_gauche, hauteur_droite)
    return 1 + (hauteur_gauche > hauteur_droite ? hauteur_gauche : hauteur_droite);
}

// ============================================
// 9. COMPTER LES NŒUDS
// ============================================

int compter_noeuds(TreeNode *racine) {
    if (racine == NULL) {
        return 0;
    }
    
    return 1 + compter_noeuds(racine->left) + compter_noeuds(racine->right);
}

// ============================================
// 10. COMPTER LES FEUILLES
// ============================================

int compter_feuilles(TreeNode *racine) {
    if (racine == NULL) {
        return 0;
    }
    
    // Un nœud est une feuille s'il n'a pas d'enfants
    if (racine->left == NULL && racine->right == NULL) {
        return 1;
    }
    
    return compter_feuilles(racine->left) + compter_feuilles(racine->right);
}

// ============================================
// 11. TROUVER MIN ET MAX
// ============================================

TreeNode* trouver_min(TreeNode *racine) {
    if (racine == NULL) {
        return NULL;
    }
    
    // Dans un ABR, le min est tout à gauche
    TreeNode *current = racine;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

TreeNode* trouver_max(TreeNode *racine) {
    if (racine == NULL) {
        return NULL;
    }
    
    // Dans un ABR, le max est tout à droite
    TreeNode *current = racine;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

void test_statistiques() {
    printf("\n=== TESTS STATISTIQUES ===\n");
    
    TreeNode *arbre = NULL;
    int valeurs[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    
    for (int i = 0; i < 9; i++) {
        arbre = inserer(arbre, valeurs[i]);
    }
    
    printf("Nombre de nœuds: %d\n", compter_noeuds(arbre));
    printf("Hauteur: %d\n", hauteur(arbre));
    printf("Nombre de feuilles: %d\n", compter_feuilles(arbre));
    
    TreeNode *min = trouver_min(arbre);
    TreeNode *max = trouver_max(arbre);
    printf("Min: %d\n", min->data);
    printf("Max: %d\n", max->data);
}

// ============================================
// 12. SUPPRIMER UN NŒUD
// ============================================

TreeNode* supprimer(TreeNode *racine, int valeur) {
    if (racine == NULL) {
        return NULL;
    }
    
    // Trouver le nœud à supprimer
    if (valeur < racine->data) {
        racine->left = supprimer(racine->left, valeur);
    } else if (valeur > racine->data) {
        racine->right = supprimer(racine->right, valeur);
    } else {
        // Nœud trouvé
        
        // Cas 1: Nœud sans enfant (feuille)
        if (racine->left == NULL && racine->right == NULL) {
            free(racine);
            return NULL;
        }
        
        // Cas 2: Nœud avec un seul enfant
        if (racine->left == NULL) {
            TreeNode *temp = racine->right;
            free(racine);
            return temp;
        }
        if (racine->right == NULL) {
            TreeNode *temp = racine->left;
            free(racine);
            return temp;
        }
        
        // Cas 3: Nœud avec deux enfants
        // Trouver le successeur (min du sous-arbre droit)
        TreeNode *successeur = trouver_min(racine->right);
        
        // Copier la valeur du successeur
        racine->data = successeur->data;
        
        // Supprimer le successeur
        racine->right = supprimer(racine->right, successeur->data);
    }
    
    return racine;
}

void test_suppression() {
    printf("\n=== TESTS SUPPRESSION ===\n");
    
    TreeNode *arbre = NULL;
    int valeurs[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int i = 0; i < 7; i++) {
        arbre = inserer(arbre, valeurs[i]);
    }
    
    printf("Avant suppression: ");
    parcours_infixe(arbre);
    printf("\n");
    
    arbre = supprimer(arbre, 20);  // Supprimer une feuille
    printf("Après suppression de 20: ");
    parcours_infixe(arbre);
    printf("\n");
    
    arbre = supprimer(arbre, 30);  // Supprimer un nœud avec deux enfants
    printf("Après suppression de 30: ");
    parcours_infixe(arbre);
    printf("\n");
}

// ============================================
// 13. VÉRIFIER SI C'EST UN ABR
// ============================================

int est_abr_helper(TreeNode *racine, int min, int max) {
    if (racine == NULL) {
        return 1;
    }
    
    if (racine->data <= min || racine->data >= max) {
        return 0;
    }
    
    return est_abr_helper(racine->left, min, racine->data) &&
           est_abr_helper(racine->right, racine->data, max);
}

int est_abr(TreeNode *racine) {
    return est_abr_helper(racine, -2147483648, 2147483647);
}

// ============================================
// 14. SOMME DE TOUS LES NŒUDS
// ============================================

int somme(TreeNode *racine) {
    if (racine == NULL) {
        return 0;
    }
    
    return racine->data + somme(racine->left) + somme(racine->right);
}

// ============================================
// 15. LIBÉRER L'ARBRE (IMPORTANT!)
// ============================================

void liberer_arbre(TreeNode *racine) {
    if (racine == NULL) {
        return;
    }
    
    // Parcours postfixe pour libérer (enfants avant parent)
    liberer_arbre(racine->left);
    liberer_arbre(racine->right);
    free(racine);
}

// ============================================
// 16. AFFICHAGE VISUEL (BASIQUE)
// ============================================

void afficher_arbre_helper(TreeNode *racine, int niveau) {
    if (racine == NULL) {
        return;
    }
    
    afficher_arbre_helper(racine->right, niveau + 1);
    
    for (int i = 0; i < niveau; i++) {
        printf("    ");
    }
    printf("%d\n", racine->data);
    
    afficher_arbre_helper(racine->left, niveau + 1);
}

void afficher_arbre(TreeNode *racine) {
    printf("\nArbre (rotation 90° horaire):\n");
    afficher_arbre_helper(racine, 0);
}

// ============================================
// 17. PARCOURS EN LARGEUR (BONUS)
// ============================================

void parcours_largeur(TreeNode *racine) {
    if (racine == NULL) {
        return;
    }
    
    // File temporaire (simple implémentation)
    TreeNode *file[100];
    int debut = 0, fin = 0;
    
    file[fin++] = racine;
    
    while (debut < fin) {
        TreeNode *current = file[debut++];
        printf("%d ", current->data);
        
        if (current->left != NULL) {
            file[fin++] = current->left;
        }
        if (current->right != NULL) {
            file[fin++] = current->right;
        }
    }
    printf("\n");
}

// ============================================
// 18. MIROIR D'UN ARBRE
// ============================================

void miroir(TreeNode *racine) {
    if (racine == NULL) {
        return;
    }
    
    // Échanger gauche et droite
    TreeNode *temp = racine->left;
    racine->left = racine->right;
    racine->right = temp;
    
    // Récursion
    miroir(racine->left);
    miroir(racine->right);
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    printf("=== CRÉATION ET INSERTION ===\n");
    TreeNode *arbre = NULL;
    int valeurs[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65};
    
    for (int i = 0; i < 11; i++) {
        arbre = inserer(arbre, valeurs[i]);
        printf("Inséré: %d\n", valeurs[i]);
    }
    
    afficher_arbre(arbre);
    
    test_recherche();
    test_parcours();
    test_statistiques();
    test_suppression();
    
    printf("\n=== AUTRES OPÉRATIONS ===\n");
    arbre = NULL;
    for (int i = 0; i < 7; i++) {
        arbre = inserer(arbre, valeurs[i]);
    }
    
    printf("Somme de tous les nœuds: %d\n", somme(arbre));
    printf("Est un ABR? %s\n", est_abr(arbre) ? "Oui" : "Non");
    
    printf("\nParcours en largeur: ");
    parcours_largeur(arbre);
    
    printf("\nAvant miroir: ");
    parcours_infixe(arbre);
    printf("\n");
    
    miroir(arbre);
    
    printf("Après miroir: ");
    parcours_infixe(arbre);
    printf("\n");
    
    afficher_arbre(arbre);
    
    liberer_arbre(arbre);
    
    printf("\n=== TOUS LES TESTS TERMINÉS ===\n");
    
    return 0;
}
