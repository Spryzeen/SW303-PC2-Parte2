#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void contar_vocales(const char* texto, int* vocales, int* consonantes, int* digitos, int* otros);

int main(void) {
	char texto[BUFFER_SIZE];

	printf("Ingresa el texto:\n");
	if (fgets(texto, BUFFER_SIZE, stdin) == NULL) {
		fprintf(stderr, "Fallo al ingresar la linea");
		return 1;
	}

	texto[strcspn(texto, "\r\n")] = '\0';

	int* contadores = (int*)malloc(4 * sizeof(int));

	printf("Texto : %s\n", texto);

	contar_vocales(texto, &contadores[0], &contadores[1], &contadores[2], &contadores[3]);

	free(contadores);

	return 0;
}

void contar_vocales(const char* texto, int* vocales, int* consonantes, int* digitos, int* otros) {
	const char* p = texto;	// Nota, si no se hace esto hay un warning, no permite usar p++
	int i = 0;
	char c = *(p + i);

	if (vocales == NULL) {
		fprintf(stderr, "Error al intentar reservar memoria para vocales\n");
		*vocales = -1;
	} else {
		*vocales = 0;
	}

	if (consonantes == NULL) {
		fprintf(stderr, "Error al intentar reservar memoria para vocales\n");
		*consonantes = -1;
	} else {
		*consonantes = 0;
	}

	if (digitos == NULL) {
		fprintf(stderr, "Error al intentar reservar memoria para vocales\n");
		*digitos = -1;
	} else {
		*digitos = 0;
	}

	if (otros == NULL) {
		fprintf(stderr, "Error al intentar reservar memoria para vocales\n");
		*otros = -1;
	} else {
		*otros = 0;
	}

	while (c != '\0') {
        // printf("-%c-\n", c);

		if (isdigit((unsigned char)c) && digitos != NULL) {
			*digitos = *digitos + 1;

		} else if (isalpha((unsigned char)c)) {
			switch (c) {
				case 'a':
				case 'A':
				case 'e':
				case 'E':
				case 'i':
				case 'I':
				case 'o':
				case 'O':
				case 'u':
				case 'U':
					if (vocales != NULL) {
						*vocales = *vocales + 1;
					}
					break;
				default:
					if (consonantes != NULL) {
						*consonantes = *consonantes + 1;
					}
					break;
			}
		} else {
			if (c != '\n' && otros != NULL) {
                    *otros = *otros + 1;
			}
		}

		i++;
		c = *(p + i);
	}

	printf("%-12s : %d\n", "Vocales", *vocales);
	printf("%-12s : %d\n", "Consonantes", *consonantes);
	printf("%-12s : %d\n", "Digitos", *digitos);
	printf("%-12s : %d\n", "Otros", *otros);
}