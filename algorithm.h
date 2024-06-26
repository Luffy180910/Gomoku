#ifndef ALGORITHM_H
#define ALGORITHM_H


#include<iostream>
#define SIZE_MAP 15

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"

typedef struct{
    int x;
    int y;
}coordinate;



void print_map();     //打印棋盘
int compute_exp(int self, int oppo); 
int absolute_value_local(int l_move, int r_move); 
int absolute_value_global(); 
coordinate min_value_tree();
coordinate max_value_tree();
coordinate ai_move(); 

int ai_move_2_flour(int* max_value_unlocal);
int ai_move_3_flour(int* min_value_unlocal,bool* change_flag);
coordinate ai_move_4_flour();

void game_start();    //游戏开始


#endif