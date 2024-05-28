// Numeric Analysis Assignment 2
// Part 2 finding the Lagrange Cubic Interpolating Polynomial for the given data set
// Name: Emir Ayar
// Number: 200030473
// Educating: Mechatrýnics Engineering
// Date: 26.05.2024

#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 100

// Function to calculate the Lagrange basis polynomial
double L(int i, double x, double x_vals[], int n) {
    double result = 1.0;
    for (int j = 0; j < n; j++) {
        if (i != j) {
            result *= (x - x_vals[j]) / (x_vals[i] - x_vals[j]);
        }
    }
    return result;
}

// Function to calculate the Lagrange interpolation polynomial at point x
double lagrangeInterpolation(double x, double x_vals[], double y_vals[], int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += y_vals[i] * L(i, x, x_vals, n);
    }
    return result;
}

int main() {
    int n;
    double x_vals[MAX_POINTS], y_vals[MAX_POINTS];
    double x;

    printf("Enter the number of data points (minimum 4 for cubic interpolation): ");
    scanf("%d", &n);

    if (n < 4) {
        printf("Error: At least 4 data points are required for cubic interpolation.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter x%d: ", i);
        scanf("%lf", &x_vals[i]);
        printf("Enter y%d: ", i);
        scanf("%lf", &y_vals[i]);
    }

    printf("Enter the x value for interpolation: ");
    scanf("%lf", &x);

    double interpolated_value = lagrangeInterpolation(x, x_vals, y_vals, n);
    printf("\nInterpolated value at x = %lf: %lf\n", x, interpolated_value);

    // Generate data points for plotting
    FILE *dataFile = fopen("interpolated_data.txt", "w");
    if (dataFile == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    double x_step = (x_vals[n-1] - x_vals[0]) / 100.0;  // Adjust the step for a better resolution
    for (double x_plot = x_vals[0]; x_plot <= x_vals[n-1]; x_plot += x_step) {
        double y_plot = lagrangeInterpolation(x_plot, x_vals, y_vals, n);
        fprintf(dataFile, "%lf %lf\n", x_plot, y_plot);
    }

    fclose(dataFile);

    // Create Gnuplot script
    FILE *gnuplotScript = fopen("plot_script.plt", "w");
    if (gnuplotScript == NULL) {
        printf("Error opening Gnuplot script file for writing.\n");
        return 1;
    }

    fprintf(gnuplotScript, "plot 'interpolated_data.txt' with lines\n");
    fprintf(gnuplotScript, "pause -1 \"Press any key to continue\"\n");

    fclose(gnuplotScript);

    return 0;
}

