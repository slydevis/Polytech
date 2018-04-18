#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define TRUE 1
#define FALSE 0

void exo1A() {
    pid_t fils_pid;
    fils_pid = fork();
    if (fils_pid == 0) {
        printf("Je suis le fils avec pid : %d\n", getpid());
        printf("Avec un père de pid : %d\n", getppid());
        sleep(10);
    } else if (fils_pid > 0) {
        printf("Je suis le père avec un pid : %d\n", getpid());
        sleep(10);
    } else {
        perror("Erreur dans la création du fils");
    }
}

void exo1B() {
    FILE *file;
    file = fopen("listeNbPremier.txt", "r");
    int nbLeft = 10;
    fpos_t pos;

    rewind(file);

    printf("Je suis le père pid = %d\n", getpid());

    while (nbLeft > 0) {
        int number;

        fscanf(file, "%d", &number);

        printf("number = %d\n", number);
        nbLeft--;
        fgetpos(file, &pos);
    }

    pid_t fils = fork();

    if (fils == 0) {
        printf("Je suis le fils pid = %d\n", getpid());
        nbLeft = 20;
        while (nbLeft > 0) {
            int number;

            fscanf(file, "%d", &number);

            printf("number = %d\n", number);
            nbLeft--;
            fgetpos(file, &pos);
        }

        printf("Fin du fils\n");
        exit(0);
    } else if (fils > 0) {
        wait(NULL);
        printf("Wait fini\n");

        fsetpos(file, &pos);

        while (!feof(file)) {
            int number;

            fscanf(file, "%d", &number);

            printf("number = %d\n", number);
            nbLeft--;
            fgetpos(file, &pos);
        }
    } else
        perror("Erreur dans la création du fils");

    fclose(file);
}

void *thread1Fct(void *args) {
    char *str = (char *) args;
    fprintf(stdout, "%s", str);
    pthread_exit("Je suis A et j'ai fini\n");
}

void *thread2Fct(void *args) {
    char *str = (char *) args;
    fprintf(stderr, "%s", str);
    return "Je suis B et j'ai fini\n";
}

void exo2A() {
    pthread_t thread1, thread2;

    printf("pid du main = %d\n", getpid());

    pthread_create(&thread1, NULL, &thread1Fct, "Thread 1\n");
    pthread_create(&thread2, NULL, &thread2Fct, "Thread 2\n");

    void *ret1, *ret2;
    pthread_join(thread2, &ret1);
    char *retStr = (char *) ret1;
    printf("%s", retStr);

    pthread_join(thread1, &ret2);
    char *retStr2 = (char *) ret2;
    printf("%s", retStr2);
}

typedef struct Tableau {
    int *data;
    int size;
} Tableau;

void *afficherTab(Tableau *tab) {
    while (TRUE) {
        printf("[ ");

        for (int i = 0; i < tab->size - 1; ++i)
            printf("%d, ", tab->data[i]);

        printf("%d", tab->data[tab->size - 1]);

        printf(" ]\n");

        usleep(100);
    }
}

void bubble_sort(Tableau *tab) {
    int tmp, finish = 1;
    while (finish) {
        finish = 0;
        for (int i = 1; i < tab->size; i++) {
            if (tab->data[i] < tab->data[i - 1]) {
                tmp = tab->data[i];
                tab->data[i] = tab->data[i - 1];
                tab->data[i - 1] = tmp;
                finish = 1;
            }
        }
    }
}

#define TAB_SIZE 500

void exo2B() {
    int tab[TAB_SIZE];

    for (int i = 0; i < TAB_SIZE; ++i)
        tab[i] = TAB_SIZE - i;

    int size = sizeof(tab) / sizeof(tab[0]);

    Tableau tableau;
    tableau.data = tab;
    tableau.size = size;

    pthread_t thread_afficher, thread_bubble;

    pthread_create(&thread_bubble, NULL, (void *) &bubble_sort, &tableau);
    pthread_create(&thread_afficher, NULL, (void *) &afficherTab, &tableau);

    pthread_join(thread_bubble, NULL);
    pthread_detach(thread_afficher);
}

void exo3() {
    pid_t fils = fork();
    if (fils == 0) {
        while (TRUE)
            printf("Et tu boucle boucle boucle\n");
    } else if (fils >= 0) {
        sleep(1);
        printf("It is time to kill my son :D\n");
        kill(fils, SIGKILL);
    } else
        perror("Erreur dans la création du fils");
}

#define R 0
#define W 1

