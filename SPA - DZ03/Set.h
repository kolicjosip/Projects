#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100
#define MAXSTRING 21

// definicija tipova
typedef char naziv[MAXSTRING];

// set
typedef struct celltag {
    naziv element;
    struct celltag* next;
} celltypeSet;

typedef celltypeSet* Set;

void SeMakeNull(Set* Ap) {
    *Ap = NULL;
}

int SeEmpty(Set A) {
    return A == NULL;
}

void SeInsert(naziv x, Set* Ap) {
    celltypeSet* novi = (celltypeSet*)malloc(sizeof(celltypeSet));
    strcpy(novi->element, x);
    novi->next = *Ap;
    *Ap = novi;
}

void SePrint(Set A) {
    if (SeEmpty(A)) {
        printf("Prazan skup ");
        return;
    }
    while (A) {
        printf("%s ", A->element);
        A = A->next;
    }
    printf("\n");
}

    // stara implementacija

/*
typedef int elementtype;

typedef struct celltag{
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
    //ako nije prazan ubacivamo sortirano
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
           //elementi su različiti, onaj u A je manji, dakle nema šanse da se nalazi negdje kasnije u B
           return 0;
       else
            //elementi su različiti, a onaj u B je manji, dakle nema šanse da se nalazi kasnije u A
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
           //elementi su različiti, onaj u A je manji, dakle nema šanse da se nalazi negdje kasnije u B
           pomA = pomA->next;
       else
            //elementi su različiti, a onaj u B je manji, dakle nema šanse da se nalazi kasnije u A
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
           //elementi su različiti, onaj u A je manji, dakle nema šanse da se nalazi negdje kasnije u B
        {
            pomC->next =  (celltype*)malloc(sizeof(celltype));
           pomC = pomC->next;
           pomC->element = pomA->element;
               pomA = pomA->next;
        }

       else
            //elementi su različiti, a onaj u B je manji, dakle nema šanse da se nalazi kasnije u A
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


int SeEmpty(Set A) {
    return A == NULL;
}

void SePrint(Set A) {
    if (SeEmpty(A)) {
        printf(" Prazan skup .\n");
        return;
    }
    celltype* pom = A;
    while (pom != NULL) {
        printf("%s ", pom->element);
        pom = pom->next;
    }
    printf("\n");
}

*/





