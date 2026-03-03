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
	carte info;
	Nod* next;
};

void inserareLaInceput(Nod** cap , carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = *cap;
	*cap = nou;
}

float pretMediuCarte(Nod* cap) {
	int nrCarti = 0;
	float sumaPreturi = 0;
	while (cap != NULL) {
		sumaPreturi += cap->info.pret;
		nrCarti++;
		cap = cap->next;
	}

	return nrCarti != 0 ? sumaPreturi / nrCarti : 0;
}

void inserareLaSfarsit(Nod** cap, carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	if ((*cap) == NULL)
		*cap = nou;
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

carte citireCarte(FILE* f)
{
	char buffer[30];
	carte c;
	fscanf(f, "%s %d %f", buffer, &c.nrPag, &c.pret);
	//dereferentiere apoi accesare, adresa caracteristicii, cele doua sunt echivalente
	c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(c.titlu, buffer);

	return c;

}
Nod* citireListaCarti(const char* numeFis)
{
	FILE* f = fopen(numeFis, "r");
	if (!f)
	{
		printf("\nEroare la deschiderea fisierului!");
		return NULL;
	}

	Nod* cap = NULL;
	
	inserareLaSfarsit(&cap, citireCarte(f));
	inserareLaSfarsit(&cap, citireCarte(f));
	inserareLaSfarsit(&cap, citireCarte(f));

	fclose(f);
	return cap;
	
}

char* titluCriteriu(Nod* cap) {
	while (cap != NULL) {
		if (cap->info.pret == 46.9) {
			char* copie = (char*)malloc(strlen(cap->info.titlu) + 1);
			if (copie != NULL) {
				strcpy(copie, cap->info.titlu);
			}
			return copie;
		}
		cap = cap->next;
	}


	return NULL;
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
void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}
int main()
{
	Nod* cap = citireListaCarti("carti.txt");
	afisareListaCarti(cap);
	printf("\nPretul mediu pentru o carte este %.2f lei", pretMediuCarte(cap));
	printf("\nTitlul carti cu pretul 46.9 lei este %s", titluCriteriu(cap));
	dezalocare(&cap);
	return 0;
}