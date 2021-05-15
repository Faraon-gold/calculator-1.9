//****************************************************************
// VITOS                Техническая справка            ver. 1.72 *
//                                                               *
// Данный код представляет собой не самый простой калькулятор.   *
// Он умеет складывать,умножать,делить,возводить в степень,      *
// вычитать числа. Берет данные из файла                         *
// Также присутствуют функции нахождения факториала.             *
//_______________________________________________________________*
// Принцип работы калькулятора с файлами!Здесь используются      *
// стеки. Было удалены векторные вычисление. Для упрощения работы*
// оставлены функции, необходимые непосредственно для задания    *
// При внесении данных из файла, необходимо в конце строки       *
// добавлять символ "n". Данные необходимо вводить в обратной    *
// польской нотации. Пример: 35 12 +                             *
//                              Программу сделал Виталий Черников*
//****************************************************************


#include <stdio.h>
#include <stdlib.h>


// Здесь мы добавляем структуру - стек

typedef struct element {
	float data;
	struct element *next;
} stack;

stack *head_stack = NULL;

void push_element(stack **head, float data);
float pop_element(stack **head);
float numb(char m, float x, float y);

int main(int argc, char *argv[]) {
	char n = 'y', str[20], t = '0';
	char in[50], out[50];
	int i = 0;
	float num, x, y;
	FILE *fin, *fan;
	while (n == 'y') {
		printf("Enter the name of the input file in the format (name.txt): \n");
		scanf(" %s", in);
		printf("Enter the name of the output file in the format (name.txt): \n");
		scanf(" %s", out);
		fin = fopen(in, "r");
		fan = fopen(out, "w");
		fprintf(fan,"$           $       $ $$$ $$$$$  $$   $$$   \n");
        fprintf(fan,"$            $     $   $    $   $  $  $     \n");
        fprintf(fan,"$$$  $  $     $   $    $    $  $    $  $    \n");
        fprintf(fan,"$ $   $        $ $     $    $   $  $    $   \n");
        fprintf(fan,"$$$  $          $     $$$   $    $$   $$$   \n");
        fprintf(fan,"\n");
        fprintf(fan,"\n");
        fprintf(fan,"Welcome to the not-so-simple calculator!\n");
        fprintf(fan,"\n");
		while (feof(fin) == 0) {
			fscanf(fin, "%c", &str[i]);
			if (str[i] == ' ') {
				if (t == '0') {
					num = strtof(str, NULL);
					push_element(&head_stack, num);
					i = 0;

				}
			} else if (str[i] == '*' || str[i] == '+' || str[i] == '-'
					|| str[i] == '/' || str[i] == '^') {
				y = pop_element(&head_stack);
				x = pop_element(&head_stack);
				push_element(&head_stack, numb(str[i], x, y));
				fprintf(fan, "%.2f  ", numb(str[i], x, y));
				t = '1';
			} else if (str[i] == 'n') {
				while (head_stack != NULL)
					pop_element(&head_stack);
				fprintf(fan, "\n");
			} else {
				t = '0';
				i = i + 1;
			}
		}

		fclose(fin);
		fclose(fan);
		printf("Do you want to continue? (y/n)");
		scanf(" %c", &n);
	}
	return 0;
}

 // Ниже представлен блок вывода, он был полностью переделан.

float numb(char m, float x, float y) {
	float w, f, S;
	switch (m) {
	case '+':
		w = x + y;
		return w;
		break;
	case '-':
		w = x - y;
		return w;
		break;
	case '*':
		w = x * y;
		return w;
		break;
	case '/':
		if (y != 0)
			w = x / y;
		return w;
		break;
	case '!':
		f = 1;
		for (int i = 1; i <= x; i++) {
			f *= i;
		}
		w = f;
		return w;
	case '^':
		f = 1;
		S = 1;
		for (int i = 1; i <= y; i++) {
			S *= x;
		}
		w = S;
		return w;
	}
	return x;
	return y;
}

void push_element(stack **head, float data) {
	stack *z = malloc(sizeof(stack));
	z->next = *head;
	z->data = data;
	*head = z;
}

float pop_element(stack **head) {
	stack *z;
	float data;
	z = *head;
	*head = (*head)->next;
	data = z->data;
	return data;
}
