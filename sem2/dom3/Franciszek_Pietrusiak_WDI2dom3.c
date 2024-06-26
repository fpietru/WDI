/*
	Franciszek Pietrusiak 458987
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int wart;
	struct Node *next;
} Node, *list;

void push(list *h, int a) {
	list u;
	u = (Node*)malloc(sizeof(Node));
	u->wart = a;
	u->next = *h;
	*h = u;
}

int size(list h) {
	int res = 0;
	while (h != NULL) {
		res++;
		h = h->next;
	}
	return res;
}

void print(list h) {
	while (h != NULL) {
		printf("%d ", h->wart);
		h = h->next;
	}
	printf("\n");
}

void wczytaj(list *h) {
	int a;
	while (scanf("%d", &a) > 0)
		push(h, a);
}


// Funkcja split dzieli jedną listę na dwie listy o prawie równej długości
void split(list *h, list *l2) {
	list pocz = *h;
	int n = size(*h);
	for (int i=(!(n&1)); i<n/2; i++) {
		*h = (*h)->next;
	}
	*l2 = (*h)->next;
	(*h)->next = NULL;
	*h = pocz;
}

// Przeszczepia Node'a z listy l1 i wszczepia go na poczatek listy l2
void przeszczep(list *l1, list *l2) {
	list u = *l1;
	(*l1) = u->next;
	u->next = *l2;
	(*l2) = u;
}

// Funkcja merge łączy dwie posortowane listy (h i l2) w jedną, również posortowaną listę i ją zwraca
list merge(list h, list l2) {
	Node res_pocz;
	list res = &res_pocz;
	res->next = NULL;
	while (1) {
		if (h == NULL) {
			res->next = l2;
			break;
		}
		else if (l2 == NULL) {
			res->next = h;
			break;
		}
		if (h->wart <= l2->wart) przeszczep(&h, &(res->next));
		else przeszczep(&l2, &(res->next));
		res = res->next;
	}
	return (res_pocz.next);
}

// Funkcja MergeSort sortuje (i modyfikuje) listę h
void MergeSort(list *h) {
	if (size(*h) == 1) return;
	list h2 = NULL;
	split(h, &h2);
	MergeSort(h);
	MergeSort(&h2);
	(*h) = merge(*h, h2);
}

int main () {
	list head = NULL;
	
	wczytaj(&head);
	MergeSort(&head);
	print(head);
	
	return 0;
}
