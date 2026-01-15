/*
 * 04_structures_chaines.c
 * Exemples de structures et chaînes de caractères
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. DÉFINITION DE STRUCTURES
// ============================================

// Structure simple
struct Point {
    int x;
    int y;
};

// Typedef pour simplifier l'utilisation
typedef struct {
    float x;
    float y;
} Point2D;

typedef struct {
    char nom[50];
    char prenom[50];
    int age;
    float note;
} Etudiant;

typedef struct {
    Point2D coin_haut_gauche;
    float largeur;
    float hauteur;
} Rectangle;

// ============================================
// 2. UTILISATION DES STRUCTURES
// ============================================

void exemple_structures_base() {
    // Déclaration et initialisation
    struct Point p1 = {10, 20};
    Point2D p2 = {5.5, 7.8};
    
    // Accès aux membres
    printf("Point p1: (%d, %d)\n", p1.x, p1.y);
    printf("Point p2: (%.2f, %.2f)\n", p2.x, p2.y);
    
    // Modification
    p1.x = 100;
    p1.y = 200;
    printf("Point p1 modifié: (%d, %d)\n", p1.x, p1.y);
    
    // Structure avec structure imbriquée
    Rectangle rect = {{0, 0}, 100, 50};
    printf("Rectangle: coin=(%.2f,%.2f), L=%.2f, H=%.2f\n",
           rect.coin_haut_gauche.x, rect.coin_haut_gauche.y,
           rect.largeur, rect.hauteur);
}

// ============================================
// 3. POINTEURS VERS STRUCTURES
// ============================================

void afficher_etudiant(Etudiant *e) {
    // Opérateur -> pour accéder aux membres via pointeur
    printf("Nom: %s %s\n", e->prenom, e->nom);
    printf("Âge: %d ans\n", e->age);
    printf("Note: %.2f/20\n", e->note);
}

void modifier_etudiant(Etudiant *e, float nouvelle_note) {
    e->note = nouvelle_note;
}

void test_pointeurs_structures() {
    Etudiant etud = {"Dupont", "Jean", 20, 15.5};
    
    printf("Avant modification:\n");
    afficher_etudiant(&etud);
    
    modifier_etudiant(&etud, 18.0);
    
    printf("\nAprès modification:\n");
    afficher_etudiant(&etud);
}

// ============================================
// 4. TABLEAUX DE STRUCTURES
// ============================================

void exemple_tableau_structures() {
    Etudiant classe[3] = {
        {"Dupont", "Jean", 20, 15.5},
        {"Martin", "Marie", 19, 17.0},
        {"Durand", "Paul", 21, 13.5}
    };
    
    printf("Liste des étudiants:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s %s - Note: %.2f\n",
               i+1, classe[i].prenom, classe[i].nom, classe[i].note);
    }
    
    // Calculer moyenne
    float somme = 0;
    for (int i = 0; i < 3; i++) {
        somme += classe[i].note;
    }
    printf("Moyenne de classe: %.2f\n", somme / 3);
}

// ============================================
// 5. STRUCTURES DYNAMIQUES
// ============================================

Etudiant* creer_etudiant(const char *nom, const char *prenom, int age, float note) {
    Etudiant *e = (Etudiant*)malloc(sizeof(Etudiant));
    if (e == NULL) return NULL;
    
    strcpy(e->nom, nom);
    strcpy(e->prenom, prenom);
    e->age = age;
    e->note = note;
    
    return e;
}

void test_structure_dynamique() {
    Etudiant *e = creer_etudiant("Durand", "Sophie", 22, 16.5);
    if (e != NULL) {
        afficher_etudiant(e);
        free(e);
    }
}

// ============================================
// 6. CHAÎNES DE CARACTÈRES - BASES
// ============================================

void exemple_chaines_base() {
    // Différentes façons de déclarer
    char str1[] = "Bonjour";  // Tableau de taille automatique
    char str2[20] = "Hello";  // Tableau de taille fixe
    char *str3 = "World";     // Pointeur vers chaîne constante
    
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);
    
    // Caractère de fin '\0'
    printf("Contenu de str1 caractère par caractère:\n");
    for (int i = 0; str1[i] != '\0'; i++) {
        printf("str1[%d] = '%c'\n", i, str1[i]);
    }
}

// ============================================
// 7. FONCTIONS SUR CHAÎNES (SANS string.h)
// ============================================

// Calculer la longueur (strlen)
int ma_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Copier une chaîne (strcpy)
void ma_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Ne pas oublier le '\0'
}

// Comparer deux chaînes (strcmp)
int ma_strcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

// Concaténer deux chaînes (strcat)
void ma_strcat(char *dest, const char *src) {
    int i = 0;
    // Trouver la fin de dest
    while (dest[i] != '\0') {
        i++;
    }
    // Copier src à la fin de dest
    int j = 0;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

// Chercher un caractère (strchr)
char* ma_strchr(const char *str, char c) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            return (char*)&str[i];
        }
        i++;
    }
    return NULL;
}

void test_fonctions_chaines() {
    char str1[50] = "Hello";
    char str2[] = "World";
    
    printf("Longueur de '%s': %d\n", str1, ma_strlen(str1));
    
    char copie[50];
    ma_strcpy(copie, str1);
    printf("Copie: %s\n", copie);
    
    int cmp = ma_strcmp(str1, str2);
    printf("Comparaison '%s' et '%s': %d\n", str1, str2, cmp);
    
    ma_strcat(str1, " ");
    ma_strcat(str1, str2);
    printf("Concaténation: %s\n", str1);
    
    char *pos = ma_strchr(str1, 'W');
    if (pos != NULL) {
        printf("'W' trouvé à la position: %ld\n", pos - str1);
    }
}

// ============================================
// 8. CHAÎNES DYNAMIQUES
// ============================================

char* creer_chaine(const char *texte) {
    int len = ma_strlen(texte);
    char *nouvelle = (char*)malloc((len + 1) * sizeof(char));
    if (nouvelle == NULL) return NULL;
    
    ma_strcpy(nouvelle, texte);
    return nouvelle;
}

char* concatener_chaines(const char *s1, const char *s2) {
    int len1 = ma_strlen(s1);
    int len2 = ma_strlen(s2);
    
    char *resultat = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    if (resultat == NULL) return NULL;
    
    ma_strcpy(resultat, s1);
    ma_strcat(resultat, s2);
    
    return resultat;
}

void test_chaines_dynamiques() {
    char *str1 = creer_chaine("Bonjour");
    char *str2 = creer_chaine(" le monde");
    
    if (str1 != NULL && str2 != NULL) {
        char *concat = concatener_chaines(str1, str2);
        if (concat != NULL) {
            printf("Chaîne concaténée: %s\n", concat);
            free(concat);
        }
        free(str1);
        free(str2);
    }
}

// ============================================
// 9. LECTURE ET ÉCRITURE AVEC FPRINTF/FSCANF
// ============================================

void exemple_fichiers() {
    // Écriture
    FILE *fichier = fopen("etudiants.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    
    Etudiant etuds[] = {
        {"Dupont", "Jean", 20, 15.5},
        {"Martin", "Marie", 19, 17.0}
    };
    
    for (int i = 0; i < 2; i++) {
        fprintf(fichier, "%s %s %d %.2f\n",
                etuds[i].nom, etuds[i].prenom, etuds[i].age, etuds[i].note);
    }
    
    fclose(fichier);
    printf("Données écrites dans etudiants.txt\n");
    
    // Lecture
    fichier = fopen("etudiants.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    
    printf("\nLecture du fichier:\n");
    Etudiant e;
    while (fscanf(fichier, "%s %s %d %f", e.nom, e.prenom, &e.age, &e.note) == 4) {
        printf("%s %s, %d ans, note: %.2f\n", e.prenom, e.nom, e.age, e.note);
    }
    
    fclose(fichier);
}

// ============================================
// 10. STRUCTURES AVEC MEMBRES DYNAMIQUES
// ============================================

typedef struct {
    char *nom;
    char *prenom;
    int age;
    float note;
} EtudiantDyn;

EtudiantDyn* creer_etudiant_dyn(const char *nom, const char *prenom, int age, float note) {
    EtudiantDyn *e = (EtudiantDyn*)malloc(sizeof(EtudiantDyn));
    if (e == NULL) return NULL;
    
    e->nom = creer_chaine(nom);
    e->prenom = creer_chaine(prenom);
    if (e->nom == NULL || e->prenom == NULL) {
        free(e->nom);
        free(e->prenom);
        free(e);
        return NULL;
    }
    
    e->age = age;
    e->note = note;
    
    return e;
}

void liberer_etudiant_dyn(EtudiantDyn *e) {
    if (e != NULL) {
        free(e->nom);
        free(e->prenom);
        free(e);
    }
}

void test_structure_membres_dynamiques() {
    EtudiantDyn *e = creer_etudiant_dyn("Durand", "Sophie", 22, 16.5);
    if (e != NULL) {
        printf("Étudiant dynamique: %s %s\n", e->prenom, e->nom);
        liberer_etudiant_dyn(e);
    }
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    printf("=== STRUCTURES DE BASE ===\n");
    exemple_structures_base();
    
    printf("\n=== POINTEURS VERS STRUCTURES ===\n");
    test_pointeurs_structures();
    
    printf("\n=== TABLEAUX DE STRUCTURES ===\n");
    exemple_tableau_structures();
    
    printf("\n=== STRUCTURES DYNAMIQUES ===\n");
    test_structure_dynamique();
    
    printf("\n=== CHAÎNES - BASES ===\n");
    exemple_chaines_base();
    
    printf("\n=== FONCTIONS SUR CHAÎNES ===\n");
    test_fonctions_chaines();
    
    printf("\n=== CHAÎNES DYNAMIQUES ===\n");
    test_chaines_dynamiques();
    
    printf("\n=== FICHIERS ===\n");
    exemple_fichiers();
    
    printf("\n=== STRUCTURES AVEC MEMBRES DYNAMIQUES ===\n");
    test_structure_membres_dynamiques();
    
    return 0;
}
