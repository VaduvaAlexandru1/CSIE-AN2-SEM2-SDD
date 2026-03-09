#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct carte
{
	char* titlu;
	int nrPag;
	float pret;
} carte;

typedef struct Nod {
	Nod* prev;
	carte info;
	Nod* next;
};


float pretMediuCarte(Nod* coada) {
	int nrCarti = 0;
	float sumaPreturi = 0;
	while (coada != NULL) {
		sumaPreturi += (coada->info).pret;
		nrCarti++;
		coada = coada->prev;
	}

	return nrCarti != 0 ? sumaPreturi / nrCarti : 0;
}

void inserareLaInceput(Nod** cap,Nod** coada, carte c) {
	//alocam memorie
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	//actualizam prop pentru nodul nou
	nou->info = c; //shallow copy util
	nou->next = *cap; // prima legatura
	nou->prev = NULL;

	//tratam cazul cand lista are 0 elemente
	if (*cap == NULL) {
		*cap = *coada = nou;
		return;
	}

	//tratam cazul cand lista are elemente
	(*cap)->prev = nou;
	*cap = nou;
}
void inserareLaSfarsit(Nod** cap,Nod** coada , carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = c;
	nou->next = NULL;
	nou->prev = *coada;

	if ((*cap) == NULL) {
		*cap = *coada = nou;
		return;
	}

	(*coada)->next = nou;
	*coada = nou;
	
}

carte initCarte(const char* titlu , int nrPagini , float pret)
{
	carte c;
	c.nrPag = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy(c.titlu, titlu);

	return c;

}


void afisareCarte(carte carte)
{
	printf("\nTitlu: %s, Numar pagini: %d, Pret: %.2f", carte.titlu, carte.nrPag, carte.pret);
}

void afisareListaCarti(Nod* cap)
{

	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void afisareInversaListaCarti(Nod* coada)
{

	while (coada != NULL) {
		afisareCarte(coada->info);
		coada = coada->prev;
	}
}

void afisareCarteListaCircularaCarti(Nod* cap) {
	if (!cap) {
		return;
	}
	Nod* aux = cap;
	afisareCarte(cap->info);
	cap = cap->next;
	while (aux != cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	};

}


void afisareCarteListaCircularaCarti2(Nod* cap) {
	if (!cap) {
		return;
	}
	Nod* aux = cap;
	do {
		afisareCarte(cap->info);
		cap = cap->next;
	} while (aux != cap);

}


float pretMaxim(Nod* cap) {
	if (!cap) {
		return;
	}
	float pretMax = 0;
	Nod* aux = cap;
	do {
		if (pretMax < cap->info.pret) pretMax = cap->info.pret;
		afisareCarte(cap->info);
		cap = cap->next;
	} while (aux != cap);

	return pretMax;

}
void dezalocare(Nod** cap , Nod** coada) {
	while ((*cap) != NULL) {
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*coada = NULL;
}
int main()
{
	Nod* cap = NULL;
	Nod* coada = NULL;
	inserareLaSfarsit(&cap, &coada, initCarte("Micul Print" , 132 , 35.2));
	inserareLaSfarsit(&cap,&coada, initCarte("Nuntatsii" , 122 , 46.9));
	inserareLaSfarsit(&cap,&coada, initCarte("Confess" , 126 , 32.5));
	afisareInversaListaCarti(coada);
	printf("\n%.2f\n" , pretMediuCarte(coada));
	//dezalocare(&cap , &coada);
	coada->next = cap;
	cap->prev = coada;

	afisareCarteListaCircularaCarti(cap);

	printf("\n%.2f pret max\n", pretMaxim(cap));

	return 0;
}