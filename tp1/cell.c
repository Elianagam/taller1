#include <stdbool.h>
#include "cell.h"
#include <stdlib.h>
#include <stddef.h>

#define ERROR_ -1

void cell_init(cell_t* cell, char value) {
	bool fixed = true;
	if (value == '0') {
		fixed = false;
		cell->value = ' ';
		cell->fixed = fixed;
	} else {
		cell->value = value;
		cell->fixed = fixed;
	}
}

int cell_write(cell_t* self, char value) {
	if (cell_is_fixed(self)) {
		return ERROR_;
	} else {
		self->value = value;
	}
	return 0;
}

void cell_destroy(cell_t* self) {
	//pass
}

bool cell_is_fixed(cell_t* self) {
	return self->fixed;
}

bool cell_has_value(cell_t* self) {
	return self->value != ' ';
}
