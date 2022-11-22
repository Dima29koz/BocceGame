#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "constants.h"
#include "utils.h"


int get_velocity(){
    printf("VELOCITY? ");
    int velocity;
    scanf("%d", &velocity);
    velocity = abs(velocity);
    if (velocity > 1000){
        printf("VELOCITY TOO HIGH\n");
        return get_velocity();
    }
    return velocity;
}

int get_angle(){
    printf("ANGLE? ");
    int angle;
    scanf("%d", &angle);
    return angle;
}

void calc_turn(int turn_idx, float* b, float* v, float* b1, float s1, float s2, float* x, float* y, int q, float* d) {
    int k1 = -20;
    //printf("%d %e %f %f %f %e %f %f %f\n", turn_idx ,b[turn_idx], v[turn_idx], b1[turn_idx], s1, s2, x[turn_idx], y[turn_idx], d[turn_idx]);
    if (turn_idx == 1) {
        k1 = 0;
    }
    float a1 = A * cos(b[turn_idx]) + k1 * cos(PI/2 + b[turn_idx]);
    float a2 = A * sin(b[turn_idx]) + k1 * sin(PI/2 + b[turn_idx]);
    float s3 = v[turn_idx] * cos(b[turn_idx]) * 5 / 100 + 1.25 * a1 / 1000;
    float s4 = v[turn_idx] * sin(b[turn_idx]) * 5 / 100 + 1.25 * a2 / 1000;

    b[turn_idx] = atan((v[turn_idx] * sin(b[turn_idx]) + a2 * 5 / 100) / (v[turn_idx] * cos(b[turn_idx]) + a1 * 5 / 100));
    
    if (b1[turn_idx] < 0) {
        s4 = -s4;
    }
    float s5 = s1 + s3;
    float s6 = s2 + s4;
    if (turn_idx != 1) {
        if (abs(s5-x[0]) < 7 && abs(s6-y[0]) < 7) {
            int k = 1;
            printf("\n\ncod ne rabotaet\n\n");
            if (turn_idx == 1) {
                v[turn_idx] = 5 * v[turn_idx];
            }
        }
    }
    
    for (int k = 2; k<=q; k++) { // 1370
        if (!(k == turn_idx || x[k] == 0)){
            if (abs(s5 - x[k]) < 10 && abs(s6 - y[k]) < 10) {
                b[k] = atan((y[k] - s2) / (x[k] - s1));
                printf("%c", 7);
                if (turn_idx == 1) {
                    v[turn_idx] = v[turn_idx] / 5;
                }
                v[turn_idx] = abs(v[turn_idx] * sin(b[turn_idx] - b[k]));
                v[k] = abs(v[turn_idx] * cos(b[turn_idx] - b[k]));
                b[turn_idx] = PI/2 + b[k];
                s5 = s1;
                s6 = s2;
                if (k==1) {
                    v[k] = 5 * v[k];
                }
                if (turn_idx==1) {
                    v[turn_idx] = 5 * v[turn_idx];
                }
            }
        }
    }
    if (v[turn_idx] < abs(A * 5 / 100)) { // 1410
        x[turn_idx] = x[turn_idx] + s5;
        y[turn_idx] = y[turn_idx] + s6;
        s1 = 0;
        s2 = 0;
        s5 = 0;
        s6 = 0;
        for (int l = 1; l <= q; l++) {
            if (v[l] > abs(A * 5 / 100)) {
                calc_turn(l, b, v, b1, s1, s2, x, y, q, d);
            }
            b[l] = 0;
            v[l] = 0;
        }
        show_shot_res(x, y, turn_idx, d);
        return;
    }
    v[turn_idx] = v[turn_idx] + A * 5 / 100;
    s1 = s5;
    s2 = s6;
    calc_turn(turn_idx, b, v, b1, s1, s2, x, y, q, d);
}

void run(int q) {
    float s1 = 0, s2 = 0;
    float v[9] = {0.0};
    float b[9] = {0.0}, b1[9] = {0.0};
    float x[9] = {0}, y[9] = {0}, d[9] = {0};
    // x[0] = (int)(2000 + 700.0 * ((rand() % 100) / 100.0));
    // y[0] = (int)(200 - 400.0 * ((rand() % 100) / 100.0));
    x[0] = 2495;
    y[0] = -178;
    printf("THE JACK IS LOCATED AT %d %d\n", (int)(x[0]), (int)(y[0]));
    for (int ball_number = 2; ball_number<=q; ball_number++){
        printf("BALL %d\n", ball_number-1);
        v[ball_number] = get_velocity();
        b1[ball_number] = get_angle();
        if (abs(b1[ball_number]) > 89) {
            printf("ANGLE TO BIG\n");
        }
        else {
            b[ball_number] = abs(b[ball_number]*PI/180);
        }
        calc_turn(ball_number, b, v, b1, s1, s2, x, y, q, d);
    }
    float sum_dist = 0;
    for (int j=2 ; j<=q ; j++){
        sum_dist = sum_dist + d[j];
    }
    print_result(q, sum_dist);
    for (int j = 0; j<=q; j++) {
        b[j] = 0;
        b1[j] = 0;
        d[j] = 0;
        v[j] = 0;
        x[j] = 0;
        y[j] = 0;
    }
}

int main() {
    srand(time(NULL));
    print_header();
    int q = 5;
    printf("THIS GAME SIMULATES THE GAME OF LAWN BOWLS\n");
    printf("DO YOU NEED INSTRUCTIONS? ENTER YES OR NO? ");
    char rules_flag[4] = "";
    fgets(rules_flag, 4, stdin);
    if (strcmp (rules_flag, "YES") == 0){
        show_rules(q);
    }
    
    char repeat_flag[4] = "";
    do  {
        run(q);
        printf("\nCARE TO TRY AGAIN? ENTER YES OR NO? ");
        char tmp[4] = "";
        scanf("%s", tmp);
        strcpy(repeat_flag, tmp);
    } while (strcmp (repeat_flag, "YES") == 0);
    return 0;
}
