/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ Maze algorithm, using a depth first search algorithm
*/

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <iostream>
#include <time.h>
#include <deque>
#include <stack>
#include <string>

enum directions
{
    NORTH,
    SOUTH,
    WEST,
    EAST,
    NONE
};

enum Wall
{
    BORDER,
    EMPTY,
    WALL
};

struct cell
{
    Wall wall;
};

struct position
{
    int mazeColumn, mazeRow;
};

class Maze
{
    private:

    cell ***mazeArray;
    int col;
    int row;
    position mazeExit;
    int exit, exitRow, exitCol;
    int exitNorth, exitSouth, exitWest, exitEast, exitX;
    int sizeRowCol;

    position setMazeEntrance(directions entranceFrom, int entrance);
    bool checkAheadInMaze(int checksOne[], int multiplierOne, int checksTwo[], int multiplierTwo, position checkCell);

    public:

    Maze(int size);
    ~Maze();
	Maze(const Maze &c);

    void mazeAlloc(int size);
    void generateMaze(int mazeCounter, int mazeEntrance, directions direction, bool newMaze=true);
    void printMaze();
    bool getWallf(float x, float y);
    bool getWalli(int x, int y);
    int generateExit(directions dir);
    int getExit(directions dir);
    void setSameExits(int exitOne, int exitTwo, Maze &left, Maze &right);
    void setAllExits(Maze &maze, int exit);
};

#endif // MAZE_H_INCLUDED
