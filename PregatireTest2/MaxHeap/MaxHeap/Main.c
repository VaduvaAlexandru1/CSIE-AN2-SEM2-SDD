#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Persoana {
	char* nume;
	int id;
	int varsta;
	float salariu;
}Persoana;

typedef struct MaxHeap {
	Persoana* vector;
	int size;
}MaxHeap;

Persoana initPersoana(int id, const char* nume, int varsta, float salariu) {
	Persoana pers;
	pers.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(pers.nume, nume);
	pers.id = id;
	pers.varsta = varsta;
	pers.salariu = salariu;

	return pers;
}

void afisarePersoana(Persoana pers) {
	printf("\nNume : %s , ID : %d , Varsta : %d , Pret : %.2f", pers.nume, pers.id, pers.varsta, pers.salariu);
}

void maxHeapify(MaxHeap maxHeap, int index) {
	//daca heap ul este gol nu avem la ce face heapify
	if (maxHeap.size <= 0) return;

	// vrem sa vedem care este maximul radacina , frunza din dreapta sau frunza din stanga
	int pozMax = index;
	int pozSt = 2 * index + 1;
	int pozDr = 2 * index + 2;

	//aici aflam care e maximul
	if (pozSt < maxHeap.size && maxHeap.vector[pozMax].id < maxHeap.vector[pozSt].id) pozMax = pozSt;
	if (pozDr < maxHeap.size && maxHeap.vector[pozMax].id < maxHeap.vector[pozDr].id) pozMax = pozDr;

	//daca frunza este mai mare ca radacina interschimbam
	if (pozMax != index) {
		Persoana aux = maxHeap.vector[pozMax];
		maxHeap.vector[pozMax] = maxHeap.vector[index];
		maxHeap.vector[index] = aux;

		// inaltimea maxima este size/2 -1 , facem heapify recursiv
		if (pozMax <= maxHeap.size / 2 - 1) maxHeapify(maxHeap, pozMax);
	}

}

void extragerePersoanaMaxHeap(MaxHeap* heap, Persoana* pers) {
	*pers = initPersoana(
		heap->vector[0].id,
		heap->vector[0].nume,
		heap->vector[0].varsta,
		heap->vector[0].salariu
	);

	Persoana pers = heap->vector[0];
	heap->vector[0] = heap->vector[heap->size - 1];
}


int main() {
	return 0;
}