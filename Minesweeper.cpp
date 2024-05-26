//지뢰찾기
/*rand()% 만 사용하면 항상 똑같은 난수가 나옵니다.
해결하기 위해 매번 실행 시 다른 난수를 생성하기 위해 srand(time(NULL))을 사용했습니다. 
*/
#include <iostream>
#include<time.h>
#include<stdlib.h>

const int MAP_SIZE{ 10 };

void Initialize_MAP(int map[MAP_SIZE][MAP_SIZE])//보이는 첫화면 초기화
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            map[i][j] = 9;
        }
    }
}


void Bomb_Map_Initialize(int stage[MAP_SIZE][MAP_SIZE], int bombNum)//폭탄만들고 초기화
{
    int i, j;
    srand((unsigned int)time(NULL));
    for (i = 0; i < MAP_SIZE; i++)
    {
        for (j = 0; j < MAP_SIZE; j++)
        {
            stage[i][j] = 0;
        }

    }
    for (int b = 0; b < bombNum; b++)
    {
        i = rand() % MAP_SIZE;
        j = rand() % MAP_SIZE;
        if (stage[i][j] == 9)
        {
            bombNum++;
        }
        else
        {
            stage[i][j] = 9;
        }
    }
    for (i = 0; i < MAP_SIZE; i++)
    {
        for (j = 0; j < MAP_SIZE; j++)
        {
            int count{};
            if (stage[i][j] != 9)
            {
                if (stage[i - 1][i - 1] == 9) count++;
                if (stage[i - 1][j] == 9) count++;
                if (stage[i - 1][j + 1] == 9) count++;
                if (stage[i][j - 1] == 9) count++;
                if (stage[i][j + 1] == 9) count++;
                if (stage[i + 1][j - 1] == 9) count++;
                if (stage[i + 1][j] == 9) count++;
                if (stage[i + 1][j + 1] == 9) count++;
                stage[i][j] = count;
            }
        }
    }
}

void ViewDraw(int map[MAP_SIZE][MAP_SIZE], int stage[MAP_SIZE][MAP_SIZE]) //입력시 결과 화면 그리기
{
    int i;
    std::cout << "  ";
    for (i = 0; i < MAP_SIZE; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (i = 0; i < MAP_SIZE; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (map[i][j] == 9)
            {
                std::cout << "* ";
            }
            else if (map[i][j] == -1)
            {
                std::cout << "P ";
            }
            else
            {
                std::cout << stage[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Find_Bomb(int i, int j, int map[MAP_SIZE][MAP_SIZE], int stage[MAP_SIZE][MAP_SIZE]) //지뢰찾기
{
    if (i < 0 || i >= MAP_SIZE || j < 0 || j >= MAP_SIZE || map[i][j] == 0)
    {
        return;
    }
    map[i][j] = stage[i][j];
    if (stage[i][j] != 0)
    {
        return;
    }


    Find_Bomb(i - 1, j, map, stage);
    Find_Bomb(i + 1, j, map, stage);
    Find_Bomb(i, j - 1, map, stage);
    Find_Bomb(i, j + 1, map, stage);
}

bool Input_Move1(int i, int j, int map[MAP_SIZE][MAP_SIZE], int stage[MAP_SIZE][MAP_SIZE])//지뢰찾기 입력
{
    if (stage[i][j] == 9)
    {
        return true;
    }
    else if (stage[i][j] > 0 && stage[i][j] < 9)
    {
        map[i][j] = stage[i][j];
    }
    else if (stage[i][j] == 0)
    {
        Find_Bomb(i, j, map, stage);
    }
    return false;
}

void Input_Move0(int i, int j, int map[MAP_SIZE][MAP_SIZE]) //깃발 꼽기 입력
{
    if (map[i][j] == -1)
    {
        map[i][j] = 9;
    }
    else if (map[i][j] == 9)
    {
        map[i][j] = -1;
    }
}

bool IsClear(int map[MAP_SIZE][MAP_SIZE], int stage[MAP_SIZE][MAP_SIZE])//클리어함수
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (stage[i][j] != 9 && (map[i][j] == 9 || map[i][j] == -1))
            {
                return false;
            }
        }
    }
    return true;
}

void FinalDraw(int stage[MAP_SIZE][MAP_SIZE])// 클리어 또는 실패시 화면 그리기
{
    std::cout << "  ";
    int i;
    for (i = 0; i < MAP_SIZE; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (i = 0; i < MAP_SIZE; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < MAP_SIZE; j++)
        {
            std::cout<< stage[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int map[MAP_SIZE][MAP_SIZE]{};
    int stage[MAP_SIZE][MAP_SIZE]{};
    int i, j, bombNum, move;
    bool boom{};
    std::cout << "폭탄 생성개수를 입력하세요 :";
    std::cin >> bombNum;
    Bomb_Map_Initialize(stage, bombNum);
    Initialize_MAP(map);
    system("cls");

    while (1)
    {
        ViewDraw(map, stage);
        std::cout << " 클릭 할 좌표를 입력하세요 + 깃발 꼽기: 0 , 지뢰 찾기: 1 : " << std::endl;
        std::cout << "(좌표 (1,1) 지뢰 찾기 -> 1 1 1, 좌표 (1,1) 깃발 꼽기 -> 1 1 0)" << std::endl;
        std::cin  >> i >> j >> move;
        if (move == 1)
        {
            boom = Input_Move1(i, j, map, stage);
        }
        else if(move == 0)
        {
            Input_Move0(i, j, map);
        }

        if (boom == 1)
        {
            break;
        }
        if (IsClear(map, stage) == 1)
        {
            break;
        }
        system("cls");
    }
    system("cls");
    FinalDraw(stage);
    if (boom == 1)
    {
        std::cout << " BOOM!!! 지뢰를 밟았습니다." << std::endl;
    }
    else
    {
        std::cout << "축하합니다. CLEAR!!!" << std::endl;
    }
}