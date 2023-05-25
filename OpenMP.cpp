#include <stdio.h>
#include <omp.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>

class Point {
public:
    double X;
    double Y;

    Point(double x, double y) {
        X = x;
        Y = y;
    }

    Point operator+(Point other) {
        return Point(X + other.X, Y + other.Y);
    }
};

double calculate(int i, int N, Point center, double radius) {
    Point point1 = center + Point(radius * cos(2 * M_PI * i / N), radius * sin(2 * M_PI * i / N));
    Point point2 = center + Point(radius * cos(2 * M_PI * (i + 1) / N), radius * sin(2 * M_PI * (i + 1) / N));
    return point1.X * point2.Y - point2.X * point1.Y;
}

void test(int threads_n) {
    omp_set_dynamic(0);
    omp_set_num_threads(threads_n);

    printf("thread count %i\n", threads_n);

    const int N = 400000000;

    double A = 0;

    clock_t start = clock();

#pragma omp parallel for reduction(+:A)
    for (int i = 0; i < N; i++)
    {
        A += calculate(i, N, Point(10, 10), 4);
    }

    clock_t end = clock();

    printf("%f\n", abs(A / 2));
    printf("time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main(int argc, char* argv[])
{
    for (int i = 1; i <= 10; i++) {
        test(i);
    }
    return 0;
}