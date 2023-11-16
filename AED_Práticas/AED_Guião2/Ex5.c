#include <stdio.h>
#include <math.h>

// The coefficients of a degree n polynomial
// are stored in an array p of size (n + 1)
// p[0] is the coefficient of the largest degree term
// p[n] is the coefficient of the zero-degree term
// Display a polynomial
// Pre-Conditions: coef != NULL and degree >= 0
// Example of produced output:
// Pol(x) = 1.000000 * x^2 + 4.000000 * x^1 + 1.000000

void DisplayPol(double* coef, size_t degree) {
  if (coef == NULL || degree < 0) {
    printf("Invalid input: coef is NULL or degree is zero.\n");
    return;
  }

  int count=0;
  printf("Pol(x) = ", degree);
  for (size_t i = 0; i <= degree; i++) {
    printf("%.6lf * x^%zu", coef[i],degree-count);
    count+=1;
    if (i != degree) {
      printf(" + ");
    }
  }
  printf("\n");
}

// Compute the value of a polynomial using Horner’s method:
// Pre-Conditions: coef != NULL and degree >= 0
double ComputePol(double* coef, size_t degree, double x) {
  if (coef == NULL || degree<0) {
    return -1;
  }

  double result = coef[0];
  for (size_t i = 1; i <= degree; i++) {
    result = result * x + coef[i];
  }
  return result;
}

// Test example:
// Pol(x) = 1.000000 * x^2 + 4.000000 * x^1 + 1.000000
// Pol(2.000000) = 13.000000
// Compute the real roots, if any, of a second-degree polynomial
// Pre-Conditions: coef != NULL and degree == 2 and coef[0] != 0
// Pre-Conditions: root_1 != NULL and root_2 != NULL
// Return values: 0 -> no real roots
// 1 -> 1 real root with multiplicity 2
// 2 -> 2 distinct real roots
// The computed root values are returned via the root_1 and root_2
// pointer arguments
// Assign 0.0 to the *root_1 and *root_2 if there are no real roots
unsigned int GetRealRoots(double* coef, size_t degree, double* root_1, double* root_2) {
  if (degree != 2 || coef[0] == 0) {
    *root_1 = *root_2 = 0.0;
    return 0;
  }

  double discriminant = coef[1] * coef[1] - 4 * coef[0] * coef[2];
  if (discriminant < 0) {
    *root_1 = *root_2 = 0.0;
    return 0;
  } else if (discriminant == 0) {
    *root_1 = *root_2 = -coef[1] / (2 * coef[0]);
    return 1;
  } else {
    *root_1 = (-coef[1] + sqrt(discriminant)) / (2 * coef[0]);
    *root_2 = (-coef[1] - sqrt(discriminant)) / (2 * coef[0]);
    return 2;
  }
}

int main() {
  double coef[] = {1.0, 4.0, 1.0};
  size_t degree = 2;
  double x = 2.0;
  double root_1, root_2;

  DisplayPol(coef, degree);
  printf("Pol(%lf) = %lf\n", x, ComputePol(coef, degree, x));

  unsigned int num_roots = GetRealRoots(coef, degree, &root_1, &root_2);
  if (num_roots == 0) {
    printf("No real roots.\n");
  } else if (num_roots == 1) {
    printf("1 real root with multiplicity 2: %lf\n", root_1);
  } else {
    printf("2 distinct real roots: %lf, %lf\n", root_1, root_2);
  }

  return 0;
}

