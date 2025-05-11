#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CLAUSES 1000
#define MAX_VARS 100

typedef struct {
    int litere[MAX_VARS];
    int numar_litere;
} Clauza;


int citesteClauze(const char *filename, Clauza clauze[]) {
    FILE *fisier = fopen(filename, "r");
    int numarLitere, numarClauze, i = 0;

    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului %s!\n", filename);
        return -1;
    }

    fscanf(fisier, "%d %d", &numarLitere, &numarClauze);
    while (fscanf(fisier, "%d", &clauze[i].litere[clauze[i].numar_litere]) != EOF) {
        if (clauze[i].litere[clauze[i].numar_litere] == 0) {
            i++;
        } else {
            clauze[i].numar_litere++;
        }
    }

    fclose(fisier);
    return i;
}


bool dp(int numarClauze, Clauza clauze[], bool *assignment, int numarLitere) {
    int i, j;


    for (i = 0; i < numarClauze; i++) {
        bool satisfacut = false;
        for (j = 0; j < clauze[i].numar_litere; j++) {
            int litera = clauze[i].litere[j];
            if (litera > 0 && assignment[litera - 1]) {
                satisfacut = true;
                break;
            } else if (litera < 0 && !assignment[-litera - 1]) {
                satisfacut = true;
                break;
            }
        }
        if (!satisfacut) {
            return false;
        }
    }

    return true;
}

int main() {
    const char *fisier = "mpi.txt";
    Clauza clauze[MAX_CLAUSES];
    bool assignment[MAX_VARS] = {false};
    int numarClauze, numarLitere;


    numarClauze = citesteClauze(fisier, clauze);

    if (numarClauze == -1) {
        printf("Nu s-au citit clauze. Verifica fisierul mpi.txt.\n");
        return 1;
    }


    if (dp(numarClauze, clauze, assignment, numarLitere)) {
        printf("Formula este satisfiabila!\n");
    } else {
        printf("Formula nu este satisfiabila!\n");
    }

    return 0;
}
