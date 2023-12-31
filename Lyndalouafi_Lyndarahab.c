#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
/* LYNDA LOUAFI & LYNDA RAHAB */ 
#define TAILLE_MIN 2
#define TAILLE_MAX 10
#define VALEUR_MAX 9

int TAILLE_BUFFER;

sem_t plein, vide, mutex;

int LignesMatriceA, ColonnesMatriceB, LignesA_ColonnesB;

int MatA[TAILLE_MAX][TAILLE_MAX];
int MatB[TAILLE_MAX][TAILLE_MAX];
int MatResult[TAILLE_MAX][TAILLE_MAX];

int ip = 0, ic = 0;
int* tampon;

void remplirMatrices() {
    srand(time(NULL));

    LignesMatriceA = rand() % 9;
    ColonnesMatriceB = rand() % 9;
    LignesA_ColonnesB = rand() % 9;

    TAILLE_BUFFER = ColonnesMatriceB;

    for (int i = 0; i < LignesMatriceA; ++i) {
        for (int j = 0; j < LignesA_ColonnesB; ++j) {
            MatA[i][j] = rand() % (VALEUR_MAX + 1);
        }
    }

    for (int i = 0; i < LignesA_ColonnesB; ++i) {
        for (int j = 0; j < ColonnesMatriceB; ++j) {
            MatB[i][j] = rand() % (VALEUR_MAX + 1);
        }
    }
}

void *producteur(void *arg) {
    int* args = (int *)arg;

    int ligne = args[0];
    int colonne = args[1];
    int donnee = 0;

    for (int i = 0; i < LignesA_ColonnesB; i++) {
        donnee += MatA[ligne][i] * MatB[i][colonne];
    }

    sem_wait(&vide);
    sem_wait(&mutex);

    tampon[ip] = donnee;
    ip = (ip + 1) % TAILLE_BUFFER;

    sem_post(&plein);
    sem_post(&mutex);
}

void *consommateur(void *arg) {
    sem_wait(&plein);
    sem_wait(&mutex);

    int donnee = tampon[ic];
    MatResult[ic / ColonnesMatriceB][ic % ColonnesMatriceB] = donnee;
    ic = (ic + 1) % TAILLE_BUFFER;

    sem_post(&vide);
    sem_post(&mutex);
}

void afficherMatriceResultat() {
    printf("Le résultat est :\n\n");
    for (int i = 0; i < LignesMatriceA; i++) {
        for (int j = 0; j < ColonnesMatriceB; j++) {
            printf("%d\t", MatResult[i][j]);
        }
        printf("\n");
    }
}

int main() {
    remplirMatrices();

    int tailleResultat = LignesMatriceA * ColonnesMatriceB;
    tampon = malloc(TAILLE_BUFFER * sizeof(int));

    sem_init(&mutex, 0, 1);
    sem_init(&plein, 0, 0);
    sem_init(&vide, 0, TAILLE_BUFFER);

    pthread_t producteurs[tailleResultat];
    pthread_t consommateurs[tailleResultat];

    int lignesMatriceA = 0;
    int colonnesMatriceB = 0;

    int vecteur[tailleResultat][2];

    for (int i = 0; i < tailleResultat; i++) {
        vecteur[i][0] = lignesMatriceA;
        vecteur[i][1] = colonnesMatriceB;

        colonnesMatriceB++;

        if (colonnesMatriceB == ColonnesMatriceB) {
            colonnesMatriceB = 0;
            lignesMatriceA++;
        }
    }

    for (int i = 0; i < tailleResultat; i++) {
        pthread_create(&producteurs[i], NULL, &producteur, (void *)vecteur[i]);
    }

    for (int i = 0; i < tailleResultat; i++) {
        pthread_create(&consommateurs[i], NULL, &consommateur, NULL);
    }

    for (int i = 0; i < tailleResultat; i++) {
        pthread_join(producteurs[i], NULL);
    }

    for (int i = 0; i < tailleResultat; i++) {
        pthread_join(consommateurs[i], NULL);
    }

    afficherMatriceResultat();

    free(tampon);

    return 0;
}