void exo4A() {
    // Pipe fils lecture de caractère
    int fd_car[2];
    pipe(fd_car);

    // Pipe fils lecture de chiffre
    int fd_digit[2];
    pipe(fd_digit);

    pid_t pid_fils_digit = fork();
    if (pid_fils_digit == 0) {
        printf("Début processus digit\n");
        int somme = 0;
        char chiffre = 0;

        while (chiffre != '0') {
            read(fd_digit[R], &chiffre, 1);
            somme += atoi(&chiffre);
            printf("somme = %d\n", somme);
        }

        printf("Envoie du résultat\n");

        write(fd_digit[W], &somme, 4);

        printf("Fin processus digit\n");
        exit(0);
    } else if (pid_fils_digit > 0) {
        printf("Début processus car\n");
        pid_t pid_fils_car = fork();

        if (pid_fils_car == 0) {
            char nb_car[26];
            char car = 0;

            for (int i = 0; i < 26; ++i)
                nb_car[i] = 0;

            while (car != '0') {
                read(fd_car[R], &car, 1);
                if (car != '0') {
                    int pos = tolower(car) - 'a';
                    nb_car[pos]++;
                    printf("pos = %d, nb_car[%d] = %d\n", pos, pos, nb_car[pos]);
                }
            }

            // On envoie le résultat
            write(fd_car[W], nb_car, 26);

            printf("Fin processus car\n");
            exit(0);
        } else if (pid_fils_car > 0) {
            // Processus père
            int car;
            do {
                car = getchar();
                if (isdigit(car)) {
                    write(fd_digit[W], &car, 1);
                } else if (isalpha(car)) {
                    write(fd_car[W], &car, 1);
                }
            } while (car != EOF);

            // AJout du charactère 0 dans les deux fils pour les stopper
            write(fd_car[W], "0", 1);
            write(fd_digit[W], "0", 1);

            waitpid(pid_fils_car, NULL, 0);
            waitpid(pid_fils_digit, NULL, 0);

            int somme;
            read(fd_digit[R], &somme, 4);

            printf("Résultat de la somme = %d\n", somme);

            char car_num[26];
            read(fd_car[R], car_num, 26);

            for (int i = 0; i < sizeof(car_num) / sizeof(car_num[0]); ++i)
                printf("car_num[%c] = %d\n", (char) 'a' + i, car_num[i]);

            close(fd_car[W]);
            close(fd_car[R]);

            close(fd_digit[W]);
            close(fd_digit[R]);

            printf("Fin processus père\n");
        } else
            perror("Erreur dans la création du fils carac\n");
    } else
        perror("Erreur dans la création du fils digit\n");
}

// EXO 4B
void vie_des_fils(int *fd_pipe, FILE *file) {
    int entier, next = 0;
    int status;
    int first = 0;
    pid_t pid_fils;

    read(fd_pipe[R], &entier, 4);

    if (entier == -1) {
        close(fd_pipe[R]);
        close(fd_pipe[W]);

        printf("FIN\n");
        fclose(file);

        exit(0);
    }

    // Ecriture de l'entier
    fprintf(file, "%d\n", entier);
    fflush(NULL);

    printf("DEBUT : PID = %d, entier = %d\n", getpid(), entier);

    int fd_fils_pipe[2];
    pipe(fd_fils_pipe);

    while (next != -1) {
        read(fd_pipe[R], &next, 4);

        if (next % entier != 0) {
            // Nombre non premier
            if (first == 0) {
                first = 1;

                write(fd_fils_pipe[W], &next, 4);

                pid_fils = fork();
                if (pid_fils == 0) {
                    vie_des_fils(fd_fils_pipe, file);
                }
            } else {
                write(fd_fils_pipe[W], &next, 4);
            }
        }
    }

    close(fd_pipe[R]);
    close(fd_pipe[W]);

    waitpid(pid_fils, &status, 0);
    printf("FIN : PID = %d, entier = %d\n", getpid(), entier);
    exit(0);
}

void exo4B() {
    int status;
    FILE *file = fopen("nbPremier.txt", "w+");

    int fd_pipe[2];
    pipe(fd_pipe);

    int entier[100];
    for (int i = 0; i < 100; i++)
        entier[i] = i + 1;

    pid_t pid_fils = fork();

    if (pid_fils == 0) { // Processus fils
        vie_des_fils(fd_pipe, file);
    } else if (pid_fils > 0) { // Processus Père
        for (int i = 1; i < 100; i++) {
            write(fd_pipe[W], &entier[i], 4);
//            usleep(200);
        }

        int fin_pere_msg = -1;
        write(fd_pipe[W], &fin_pere_msg, 4);

        wait(&status);
        fclose(file);
    } else
        perror("Erreur dans la création du fils");
}

// EXO 5
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

void exo5() {
    char *zone;
    int fd;

    printf("Ouverture de la mémoire partagee\n");
    zone = creeSegment(2048, "partage.mem", fd);

    system("ipcs -m");

    sprintf(zone, "Test zone memoire partagee");

    printf("\n\nmemoire partage : \n %s\n", zone);
    sleep(5);

    printf("Fermeture de la mémoire partagee\n");
    fermerSegment(2048, "partage.mem", fd, zone);
}

int main() {
//     exo1A();
//    exo1B();
//     exo2A();
//    exo2B();
//    exo3();
//    exo4A();
//    exo4B();
    exo5();
    return 0;
}
