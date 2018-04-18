#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>

void afficher_pair() {
    int i;
    for (i = 2; i <= 1000; i = i + 2)
        printf("Processus pair : %d\n", i);
}

void afficher_impair() {
    int i;
    for (i = 1; i <= 999; i = i + 2)
        printf("Processus impair : %d\n", i);
}

void exo1A() {
    pthread_t thread_pair;
    pthread_t thread_impair;

    pthread_create(&thread_pair, NULL, (void *) afficher_pair, NULL);
    pthread_create(&thread_impair, NULL, (void *) afficher_impair, NULL);

    pthread_join(thread_pair, NULL);
    pthread_join(thread_impair, NULL);

    printf("Fin du processus mère\n");
}

/* Réutilisation des fonctions faites dans le TP1 */
char *creeSegment(int size, char *filename, int key) {
    int ret;
    char *partage = NULL;

    key = shm_open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (key == -1) {
        perror("Erreur de la fonction shm_open()");
        exit(1);
    }

    //	Trunc de la memoire partagé a la taille
    ret = ftruncate(key, size);
    if (ret == -1) {
        perror("Erreur dans la fonction ftruncate()");
        exit(1);
    }

    partage = (char *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, key, 0);
    if (partage == MAP_FAILED) {
        perror("Erreur de la fonction mmap()");
        exit(1);
    }

    printf("Clef memoire = %d\n", key);

    return partage;
}

void fermerSegment(int size, char *filename, int fd, char *partage) {
    int res = munmap(partage, size);
    if (res == -1) {
        perror("Erreur avec la fonction munmap()");
        exit(1);
    }

    close(fd);

    res = shm_unlink(filename);
    if (res == -1) {
        perror("Erreur avec la fonction shm_unlink()");
        exit(1);
    }
}

#define MAX_IT 1000

void fn_pair(char *zone) {
    int nb = 0;
    while (atoi(zone) != MAX_IT) {
        if (atoi(zone) != nb) {
            nb = atoi(zone);
            if (nb % 2 == 0)
                printf("Processus pair : %d\n", nb);
        }
    }

    printf("Processus pair fin\n");
}

void fn_impair(char *zone) {
    int nb = 0;
    while (atoi(zone) != MAX_IT) {
        if (atoi(zone) != nb) {
            nb = atoi(zone);
            if (nb % 2 == 1)
                printf("Processus impair : %s\n", zone);
        }
    }

    printf("Processus impair fin\n");
}

void exo1B() {
    int fd;
    char *zone = creeSegment(2048, "partage.mem", fd);

    pthread_t thread_pair;
    pthread_t thread_impair;
    pthread_create(&thread_pair, NULL, (void *) fn_pair, zone);
    pthread_create(&thread_impair, NULL, (void *) fn_impair, zone);

    for (int i = 1; i <= MAX_IT; ++i) {
        sprintf(zone, "%d", i);
        usleep(100);
    }

    pthread_join(thread_impair, NULL);
    pthread_join(thread_pair, NULL);

    fermerSegment(2048, "partage.mem", fd, zone);

    printf("Fin du processus mère\n");
}

sem_t sem_pair;
sem_t sem_impair;

void fnc_pair(char *zone) {
    int it = 0;
    int nb = 0;

    while (nb != MAX_IT) {
        int val = atoi(zone);
        if (val != nb) {
            nb = val;

            if (it == 10) {
                it = 0;
                printf("\n");
                sem_post(&sem_impair);
                sem_wait(&sem_pair);
            }

            if (nb % 2 == 0) {
                printf("Thread pair : %d\n", nb);
                it++;
            }
        }
    }

    printf("Fin du processus pair\n");
    sem_post(&sem_impair);
    pthread_exit(NULL);
}

void fnc_impair(char *zone) {
    int it = 0;
    int nb = 0;

    sem_wait(&sem_impair);
    while (nb != MAX_IT) {
        int val = atoi(zone);
        if (val != nb) {
            nb = val;

            if (it == 10) {
                it = 0;
                printf("\n");
                sem_post(&sem_pair);
                sem_wait(&sem_impair);
            }

            if (nb % 2 != 0) {
                printf("thread impair : %d\n", val);
                it++;
            }
        }

    }

    printf("Fin du processus impair\n");
    sem_post(&sem_pair);
    pthread_exit(NULL);
}

