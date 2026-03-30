#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;
typedef struct HashTable HashTable;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int size;
};

Carte initCarte(const char* titlu, int nrPagini, float pret) {
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	return c;
}

void inserareLaSfarsit(Nod** cap, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = NULL;
	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}



void afisareCarte(Carte carte) {
	printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}



void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

HashTable initTabela(int dim) {
	HashTable tabela;
	tabela.size = dim;
	tabela.vector = (Nod**)malloc(dim * sizeof(Nod*));

	for (int i = 0; i < dim; ++i) tabela.vector[i] = NULL;

	return tabela;
}

int hash(int nrPagini, int size) {
	return nrPagini % size;
}

//mecanismul de tratare al coliziunilor este chaining

void inserareInHashTable(HashTable tabela , Carte c) {
	if (tabela.size <= 0) return;
	int poz = hash(c.nrPagini, tabela.size);
	if (poz < 0 || poz >= tabela.size) return;
	inserareLaSfarsit(&(tabela.vector[poz]), c);
}

void parcurgereHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.size; ++i) {
		printf("Pozitie %d : \n", i);
		afisareListaCarti(tabela.vector[i]);
	}
}

void dezalocareTabela(HashTable tabela) {
	for (int i = 0; i < tabela.size; ++i) {
		dezalocare(&(tabela.vector[i]));
	}
	free(tabela.vector);
}

//pretul mediu pentru cartile cu un nr de pag dat ca parametru

float pretMediuPag(HashTable tabela , int nrPagini) {
	int poz = nrPagini % tabela.size;//2
	Nod* cap = tabela.vector[poz];

	float pret = 0;
	int cnt = 0;

	while (cap != NULL) {
		{
			if (cap->info.nrPagini == nrPagini) pret += cap->info.pret;
			cnt++;
		}
		cap = cap->next;
	}

	return cnt == 0 ? 0 : pret/cnt;

}

int main() {

	HashTable tabela = initTabela(6);

	inserareInHashTable(tabela, initCarte("Micul Print", 132, 35.2));
	inserareInHashTable(tabela, initCarte("Nuntasii", 122, 46.9));
	inserareInHashTable(tabela, initCarte("Confess", 126, 34.3));

	//parcurgereHashTable(tabela);
	int nrPagini = 122;
	printf("\nPretul mediu pentru o carte cu %d nr pagini este : %.2f lei", nrPagini, pretMediuPag(tabela, nrPagini));
	dezalocareTabela(tabela);
	return 0;
}