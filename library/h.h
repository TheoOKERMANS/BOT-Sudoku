#ifndef H_H
# define H_H

typedef struct Case
{
    int x;
    int y;
    int value;
    int hasValue;
} Case;

typedef struct Map
{
    struct Case grid[9][9];
} Map;

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 9
#define LOOP 100

int random_number(int min,int max);
int fastrand();

const char* print_map(Map map);
const char* print_int_list(int* list);
const char* print_boolean(int bool);
const char* print_int(int value);

Map init_map();
Map init_map_from_table();
Map put_random_number_in_map(Map map);
Map resolve_map(Map map);
int can_be_value(Map map,int x, int y, int value);
int can_be_on_line(Map map,int x, int y, int value);
int can_be_on_column(Map map,int x, int y, int value);
int can_be_on_block(Map map,int x, int y, int value);
int* convert_int_array_to_right_size(int* list);
int* get_numbers_in_block(Map map,int x,int y);
int number_not_in_list(int number, int* list,int size);
int* get_numbers_not_in_block(Map map,int x,int y);
int is_solved(Map map);
int is_line_completed(Map map, int x);
int is_column_completed(Map map, int y);

#endif