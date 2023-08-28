#ifndef CPLOTLIB_H
#define CPLOTLIB_H

#include <assert.h>

#include "raylib.h"
#include "numc.h"

#define WIDTH 800
#define HEIGHT 600
#define NO_ANIMATION_FPS 30
#define ARRAY_SIZE 10000
#define COLORS_AMOUNT 12
#define BASIC_COLOR CLITERAL(Color) { 72, 135, 184, 255 }

void init(void); // initialize the raylib window
void plot(double start, double end, size_t functions_amount, function_type* functions); // draws a plots of given number of functions
void circle(const double* X, const double* Y, const double* R, size_t circles_amount); // draws a circles with centers in (x_i, y_i) and radius r_i
void scatter(const double* X, const double* Y, size_t amount); // draws a scatter plot
void bar(const double* Y, size_t amount); // draws a bar plot
void histogram(const double* X, const double* Y, size_t amount); // draws a histogram

#endif // CPLOTLIB_H
