#include<ctype.h>
#include<stdlib.h>

int PrefixEval(const char* izraz)
{
    Stack stog;
    StMakeNull(&stog);  // Inicijaliziraj stog


    int i, n;
    n = strlen(izraz);

    for (i = n - 1; i >= 0; i--)
    {
        char znak;
        znak = izraz[i];

        if (znak == ' ') continue; // Preskacemo bjeline

        if (znak == 'T')        // T = istina (1)
        {
            StPush(1, &stog);
        }
        else if (znak == 'F')       // F = laz (0)
        {
            StPush(0, &stog);
        }
        else if (znak == '-')
        {

            if (StEmpty(stog))
            {
                return -1;  // Greska - nemamo dovoljno operanada
            }
            else
            {
                int operand;
                operand = StTop(stog);
                StPop(&stog);
                StPush(!operand, &stog);
            }
        }
        else if(znak == '>')
        {
            int k,l;
            k = i-1;
            l = i-2;

            int operand1, operand2;

            operand1 = StTop(stog);
            StPop(&stog);

            if (StEmpty(stog)) return -1;

            operand2= StTop(stog);
            StPop(&stog);

            if(i>=2 && izraz[l] == '<' && izraz[k] == '-')      // Provjera bikondicionala
            {
                i -= 2;  // Preskoci "<-"

                StPush((operand1 && operand2) || (!operand1 && !operand2), &stog);

            }
            else if(i>=1 && izraz[k] == '-')
            {
                i--;
                StPush(!operand1 || operand2, &stog);
            }
            else return -1;  // Nepravilan zapis bikondicionala
        }

        else if (znak == '&' || znak == '|')
        {
            if (StEmpty(stog)) return -1;  // Greska - nemamo dovoljno operanada

            int operand1;

            operand1 = StTop(stog);
            StPop(&stog);

            if (StEmpty(stog)) return -1;

            int operand2;
            operand2 = StTop(stog);
            StPop(&stog);

            if (znak == '&')
            {
                StPush(operand1 && operand2, &stog);
            }
            if(znak == '|')
            {
                StPush(operand1 || operand2, &stog);
            }

            if (StEmpty(stog)) return -1;
        }
        else return -1;
    }

    // Ako je rezultat izraza validan, stog treba imati tocno jedan element
    if (!StEmpty(stog))
    {
        int rezultat = StTop(stog);
        StPop(&stog);
        if (StEmpty(stog)) return rezultat;  // Vraca 1 za istinu, 0 za laz
    }

    return -1;  // Nepravilan izraz

}
