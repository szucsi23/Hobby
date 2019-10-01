#include <iostream>
#include <ctime>

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

enum Direction {
    NORTH, EAST, SOUTH, WEST
};

struct SDL_Point {
    int x = 0;
    int y = 1;
};

bool grid[GRID_WIDTH] [GRID_HEIGHT];

void ResetGrid();
int validPoint(SDL_Point p);
void createMaze(SDL_Point p);
void PrintGrid();

int main()
{

    srand( time(0) );
    ResetGrid();
    SDL_Point point;
    createMaze(point);
    PrintGrid();
    return 0;
}
void ResetGrid()
{

    for (int i=0; i<GRID_HEIGHT; ++i)
    {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grid[i][j] = false;
        }

    }
}

int validPoint(SDL_Point p)
{
    if (p.x < 0 || p.x >= GRID_WIDTH) return false;
    if (p.y < 0 || p.y >= GRID_HEIGHT) return false;
    return true;
}

void createMaze(SDL_Point p)
{
    grid[p.x][p.y] = true;

    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;
    for (int i=0; i<4; ++i)
    {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }

    for (int i=0; i<4; ++i)
    {
        int dx=0, dy=0;
        switch (dirs[i])
        {
            case NORTH: dy = -1; break;
            case SOUTH: dy = 1; break;
            case EAST: dx = 1; break;
            case WEST: dx = -1; break;
        }

        SDL_Point p2;
        p2.x = p.x + (dx*2);
        p2.y = p.y + (dy*2);
        if (validPoint(p2))
        {
            if (grid[p2.x][p2.y] == false)
            {
                grid[p2.x-dx][p2.y-dy] = true;
                createMaze(p2);
            }
        }
    }
}
void PrintGrid()
{

    for (int y=0; y<GRID_HEIGHT; ++y)
    {
        for (int x=0; x<GRID_WIDTH; ++x)
        {
            if(grid[x][y]) std::cout << ' ';
            else std::cout << '#';
        }
        std::cout << std::endl;
    }
}