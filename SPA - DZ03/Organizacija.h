#include <stdlib.h>

// pomocna funkcija za PrKolegij i PrSlastica
int PrPriority(PriorityQueue A, char* naziv) {
    for (int i = 0; i <= A.last; i++) {
        if (strcmp(A.elements[i].prvi, naziv) == 0) {
            return A.elements[i].drugi;
        }
    }
    return -1;  // nije pronaden kolegij ili slastica
}

int PrSlastica(PriorityQueue Slastice, char* slastica) {
    return PrPriority(Slastice, slastica);
}

int PrKolegij(PriorityQueue Kolegiji, char* kolegij) {
    return PrPriority(Kolegiji, kolegij);
}

void Sort(Mapping M, PriorityQueue Slastice, PriorityQueue Kolegiji, naziv* dani) {
    naziv pomocnoDani[5] = {"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak"};

    for (int i = 0; i < 5; i++){
        strcpy(dani[i], pomocnoDani[i]);    // kopiramo dane u polje dani
    }

    PriorityQueue pomocniPrioriteti;    // pomocni a.t.p. PriorityQueue
    PrMakeNull(&pomocniPrioriteti);

    for(int i = 0; i < 5; i++){
        par2 par;
        int prioritet = 0;

        // ako je M(dani[i]) vraca 1 i par = M(dani[i])
        if(MaCompute(M, dani[i], &par)){
            // prioritet dana je suma prioriteta slastica i kolegija
            prioritet = PrSlastica(Slastice, par.prvi) + PrKolegij(Kolegiji, par.drugi);
        }

        par1 temp;
        // prekopiramo u temp i-ti dan i prioritet i-tog dana
        strcpy(temp.prvi, dani[i]);
        temp.drugi = prioritet;

        // ubacimo podatke iz temp u pomocni prioritetni red
        PrInsert(temp, &pomocniPrioriteti);
    }

    for (int i = 0; i < 5; i++) {
        int maxIndex = 0;
        for (int j = 1; j <= pomocniPrioriteti.last; j++) {
            if (pomocniPrioriteti.elements[j].drugi <= pomocniPrioriteti.elements[maxIndex].drugi) {
                maxIndex = j;   // postavljamo max indeks
            }
        }

        strcpy(dani[i], pomocniPrioriteti.elements[maxIndex].prvi);

        // zamjena prioriteta
        for (int j = maxIndex; j < pomocniPrioriteti.last; j++) {
            pomocniPrioriteti.elements[j] = pomocniPrioriteti.elements[j + 1];
        }
        pomocniPrioriteti.last--;
    }
}

void Subset(Mapping M, PriorityQueue Slastice, PriorityQueue Kolegiji, Set* niz) {
    naziv dani[5] = {"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak"};
    int prioriteti[10];
    int subsetCount = 0;

    // koristimo jedan dodatni skup
    Set tempSet;
    SeMakeNull(&tempSet);

    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {

            // ocistimo skup za ponovno koristenje
            SeMakeNull(&tempSet);

            // dodajemo dane u leksikografskom redoslijedu
            if (strcmp(dani[i], dani[j]) < 0) {
                SeInsert(dani[j], &tempSet);
                SeInsert(dani[i], &tempSet);
            } else {
                SeInsert(dani[i], &tempSet);
                SeInsert(dani[j], &tempSet);
            }

            // dohvatimo elemente raspona iz Mappinga
            par2 element1, element2;
            if (!MaCompute(M, dani[i], &element1) || !MaCompute(M, dani[j], &element2)) {
                continue; // preskoci ako nije moguce dohvatiti elemente
            }

            // racunamo prioritet
            float sumaPrioriteta = PrSlastica(Slastice, element1.prvi) + PrKolegij(Kolegiji, element1.drugi) +
                                   PrSlastica(Slastice, element2.prvi) + PrKolegij(Kolegiji, element2.drugi);
            float prosjek = sumaPrioriteta / 2.0;

            // provjera prosjeka prioriteta
            if (prosjek <= 5) {
                niz[subsetCount] = tempSet; // spremamo trenutni skup u niz
                prioriteti[subsetCount] = (int)(prosjek * 10); // prosjek pomnozen s 10 zbog preciznosti
                subsetCount++;

                // kreiramo novi prazni skup za daljnje iteracije
                SeMakeNull(&tempSet);
            }
        }
    }

    // sortiranje polja niz prema prioritetima
    for (int i = 0; i < subsetCount - 1; i++) {
        for (int j = i + 1; j < subsetCount; j++) {
            if (prioriteti[i] > prioriteti[j]) {

                // zamjena bez dodatnog skupa
                Set tempSet = niz[i];
                niz[i] = niz[j];
                niz[j] = tempSet;

                // zamjena prioriteta
                int tempPrioritet = prioriteti[i];
                prioriteti[i] = prioriteti[j];
                prioriteti[j] = tempPrioritet;
            }
        }
    }
}




