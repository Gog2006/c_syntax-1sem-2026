/*
 * 06_piles_files.c
 * Exemples de piles (LIFO) et files (FIFO)
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================
// PILE (STACK) - LIFO
// ============================================

typedef struct NodePile {
    int data;
    struct NodePile *next;
} NodePile;

typedef struct {
    NodePile *sommet;
    int taille;
} Pile;

// Créer une pile vide
Pile* creer_pile() {
    Pile *p = (Pile*)malloc(sizeof(Pile));
    if (p == NULL) return NULL;
    p->sommet = NULL;
    p->taille = 0;
    return p;
}

// Vérifier si la pile est vide
int pile_est_vide(Pile *p) {
    return p->sommet == NULL;
}

// Empiler (push)
void push(Pile *p, int valeur) {
    NodePile *nouveau = (NodePile*)malloc(sizeof(NodePile));
    if (nouveau == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    nouveau->data = valeur;
    nouveau->next = p->sommet;
    p->sommet = nouveau;
    p->taille++;
}

// Dépiler (pop)
int pop(Pile *p) {
    if (pile_est_vide(p)) {
        printf("Erreur: pile vide\n");
        return -1;
    }
    
    NodePile *temp = p->sommet;
    int valeur = temp->data;
    p->sommet = p->sommet->next;
    free(temp);
    p->taille--;
    
    return valeur;
}

// Voir le sommet sans dépiler (peek)
int peek(Pile *p) {
    if (pile_est_vide(p)) {
        printf("Erreur: pile vide\n");
        return -1;
    }
    return p->sommet->data;
}

// Afficher la pile
void afficher_pile(Pile *p) {
    if (pile_est_vide(p)) {
        printf("Pile vide\n");
        return;
    }
    
    printf("Pile (sommet -> bas): ");
    NodePile *current = p->sommet;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Libérer la pile
void liberer_pile(Pile *p) {
    while (!pile_est_vide(p)) {
        pop(p);
    }
    free(p);
}

// ============================================
// TESTS PILE
// ============================================

void test_pile_base() {
    printf("=== TESTS PILE DE BASE ===\n");
    
    Pile *p = creer_pile();
    
    printf("Pile vide? %s\n", pile_est_vide(p) ? "Oui" : "Non");
    
    push(p, 10);
    push(p, 20);
    push(p, 30);
    push(p, 40);
    
    afficher_pile(p);
    printf("Taille: %d\n", p->taille);
    
    printf("Sommet: %d\n", peek(p));
    
    printf("Pop: %d\n", pop(p));
    afficher_pile(p);
    
    printf("Pop: %d\n", pop(p));
    afficher_pile(p);
    
    liberer_pile(p);
}

// ============================================
// APPLICATION: PARENTHÈSES ÉQUILIBRÉES
// ============================================

int verifier_parentheses(const char *expression) {
    Pile *p = creer_pile();
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char c = expression[i];
        
        // Ouvrant: empiler
        if (c == '(' || c == '[' || c == '{') {
            push(p, c);
        }
        // Fermant: vérifier correspondance
        else if (c == ')' || c == ']' || c == '}') {
            if (pile_est_vide(p)) {
                liberer_pile(p);
                return 0;  // Pas équilibré
            }
            
            char ouvert = pop(p);
            if ((c == ')' && ouvert != '(') ||
                (c == ']' && ouvert != '[') ||
                (c == '}' && ouvert != '{')) {
                liberer_pile(p);
                return 0;  // Pas équilibré
            }
        }
    }
    
    int equilibre = pile_est_vide(p);
    liberer_pile(p);
    return equilibre;
}

void test_parentheses() {
    printf("\n=== VÉRIFICATION PARENTHÈSES ===\n");
    
    char *tests[] = {
        "()",
        "()[]{}",
        "{[()]}",
        "((()))",
        "({[}])",
        "(()",
        "())",
        "{[(])}"
    };
    
    for (int i = 0; i < 8; i++) {
        printf("%s : %s\n", tests[i],
               verifier_parentheses(tests[i]) ? "Équilibré" : "Non équilibré");
    }
}

// ============================================
// APPLICATION: NOTATION POLONAISE INVERSE (RPN)
// ============================================

int evaluer_rpn(const char *expression) {
    Pile *p = creer_pile();
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char c = expression[i];
        
        // Si c'est un chiffre
        if (c >= '0' && c <= '9') {
            push(p, c - '0');
        }
        // Si c'est un opérateur
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (p->taille < 2) {
                printf("Erreur: expression invalide\n");
                liberer_pile(p);
                return 0;
            }
            
            int b = pop(p);
            int a = pop(p);
            int resultat;
            
            switch (c) {
                case '+': resultat = a + b; break;
                case '-': resultat = a - b; break;
                case '*': resultat = a * b; break;
                case '/': resultat = a / b; break;
            }
            
            push(p, resultat);
        }
        // Ignorer les espaces
    }
    
    int resultat = pop(p);
    liberer_pile(p);
    return resultat;
}

void test_rpn() {
    printf("\n=== NOTATION POLONAISE INVERSE ===\n");
    
    // 3 4 + => 3 + 4 = 7
    printf("34+ = %d\n", evaluer_rpn("34+"));
    
    // 5 1 2 + 4 * + 3 - => 5 + ((1 + 2) * 4) - 3 = 14
    printf("512+4*+3- = %d\n", evaluer_rpn("512+4*+3-"));
    
    // 2 3 * 4 + => (2 * 3) + 4 = 10
    printf("23*4+ = %d\n", evaluer_rpn("23*4+"));
}

// ============================================
// FILE (QUEUE) - FIFO
// ============================================

typedef struct NodeFile {
    int data;
    struct NodeFile *next;
} NodeFile;

typedef struct {
    NodeFile *tete;   // Pour défiler (dequeue)
    NodeFile *queue;  // Pour enfiler (enqueue)
    int taille;
} File;

// Créer une file vide
File* creer_file() {
    File *f = (File*)malloc(sizeof(File));
    if (f == NULL) return NULL;
    f->tete = NULL;
    f->queue = NULL;
    f->taille = 0;
    return f;
}

// Vérifier si la file est vide
int file_est_vide(File *f) {
    return f->tete == NULL;
}

// Enfiler (enqueue)
void enqueue(File *f, int valeur) {
    NodeFile *nouveau = (NodeFile*)malloc(sizeof(NodeFile));
    if (nouveau == NULL) {
        printf("Erreur d'allocation\n");
        return;
    }
    
    nouveau->data = valeur;
    nouveau->next = NULL;
    
    if (file_est_vide(f)) {
        f->tete = nouveau;
        f->queue = nouveau;
    } else {
        f->queue->next = nouveau;
        f->queue = nouveau;
    }
    
    f->taille++;
}

// Défiler (dequeue)
int dequeue(File *f) {
    if (file_est_vide(f)) {
        printf("Erreur: file vide\n");
        return -1;
    }
    
    NodeFile *temp = f->tete;
    int valeur = temp->data;
    f->tete = f->tete->next;
    
    if (f->tete == NULL) {
        f->queue = NULL;  // La file est maintenant vide
    }
    
    free(temp);
    f->taille--;
    
    return valeur;
}

// Voir le premier élément
int front(File *f) {
    if (file_est_vide(f)) {
        printf("Erreur: file vide\n");
        return -1;
    }
    return f->tete->data;
}

// Afficher la file
void afficher_file(File *f) {
    if (file_est_vide(f)) {
        printf("File vide\n");
        return;
    }
    
    printf("File (tête -> queue): ");
    NodeFile *current = f->tete;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Libérer la file
void liberer_file(File *f) {
    while (!file_est_vide(f)) {
        dequeue(f);
    }
    free(f);
}

// ============================================
// TESTS FILE
// ============================================

void test_file_base() {
    printf("\n=== TESTS FILE DE BASE ===\n");
    
    File *f = creer_file();
    
    printf("File vide? %s\n", file_est_vide(f) ? "Oui" : "Non");
    
    enqueue(f, 10);
    enqueue(f, 20);
    enqueue(f, 30);
    enqueue(f, 40);
    
    afficher_file(f);
    printf("Taille: %d\n", f->taille);
    
    printf("Premier élément: %d\n", front(f));
    
    printf("Dequeue: %d\n", dequeue(f));
    afficher_file(f);
    
    printf("Dequeue: %d\n", dequeue(f));
    afficher_file(f);
    
    enqueue(f, 50);
    afficher_file(f);
    
    liberer_file(f);
}

// ============================================
// APPLICATION: SIMULATION FILE D'ATTENTE
// ============================================

typedef struct {
    int id;
    char nom[50];
} Client;

typedef struct NodeClient {
    Client data;
    struct NodeClient *next;
} NodeClient;

typedef struct {
    NodeClient *tete;
    NodeClient *queue;
    int taille;
} FileClients;

FileClients* creer_file_clients() {
    FileClients *f = (FileClients*)malloc(sizeof(FileClients));
    if (f == NULL) return NULL;
    f->tete = NULL;
    f->queue = NULL;
    f->taille = 0;
    return f;
}

void ajouter_client(FileClients *f, int id, const char *nom) {
    NodeClient *nouveau = (NodeClient*)malloc(sizeof(NodeClient));
    if (nouveau == NULL) return;
    
    nouveau->data.id = id;
    snprintf(nouveau->data.nom, 50, "%s", nom);
    nouveau->next = NULL;
    
    if (f->tete == NULL) {
        f->tete = nouveau;
        f->queue = nouveau;
    } else {
        f->queue->next = nouveau;
        f->queue = nouveau;
    }
    
    f->taille++;
    printf("Client %d (%s) ajouté à la file\n", id, nom);
}

void servir_client(FileClients *f) {
    if (f->tete == NULL) {
        printf("Aucun client en attente\n");
        return;
    }
    
    NodeClient *temp = f->tete;
    printf("Service du client %d (%s)\n", temp->data.id, temp->data.nom);
    
    f->tete = f->tete->next;
    if (f->tete == NULL) {
        f->queue = NULL;
    }
    
    free(temp);
    f->taille--;
}

void afficher_file_attente(FileClients *f) {
    if (f->tete == NULL) {
        printf("File d'attente vide\n");
        return;
    }
    
    printf("File d'attente (%d clients): ", f->taille);
    NodeClient *current = f->tete;
    while (current != NULL) {
        printf("%s ", current->data.nom);
        current = current->next;
    }
    printf("\n");
}

void test_simulation() {
    printf("\n=== SIMULATION FILE D'ATTENTE ===\n");
    
    FileClients *banque = creer_file_clients();
    
    ajouter_client(banque, 1, "Alice");
    ajouter_client(banque, 2, "Bob");
    ajouter_client(banque, 3, "Charlie");
    
    afficher_file_attente(banque);
    
    servir_client(banque);
    afficher_file_attente(banque);
    
    ajouter_client(banque, 4, "David");
    afficher_file_attente(banque);
    
    servir_client(banque);
    servir_client(banque);
    afficher_file_attente(banque);
    
    // Libérer
    while (banque->tete != NULL) {
        servir_client(banque);
    }
    free(banque);
}

// ============================================
// COMPARAISON PILE VS FILE
// ============================================

void comparaison_pile_file() {
    printf("\n=== COMPARAISON PILE VS FILE ===\n");
    
    Pile *pile = creer_pile();
    File *file = creer_file();
    
    // Ajouter les mêmes valeurs
    printf("Ajout de 1, 2, 3, 4, 5\n");
    for (int i = 1; i <= 5; i++) {
        push(pile, i);
        enqueue(file, i);
    }
    
    printf("\nRetrait de la pile (LIFO):\n");
    while (!pile_est_vide(pile)) {
        printf("%d ", pop(pile));
    }
    printf("\n");
    
    printf("\nRetrait de la file (FIFO):\n");
    while (!file_est_vide(file)) {
        printf("%d ", dequeue(file));
    }
    printf("\n");
    
    liberer_pile(pile);
    liberer_file(file);
}

// ============================================
// PROGRAMME PRINCIPAL
// ============================================

int main() {
    test_pile_base();
    test_parentheses();
    test_rpn();
    test_file_base();
    test_simulation();
    comparaison_pile_file();
    
    printf("\n=== TOUS LES TESTS TERMINÉS ===\n");
    
    return 0;
}
