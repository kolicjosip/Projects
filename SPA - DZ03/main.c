#include<stdio.h>
#include<string.h>

#include"Set.h"
#include"PriorityQueue.h"
#include"Mapping.h"
#include"Organizacija.h"

int main()
{
    PriorityQueue Slastice, Kolegiji;

    PrMakeNull(&Slastice); PrMakeNull(&Kolegiji);

    naziv slastice[5]={"Palacinke", "Germknedle", "Vruca cokolada", "Fritule", "Vafli"},
    kolegiji[5]={"SPA", "Vjerojatnost", "Gradja racunala", "Diskretna", "DIFRAF"},
    dan[5]={"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak"};

    for(int i=0; i<5;i++)
    {
        par1 temp;

        strcpy(temp.prvi,slastice[i]);
        temp.drugi=i+1;

        PrInsert(temp,&Slastice);

        strcpy(temp.prvi,kolegiji[i]);

        PrInsert(temp,&Kolegiji);
    }

    printf("%d %d\n", PrSlastica(Slastice,"Fritule"), PrKolegij(Kolegiji,"SPA"));

    Mapping M;

    MaMakeNull(&M);

    par2 pom;

    strcpy(pom.prvi,slastice[3]); strcpy(pom.drugi,kolegiji[1]); MaAssign(&M,dan[0],pom);
    strcpy(pom.prvi,slastice[1]); strcpy(pom.drugi,kolegiji[0]); MaAssign(&M,dan[1],pom);
    strcpy(pom.prvi,slastice[2]); strcpy(pom.drugi,kolegiji[4]); MaAssign(&M,dan[2],pom);
    strcpy(pom.prvi,slastice[4]); strcpy(pom.drugi,kolegiji[3]); MaAssign(&M,dan[3],pom);
    strcpy(pom.prvi,slastice[0]); strcpy(pom.drugi,kolegiji[2]); MaAssign(&M,dan[4],pom);

    naziv dani[5];

    Sort(M,Slastice,Kolegiji,dani);

    for(int i=0;i<5;i++)
        printf("%s ",dani[i]);
    printf("\n");

    Set niz[10]; int i;

    for(i=0;i<10;i++)
        SeMakeNull(niz+i);

    Subset(M,Slastice,Kolegiji,niz);

    i=0;

    while(!SeEmpty(niz[i]))
    {
        SePrint(niz[i++]);
        printf("\n");
    }

    return 0;
}
