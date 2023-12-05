#include <stdio.h>
#include <stdlib.h>

struct ll_node {
	int first;
	struct ll_node* rest;
};

void copy(char*, char*);
void prepend(struct ll_node** lst, int value);
void free_ll(struct ll_node**);

int main() {
//	printf("%d\n", sizeof(int));
//	int a = 3;
//	printf("%p\n", &a);
//	int b = 4;
//	printf("%p\n", &b);
//	int c = 6;
//	printf("%p\n", &c);
//
//	int* p, *q;
//	printf("sizeof p: %d\n", sizeof(p));
// 	printf("%p\n%p\n", &p, &q);
// 	
// 	printf("\n\n\n\n");
//	int* array = (int*)malloc(sizeof(int) * 3);
//	printf("%p\n", array);
//	printf("%p\n", &array);
//	
//	a = a ^ b;
//	b = a ^ b;
//	a = a ^ b;
//	printf("%d %d\n", a, b);
//	
//	char* source = (char*) malloc(sizeof(char) * 4);
//	source = "here";
//	char* cmpo = (char*) malloc(sizeof(char) * 4);
//	printf("before: %s\n", cmpo);
//	copy(source, cmpo);
//	printf("after: %s\n", cmpo);

// char* s = "string";
//	printf("%p\n", s);
//	char s1[7] = "string";
//	printf("%p\n", s1);

	struct ll_node* newList = (struct ll_node*) malloc(sizeof(struct ll_node));
	newList->first = 3;
	newList->rest = NULL;
	prepend(&newList, 54);
	printf("%d\n", newList->first);
	printf("%d\n", newList->rest->first);
	free_ll(&newList);
	printf("%p\n", newList);
	return 0;
}

void copy(char* s, char* d) {
	while (*d++ = *s++);
}

void prepend(struct ll_node** lst, int value) {
	struct ll_node* tmp = (struct ll_node*) malloc(sizeof(struct ll_node));
	tmp->first = value;
	tmp->rest = (*lst);
	(*lst) = tmp;
}

void free_ll(struct ll_node** lst) {
	if (*lst) {
		free_ll(&((*lst)->rest));
		free(*lst);
	}
	*lst = NULL;
}
