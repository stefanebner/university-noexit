/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ Maze algorithm, using a depth first search algorithm
*/

#include "Maze.h"

using namespace std;
Maze::Maze(int size = 13)
{
    sizeRowCol = size;
    mazeAlloc(size);
}

Maze::~Maze()
{
    for (int y1 = 0; y1 < col; y1++) {
        for (int x1 = 0; x1 < row; x1++) {
            delete mazeArray[y1][x1];
        }
        delete [] mazeArray[y1];
    }

    delete [] mazeArray;
}

Maze::Maze(const Maze &c)
{
    col=c.col;
    row=c.row;
    mazeExit=c.mazeExit;
    exit=c.exit;
    exitRow=c.exitRow;
    exitCol=c.exitCol;
    exitNorth=c.exitNorth;
    exitSouth=c.exitSouth;
    exitWest=c.exitWest;
    exitEast=c.exitEast;
    exitX=c.exitX;
    sizeRowCol=c.sizeRowCol;

    mazeAlloc(sizeRowCol);

    for (int y1 = 0; y1 < col; y1++)
    {
        for (int x1 = 0; x1 < row; x1++)
        {
            mazeArray[y1][x1]->wall=c.mazeArray[y1][x1]->wall;
        }
    }

}

void Maze::mazeAlloc(int size)
{
    col=row=size;
    mazeArray = new cell**[col];


    for (int y1 = 0; y1 < col; y1++)
    {
        mazeArray[y1] = new cell*[row];
        for (int x1 = 0; x1 < row; x1++)
        {
            mazeArray[y1][x1] = new cell;
            mazeArray[y1][x1]->wall = WALL;
        }
    }
}

position Maze::setMazeEntrance(directions entranceFrom, int entrance)
{
    position currentCell;

    switch(entranceFrom)
    {
    case NONE:
        mazeArray[6][6]->wall=EMPTY;
        currentCell.mazeRow=6;
        currentCell.mazeColumn=6;
        mazeArray[6][5]->wall=EMPTY;
        currentCell.mazeRow=5;
        currentCell.mazeColumn=6;
        mazeArray[6][4]->wall=EMPTY;
        currentCell.mazeRow=4;
        currentCell.mazeColumn=6;
        break;

    case NORTH:
        mazeArray[entrance][1]->wall = EMPTY;
        currentCell.mazeRow=1;
        currentCell.mazeColumn=entrance;
        break;

    case SOUTH:
        mazeArray[entrance][11]->wall = EMPTY;
        currentCell.mazeRow=11;
        currentCell.mazeColumn=entrance;
        break;

    case EAST:
        mazeArray[11][entrance]->wall = EMPTY;
        currentCell.mazeColumn=11;
        currentCell.mazeRow=entrance;
        break;

    case WEST:
        mazeArray[1][entrance]->wall = EMPTY;
        currentCell.mazeColumn=1;
        currentCell.mazeRow=entrance;
        break;
    }
    return currentCell;
}

