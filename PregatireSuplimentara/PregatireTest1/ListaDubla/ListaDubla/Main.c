#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Tren {
	char* ruta;
	int numarVagoane;
	float pretBilet;
}Tren;
//[*ruta , nrVag , pretBilet][ ][ ][][]][]

struct Nod {
	Tren info;
	Nod* next;
	Nod* prev;
};

Tren citireTren(FILE* fisier) {

	//fisierul nu trebuie verificati obligatoriu la test 
	//este doar un good practice
	Tren tNUll = { NULL , 0 , 0.0 };

	if (!fisier) {
		printf("Fisier invalid");
		return tNUll;
	}

	Tren t1;
	char buffer[30];

	fscanf(fisier, "%s %d %f", buffer, &(t1.numarVagoane), &(t1.pretBilet));

	t1.ruta = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(t1.ruta, buffer);

	return t1;

}

void afisareTren(Tren t1) {
	printf("Ruta : %s , Numar Vagoane : %d , Pret bilet : %.2f\n", t1.ruta, t1.numarVagoane, t1.pretBilet);
}

void inserareLaInceput(Nod** cap , Nod** coada, Tren t1) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));//"desenam nodul in memorie"
	nou->info = t1; // shallow copy util

	nou->next = *cap;
	nou->prev = NULL;

	if (*cap == NULL) {
		*cap = *coada = nou;
		return;
	}

	(*cap)->prev = nou;

	*cap = nou;
}

void inserareLaFinal(Nod** cap, Nod** coada, Tren t1) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));//"desenam nodul in memorie"
	nou->info = t1; // shallow copy util

	nou->next = NULL;
	nou->prev = *coada;

	if (*cap == NULL) {
		*cap = *coada = nou;
		return;
	}

	(*coada)->next = nou;
	*coada = nou;

}


void freeListaDubla(Nod** cap , Nod** coada) {
	if (*cap == NULL) {
		printf("Lista goala");
		return;
	}
	

	while ((*cap) != NULL) {
		free((*cap)->info.ruta);
		Nod* aux = *cap; // shalow coppy
		*cap = (*cap)->next;// trecem mai departe in lista	
		free(aux);//dezalocat vechiul cap
	}

	*coada = NULL;
}

Tren* conversieListaSimplaVector(Nod* cap, int nrTrenuri) {
	Tren* trenuri = (Tren*)malloc(sizeof(Tren) * nrTrenuri);
	int contor = 0;
	Nod* aux = cap;

	while (aux != NULL) {
		trenuri[contor].numarVagoane = (aux->info).numarVagoane;
		trenuri[contor].pretBilet = (aux->info).pretBilet;
		trenuri[contor].ruta = malloc(sizeof(char) * (strlen((aux->info).ruta) + 1));
		strcpy(trenuri[contor].ruta, (aux->info).ruta);
		contor++;
		trenuri[contor] = aux->info;
		aux = aux->next;
	}

	return trenuri;
}

void afisLista(Nod* cap) {
	if (cap == NULL) {
		printf("Lista este goala\n");
		return;
	}

	Nod* aux = cap;
	while (aux != NULL) {
		afisareTren(aux->info);
		aux = aux->next;
	}
}

void afisareInversa(Nod* coada) {
	if (coada == NULL) {
		printf("Lista este goala\n");
		return;
	}

	Nod* aux = coada;
	while (aux != NULL) {
		afisareTren(aux->info);
		aux = aux->prev;
	}
}

void templateParcurgereListaCirculara(Nod* cap){
	if (!cap)
	{
		return;
	}
	Nod* aux = cap;
	do
	{
		//operatia care trebuie facuta , cod de executat pe fiecare nod

		cap = cap->next;

	} while (cap != aux);
}

int main() {
	int nrTrenuri = 0;
	Nod* cap = NULL;
	Nod* coada = NULL;
	
	FILE* fisier;
	fisier = fopen("trenuri.txt", "r");
	if (!fisier) {
		printf("Eroare la deschiderea fisierului\n");
		return;
	}

	if (fscanf(fisier, "%d", &nrTrenuri) != 1) {
		printf("Eroare la citire din fisier");
	}

	for (int i = 0; i < nrTrenuri; ++i) {
		inserareLaFinal(&cap,&coada, citireTren(fisier));
	}

	afisLista(cap);
	printf("---------------------------\n");
	afisareInversa(coada);

	fclose(fisier);
	freeListaDubla(&cap, &coada);

	cap->prev = coada;
	coada->next = cap;

	return 0;
}