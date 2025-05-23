#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// implementacija ATP-a SET
typedef int elementtype;

typedef struct celltag
{
    elementtype element;
    struct celltag* next;
}celltype;

typedef celltype* Set;

void SeMakeNull(Set* Ap)
{
    *Ap = (celltype*)malloc(sizeof(celltype));
    (*Ap)->next = NULL;
}

void SeInsert(elementtype x, Set* Ap)
{
    celltype* novi = (celltype*)malloc(sizeof(celltype));
    novi->element = x;
    if((*Ap)->next == NULL)
    {
        (*Ap)->next = novi;
        novi->next = NULL;
        return;
    }
    /*ako nije prazan ubacivamo sortirano*/
    celltype* pom = *Ap;
    while(pom->next!=NULL && pom->next->element<x)
        pom = pom->next;
    if(pom->next!=NULL && pom->next->element == x)
        return;
    novi->next = pom->next;
    pom->next = novi;

}

void SeDelete(elementtype x, Set* Ap)
{
    if((*Ap)->next == NULL)
        return;
    celltype* pom = *Ap;
    while(pom->next!=NULL && pom->next->element < x )
        pom = pom->next;
    if(pom->next!=NULL && pom->next->element == x)
    {
        celltype* temp = pom->next;
        pom->next = pom->next->next;
        free(temp);
    }
}


//napravi na satu
int SeMember(elementtype x, Set A)
{
    if(A->next == NULL)
    {
        return 0;
    }
    celltype* pom = A->next;
    while(pom!=NULL && pom->element < x)
        pom = pom->next;
    if(pom!=NULL && pom->element == x)
        return 1;
    return 0;
}

int SeSubset(Set A,Set B)
{
   celltype *pomA, *pomB;
   pomA = A->next;
   pomB = B->next;

   while(pomA!=NULL && pomB!=NULL)
   {
       //usporedimo trenutne elemente liste A i B
       if(pomA->element == pomB->element)
       {
           pomA = pomA->next;
           pomB = pomB->next;
       }
       else if(pomA->element < pomB->element)
           //elementi su razliciti, onaj u A je manji, dakle nema sanse da se nalazi negdje kasnije u B
           return 0;
       else
            //elementi su razliciti, a onaj u B je manji, dakle nema sanse da se nalazi kasnije u A
           pomB = pomB->next;
   }
   if(pomA == NULL)
        return 1;
   return 0;
}

elementtype SeMin(Set A)
{
    if(A->next==NULL)
        exit(601);
    return A->next->element;
}

elementtype SeMax(Set A)
{
    if(A->next==NULL)
        exit(601);
    celltype* pom = A;
    while(pom->next!=NULL)
        pom = pom->next;
    return pom->element;
}

int SeUnion(Set A, Set B, Set* Cp)
{
    celltype *pomA, *pomB, *pomC;
   //stvaramo zaglavlje u listi C
   *Cp = (celltype*)malloc(sizeof(celltype));
   pomA = A->next;
   pomB = B->next;
   pomC = *Cp;

   while(pomA!=NULL && pomB!=NULL)
   {
       //usporedimo trenutne elemente liste A i B
       if(pomA->element == pomB->element)
       {
           //dodajemo element u C
           pomC->next =  (celltype*)malloc(sizeof(celltype));
           pomC = pomC->next;
           pomC->element = pomA->element;
           pomA = pomA->next;
           pomB = pomB->next;
       }
       else if(pomA->element < pomB->element)
       {
           pomC->next =  (celltype*)malloc(sizeof(celltype));
           pomC = pomC->next;
           pomC->element = pomA->element;
           pomA = pomA->next;
       }
       else
       {
           pomC->next =  (celltype*)malloc(sizeof(celltype));
           pomC = pomC->next;
           pomC->element = pomB->element;
           pomB = pomB->next;
       }
   }
   if(pomA!=NULL)
   {
       pomC->next =  (celltype*)malloc(sizeof(celltype));
        pomC = pomC->next;
        pomC->element = pomA->element;
        pomA = pomA->next;
   }
      if(pomB!=NULL)
   {
       pomC->next =  (celltype*)malloc(sizeof(celltype));
        pomC = pomC->next;
        pomC->element = pomB->element;
        pomB = pomB->next;
   }
   pomC->next = NULL;
}


