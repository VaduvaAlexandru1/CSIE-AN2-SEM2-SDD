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

/// <summary>
/// Deleting an element from a stack or a queue
/// </summary>
/// <param name="head"> : The head of stack or queue</param>
void Pop(Nod** head) {
	if (isEmpty(*head)) return;

	Nod* aux = *head;
	*head = (*head)->next;

	free(aux->carte.titlu);
	free(aux);
}
//gave an alias to pop as dequeue because in the scope of a stack and a queue these operations have the save code
#define Dequeue Pop

/// <summary>
/// Get a look at the info from head without deleting
/// </summary>
/// <param name="head"> : The head of the list (stack/queue)></param>
/// <returns>The info struct (Carte in this case)</returns>
Carte Peek(Nod* head) {
	if (isEmpty(head)) {
		printf("Stack gol!\n");
		exit(1);
	}
	return head->carte;
}
/// <summary>
/// Prints a list
/// </summary>
/// <param name="head"> : The head of the list</param>
void print(Nod* head) {
	while (head != NULL) {
		outCarte(Peek(head));
		head = head->next;
	}
}

// stack functions

/// <summary>
/// Adding an element into a stack
/// </summary>
/// <param name="stack"> : The head of the stack></param>
/// <param name="c"> : Info to add</param>
void Push(Nod** stack , Carte c) {
	Nod* newHead = (Nod*)malloc(sizeof(Nod));
	newHead->carte = c;
	newHead->next = *stack;
	*stack = newHead;
}

//queue functions

/// <summary>
/// Adding an element into a queue
/// </summary>
/// <param name="queue"> : The head of the queue</param>
/// <param name="c"> : Info to add</param>
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
	printf("---------STACK TESTING---------");
	Nod* stack = NULL;

	Push(&stack, initCarte("Robinson Crusoe", 250, 30.4));
	Push(&stack, initCarte("Antreneaza ti creierul", 551, 85.9));

	Pop(&stack);

	print(stack);
	printf("\n---------QUEUE TESTING---------");

	Nod* queue = NULL;

	Enqueue(&queue, initCarte("Robinson Crusoe", 250, 30.4));
	Enqueue(&queue, initCarte("Antreneaza ti creierul", 551, 85.9));

	Dequeue(&queue);

	print(queue);
}