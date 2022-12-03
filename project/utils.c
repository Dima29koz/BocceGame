#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

void show_rules(int balls_amount){
    PRINT("\nIN THIS GAME YOU ROLL %d BALLS SUCCESSIVELY AT A TARGET\n", balls_amount-1);
    PRINT("BALL (CALLED A JACK). THE OBJECT IS TO GET THE BALLS AS CLOSE\n");
    PRINT("TO THE JACK AS POSSIBLE.  THE BALLS ARE 10 CM IN DIAMETER AND\n");
    PRINT("ARE WEIGHTED SO THAT THEY ROLL IN A CURVE. YOU WILL HAVE TO\n");
    PRINT("ROLL THEM AT AN ANGLE TO THE LINE FROM YOU AT COORDINATES 0,0\n");
    PRINT("TO THE JACK AT COORDINATES X,Y. A POSITIVE ANGLE WILL MAKE\n");
    PRINT("THE BALL CURVE CLOCKWISE. A NEGATIVE ANGLE WILL MAKE IT CURVE\n");
    PRINT("ANTI-CLOCKWISE.  THE JACK IS A 4 CM WIDE AND WILL ROLL\n");
    PRINT("STRAIGHT IF YOU HIT IT.  BALLS HIT BY YOUR THROWN BALL MAY\n");
    PRINT("CURVE IN EITHER DIRECTION.\n");
    PRINT("\nHINT. TRY AN INITIAL VELOCITY OF 500 AND AN ANGLE OF 10\n\n\n");
}

void tab(int amount){
    for (int i=0; i< amount; i++){
        PRINT(" ");
    }
}

void print_header(){
    tab(25);
    PRINT("BOCCE\n");
    tab(19);
    PRINT("CREATIVE COMPUTING\n");
    tab(17);
    PRINT("MORRISTOWN  NEW JERSEY\n");
    PRINT("\n\n\n");
}

void show_shot_res(float* x, float* y, int last_shot_idx, float* d) {
    PRINT("JACK AT COORDINATES %d %d\n", (int)(x[0]), (int)(y[0]));
    for (int m=2; m <= last_shot_idx; m++){
        float distance = sqrtf((y[0] - y[m]) * (y[0] - y[m]) + (x[0] - x[m]) * (x[0] - x[m])) - 7;
        d[m] = (distance >= 0) ? distance : 0;
        PRINT("BALL %d AT COORDINATES %f %f IT IS %f FROM THE JACK\n", m-1, x[m], y[m], d[m]);
    }
    PRINT("\n");
    if (d[last_shot_idx] < 10) {
        tab(15);
        PRINT("EXCELLENT SHOT! \n");
    }
    else if (d[last_shot_idx] < 20) {
        tab(15);
        PRINT("GOOD SHOOTING! \n");
    }
    else if (d[last_shot_idx] < 30) {
        tab(15);
        PRINT("NICE TRY! \n");
    }
    else if (d[last_shot_idx] > 500) {
        tab(5);
        PRINT("YECH! OVER %d FEET AWAY!\n", (int)(d[last_shot_idx] / 30.48));
    }

    if (x[last_shot_idx] > x[0]) {
        PRINT("LONG AND ");
    }
    else if (x[last_shot_idx] < x[0]) {
        PRINT("SHORT AND ");
    }

    if (y[last_shot_idx] > y[0]) {
        PRINT("TO THE LEFT\n");
    }
    else if (y[last_shot_idx] < y[0]) {
        PRINT("TO THE RIGHT\n");
    }
    
    PRINT("\n");
}

void print_result(int q, float sum_dist) {
    PRINT("\nTHE TOTAL DISTANCE OF ALL BALLS FROM THE JACK IS %f CM\n", sum_dist);
    if (sum_dist < q * q) {
        PRINT("MAGNIFICENT BOWLING! WHAT AN EYE!!\n");
    }
    else if (sum_dist < 2 * q * q) {
        PRINT("EXCELLENT BUT COULD BE BETTER:\n");
    }
    else if (sum_dist < 3 * q * q) {
        PRINT("GOOD BUT NEEDS SOME IMPROVEMENT\n");
    }
    else if (sum_dist < 6 * q * q) {
        PRINT("FAIR - YOU NEED MORE PRACTICE\n");
    }
    else if (sum_dist < 10 * q * q) {
        PRINT("POOR - TRY TO BE MORE CONSISTANT\n");
    }
    else if (sum_dist < 20 * q * q) {
        PRINT("YOUR GAME NEEDS LOTS OF WORK\n");
    }
    else {
        PRINT("DON'T PLAY THIS GAME FOR MONEY!!\n");
    }
}

long VAL(char *string) {
    char *endptr;
    return strtol(string, &endptr, 10);
}

void input_string(char **p_target) {
    *p_target = malloc(512);
    input(*p_target);
    strtok(*p_target, "\n");
}

void input_number(int *p_target) {
    char *p_number_as_string;
    input_string(&p_number_as_string);
    *p_target = VAL(p_number_as_string);
}

