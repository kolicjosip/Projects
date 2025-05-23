#include<stdio.h>
#include<stdlib.h>

#define MAXLENGTH 100
#define MAXSTRING 21

// definicija tipova
typedef char naziv[MAXSTRING];

typedef struct {
    naziv prvi;
    naziv drugi;
} par2;

typedef struct {
    naziv domainelement;
    par2 rangeelement;
} celltype1;

typedef struct {
    int last;
    celltype1 pairs[MAXLENGTH];
} Mapping;

void MaMakeNull(Mapping* Mp) {
    Mp->last = -1;
}

void MaAssign(Mapping* Mp, naziv d, par2 r) {
    if (Mp->last >= MAXLENGTH - 1) exit(101);

    for (int i = 0; i <= Mp->last; i++) {
        if (strcmp(Mp->pairs[i].domainelement, d) == 0) {
            Mp->pairs[i].rangeelement = r;
            return;
        }
    }
    Mp->last++;
    strcpy(Mp->pairs[Mp->last].domainelement, d);
    Mp->pairs[Mp->last].rangeelement = r;
}

int MaCompute(Mapping M, naziv d, par2* r) {
    for (int i = 0; i <= M.last; i++) {
        if (strcmp(M.pairs[i].domainelement, d) == 0) {
            *r = M.pairs[i].rangeelement;
            return 1;
        }
    }
    return 0;
}