void Maze::generateMaze(int mazeCounter, int mazeEntrance, directions direction, bool newMaze)
{
    directions possibleDirections[24][4] =
    {
        { WEST, SOUTH, NORTH, EAST }, { WEST, SOUTH, EAST, NORTH }, { WEST, NORTH, SOUTH, EAST },
        { WEST, NORTH, EAST, SOUTH }, { WEST, EAST, SOUTH, NORTH }, { WEST, EAST, NORTH, SOUTH },
        { SOUTH, WEST, NORTH, EAST }, { SOUTH, WEST, EAST, NORTH }, { SOUTH, NORTH, WEST, EAST },
        { SOUTH, NORTH, EAST, WEST }, { SOUTH, EAST, WEST, NORTH }, { SOUTH, EAST, NORTH, WEST },
        { NORTH, SOUTH, WEST, EAST }, { NORTH, SOUTH, EAST, WEST }, { NORTH, WEST, SOUTH, EAST },
        { NORTH, WEST, EAST, SOUTH }, { NORTH, EAST, SOUTH, WEST }, { NORTH, EAST, WEST, SOUTH },
        { EAST, SOUTH, NORTH, WEST }, { EAST, SOUTH, WEST, NORTH }, { EAST, NORTH, SOUTH, WEST },
        { EAST, NORTH, WEST, SOUTH }, { EAST, WEST, SOUTH, NORTH }, { EAST, WEST, NORTH, SOUTH }
    };

    exitX=                      mazeEntrance;
    stack<position>             cellStack;
    position                    entrance, exit, currentCell, nextCell;
    int mazeRow=                row-1;
    int mazeCol=                col-1;
    bool DFS=                   true;
    bool successfull=           false;
    bool goBackOneCell=         true;
    int possibleChecksOne[6]=   {1 , 1 , 1 , 2 , 2 , 2};
    int possibleChecksTwo[6]=   {0 ,-1 ,+1 , 0 ,-1 ,+1};
    srand((unsigned)time(0));

    currentCell=setMazeEntrance(direction, mazeEntrance);
    cellStack.push(currentCell);
    nextCell.mazeRow=currentCell.mazeRow;
    nextCell.mazeColumn=currentCell.mazeColumn;

    while (DFS)
    {
        goBackOneCell = true;
        int listOfDirections = rand()%24;
        for (int direction=0; direction<4; direction++)
        {
                successfull = false;
                switch (possibleDirections[listOfDirections][direction])
                {
                    case WEST:
                    if  (currentCell.mazeColumn>=2 && checkAheadInMaze(possibleChecksOne, -1, possibleChecksTwo, 1, currentCell))
                    {
                        nextCell.mazeColumn=currentCell.mazeColumn-1;
                        nextCell.mazeRow=currentCell.mazeRow;
                        successfull = true;
                    }
                    break;

                    case EAST:
                    if  (currentCell.mazeColumn<=sizeRowCol-3 && checkAheadInMaze(possibleChecksOne, 1, possibleChecksTwo, 1, currentCell))
                    {
                        nextCell.mazeColumn=currentCell.mazeColumn+1;
                        nextCell.mazeRow=currentCell.mazeRow;
                        successfull = true;
                    }
                    break;

                    case NORTH:
                    if  (currentCell.mazeRow>=2 && checkAheadInMaze(possibleChecksTwo, 1, possibleChecksOne, -1, currentCell))
                    {
                        nextCell.mazeRow=currentCell.mazeRow-1;
                        nextCell.mazeColumn=currentCell.mazeColumn;
                        successfull = true;
                    }
                    break;

                    case SOUTH:
                    if  (currentCell.mazeRow <= sizeRowCol-3 && checkAheadInMaze(possibleChecksTwo, 1, possibleChecksOne, 1, currentCell))
                    {
                        nextCell.mazeRow=currentCell.mazeRow+1;
                        nextCell.mazeColumn=currentCell.mazeColumn;
                        successfull = true;
                    }
                    break;
                }

                if (successfull)
                {
                        cellStack.push(currentCell);
                        mazeArray[nextCell.mazeColumn][nextCell.mazeRow]->wall=EMPTY;
                        currentCell=nextCell;
                        goBackOneCell=false;
                        successfull=false;
                }
                else continue;
        }

        if (goBackOneCell)
        {//if the stack is empty == done
            if (cellStack.empty()) DFS = false;
            else
            {// start again in the last cell
                currentCell=cellStack.top();
                cellStack.pop();
            }
        }
    }
}

bool Maze::checkAheadInMaze(int checksOne[], int multiplierOne, int checksTwo[], int multiplierTwo, position checkCell)
{
    if(
        mazeArray[checkCell.mazeColumn+(checksOne[0]*multiplierOne)][checkCell.mazeRow+(checksTwo[0]*multiplierTwo)]->wall == WALL &&
        mazeArray[checkCell.mazeColumn+(checksOne[1]*multiplierOne)][checkCell.mazeRow+(checksTwo[1]*multiplierTwo)]->wall == WALL &&
        mazeArray[checkCell.mazeColumn+(checksOne[2]*multiplierOne)][checkCell.mazeRow+(checksTwo[2]*multiplierTwo)]->wall == WALL &&
        mazeArray[checkCell.mazeColumn+(checksOne[3]*multiplierOne)][checkCell.mazeRow+(checksTwo[3]*multiplierTwo)]->wall == WALL &&
        mazeArray[checkCell.mazeColumn+(checksOne[4]*multiplierOne)][checkCell.mazeRow+(checksTwo[4]*multiplierTwo)]->wall == WALL &&
        mazeArray[checkCell.mazeColumn+(checksOne[5]*multiplierOne)][checkCell.mazeRow+(checksTwo[5]*multiplierTwo)]->wall == WALL
       )    return true;
       else return false;
}

