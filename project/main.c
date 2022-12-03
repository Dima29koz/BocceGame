#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.h"
#include "funcs.h"

#define A -49.3F
#define PI 3.14159F


int get_velocity(){
    PRINT("VELOCITY? ");
    int velocity;
    input_number(&velocity);
    velocity = abs(velocity);
    if (velocity > 1000){
        PRINT("VELOCITY TOO HIGH\n");
        return get_velocity();
    }
    return velocity;
}

int get_angle(){
    PRINT("ANGLE? ");
    int angle;
    input_number(&angle);
    return angle;
}

void calc_turn(int turn_idx, float* b, float* v, float* b1, float s1, float s2, float* x, float* y, int q, float* d) {
    int k1 = -20;
    if (turn_idx == 1) {
        k1 = 0;
    }
    float a1 = A * cosf(b[turn_idx]) + k1 * cosf(PI/2 + b[turn_idx]);
    float a2 = A * sinf(b[turn_idx]) + k1 * sinf(PI/2 + b[turn_idx]);
    float s3 = v[turn_idx] * cosf(b[turn_idx]) * .05F + 1.25E-03F * a1;
    float s4 = v[turn_idx] * sinf(b[turn_idx]) * .05F + 1.25E-03F * a2;

    b[turn_idx] = atanf((v[turn_idx] * sinf(b[turn_idx]) + a2 * .05F) / (v[turn_idx] * cosf(b[turn_idx]) + a1 * .05F));
    
    if (b1[turn_idx] < 0) {
        s4 = -s4;
    }
    float s5 = s1 + s3;
    float s6 = s2 + s4;
    if (turn_idx != 1) {
        if (fabsf(s5-x[0]) < 7 && fabsf(s6-y[0]) < 7) {
            if (turn_idx == 1) {
                v[turn_idx] = 5 * v[turn_idx];
            }
        }
    }
    
    for (int k = 2; k<=q; k++) { // 1370
        if (!(k == turn_idx || x[k] == 0)){
            if (fabsf(s5 - x[k]) < 10 && fabsf(s6 - y[k]) < 10) {
                b[k] = atanf((y[k] - s2) / (x[k] - s1));
                PRINT("%c", 7);
                if (turn_idx == 1) {
                    v[turn_idx] = v[turn_idx] / 5;
                }
                v[turn_idx] = fabsf(v[turn_idx] * sinf(b[turn_idx] - b[k]));
                v[k] = fabsf(v[turn_idx] * cosf(b[turn_idx] - b[k]));
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
    if (v[turn_idx] < fabsf(A * .05F)) { // 1410
        x[turn_idx] = x[turn_idx] + s5;
        y[turn_idx] = y[turn_idx] + s6;
        s1 = 0;
        s2 = 0;
        s5 = 0;
        s6 = 0;
        for (int l = 1; l <= q; l++) {
            if (v[l] > fabsf(A * .05F)) {
                calc_turn(l, b, v, b1, s1, s2, x, y, q, d);
            }
            b[l] = 0;
            v[l] = 0;
        }
        show_shot_res(x, y, turn_idx, d);
        return;
    }
    v[turn_idx] = v[turn_idx] + A * .05F;
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
    PRINT("THE JACK IS LOCATED AT %d %d\n", (int)(x[0]), (int)(y[0]));
    for (int ball_number = 2; ball_number<=q; ball_number++){
        PRINT("BALL %d\n", ball_number-1);
        v[ball_number] = get_velocity();
        b1[ball_number] = get_angle();
        if (fabsf(b1[ball_number]) > 89) {
            PRINT("ANGLE TO BIG\n");
        }
        else {
            b[ball_number] = fabsf(b[ball_number]*PI/180);
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
    PRINT("THIS GAME SIMULATES THE GAME OF LAWN BOWLS\n");
    PRINT("DO YOU NEED INSTRUCTIONS? ENTER YES OR NO? ");
    char *rules_flag;
    input_string(&rules_flag);
    if (strcmp (rules_flag, "YES") == 0){
        show_rules(q);
    }
    
    char repeat_flag[4] = "";
    do  {
        run(q);
        PRINT("\nCARE TO TRY AGAIN? ENTER YES OR NO? ");
        char *tmp_flag;
        input_string(&tmp_flag);
        strcpy(repeat_flag, tmp_flag);
    } while (strcmp (repeat_flag, "YES") == 0);
    return 0;
}