//napravi na satu
int SeIntersection(Set A, Set B, Set* Cp)
{
   celltype *pomA, *pomB, *pomC;
   //stvaramo zaglavlje u listi C
   *Cp = (celltype*)malloc(sizeof(celltype));
   pomA = A->next;
   pomB = B->next;
   pomC = *Cp;

   while(pomA!=NULL && pomB!=NULL)
   {
       //usporedimo trenutne elemente liste A i B
       if(pomA->element == pomB->element)
       {
           //dodajemo element u C
           pomC->next =  (celltype*)malloc(sizeof(celltype));
           pomC = pomC->next;
           pomC->element = pomA->element;
           pomA = pomA->next;
           pomB = pomB->next;
       }
       else if(pomA->element < pomB->element)
           //elementi su razliciti, onaj u A je manji, dakle nema sanse da se nalazi negdje kasnije u B
           pomA = pomA->next;
       else
            //elementi su razliciti, a onaj u B je manji, dakle nema sanse da se nalazi kasnije u A
           pomB = pomB->next;
   }
   pomC->next = NULL;
}

int SeDifference(Set A, Set B, Set* Cp)
{
    celltype *pomA, *pomB, *pomC;
   //stvaramo zaglavlje u listi C
   *Cp = (celltype*)malloc(sizeof(celltype));
   pomA = A->next;
   pomB = B->next;
   pomC = *Cp;

   while(pomA!=NULL && pomB!=NULL)
   {
       //usporedimo trenutne elemente liste A i B
       if(pomA->element == pomB->element)
       {
           pomA = pomA->next;
           pomB = pomB->next;
       }
       else if(pomA->element < pomB->element)
        //dodajemo
           //elementi su razliciti, onaj u A je manji, dakle nema sanse da se nalazi negdje kasnije u B
        {
            pomC->next =  (celltype*)malloc(sizeof(celltype));
           pomC = pomC->next;
           pomC->element = pomA->element;
               pomA = pomA->next;
        }

       else
            //elementi su razliciti, a onaj u B je manji, dakle nema sanse da se nalazi kasnije u A
           pomB = pomB->next;
   }
   //na kraju dodamo sta je ostalo iz A
   if(pomA!=NULL)
   {
       pomC->next =  (celltype*)malloc(sizeof(celltype));
        pomC = pomC->next;
        pomC->element = pomA->element;
        pomA = pomA->next;
   }
   pomC->next = NULL;
}

// Struktura koja opisuje plocicu
typedef struct {
    int a, b;
    int dostupna;
} plocica;

int min_plocice = INT_MAX;
Set najbolji_setovi[100];
int broj_rjesenja = 0;
Set trenutni_set;

void spremi_rjesenje(int broj_plocica) {
    if (broj_plocica > min_plocice) return;

    if (broj_plocica < min_plocice) {
        min_plocice = broj_plocica;
        broj_rjesenja = 0;
    }

    // kopiramo trenutni set u novi set za pohranu
    Set novi_set;
    SeMakeNull(&novi_set);
    celltype *pom = trenutni_set->next;
    while (pom) {
        SeInsert(pom->element, &novi_set);
        pom = pom->next;
    }

    // provjera postoji li rjesenje vec u najbolji_setovi
    for (int i = 0; i < broj_rjesenja; i++) {
        if (SeSubset(najbolji_setovi[i], novi_set) && SeSubset(novi_set, najbolji_setovi[i])) {
            return;
        }
    }

    najbolji_setovi[broj_rjesenja++] = novi_set;
}

void poploci_rekurzivno(int m, int n, plocica *zaliha, int br, int broj_plocica) {
    if (m == 0 || n == 0) {
        spremi_rjesenje(broj_plocica);
        return;
    }

    for (int i = 0; i < br; i++) {
        if (zaliha[i].dostupna) {
            if (zaliha[i].a == m) {
                zaliha[i].dostupna = 0;
                SeInsert(i, &trenutni_set);
                poploci_rekurzivno(m, n - zaliha[i].b, zaliha, br, broj_plocica + 1);
                SeDelete(i, &trenutni_set);
                zaliha[i].dostupna = 1;
            }
            if (zaliha[i].b == n) {
                zaliha[i].dostupna = 0;
                SeInsert(i, &trenutni_set);
                poploci_rekurzivno(m - zaliha[i].a, n, zaliha, br, broj_plocica + 1);
                SeDelete(i, &trenutni_set);
                zaliha[i].dostupna = 1;
            }
        }
    }
}

int poploci(int m, int n, plocica *zaliha, int br) {
    min_plocice = INT_MAX;
    broj_rjesenja = 0;
    SeMakeNull(&trenutni_set);
    poploci_rekurzivno(m, n, zaliha, br, 0);
    if (min_plocice == INT_MAX) return -1;  // neuspjeno postavljanje plocica
    return min_plocice;
}

void ispisi(int m, int n, plocica *zaliha, int br, int mini, int *pom) {
    *pom = broj_rjesenja;
    for (int i = broj_rjesenja-1; i >= 0; i--) {
        celltype *temp = najbolji_setovi[i]->next;
        while (temp) {
            printf("(%d,%d) ", zaliha[temp->element].a, zaliha[temp->element].b);
            temp = temp->next;
        }
        printf("\n");
    }
}
