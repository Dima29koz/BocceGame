#include <stdio.h>
#include <math.h>

void show_rules(int balls_amount){
    printf("\nIN THIS GAME YOU ROLL %d BALLS SUCCESSIVELY AT A TARGET\n", balls_amount-1);
    printf("BALL (CALLED A JACK). THE OBJECT IS TO GET THE BALLS AS CLOSE\n");
    printf("TO THE JACK AS POSSIBLE.  THE BALLS ARE 10 CM IN DIAMETER AND\n");
    printf("ARE WEIGHTED SO THAT THEY ROLL IN A CURVE. YOU WILL HAVE TO\n");
    printf("ROLL THEM AT AN ANGLE TO THE LINE FROM YOU AT COORDINATES 0,0\n");
    printf("TO THE JACK AT COORDINATES X,Y. A POSITIVE ANGLE WILL MAKE\n");
    printf("THE BALL CURVE CLOCKWISE. A NEGATIVE ANGLE WILL MAKE IT CURVE\n");
    printf("ANTI-CLOCKWISE.  THE JACK IS A 4 CM WIDE AND WILL ROLL\n");
    printf("STRAIGHT IF YOU HIT IT.  BALLS HIT BY YOUR THROWN BALL MAY\n");
    printf("CURVE IN EITHER DIRECTION.\n");
    printf("\nHINT. TRY AN INITIAL VELOCITY OF 500 AND AN ANGLE OF 10\n\n\n");
}

void tab(int amount){
    for (int i=0; i< amount; i++){
        printf(" ");
    }
}

void print_header(){
    tab(25);
    printf("BOCCE\n");
    tab(19);
    printf("CREATIVE COMPUTING\n");
    tab(17);
    printf("MORRISTOWN  NEW JERSEY\n");
    printf("\n\n\n");
}

void show_shot_res(float* x, float* y, int last_shot_idx, float* d) {
    printf("JACK AT COORDINATES %d %d\n", (int)(x[0]), (int)(y[0]));
    for (int m=2; m <= last_shot_idx; m++){
        float distance = sqrtf((y[0] - y[m]) * (y[0] - y[m]) + (x[0] - x[m]) * (x[0] - x[m])) - 7;
        d[m] = (distance >= 0) ? distance : 0;
        printf("BALL %d AT COORDINATES %f %f IT IS %f FROM THE JACK\n", m-1, x[m], y[m], d[m]);
    }
    printf("\n");
    if (d[last_shot_idx] < 10) {
        tab(15);
        printf("EXCELLENT SHOT! \n");
    }
    else if (d[last_shot_idx] < 20) {
        tab(15);
        printf("GOOD SHOOTING! \n");
    }
    else if (d[last_shot_idx] < 30) {
        tab(15);
        printf("NICE TRY! \n");
    }
    else if (d[last_shot_idx] > 500) {
        tab(5);
        printf("YECH! OVER %d FEET AWAY!\n", (int)(d[last_shot_idx] / 30.48));
    }

    if (x[last_shot_idx] > x[0]) {
        printf("LONG AND ");
    }
    else if (x[last_shot_idx] < x[0]) {
        printf("SHORT AND ");
    }

    if (y[last_shot_idx] > y[0]) {
        printf("TO THE LEFT\n");
    }
    else if (y[last_shot_idx] < y[0]) {
        printf("TO THE RIGHT\n");
    }
    
    printf("\n");
}

void print_result(int q, float sum_dist) {
    printf("\nTHE TOTAL DISTANCE OF ALL BALLS FROM THE JACK IS %f CM\n", sum_dist);
    if (sum_dist < q * q) {
        printf("MAGNIFICENT BOWLING! WHAT AN EYE!!\n");
    }
    else if (sum_dist < 2 * q * q) {
        printf("EXCELLENT BUT COULD BE BETTER:\n");
    }
    else if (sum_dist < 3 * q * q) {
        printf("GOOD BUT NEEDS SOME IMPROVEMENT\n");
    }
    else if (sum_dist < 6 * q * q) {
        printf("FAIR - YOU NEED MORE PRACTICE\n");
    }
    else if (sum_dist < 10 * q * q) {
        printf("POOR - TRY TO BE MORE CONSISTANT\n");
    }
    else if (sum_dist < 20 * q * q) {
        printf("YOUR GAME NEEDS LOTS OF WORK\n");
    }
    else {
        printf("DON'T PLAY THIS GAME FOR MONEY!!\n");
    }
}