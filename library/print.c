#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "structure.c"
//----------------------------------------------------------------
//Initialisation des fonctions et des structure

const char* print_map(Map map);
const char* print_int_list(int* list);
const char* print_boolean(int bool);

//----------------------------------------------------------------

const char* print_map(Map map){
    static char result[] = "";
    *result = 0;
    for(int i = 0;i < 9;i++)
    {
        strcat(result,"|");
        for(int j = 0;j < 9;j++)
        {
            char value[255];
            sprintf(value,"%d",map.grid[i][j].value);
            strcat(result," ");
            if(map.grid[i][j].value > 0)strcat(result,value);
            else strcat(result," ");
        }
        strcat(result," |\n");
    }
    return result;
}

const char* print_int_list(int* list)
{
    static char result[] = "{";
    *result = 0;
    for(int i = 0;i < 9;i++)
    {
        strcat(result," ");
        char value[100];
        sprintf(value,"%d",list[i]);
        strcat(result,value);
        strcat(result," ");
    }
    strcat(result,"}");
    return result;
}

const char* print_boolean(int bool)
{
    if(bool == 1)return "true";
    else return "false";
}

const char* print_int(int value)
{
    static char result[] = "";
    sprintf(result,"%d",value);
    return result;
}