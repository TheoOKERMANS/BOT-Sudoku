#include "library/h.h"

int main(int argc, char *argv[]) {
    printf("Start\n");
    
    clock_t start = clock();

    int solved = 0;
    int map_tested = 0;
    while(map_tested < LOOP)
    {
        Map carte = init_map();
        printf(print_map(carte));
        carte = resolve_map(carte);
        //printf("\n\n\n\n\n");
        //printf(print_map(carte));
        //printf(print_boolean(is_solved(carte)));
        //printf("\n");
        map_tested++;
        solved += is_solved(carte);
        if(is_solved(carte))
            printf("%s\n", print_int(map_tested));
    }
    printf("Stop\n%i/%i\n",solved,LOOP);
    
    clock_t end = clock();
    int elapsed = (end - start);
    printf("Time measured: %i ms.\n%ims/1000 tested map", elapsed, (elapsed*1000)/map_tested);


    return 0;
}