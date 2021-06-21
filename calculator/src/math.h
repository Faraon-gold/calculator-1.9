#ifndef MATH_H_
#define MATH_H_
#include <stdio.h>

float numb_s(char sign, float x, float y);
float* numb_l(char sign, float *x, float *y);
float* vect_l(char sign, int size, float *a, float *b);
double factorial(int f);
void numbers_q(FILE *output, char *s, char sign);
void vectors_q(FILE *output, char *s, char sign);
void calc_q(FILE *input, char *s);


#endif /* MATH_H_ */
