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


// Map
short map[SIZE_MAP][SIZE_MAP]={0};
int map_value[SIZE_MAP][SIZE_MAP];
int direction_8[8][2] = { 1,1,-1,-1,1,0,-1,0,1,-1,-1,1,0,1,0,-1 };
char player_name[10] = "Luffy";
int round_count = 0;

void print_map()     //打印棋盘
{
    for(int i=0;i<SIZE_MAP;i++)
    {
        for(int j=0;j<SIZE_MAP;j++)
        {   

            if(map[i][j]==0)
            std::cout<<RED<<map[i][j]<<" "<<RESET;
            
            if(map[i][j]==1)
            std::cout<<GREEN<<map[i][j]<<" "<<RESET;
            
            if(map[i][j]==2)
            std::cout<<YELLOW<<map[i][j]<<" "<<RESET;
        }
        std::cout<<std::endl;
    }
    //print the round

    std::cout<<std::endl<<"Round: "<<round_count<<std::endl;
}

int compute_exp(int self, int oppo) 
{
	int sum = 1;
	for (int i = 0; i < self; i++) {
		sum *= 10;
	}
	if (oppo == 2)
		sum /= 10;
	if (oppo == 1)
		sum /= 2;
	return sum;
}

int absolute_value_local(int l_move, int r_move) 
{
	int self_length_4_1[4] = { 0 }, oppo_length_4_1[4] = { 0 };
	int self_length_4_f1[4] = { 0 }, oppo_length_4_f1[4] = { 0 };


	for (int i = 0; i < 8; i++) {
		int move_step = 0;
		while (map[l_move + move_step * direction_8[i][0]][r_move + move_step * direction_8[i][1]] == 1
			&& (l_move + move_step * direction_8[i][0] >= 0 && l_move + move_step * direction_8[i][0] < SIZE_MAP)
			&& (r_move + move_step * direction_8[i][1] >= 0 && r_move + move_step * direction_8[i][1] < SIZE_MAP)) {
			self_length_4_1[i / 2]++;
			move_step++;
		}
		if (!(l_move + move_step * direction_8[i][0] >= 0 && l_move + move_step * direction_8[i][0] < SIZE_MAP)
			|| !(r_move + move_step * direction_8[i][1] >= 0 && r_move + move_step * direction_8[i][1] < SIZE_MAP)
			|| map[l_move + move_step * direction_8[i][0]][r_move + move_step * direction_8[i][1]] != 0) {
			oppo_length_4_1[i / 2]++;

		}
	}
	for (int i = 0; i < 8; i++) {
		int move_step_f1 = 0;
		while (map[l_move + move_step_f1 * direction_8[i][0]][r_move + move_step_f1 * direction_8[i][1]] == 2
			&&(l_move + move_step_f1 * direction_8[i][0] >= 0 && l_move + move_step_f1 * direction_8[i][0] < SIZE_MAP)
			&& (r_move + move_step_f1 * direction_8[i][1] >= 0 && r_move + move_step_f1 * direction_8[i][1] < SIZE_MAP)) {
			self_length_4_f1[i / 2]++;
			move_step_f1++;
		}
		if (!(l_move + move_step_f1 * direction_8[i][0] >= 0 && l_move + move_step_f1 * direction_8[i][0] < SIZE_MAP)
			|| !(r_move + move_step_f1 * direction_8[i][1] >= 0 && r_move + move_step_f1 * direction_8[i][1] < SIZE_MAP)
			|| map[l_move + move_step_f1 * direction_8[i][0]][r_move + move_step_f1 * direction_8[i][1]] != 0) {
			oppo_length_4_f1[i / 2]++;

		}
	}
	int value_of_this_site = 0;
	for (int i = 0; i < 4; i++) {
		value_of_this_site += compute_exp(self_length_4_1[i], oppo_length_4_1[i]);
		value_of_this_site -= (0.9)*compute_exp(self_length_4_f1[i], oppo_length_4_f1[i]);
	}
	return value_of_this_site;
}

int absolute_value_global() 
{
    int value_of_map = 0;
    for(int i=0;i<SIZE_MAP;i++)
    {
        for(int j=0;j<SIZE_MAP;j++)
        {
        value_of_map+=absolute_value_local(i,j);
        }
    }
    return value_of_map;
}

coordinate min_value_tree(){
    int min_value = 1000000000;
    coordinate min_coordinate = { -1, -1 };
    for (int i = 0; i < SIZE_MAP; i++) {
        for (int j = 0; j < SIZE_MAP; j++) {
            if (map[i][j] == 0) {
                map[i][j] = 2;
                int value_of_this_site = absolute_value_global();
                map[i][j] = 0;
                if (value_of_this_site < min_value) {
                    min_value = value_of_this_site;
                    min_coordinate.x = i;
                    min_coordinate.y = j;
                }
            }
        }
    }
    return min_coordinate;
}

coordinate max_value_tree(){
    int max_value = -1000000000;
    coordinate max_coordinate = { -1, -1 };
    for (int i = 0; i < SIZE_MAP; i++) {    
        for (int j = 0; j < SIZE_MAP; j++) {
            if (map[i][j] == 0) {
                map[i][j] = 1;
                int value_of_this_site = absolute_value_global();
                map[i][j] = 0;
                if (value_of_this_site > max_value) {
                    max_value = value_of_this_site;
                    max_coordinate.x = i;
                    max_coordinate.y = j;
                }
            }
        }
    }
    return max_coordinate;
}

coordinate ai_move() 
{
	int min_value = 1000000000;
	coordinate min_coordinate = { -1, -1 };
	for (int i = 0; i < SIZE_MAP; i++) {
		for (int j = 0; j < SIZE_MAP; j++) {
			if (map[i][j] == 0) {
                map[i][j] = 2;

                coordinate temp_max=max_value_tree();
                map[temp_max.x][temp_max.y]=1;
                int value_of_this_site = absolute_value_global();
                map[temp_max.x][temp_max.y]=0;

				map[i][j] = 0;
                if (value_of_this_site < min_value) {
					min_value = value_of_this_site;
					min_coordinate.x = i;
					min_coordinate.y = j;
				}
			}
		}
	}
    printf("min_value:%d\n",min_value);
	return min_coordinate;
}

void game_start()    //游戏开始
{
    //初始化玩家名
    std::cout<<"Please input your name: ";
    std::cin>>player_name;

    //初始化棋盘
    for(int i=0;i<SIZE_MAP;i++)
    {
        for(int j=0;j<SIZE_MAP;j++)
        {
            map[i][j]=0;
        }
    }
    //玩家1先手
    int player=1;
    //打印棋盘
    print_map();
    //游戏循环
    while(1)
    {
        //玩家输入坐标
        int x,y;
        std::cout<<"Player "<<player_name<<" input x,y: ";
        std::cin>>x>>y;
        //判断输入是否合法
        if(x<0 || x>=SIZE_MAP || y<0 || y>=SIZE_MAP)
        {
            std::cout<<"Invalid input!"<<std::endl;
            continue;
        }
        //判断该位置是否已经有棋子
        if(map[x][y]!=0)
        {
            std::cout<<"This position has already been occupied!"<<std::endl;
            continue;
        }
        //落子
        map[x][y]=player;
        //打印棋盘
        print_map();
        //ai落子
        coordinate ai_coordinate=ai_move();
        map[ai_coordinate.x][ai_coordinate.y]=2;
        //打印棋盘
        print_map();
        round_count++;
    }
}

