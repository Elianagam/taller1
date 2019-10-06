#ifndef _TABLE_H_
#define _TABLE_H_

#include "cell.h"

typedef struct {
	cell_t cells[9][9];
} table_t;

void table_init(table_t* table);

char* table_get(table_t* table, char* buffer);

int table_write_value(table_t* table, int n_row, int n_col, char value);

bool table_verify(table_t* table);

void table_reset(table_t* table);

void table_destroy(table_t* table);

#endif

