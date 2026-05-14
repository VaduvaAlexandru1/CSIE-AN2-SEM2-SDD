#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Persoana {
	char* nume;
	int id;
	int varsta;
	float salariu;
}Persoana;

struct Nod {
	Persoana pers;
	Nod* stanga;
	Nod* dreapta;
};

Persoana initPersoana(int id ,const char* nume, int varsta, float salariu) {
	Persoana pers;
	pers.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(pers.nume, nume);
	pers.id = id;
	pers.varsta = varsta;
	pers.salariu = salariu;

	return pers;
}

void afisarePersoana(Persoana pers) {
	printf("\nNume : %s , ID : %d , Varsta : %d , Pret : %.2f" , pers.nume , pers.id , pers.varsta , pers.salariu);
}

void insertBST(Nod** radacina , Persoana pers) {
	
	if (*radacina == NULL) {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->pers = pers;
		nod->dreapta = NULL;
		nod->stanga = NULL;
		*radacina = nod;

		return;
	}
	if ((*radacina)->pers.id == pers.id) return;

	if (pers.id < (*radacina)->pers.id) {
		insertBST(&(*radacina)->stanga, pers);
		return;
	}
	if (pers.id > (*radacina)->pers.id) {
		insertBST(&(*radacina)->dreapta, pers);
		return;
	}


}

Persoana searchByID(Nod* rad, int id) {
	if (rad == NULL) return initPersoana(-1, "Anonim", 0, 0);

	if (rad->pers.id > id) return searchByID(rad->stanga, id);
	if (rad->pers.id < id) return searchByID(rad->dreapta, id);

	return initPersoana(rad->pers.id, rad->pers.nume, rad->pers.varsta, rad->pers.salariu);
}

void inordine(Nod* radacina) {
	if (radacina == NULL) return;
	inordine(radacina->stanga);
	afisarePersoana(radacina->pers);
	inordine(radacina->dreapta);
}

void preordine(Nod* radacina) {
	if (radacina == NULL) return;
	afisarePersoana(radacina->pers);
	preordine(radacina->stanga);
	preordine(radacina->dreapta);
}

void postordine(Nod* radacina) {
	if (radacina == NULL) return;
	postordine(radacina->stanga);
	postordine(radacina->dreapta);
	afisarePersoana(radacina->pers);
}

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int treeHeight(Nod* radacina) {
	if (radacina == NULL) return 0;

	return maxim(treeHeight(radacina->stanga), treeHeight(radacina->dreapta)) + 1;
}

void dezalocare(Nod** radacina) {
	if (*radacina == NULL) return;

	dezalocare(&(*radacina)->stanga);
	dezalocare(&(*radacina)->dreapta);

	free((*radacina)->pers.nume);
	free(*radacina);
}

int main() {

	Nod* rad = NULL;

	insertBST(&rad, initPersoana(7, "Andrei", 23, 4500));
	insertBST(&rad, initPersoana(4, "Maria", 28, 5200));
	insertBST(&rad, initPersoana(10, "George", 35, 6100));
	insertBST(&rad, initPersoana(2, "Elena", 21, 3900));
	insertBST(&rad, initPersoana(6, "Alex", 30, 4800));
	insertBST(&rad, initPersoana(8, "Ioana", 26, 5500));
	insertBST(&rad, initPersoana(11, "Mihai", 40, 7000));

	printf("\n---------cautare dupa id-----------");

	Persoana pers = searchByID(rad, 2);
	afisarePersoana(pers);
	free(pers.nume);

	printf("\n---------Inaltime arbore-----------");
	printf("\n%d" , treeHeight(rad));
	dezalocare(&rad);

	return 0;
}