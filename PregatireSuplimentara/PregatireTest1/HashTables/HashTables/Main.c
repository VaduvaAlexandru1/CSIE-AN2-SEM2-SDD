#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct HashTable HashTable;

typedef struct Tren {
	char* ruta;
	int numarVagoane;
	float pretBilet;
}Tren;
//[*ruta , nrVag , pretBilet][ ][ ][][]][]

struct Nod {
	Tren info;
	Nod* next;
};

struct HashTable {
	Nod** vector; 
	int size;
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

void inserareLaFinal(Nod** cap, Tren t1) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));//"desenam nodul in memorie"
	nou->info = t1; // shallow copy util
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
		return;
	}

	Nod* aux = *cap;
	while (aux->next != NULL) {
		aux = aux->next;
	}
	aux->next = nou;
}


void freeListaSimpla(Nod** cap) {
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

//hashTable
int hash(int nrVagoane, int size) {
	return nrVagoane % size;
}

void inserareHashTable(HashTable ht, Tren t1) {
	if (ht.size <= 0) return;

	int pozitie = hash(t1.numarVagoane, ht.size);
	if (pozitie >= 0 && pozitie < ht.size) {
		inserareLaFinal(&(ht.vector[pozitie]), t1);
	}
}

void dezalocareHash(HashTable ht) {
	for (int i = 0; i < ht.size; ++i) {
		freeListaSimpla(&(ht.vector[i]));
	}
	free(ht.vector);
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.size; ++i) {
		printf("POZITIE HASHTABLE : %d \n", i);
		afisLista(ht.vector[i]);
	}
}
int main() {
	int nrTrenuri = 0;
	FILE* fisier;
	fisier = fopen("trenuri.txt", "r");
	if (!fisier) {
		printf("Eroare la deschiderea fisierului\n");
		return;
	}

	if (fscanf(fisier, "%d", &nrTrenuri) != 1) {
		printf("Eroare la citire din fisier");
	}

	int dim = 5;
	HashTable ht1;
	ht1.size = dim;
	ht1.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; ++i) {
		ht1.vector[i] = NULL;
	}

	for (int i = 0; i < nrTrenuri; ++i) {
		
		inserareHashTable(ht1 , citireTren(fisier));
	}

	afisareHashTable(ht1);
	fclose(fisier);
	dezalocareHash(ht1);


	return 0;
}