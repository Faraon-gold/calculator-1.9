#include "math.h"

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

// результат числового выражения для стека
float numb_s(char sign, float x, float y) {
	float res, f, S;
	switch (sign) {
	case '+':
		res = x + y;
		return res;
		break;
	case '-':
		res = x - y;
		return res;
		break;
	case '*':
		res = x * y;
		return res;
		break;
	case '/':
		if (y != 0)
			res = x / y;
		return res;
		break;
	case '!':
		f = 1;
		for (int i = 1; i <= x; i++) {
			f *= i;
		}
		res = f;
		return res;
	case '^':
		f = 1;
		S = 1;
		for (int i = 1; i <= y; i++) {
			S *= x;
		}
		res = S;
		return res;
	}
	return x;
	return y;
}


//результат числового выражения для списков
float* numb_l(char sign, float *x, float *y) {
	float f, S, *res_numb;
	res_numb = malloc(sizeof(float));
	switch (sign) {
	case '+':
		res_numb[0] = x[0] + y[0];
		return res_numb;
	case '-':
		res_numb[0] = x[0] - y[0];
		return res_numb;
	case '*':
		res_numb[0] = x[0] * y[0];
		return res_numb;
	case '/':
		if (y != 0) {
			res_numb[0] = x[0] / y[0];
			return res_numb;
		} else {
			return 0;
		}
	case '!':
		f = 1;
		for (int i = 1; i <= x[0]; i++) {
			f *= i;
		}
		res_numb[0] = f;
		return res_numb;
	case '^':
		f = 1;
		S = 1;
		for (int i = 1; i <= y[0]; i++) {
			S *= x[0];
		}
		res_numb[0] = S;
		return res_numb;
	}
	return x;
	return y;
	free(x);
	free(y);
	free(res_numb);
}


// результат векторного выражения для списков
float* vect_l(char sign, int size, float *a, float *b) {
	float *res_vect;
	switch (sign) {
	case '+':
		res_vect = malloc(size * sizeof(float));
		for (int i = 0; i < size; i++) {
			res_vect[i] = a[i] + b[i];
		}
		return res_vect;

	case '-':
		res_vect = malloc(size * sizeof(float));
		for (int i = 0; i < size; i++) {
			res_vect[i] = a[i] - b[i];
		}
		return res_vect;

	case '*':
		res_vect = malloc(sizeof(float));
		res_vect[0] = 0;
		for (int i = 0; i < size; i++) {
			res_vect[0] += a[i] * b[i];
		}
		return res_vect;
	}
	return a;
	return b;
	free(a);
	free(b);
	free(res_vect);
}

double factorial(int f) {
	double fact = 1;

	for (int i = 2; i <= f; i++)
		fact *= i;

	return fact;
}

// результат числового выражения для очереди
void numbers_q(FILE *output, char *s, char sign) {
	int index = 3;

	if (sign == '!') {
		int x = read_int(s, &index);
		fprintf(output, "%.0lf\n", factorial(x));
		return;
	}

	double x = read_double(s, &index);
	double y = read_double(s, &index);

	if (sign == '+') {
		fprintf(output, "%.2lf\n", x + y);
	} else if (sign == '-') {
		fprintf(output, "%.2lf\n", x - y);
	} else if (sign == '*') {
		fprintf(output, "%.2lf\n", x * y);
	} else if (sign == '/') {
		if (y == 0)
			fprintf(output, "division by zero\n");
		else
			fprintf(output, "%.2lf\n", (double) x / y);
	} else if (sign == '^') {

		float S = 1;
		for (int i = 1; i <= y; i++) {
			S *= x;
		}
		fprintf(output, "%.2lf\n", S);
	}

	else {
		fprintf(output, "unknown operation '%c'\n", sign);
	}
}


// результат векторного выражения для очереди
void vectors_q(FILE *output, char *s, char sign) {
	int index = 3;
	int n = read_int(s, &index); // размерность вектора

	double *v1 = (double*) malloc(n * sizeof(double));
	double *v2 = (double*) malloc(n * sizeof(double));

	// считываем вектора
	for (int i = 0; i < n; i++)
		v1[i] = read_double(s, &index);

	for (int i = 0; i < n; i++)
		v2[i] = read_double(s, &index);

	if (sign == '*') {
		double res = 0;

		for (int i = 0; i < n; i++)
			res += v1[i] * v2[i];

		fprintf(output, "%.2lf\n", res);
	} else if (sign == '+' || sign == '-') {
		if (sign == '+') {
			for (int i = 0; i < n; i++)
				fprintf(output, "%.2lf ", v1[i] + v2[i]);
			fprintf(output, "\n");
		} else {
			for (int i = 0; i < n; i++)
				fprintf(output, "%.2lf ", v1[i] - v2[i]);
			fprintf(output, "\n");
		}

	} else {
		fprintf(output, "unknown operation '%c'\n", sign);
	}

	free(v1);
	free(v2);
}

// вычисление значения выражения для очереди
void calc_q(FILE *input, char *s) {
	char sign = s[0];
	char op = s[2];

	if (op == 'c') {
		numbers_q(input, s, sign);
	} else if (op == 'v') {
		vectors_q(input, s, sign);
	}
}
