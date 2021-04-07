#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "math.c"

#define SIZE 9

//----------------------------------------------------------------
//Initialisation des fonctions et des structure

typedef struct Case Case;
typedef struct Map Map;

Map init_map();
Map init_map_from_table();
Map put_random_number_in_map(Map map);
Map resolve_map();
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

//----------------------------------------------------------------

struct Case
{
    int x;
    int y;
    int value;
    int hasValue;
};

struct Map
{
    Case grid[9][9];
};

Map init_map()
{
    Map map;
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            Case c;
            c.x = i;
            c.y = j;
            c.value = -1;
            c.hasValue = 0;
            map.grid[i][j] = c;
        }
    }
    map = put_random_number_in_map(map);
    return map;
}

Map init_map_from_table()
{
    Map map;
    int table[9][9] = {
        {0,0,0,2,6,0,7,0,1},
        {6,8,0,0,7,0,0,9,0},
        {1,9,0,0,0,4,5,0,0},
        {8,2,0,1,0,0,0,4,0},
        {0,0,4,6,0,2,9,0,0},
        {0,5,0,0,0,3,0,2,8},
        {0,0,9,3,0,0,0,7,4},
        {0,4,0,0,5,0,0,3,6},
        {7,0,3,0,1,8,0,0,0}
        };
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            Case c;
            c.x = i;
            c.y = j;
            c.value =  table[i][j];
            c.hasValue = 1;
            map.grid[i][j] = c;
        }
    }

    return map;
}

Map put_random_number_in_map(Map map)
{
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            int random = random_number(1,9);
            if(can_be_value(map,i,j,random) == 1){
                map.grid[i][j].value = random;
            }
            else map.grid[i][j].value = 0;
            map.grid[i][j].hasValue = 1;
        }
    }
    return map;
}

int is_line_completed(Map map, int x)
{
    for(int i = 0;i < 9;i++)
    {
        if(map.grid[x][i].value == 0)return 0;
    }
    return 1;
}

int is_column_completed(Map map, int y)
{
    for(int i = 0;i < 9;i++)
    {
        if(map.grid[i][y].value == 0)return 0;
    }
    return 1;
}

int can_be_on_line(Map map,int x, int y, int value)
{
    for(int i = 0;i < 9;i++)
    {
        if(map.grid[x][i].value == value && map.grid[x][i].hasValue == 1){
            return 0;
        }
    }
    return 1;
}
int can_be_on_column(Map map,int x, int y, int value)
{
    for(int i = 0;i < 9;i++)
    {
        if(map.grid[i][y].value == value && map.grid[i][y].hasValue == 1){
            return 0;
        }
    }
    return 1;
}
int can_be_on_block(Map map,int x, int y, int value)
{
    int xbloc = x/3;
    int ybloc = y/3;
    for(int i = xbloc*3;i < (xbloc+1)*3;i++)
    {
        for(int j = ybloc*3;j < (ybloc+1)*3;j++)
        {
            if(map.grid[i][j].value == value && map.grid[i][j].hasValue == 1){
                return 0;
            }
        }
    }
    return 1;
}

int can_be_value(Map map,int x, int y, int value)
{
    if(can_be_on_line(map,x,y,value) == 0)return 0;
    if(can_be_on_column(map,x,y,value) == 0)return 0;
    if(can_be_on_block(map,x,y,value) == 0)return 0;
    return 1;
}

int* get_numbers_in_block(Map map,int x,int y)
{
    static int result[9];
    int numbers_added = 0;
    int xbloc = x/3;
    int ybloc = y/3;
    for(int i = xbloc*3;i < (xbloc+1)*3;i++)
    {
        for(int j = ybloc*3;j < (ybloc+1)*3;j++)
        {
            if(map.grid[i][j].value != 0 && map.grid[i][j].hasValue == 1){
                result[numbers_added] = map.grid[i][j].value;
                numbers_added++;
            }
        }
    }
    return result;
}

int number_not_in_list(int number, int* list,int size)
{
    for(int i = 0;i < size;i++){
        if(list[i] == number)return 0;
    }
    return 1;
}

int* get_numbers_not_in_block(Map map,int x,int y)
{
    static int result[9];
    int added_numbers = 0;
    int* numbers_in_block = get_numbers_in_block(map,x,y);
    for(int i = 1;i < 10;i++)
    {
        if(number_not_in_list(i,numbers_in_block,9))
        {
            result[added_numbers] = i;
            added_numbers++;
        }
    }
    return result;
}

int is_solved(Map map)
{
    for(int i = 0;i <9;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            if(map.grid[i][j].value == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
Map resolve_map(Map map)
{
    int end = 0;
    while(end == 0)
    {
        end = 1;
        for(int i = 0; i < 9;i++)
        {
            for(int j = 0; j < 9;j++)
            {
                if(map.grid[i][j].value == 0){
                    for(int k = 1;k < 10;k++)
                    {
                        int possible_in_one_block = 0;
                        int xpossible_case = -1;
                        int ypossible_case = -1;
                        int xbloc = i/3;
                        int ybloc = j/3;
                        int stop = 0;
                        for(int l = xbloc*3;(l < (xbloc+1)*3) && (stop == 0);l++)
                        {
                            for(int m = ybloc*3;(m < (ybloc+1)*3) && (stop == 0);m++)
                            {
                                if(map.grid[l][m].value == 0 && can_be_value(map,l,m,k))
                                {
                                    possible_in_one_block++;
                                    xpossible_case = l;
                                    ypossible_case = m;
                                    if(possible_in_one_block>1)stop = 1;
                                }
                            }
                        }
                        if(possible_in_one_block == 1)
                        {
                            map.grid[xpossible_case][ypossible_case].value = k;
                            end = 0;
                        }
                    }
                }
            }
        }
    }
    return map;
}