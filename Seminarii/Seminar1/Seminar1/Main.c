#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>

void interschimbare(int *nr1, int *nr2) {
	int aux = *nr1;
	*nr1 = *nr2;
	*nr2 = aux;
}

void main() {
	int an = 2026;
	char litera = 'b';
	float inaltime = 1.71;

	printf("An: %d , litera : %c , inaltime : %.2f", an, litera, inaltime);

	char prenume[6];

	prenume[0] = 82;
	prenume[1] = 97;
	prenume[2] = 114;
	prenume[3] = 101;
	prenume[4] = 115;
	prenume[5] = 0;

	printf("\nPrenume : %s", prenume);

	char* strada = (char*)malloc(sizeof(char) * (strlen("Mihai Eminescu") + 1));
	strcpy(strada, "Mihai Eminescu");

	printf("\nStrada : %s", strada);
	
	free(strada);

	int nr1 = 10;
	int nr2 = 7;

	interschimbare(&nr1, &nr2);
	printf("\nNr1 : %d , Nr2 : %d", nr1, nr2);

}