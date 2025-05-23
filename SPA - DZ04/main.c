#include<stdio.h>
#include"plocice.h"

int main()
{
    plocica zaliha[6];
    int ukupno, pom=-1;

    zaliha[0].a=4; zaliha[0].b=7; zaliha[0].dostupna=1;
    zaliha[1].a=4; zaliha[1].b=6; zaliha[1].dostupna=1;
    zaliha[2].a=2; zaliha[2].b=10; zaliha[2].dostupna=1;
    zaliha[3].a=6; zaliha[3].b=3; zaliha[3].dostupna=1;
    zaliha[4].a=4; zaliha[4].b=4; zaliha[4].dostupna=1;
    zaliha[5].a=2; zaliha[5].b=7; zaliha[5].dostupna=1;

    ukupno=poploci(6,10,zaliha,6);

    printf("%d\n",ukupno);

    ispisi(6,10,zaliha,6,ukupno,&pom);

    return 0;
}

