#include "h.h"

int INITIALISATION_RANDOM;
int RANDOM;

int random_number(int min,int max)
{
    return (fastrand()%(max+min-1))+min;
}
int fastrand() { 
    if(INITIALISATION_RANDOM != 1){
        time_t t;
        srand((unsigned) time(&t));
        INITIALISATION_RANDOM = 1;
        RANDOM = rand();
    }
    RANDOM = (214013*RANDOM+rand()); 
    return (RANDOM>>16)&0x7FFF; 
} 