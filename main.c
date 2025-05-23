#include <stdio.h>

typedef int labeltype;
#include "BinaryTree.h"

typedef int elementtype;
#include "List.h"

#include "Huffman.h"

int main(void){
    List L;
    LiMakeNull(&L);

    int brojevi[7] = {3,5,6,3,2,4,4};
    int i;
    for(i = 0; i < 7; ++i) {
        LiInsert(brojevi[i], LiEnd(L), &L);
    }

    printf("Vrijeme izvrsavanja je %d.", PrintTree(HuffmanTree(L)));
    return 0;
}
