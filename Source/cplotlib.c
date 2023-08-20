#include "cplotlib.h"

const Color colors[COLORS_AMOUNT] = {
        BLUE, GREEN, PURPLE, RED,
        BROWN, PINK, BLACK,GRAY,
        BEIGE, SKYBLUE, MAROON, VIOLET
};

void init(void)
{
    InitWindow(WIDTH, HEIGHT, "@eesuck");
    SetTargetFPS(NO_ANIMATION_FPS);
}

void plot(const double start, const double end, size_t functions_amount, function_type* functions[])
{
    init();

    double* X = linspace(start, end, ARRAY_SIZE);
    double* Y[functions_amount];

    for (size_t function_index = 0; function_index < functions_amount; function_index++)
    {
        Y[function_index] = apply_to_array(X, ARRAY_SIZE, functions[function_index]);
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t function_index = 0; function_index < functions_amount; function_index++)
        {
            for (size_t point = 0; point < ARRAY_SIZE; point++)
            {
                DrawPixel((int)X[point] + WIDTH / 2,
                          (int)-Y[function_index][point] + HEIGHT / 2,
                          colors[function_index % COLORS_AMOUNT]);

                DrawPixel((int)X[point] + WIDTH / 2,
                          (int)-Y[function_index][point] + HEIGHT / 2 + 1,
                          colors[function_index % COLORS_AMOUNT]);
            }
        }

        EndDrawing();
    }
}

void circle(const double* X, const double* Y, const double* R, size_t circles_amount)
{
    init();

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t circle_index = 0; circle_index < circles_amount; circle_index++)
        {
            DrawCircleLines(
                    (int)(WIDTH / 2.0 + X[circle_index]),
                    (int)(HEIGHT / 2.0 - Y[circle_index]),
                    (float)R[circle_index],
                    colors[circle_index % COLORS_AMOUNT]);

            DrawCircleLines(
                    (int)(WIDTH / 2.0 + X[circle_index]),
                    (int)(HEIGHT / 2.0 - Y[circle_index]),
                    (float)(R[circle_index] + 1.0),
                    colors[circle_index % COLORS_AMOUNT]);
        }

        EndDrawing();
    }

}

void scatter(const double *X, const double *Y, size_t amount)
{
    init();

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t point = 0; point < amount; point++)
        {
            DrawCircle((int)X[point], HEIGHT - Y[point], 3, BASIC_COLOR);
        }

        EndDrawing();
    }
}

void bar(const double *Y, size_t amount)
{
    init();

    double space = (float)WIDTH / (float)amount;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t point = 0; point < amount; point++)
        {
            DrawRectangle(
                    (int)(space / 10 + space * point),
                    HEIGHT - Y[point],
                    (int)(space * 0.8),
                    (int)Y[point],
                    BASIC_COLOR);
        }

        EndDrawing();
    }
}

void histogram(const double *X, const double *Y, size_t amount)
{
    assert(0 && "TODO: not implemented");
}