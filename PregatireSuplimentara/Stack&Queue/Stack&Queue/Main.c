#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
}Carte;

typedef struct Nod{
	Nod* next;
	Carte carte;
};

Carte initCarte(const char* titlu , int nrPagini , float pret) {
	Carte c;
	c.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(c.titlu, titlu);
	c.nrPagini = nrPagini;
	c.pret = pret;

	return c;
}

void outCarte(Carte c) {
	printf("\n%s , %d , %.2f", c.titlu, c.nrPagini, c.pret);
}

//common functions
int isEmpty(Nod* head) {
	return head == NULL;
}
void Pop(Nod** stack) {
	if (isEmpty(*stack)) return;

	Nod* aux = *stack;
	*stack = (*stack)->next;

	free(aux->carte.titlu);
	free(aux);
}
#define Dequeue Pop

Carte Peek(Nod* head) {
	if (isEmpty(head)) {
		printf("Stack gol!\n");
		exit(1);
	}
	return head->carte;
}

void print(Nod* head) {
	while (head != NULL) {
		outCarte(Peek(head));
		head = head->next;
	}
}

// stack functions
void Push(Nod** stack , Carte c) {
	Nod* newHead = (Nod*)malloc(sizeof(Nod));
	newHead->carte = c;
	newHead->next = *stack;
	*stack = newHead;
}

//queue functions
void Enqueue(Nod** queue , Carte c) {
	Nod* newNode = (Nod*)malloc(sizeof(Nod));
	newNode->carte = c;
	newNode->next = NULL;

	if (isEmpty(*queue))
	{
		*queue = newNode;
	}
	else {
		Nod* aux = *queue;
		while (aux->next != NULL) aux = aux->next;
		aux->next = newNode;
	}

}

int main() {
	printf("---------IMPLEMENTARE STACK---------");
	Nod* stack = NULL;

	Push(&stack, initCarte("Robinson Crusoe", 250, 30.4));
	Push(&stack, initCarte("Antreneaza ti creierul", 551, 85.9));

	Pop(&stack);

	print(stack);
	printf("\n---------IMPLEMENTARE QUEUE---------");

	Nod* queue = NULL;

	Enqueue(&queue, initCarte("Robinson Crusoe", 250, 30.4));
	Enqueue(&queue, initCarte("Antreneaza ti creierul", 551, 85.9));

	Dequeue(&queue);

	print(queue);
}