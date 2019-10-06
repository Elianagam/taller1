#include <stdbool.h>
#include "table.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 9
#define LEN_TABLE 722
#define ERROR_ -1
#define DONT_WRITE -2

// FUNCIONES AUXILIARES -------------------
int border_1(char* buffer, int pos) {
	if (pos != 0) buffer[pos++] = '\n';
	
	char border1[] = "U===========U===========U===========U\n\0";
	for (int i = 0; i < 38; i++) {
	 buffer[pos++] = border1[i];
	}
	return pos++;
}

int border_2(char* buffer, int pos) {
	char border2[] = "\nU---+---+---U---+---+---U---+---+---U\n\0";
	for (int i = 0; i < 39; i++) {
		buffer[pos++] = border2[i];
	}
	return pos++;
}

void table_append_cells(FILE* file, table_t* table) {
	char ch;
	int n_col;
	for (int n_row = 0; n_row < SIZE; n_row++) {
		n_col = 0;
		while (n_col < SIZE) {
			ch = fgetc(file);
			if (ch != ' ' && ch != '\n') {
				cell_init(&table->cells[n_row][n_col], ch);	
				n_col++;
			}
		}
	}
}

bool check_row(table_t* table, int n_row, int n_col) {
	cell_t* cell = &table->cells[n_row][n_col];
	if (cell_has_value(cell)) {
		for (int l = n_col+1; l < SIZE; l++) {
			if (&cell->value == &table->cells[n_row][l].value) {
				return false;
			}
		}
	} 		
	return true;
}

bool check_column(table_t* table, int n_col) {
	for (int j = 0; j < SIZE; j++) {
		cell_t* cell = &table->cells[j][n_col];
		if (cell_has_value(cell)) {
			for (int l = j+1; l < SIZE; l++) {
				if (&cell->value == &table->cells[l][n_col].value)
					return false;
			}
		}
	}
	return true;
}

bool check_box(table_t* table, int n_row, int n_col) {
	char* array = malloc(9 * sizeof(char) + 1);;
	int pos = 0;
	for (int i = n_row; i < n_row+3; i++) {
		for (int j = n_col; j < n_col+3; j++) {
			cell_t* cell = &table->cells[i][j];
			if (cell_has_value(cell)) {
				array[pos++] = cell->value;
			}
		}
	}
	for (int l = 0; l < pos; l++) {
		for (int r = l+1; r < pos; r++) {
			if (array[l] == array[r]) {
				free(array);
				return false;
			}
		}
	}
	free(array);
	return true;
}

// FUNCIONES TABLA ------------------------
void table_init(table_t* table) {
	FILE* file = fopen("board.txt", "r");

	table_append_cells(file, table);
	fclose(file);
}

bool table_verify(table_t* table) {
	for (int n_row = 0; n_row < SIZE; n_row++) {
		if (!check_column(table, n_row))
			return false; // necesito un solo loop para checkear cols
		for (int n_col = 0; n_col < SIZE; n_col++) {
			if (!check_row(table, n_row, n_col)) {
				return false;
			}
		}			
	}
	for (int i = 0; i < SIZE; i+=3) {
		for (int j = 0; j < SIZE; j+=3) {
			if (!check_box(table, i, j))
			return false;
		}
	}
	return true;
}

char* table_get(table_t* table, char* buffer) {
	int pos = 0;
	pos = border_1(buffer, pos);
	for (int i = 0; i < SIZE; i++) {
		buffer[pos++] = 'U';
		for (int j = 0; j < SIZE; j++) {
				buffer[pos++] = ' ';
				cell_t* cell = &table->cells[i][j];
				buffer[pos++] = cell->value;
				buffer[pos++] = ' ';
			if ((j+1) % 3 == 0) {
				buffer[pos++] = 'U';
			} else {
				buffer[pos++] = '|';
			}
		}
		if ((i+1) % 3 == 0) {
			pos = border_1(buffer, pos);
		} else {
			pos = border_2(buffer, pos);
		}
	}
	return buffer;
}

int table_write_value(table_t* table, int n_row, int n_col, char value) {
	if (cell_write(&table->cells[n_row-1][n_col-1], value) == 0) {
		return 0;
	} else {
		// fixed, no se escribe
		return DONT_WRITE;
	}
}

void table_reset(table_t* table) {
	for (int n_row = 0; n_row < SIZE; n_row++) {
		for (int n_col = 0; n_col < SIZE; n_col++) {
			if (!cell_is_fixed(&table->cells[n_row][n_col])) {
				cell_write(&table->cells[n_row][n_col], ' ');
			}
		}
	}
}

void table_destroy(table_t* table) {
	/*for (int n_row = 0; n_row < SIZE; n_row++) {
		for (int n_col = 0; n_col < SIZE; n_col++) {
			free(table->cells[n_row][n_col]);
		}
	}
	free(table);*/
}
