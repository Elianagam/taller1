#ifndef _CELL_H
#define _CELL_H

typedef struct {
    char value;
    bool fixed;
} cell_t;

void cell_init(cell_t* cell, char value);

int cell_write(cell_t* self, char value);

void cell_delete_value(cell_t* self);

void cell_destroy(cell_t* self);

bool cell_is_fixed(cell_t* self);

bool cell_has_value(cell_t* self);

#endif

