#include <stdio.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_ieee_utils.h>

int main() {
	float x = 4096.0;
	for (int i = 0; i < 300; i++) {
		printf("%f\n", x);
		gsl_ieee_printf_float(&x);
		printf("\n");
		x /= 2;
	}
	return 0;
}
