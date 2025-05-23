#include<stdio.h>
#include<stdlib.h>

#define MAXLENGTH 100
#define MAXSTRING 21

// definicija tipova
typedef char naziv[MAXSTRING];

typedef struct {
    naziv prvi;
    int drugi;
} par1;

typedef struct {
    par1 elements[MAXLENGTH];
    int last;
} PriorityQueue;


void PrMakeNull(PriorityQueue* Ap) {
    Ap->last = -1;
}

void PrInsert(par1 x, PriorityQueue* Ap) {
    Ap->elements[++(Ap->last)] = x;
}

int PrEmpty(PriorityQueue A)
{
    if(A.last == -1)
        return 1;
    return 0;
}

// stara implementacija

/*

elementtype PrDeleteMin(PriorityQueue* Ap)
{
    int i,j;
    elementtype minel, temp;
    if(Ap->last<0)
        exit(802);
    else
    {
        //najmanji element se nalazi u korijenu
        minel = Ap->elements[0];
        //prebacimo zadnji element u prvi;
        Ap->elements[0] = Ap->elements[Ap->last];
        //izbacimo zadnji element
        (Ap->last)--;
        i = 0;
        while(i<=(Ap->last+1)/2-1)
        {
            //mičemo element u čvoru i prema dolje
            if(2*i+1 == Ap->last || (Ap->elements[2*i+1]<Ap->elements[2*i+2]))
                j = 2*i+1;
            else
                j=2*i+2;
            if(Ap->elements[i]>Ap->elements[j])
            {
                temp = Ap->elements[i];
                Ap->elements[i] = Ap->elements[j];
                Ap->elements[j] = temp;
                i=j;
            }
            else
                return minel;
        }
        return minel;
    }
}

*/
