typedef struct {
    int korak;
    int duljina1;
    int duljina2;
} KorakInfo;

KorakInfo koraci[1000];
int brojKoraka = 0;

void DodajKorak(int duljina1, int duljina2) {
    koraci[brojKoraka].korak = brojKoraka + 1;
    koraci[brojKoraka].duljina1 = duljina1;
    koraci[brojKoraka].duljina2 = duljina2;
    brojKoraka++;
}

BinaryTree HuffmanTree(List L) {
    List duljine;
    LiMakeNull(&duljine);

    int trenutnaDuljina = 1;
    for (int i = 1; i <= L.last; i++) {
        if (LiRetrieve(i, L) >= LiRetrieve(i - 1, L)) {
        trenutnaDuljina++;
    }
    else {
        LiInsert(trenutnaDuljina, LiEnd(duljine), &duljine);
        trenutnaDuljina = 1;
    }
    }
    LiInsert(trenutnaDuljina, LiEnd(duljine), &duljine);


    BinaryTree stablo;
    BiMakeNull(&stablo);

    while (duljine.last > 0) {
        int min1 = LiRetrieve(0, duljine);
        int pos1 = 0;
        for (int i = 1; i <= duljine.last; i++) {
            if (LiRetrieve(i, duljine) < min1) {
                min1 = LiRetrieve(i, duljine);
                pos1 = i;
            }
        }
        LiDelete(pos1, &duljine);

        int min2 = LiRetrieve(0, duljine);
        int pos2 = 0;
        for (int i = 1; i <= duljine.last; i++) {
            if (LiRetrieve(i, duljine) < min2) {
                min2 = LiRetrieve(i, duljine);
                pos2 = i;
            }
        }
        LiDelete(pos2, &duljine);

        DodajKorak(min1, min2);

        int suma = min1 + min2;
        LiInsert(suma, LiEnd(duljine), &duljine);

        BinaryTree lijevo, desno;
        BiMakeNull(&lijevo);
        BiMakeNull(&desno);

        BiCreate(min1, NULL, NULL, &lijevo);
        BiCreate(min2, NULL, NULL, &desno);
        BiCreate(suma, lijevo, desno, &stablo);
    }

    return stablo;
}

int PrintTree(BinaryTree B) {
    int ukupnoVrijeme = 0;

    for (int i = 0; i < brojKoraka; i++) {
        printf("%d. korak: spoji liste duljine %d i %d", koraci[i].korak, koraci[i].duljina1, koraci[i].duljina2);
        printf("\n");
        ukupnoVrijeme += koraci[i].duljina1 + koraci[i].duljina2;
    }

    return ukupnoVrijeme;
}
