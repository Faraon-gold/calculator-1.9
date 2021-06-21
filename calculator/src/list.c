#include <stdlib.h>
#include "list.h"

#include "math.h"

// считывание указателей, добавление чисел
float* add_numb(FILE *input, int size) {
	float *numb;
	numb = malloc(size * sizeof(float));
	for (int i = 0; i < size; i++) {
		fscanf(input, "%f", &numb[i]);
	}
	return numb;
}

// добавление элемента списка для входных данных
void add_el(struct list1 *current, FILE *input) {
	struct list1 *z = malloc(sizeof(struct list1));
	fscanf(input, " %c", &z->sign);
	fscanf(input, " %c", &z->choose);
	if (z->choose == 'v') {
		fscanf(input, " %i", &z->size);
	} else {
		z->size = 1;
	}
	if (z->sign != '!') {
		z->x = add_numb(input, z->size);
		z->y = add_numb(input, z->size);
	} else {
		z->x = add_numb(input, z->size);
		z->y = NULL;
	}
	z->next = NULL; // последний элемент списка
	current->next = z; // переустановка указателя
}

// добавление элемента списка для выходных данных
void res_add_el(struct list2 *res_current, struct list1 *current) {
	struct list2 *z_res = malloc(sizeof(struct list1));
	if (current->choose == 'v') {
		z_res->res = vect_l(current->sign, current->size, current->x,
				current->y);
	} else {
		z_res->res = numb_l(current->sign, current->x, current->y);
	}
	z_res->res_next = NULL;
	res_current->res_next = z_res;
}
