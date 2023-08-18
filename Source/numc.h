#ifndef NUMC_H
#define NUMC_H

#include <assert.h>

#include "math.h"
#include "malloc.h"
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600
#define NO_ANIMATION_FPS 30
#define ARRAY_SIZE 10000
#define COLORS_AMOUNT 12
#define EPSILON 1E-3
#define BASIC_COLOR CLITERAL(Color) { 72, 135, 184, 255 }

typedef double function_type(double x);

double* linspace(double start, double end, unsigned int amount); // returns a linear spaced segment
double* use_to_array(const double* array, unsigned int length, function_type function); // calls a unary function to each number in an array
void init(void); // initialize the raylib window
void plot(double start, double end, unsigned int functions_amount, function_type* functions[]); // draws a plots of given number of functions
void circle(const double* X, const double* Y, const double* R, unsigned int circles_amount); // draws a circles with centers in (x_i, y_i) and radius r_i
void scatter(const double* X, const double* Y, unsigned int amount); // draws a scatter plot
void bar(const double* Y, unsigned int amount); // draws a bar plot
void histogram(const double* X, const double* Y, unsigned int amount); // draws a histogram

#endif // NUMC_H