void exo2() {
    sem_init(&sem_pair, 0, 0);
    sem_init(&sem_impair, 0, 0);

    int fd;
    char *zone = creeSegment(2048, "partage.mem", fd);

    pthread_t thread_pair;
    pthread_t thread_impair;

    pthread_create(&thread_pair, NULL, (void *) fnc_pair, zone);
    pthread_create(&thread_impair, NULL, (void *) fnc_impair, zone);

    for (int i = 1; i <= MAX_IT; ++i) {
        sprintf(zone, "%d", i);
        usleep(100);
    }

    pthread_join(thread_impair, NULL);
    pthread_join(thread_pair, NULL);

    fermerSegment(2048, "partage.mem", fd, zone);

    printf("Fin du processus mère\n");
}

#define NO_PLACES 2
#define NO_CARS 5

sem_t semaPlace;

void enterParking(int carId) {
    printf("Voiture n°%d entre dans le parking\n", carId);
}

void leaveParking(int carId) {
    printf("Voiture n°%d sort du parking\n", carId);
    sem_post(&semaPlace);
    pthread_exit(NULL);
}

void carLife(int carId) {
    printf("Voiture n°%d souhaite rentrer dans le parking\n", carId);

    sem_wait(&semaPlace);
    enterParking(carId);

    sleep((unsigned int) (random() % 5));

    leaveParking(carId);
}

void exo3A() {
    pthread_t thread_cars[NO_CARS];

    srandom((unsigned int) time(NULL)); // random initialisation

    sem_init(&semaPlace, 0, NO_PLACES);

    for (int i = 0; i < NO_CARS; ++i)
        pthread_create(&thread_cars[i], NULL, (void *) carLife, (void *) i);

    for (int i = 0; i < NO_CARS; ++i)
        pthread_join(thread_cars[i], NULL);
}

#define NO_ENTRIES 2
#define NO_EXITS 1

sem_t sem_place;
sem_t semEntree;
sem_t semSortie;

void exo3B_enterParking(int carId) {
    sem_wait(&semEntree);
    printf("Voiture n°%d passe la porte\n", carId);

    sleep(1);

    printf("Voiture n°%d a passé la porte\n", carId);
    sem_post(&semEntree);

    printf("Voiture n°%d entre dans le parking\n", carId);
}

void exo3B_leaveParking(int carId) {
    sem_wait(&semSortie);
    printf("Voiture n°%d passe par la sortie\n", carId);

    sleep(1);

    printf("Voiture n°%d a passé la sortie\n", carId);
    sem_post(&semSortie);

    printf("Voiture n°%d est sortie du parking\n", carId);
    sem_post(&sem_place);

    pthread_exit(NULL);
}

void exo3B_carLife(int carId) {
    printf("Voiture n°%d souhaite rentrer dans le parking\n", carId);

    sem_wait(&sem_place);
    exo3B_enterParking(carId);

    sleep((unsigned int) (random() % 5));

    printf("Voiture n°%d souhaite sortir du parking\n", carId);
    exo3B_leaveParking(carId);
}

void exo3B() {
    srandom((unsigned int) time(NULL)); // random initialisation

    sem_init(&sem_place, 0, NO_PLACES);
    sem_init(&semEntree, 0, NO_ENTRIES);
    sem_init(&semSortie, 0, NO_EXITS);

    pthread_t thread_cars[NO_CARS];

    for (int i = 0; i < NO_CARS; ++i)
        pthread_create(&thread_cars[i], NULL, (void *) exo3B_carLife, (void *) i);

    for (int i = 0; i < NO_CARS; ++i)
        pthread_join(thread_cars[i], NULL);
}

int main() {
//    exo1A();
//    exo1B();
//    exo2();
//    exo3A();
    exo3B();
    r
    eturn 0;
}
