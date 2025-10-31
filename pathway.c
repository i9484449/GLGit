#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enzyme.h"
#include "pathway.h"

#define MAX_NAME_LENGTH 30

struct pathway {
    char *nom;
    int taille;
    ptr_enzyme *tab;
};

ptr_pathway creer_pathway() {
    ptr_pathway voie = malloc(sizeof(struct pathway));
    if (!voie) {
        fprintf(stderr, "Erreur d'allocation mémoire pour pathway.\n");
        exit(EXIT_FAILURE);
    }
    voie->nom = NULL;
    voie->taille = 0;
    voie->tab = NULL;
    return voie;
}

void saisie_voie(ptr_pathway voie) {
    char buffer[MAX_NAME_LENGTH];

    printf("Nom de la voie métabolique?\n");
    fgets(buffer, MAX_NAME_LENGTH, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
    voie->nom = strdup(buffer);

    printf("Nombre d'enzymes?\n");
    scanf("%d", &voie->taille);
    getchar(); // Consume newline left by scanf

    voie->tab = malloc(sizeof(ptr_enzyme) * voie->taille);
    if (!voie->tab) {
        fprintf(stderr, "Erreur d'allocation mémoire pour enzymes.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < voie->taille; i++) {
        ptr_enzyme item = creerenzyme();
        voie->tab[i] = saisie_enzyme(item);
    }
}

void affichage_voie(const ptr_pathway voie) {
    printf("-------------\n");
    printf("Nom voie : %s, taille : %d\n", voie->nom, voie->taille);

    if (voie->taille == 0) {
        printf("Le tableau est vide, veuillez le remplir.\n");
    } else {
        for (int i = 0; i < voie->taille; i++) {
            affiche(voie->tab[i]);
        }
    }
    printf("-------------\n");
}

void ouvrir_voie(ptr_pathway voie, FILE *fichier) {
    char buffer[MAX_NAME_LENGTH];
    int poids;

    fscanf(fichier, "%s %d", buffer, &voie->taille);
    voie->nom = strdup(buffer);

    voie->tab = malloc(sizeof(ptr_enzyme) * voie->taille);
    if (!voie->tab) {
        fprintf(stderr, "Erreur d'allocation mémoire pour enzymes.\n");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < voie->taille; j++) {
        fscanf(fichier, "%s %d", buffer, &poids);
        voie->tab[j] = creer_enzyme(buffer, poids);
    }
}

void sauvegarder_voie(const ptr_pathway voie, FILE *out) {
    fprintf(out, "%s %d ", voie->nom, voie->taille);
    for (int i = 0; i < voie->taille; i++) {
        sauvegarde(voie->tab[i], out);
    }
}