bool Maze::getWallf(float x, float y)
{
    int a,b;
    a=(int)x;
    b=(int)y;
    if (mazeArray[a][b]->wall==WALL)
        return true;
    else return false;
}

bool Maze::getWalli(int x, int y)
{
    if (mazeArray[x][y]->wall==WALL)
    {
        return true;
    }
    else return false;
}

int Maze::getExit(directions dir)
{
    switch(dir)
    {
        case EAST:
        return exitEast;
        break;
        case WEST:
        return exitWest;
        break;
        case NORTH:
        return exitNorth;
        break;
        case SOUTH:
        return exitSouth;
        break;
        case NONE:
        break;
        default:
        break;
    }
}

int Maze::generateExit(directions dir)
{
    if(dir!=NORTH)
    {
        exitCol = sizeRowCol/2 ;
        exitRow = 0;
        while(exitCol<12)
        {
            if(this->mazeArray[exitCol][exitRow+1]->wall == EMPTY)
                break;
            if(exitCol==11) exitCol = 1;
            exitCol++;
        }
        exitNorth = exitCol;
        this->mazeArray[exitCol][exitRow]->wall = EMPTY;
    }
    else
    {
        exitNorth=exitX;
        this->mazeArray[exitX][0]->wall = EMPTY;
    }

    if(dir!=SOUTH)
    {
        exitCol = sizeRowCol/2;
        exitRow = sizeRowCol-1;
        while(exitCol>1)
        {
            if(this->mazeArray[exitCol][exitRow-1]->wall == EMPTY) break;
            if(exitCol==2) exitCol = sizeRowCol-1;
            exitCol--;
        }
        exitSouth = exitCol;
        this->mazeArray[exitCol][exitRow]->wall = EMPTY;
    }
    else
    {
        exitSouth=exitX;
        this->mazeArray[exitX][sizeRowCol-1]->wall = EMPTY;
    }

    if(dir!=EAST)
    {
        exitCol = 0;
        exitRow = sizeRowCol/2;
        while(exitRow<12)
        {
            if(this->mazeArray[sizeRowCol-2][exitRow]->wall == EMPTY)
            {
                this->mazeArray[sizeRowCol-1][exitRow]->wall = EMPTY;
                break;
            }
            if(exitRow==11) exitRow = 1;
            exitRow++;
        }
        exitEast=exitRow;
    }
    else
    {
        exitEast=exitX;
        this->mazeArray[sizeRowCol-1][exitX]->wall = EMPTY;
    }

    if(dir!=WEST)
    {
        exitCol = sizeRowCol-1;
        exitRow = sizeRowCol/2;
        while(exitRow>1)
        {
            if(this->mazeArray[1][exitRow]->wall == EMPTY)
            {
                this->mazeArray[0][exitRow]->wall = EMPTY;
                break;
            }
            if(exitRow==2) exitRow=sizeRowCol-1;
            exitRow--;
        }
        exitWest = exitRow;
    }
    else
    {
        exitWest=exitX;
        this->mazeArray[0][exitX]->wall = EMPTY;
    }
}

void Maze::setSameExits(int exitOne, int exitTwo, Maze &left, Maze &right)
{
    setAllExits(left, exitOne);
    setAllExits(right, exitTwo);
}

void Maze::setAllExits(Maze &maze, int exit)
{
    maze.mazeArray[0][exit]->wall = EMPTY;
    maze.mazeArray[sizeRowCol-1][exit]->wall = EMPTY;
    maze.mazeArray[exit][0]->wall = EMPTY;
    maze.mazeArray[exit][sizeRowCol-1]->wall = EMPTY;
}
