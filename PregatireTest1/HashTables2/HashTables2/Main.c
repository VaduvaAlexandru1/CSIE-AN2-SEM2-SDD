#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Nod Nod;
typedef struct HashTable HashTable;

typedef struct Persoana {
	char* nume;
	int varsta;
	float salariu;
}Persoana;

struct Nod {
	Persoana info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int size;
};

Persoana citirePers(FILE* fisier) {
	char buffer[50];
	Persoana p;
	fscanf(fisier, "%s %d %f", buffer, &p.varsta, &p.salariu);

	p.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));

	strcpy(p.nume, buffer);

	return p;
}

void inserareLaFinal(Nod** cap , Persoana p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
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

void afisarePersoana(Persoana p) {
	printf("Nume : %s , Varsta : %d , Salariu : %.2f \n", p.nume, p.varsta, p.salariu);
}

int hash(int size , int varsta) {
	return varsta % size;
}

void inserareHashTable(HashTable ht, Persoana p) {
	if (ht.size <= 0) return;

	int pozitie = hash(ht.size, p.varsta);
	if (pozitie >= 0 && pozitie < ht.size) {
		inserareLaFinal(&(ht.vector[pozitie]), p);
	}
}

void dezalocareLista(Nod** cap) {
	if (*cap == NULL) {
		return;
	}

	while (*cap != NULL) {
		free((*cap)->info.nume);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void dezalocare(HashTable ht) {
	for (int i = 0; i < ht.size; ++i) {
		dezalocareLista(&(ht.vector[i]));
	}
	free(ht.vector);
}
void afisareLista(Nod* cap) {
	if (cap == NULL) {
		printf("Lista e goala\n");
		return;
	}

	Nod* aux = cap;
	while (aux != NULL) {
		afisarePersoana(aux->info);
		aux = aux->next;
	}
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.size; ++i) {
		printf("POZITIE : %d\n", i);
		afisareLista(ht.vector[i]);
	}
}

Persoana* ListaSimplaToVector(Nod* cap , int nrPersoane) {
	Persoana* pers;
	pers = (Persoana*)malloc(sizeof(Persoana) * nrPersoane);
	int pozitie = 0;

	Nod* aux = cap;
	while (aux != NULL) {
		//executie cod pe fiecare nod
		pers[pozitie].varsta = aux->info.varsta;
		pers[pozitie].salariu = aux->info.salariu;
		pers[pozitie].nume = (char*)malloc(sizeof(char) * (strlen(aux->info.nume) + 1));
		strcpy(pers[pozitie].nume, aux->info.nume);
		pozitie++;

		aux = aux->next;
	}

	return pers;

}

int main() {

	//HashTable h1;
	//int dim = 5;
	//h1.size = dim;

	//h1.vector = (Nod**)malloc(sizeof(Nod*) * h1.size);
	//for (int i = 0; i < h1.size; ++i) {
	//	h1.vector[i] = NULL;
	//}


	//afisareHashTable(h1);
	//dezalocare(h1);
	//fclose(fisier);

	Nod* cap = NULL;
	FILE* fisier = fopen("persoane.txt", "r");
	if (!fisier) {
		printf("Eroare la deschidere");
		return -1;
	}

	int nrPeroane = 0;
	if (fscanf(fisier, "%d", &nrPeroane) != 1) {
		printf("Eroare la citire");
	}
	for (int i = 0; i < nrPeroane; ++i) {
		inserareLaFinal(&cap, citirePers(fisier));
	}

	printf("LISTA SIMPLU INLANTUITA\n");
	afisareLista(cap);
	printf("CONVERSIE IN VECTOR\n");
	Persoana* pers = ListaSimplaToVector(cap , nrPeroane);
	for (int i = 0; i < nrPeroane; ++i) {
		afisarePersoana(pers[i]);
	}

	fclose(fisier);


	return 0;
}