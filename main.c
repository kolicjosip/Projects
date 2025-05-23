#include <stdio.h>

typedef int elementtype;

#include "Stack.h"
#include "Prefix.h"

int main(void) {
    char izraz1[] = "<-> -> T & F T | F - T",
     izraz2[] = "<-> -> T & F T | F T -";
    printf("%d\n", PrefixEval(izraz1));
    printf("%d", PrefixEval(izraz2));
}
