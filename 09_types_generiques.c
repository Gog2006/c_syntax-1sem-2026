/*
 * 09_types_generiques.c
 * Exemples de types génériques avec void*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. COMPRENDRE void*
// ============================================

void exemple_void_pointer() {
    printf("=== VOID POINTER ===\n");
    
    int entier = 42;
    float flottant = 3.14f;
    char caractere = 'A';
    
    // void* peut pointer vers n'importe quel type
    void *ptr;
    
    ptr = &entier;
    printf("Entier: %d\n", *(int*)ptr);  // Cast nécessaire pour déréférencer
    
    ptr = &flottant;
    printf("Flottant: %.2f\n", *(float*)ptr);
    
    ptr = &caractere;
    printf("Caractère: %c\n", *(char*)ptr);
}

// ============================================
// 2. FONCTION SWAP GÉNÉRIQUE
// ============================================

void swap_generique(void *a, void *b, size_t taille) {
    // Allouer un buffer temporaire
    void *temp = malloc(taille);
    if (temp == NULL) return;
    
    // Copier a dans temp
    memcpy(temp, a, taille);
    
    // Copier b dans a
    memcpy(a, b, taille);
    
    // Copier temp dans b
    memcpy(b, temp, taille);
    
    free(temp);
}

void test_swap_generique() {
    printf("\n=== SWAP GÉNÉRIQUE ===\n");
    
    // Swap d'entiers
    int x = 10, y = 20;
    printf("Avant swap int: x=%d, y=%d\n", x, y);
    swap_generique(&x, &y, sizeof(int));
    printf("Après swap int: x=%d, y=%d\n", x, y);
    
    // Swap de flottants
    float a = 3.14f, b = 2.71f;
    printf("\nAvant swap float: a=%.2f, b=%.2f\n", a, b);
    swap_generique(&a, &b, sizeof(float));
    printf("Après swap float: a=%.2f, b=%.2f\n", a, b);
    
    // Swap de caractères
    char c1 = 'A', c2 = 'Z';
    printf("\nAvant swap char: c1=%c, c2=%c\n", c1, c2);
    swap_generique(&c1, &c2, sizeof(char));
    printf("Après swap char: c1=%c, c2=%c\n", c1, c2);
}

// ============================================
// 3. FONCTION D'AFFICHAGE GÉNÉRIQUE
// ============================================

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING
} TypeDonnee;

void afficher_generique(void *data, TypeDonnee type) {
    switch (type) {
        case TYPE_INT:
            printf("%d", *(int*)data);
            break;
        case TYPE_FLOAT:
            printf("%.2f", *(float*)data);
            break;
        case TYPE_CHAR:
            printf("%c", *(char*)data);
            break;
        case TYPE_STRING:
            printf("%s", (char*)data);
            break;
    }
}

void test_affichage_generique() {
    printf("\n=== AFFICHAGE GÉNÉRIQUE ===\n");
    
    int entier = 42;
    float flottant = 3.14f;
    char caractere = 'X';
    char *chaine = "Bonjour";
    
    printf("Entier: ");
    afficher_generique(&entier, TYPE_INT);
    printf("\n");
    
    printf("Flottant: ");
    afficher_generique(&flottant, TYPE_FLOAT);
    printf("\n");
    
    printf("Caractère: ");
    afficher_generique(&caractere, TYPE_CHAR);
    printf("\n");
    
    printf("Chaîne: ");
    afficher_generique(chaine, TYPE_STRING);
    printf("\n");
}

// ============================================
// 4. TABLEAU GÉNÉRIQUE
// ============================================

typedef struct {
    void *data;
    size_t element_size;
    size_t capacity;
    size_t count;
} TableauGenerique;

TableauGenerique* creer_tableau_generique(size_t element_size, size_t capacity) {
    TableauGenerique *tab = (TableauGenerique*)malloc(sizeof(TableauGenerique));
    if (tab == NULL) return NULL;
    
    tab->data = malloc(element_size * capacity);
    if (tab->data == NULL) {
        free(tab);
        return NULL;
    }
    
    tab->element_size = element_size;
    tab->capacity = capacity;
    tab->count = 0;
    
    return tab;
}

void ajouter_element(TableauGenerique *tab, void *element) {
    if (tab->count >= tab->capacity) {
        printf("Tableau plein\n");
        return;
    }
    
    // Calculer l'adresse où ajouter
    void *destination = (char*)tab->data + (tab->count * tab->element_size);
    
    // Copier l'élément
    memcpy(destination, element, tab->element_size);
    
    tab->count++;
}

void* obtenir_element(TableauGenerique *tab, size_t index) {
    if (index >= tab->count) {
        return NULL;
    }
    
    return (char*)tab->data + (index * tab->element_size);
}

void liberer_tableau_generique(TableauGenerique *tab) {
    free(tab->data);
    free(tab);
}

void test_tableau_generique() {
    printf("\n=== TABLEAU GÉNÉRIQUE ===\n");
    
    // Tableau d'entiers
    TableauGenerique *tab_int = creer_tableau_generique(sizeof(int), 10);
    
    for (int i = 0; i < 5; i++) {
        int val = i * 10;
        ajouter_element(tab_int, &val);
    }
    
    printf("Tableau d'entiers: ");
    for (size_t i = 0; i < tab_int->count; i++) {
        int *val = (int*)obtenir_element(tab_int, i);
        printf("%d ", *val);
    }
    printf("\n");
    
    liberer_tableau_generique(tab_int);
    
    // Tableau de flottants
    TableauGenerique *tab_float = creer_tableau_generique(sizeof(float), 10);
    
    for (int i = 0; i < 5; i++) {
        float val = i * 1.5f;
        ajouter_element(tab_float, &val);
    }
    
    printf("Tableau de flottants: ");
    for (size_t i = 0; i < tab_float->count; i++) {
        float *val = (float*)obtenir_element(tab_float, i);
        printf("%.1f ", *val);
    }
    printf("\n");
    
    liberer_tableau_generique(tab_float);
}

// ============================================
// 5. FONCTION DE COMPARAISON GÉNÉRIQUE
// ============================================

// Prototype de fonction de comparaison
typedef int (*CompareFunc)(const void*, const void*);

int comparer_int(const void *a, const void *b) {
    int val_a = *(int*)a;
    int val_b = *(int*)b;
    return val_a - val_b;
}

int comparer_float(const void *a, const void *b) {
    float val_a = *(float*)a;
    float val_b = *(float*)b;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

int comparer_string(const void *a, const void *b) {
    const char *str_a = *(const char**)a;
    const char *str_b = *(const char**)b;
    return strcmp(str_a, str_b);
}

// ============================================
// 6. TRI GÉNÉRIQUE (TRI À BULLES)
// ============================================

void tri_bulles_generique(void *base, size_t count, size_t size, CompareFunc compare) {
    char *arr = (char*)base;
    void *temp = malloc(size);
    if (temp == NULL) return;
    
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - i - 1; j++) {
            void *elem1 = arr + j * size;
            void *elem2 = arr + (j + 1) * size;
            
            if (compare(elem1, elem2) > 0) {
                // Échanger
                memcpy(temp, elem1, size);
                memcpy(elem1, elem2, size);
                memcpy(elem2, temp, size);
            }
        }
    }
    
    free(temp);
}

void test_tri_generique() {
    printf("\n=== TRI GÉNÉRIQUE ===\n");
    
    // Tri d'entiers
    int tab_int[] = {5, 2, 8, 1, 9, 3};
    int taille_int = 6;
    
    printf("Avant tri (int): ");
    for (int i = 0; i < taille_int; i++) {
        printf("%d ", tab_int[i]);
    }
    printf("\n");
    
    tri_bulles_generique(tab_int, taille_int, sizeof(int), comparer_int);
    
    printf("Après tri (int): ");
    for (int i = 0; i < taille_int; i++) {
        printf("%d ", tab_int[i]);
    }
    printf("\n");
    
    // Tri de flottants
    float tab_float[] = {3.5f, 1.2f, 4.8f, 2.1f, 3.0f};
    int taille_float = 5;
    
    printf("\nAvant tri (float): ");
    for (int i = 0; i < taille_float; i++) {
        printf("%.1f ", tab_float[i]);
    }
    printf("\n");
    
    tri_bulles_generique(tab_float, taille_float, sizeof(float), comparer_float);
    
    printf("Après tri (float): ");
    for (int i = 0; i < taille_float; i++) {
        printf("%.1f ", tab_float[i]);
    }
    printf("\n");
    
    // Tri de chaînes
    char *tab_string[] = {"Zoe", "Alice", "Marie", "Bob", "Charlie"};
    int taille_string = 5;
    
    printf("\nAvant tri (string): ");
    for (int i = 0; i < taille_string; i++) {
        printf("%s ", tab_string[i]);
    }
    printf("\n");
    
    tri_bulles_generique(tab_string, taille_string, sizeof(char*), comparer_string);
    
    printf("Après tri (string): ");
    for (int i = 0; i < taille_string; i++) {
        printf("%s ", tab_string[i]);
    }
    printf("\n");
}

// ============================================
// 7. RECHERCHE GÉNÉRIQUE
// ============================================

void* recherche_lineaire_generique(void *base, size_t count, size_t size, 
                                     void *key, CompareFunc compare) {
    char *arr = (char*)base;
    
    for (size_t i = 0; i < count; i++) {
        void *elem = arr + i * size;
        if (compare(elem, key) == 0) {
            return elem;
        }
    }
    
    return NULL;
}

void test_recherche_generique() {
    printf("\n=== RECHERCHE GÉNÉRIQUE ===\n");
    
    int tab[] = {10, 20, 30, 40, 50};
    int taille = 5;
    
    int cle = 30;
    int *resultat = (int*)recherche_lineaire_generique(tab, taille, sizeof(int), 
                                                        &cle, comparer_int);
    
    if (resultat != NULL) {
        printf("Trouvé: %d\n", *resultat);
    } else {
        printf("Non trouvé\n");
    }
    
    cle = 25;
    resultat = (int*)recherche_lineaire_generique(tab, taille, sizeof(int), 
                                                   &cle, comparer_int);
    
    if (resultat != NULL) {
        printf("Trouvé: %d\n", *resultat);
    } else {
        printf("25 non trouvé\n");
    }
}

// ============================================
// 8. PILE GÉNÉRIQUE
// ============================================

typedef struct {
    void *data;
    size_t element_size;
    size_t capacity;
    size_t top;
} PileGenerique;

PileGenerique* creer_pile_generique(size_t element_size, size_t capacity) {
    PileGenerique *pile = (PileGenerique*)malloc(sizeof(PileGenerique));
    if (pile == NULL) return NULL;
    
    pile->data = malloc(element_size * capacity);
    if (pile->data == NULL) {
        free(pile);
        return NULL;
    }
    
    pile->element_size = element_size;
    pile->capacity = capacity;
    pile->top = 0;
    
    return pile;
}

int push_generique(PileGenerique *pile, void *element) {
    if (pile->top >= pile->capacity) {
        return 0;  // Pile pleine
    }
    
    void *destination = (char*)pile->data + (pile->top * pile->element_size);
    memcpy(destination, element, pile->element_size);
    pile->top++;
    
    return 1;
}

int pop_generique(PileGenerique *pile, void *element) {
    if (pile->top == 0) {
        return 0;  // Pile vide
    }
    
    pile->top--;
    void *source = (char*)pile->data + (pile->top * pile->element_size);
    memcpy(element, source, pile->element_size);
    
    return 1;
}

void liberer_pile_generique(PileGenerique *pile) {
    free(pile->data);
    free(pile);
}

void test_pile_generique() {
    printf("\n=== PILE GÉNÉRIQUE ===\n");
    
    PileGenerique *pile = creer_pile_generique(sizeof(int), 10);
    
    printf("Push: ");
    for (int i = 1; i <= 5; i++) {
        push_generique(pile, &i);
        printf("%d ", i);
    }
    printf("\n");
    
    printf("Pop: ");
    int val;
    while (pop_generique(pile, &val)) {
        printf("%d ", val);
    }
    printf("\n");
    
    liberer_pile_generique(pile);
}

// ============================================
// 9. LISTE CHAÎNÉE GÉNÉRIQUE
// ============================================

typedef struct NodeGen {
    void *data;
    struct NodeGen *next;
} NodeGen;

NodeGen* creer_noeud_generique(void *data, size_t size) {
    NodeGen *node = (NodeGen*)malloc(sizeof(NodeGen));
    if (node == NULL) return NULL;
    
    node->data = malloc(size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    
    memcpy(node->data, data, size);
    node->next = NULL;
    
    return node;
}

NodeGen* inserer_tete_generique(NodeGen *head, void *data, size_t size) {
    NodeGen *nouveau = creer_noeud_generique(data, size);
    if (nouveau == NULL) return head;
    
    nouveau->next = head;
    return nouveau;
}

void liberer_liste_generique(NodeGen *head) {
    while (head != NULL) {
        NodeGen *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    exemple_void_pointer();
    test_swap_generique();
    test_affichage_generique();
    test_tableau_generique();
    test_tri_generique();
    test_recherche_generique();
    test_pile_generique();
    
    printf("\n=== TOUS LES TESTS TERMINÉS ===\n");
    
    return 0;
}
