/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ The game itself
*/

#ifndef NOEXIT_H_INCLUDED
#define NOEXIT_H_INCLUDED

#include "HighScoreManager.h"
#include "Maze.h"
#include "Variables.h"

#include "ofMain.h"
#include "ofTrueTypeFont.h"

#include <cctype>
#include <string>
#include <cmath>
#include "assert.h"


class NoExit: public ofBaseApp
{
    public:
        NoExit();

        ~NoExit();

		void update();
		void draw();
        void resetAll();
        void deleteAll();
        int returnScore();
        void keyPressedGame(int key);
        void playerPositioning(float z=0, float y=0);
        bool getGameStopped();
        void setGameStopped();


    private:
        int mazeSize;
        //the 4 Mazes
        Maze *current, *up, *down, *left, *right;
        //rotation
        int rotatedLeft, rotatedRight;
        int rotatedAngle;
        bool rotateCCW, rotateCW;
        //cube&player position
        float moveDown, moveZ, moveY, moveTemp, movePlayer, increasingMoveSpeed;
        ofPoint player;
        int positionY, positionZ;
        //roation of the cube to another side
        bool exitFound, exitRotation;;
        int northExit, southExit, westExit, eastExit;
        float rotation;
        bool rotationStarted;
        int counter;
        //help with gamestate
        bool restart, gameStopped;
        //both fonts ill be using
        ofTrueTypeFont::ofTrueTypeFont inGameFont2;
        ofTrueTypeFont::ofTrueTypeFont inGameFont;
        //highscore
        int player1Score, player2Score, currentPoints;
        char scoreBuffer[33];
        float currentFrames;

        void rotateCube();
        void setCurrentExits();
        void generateMazes(directions dir, directions dir2);
        void setNewMazes();
        void moveCube();
        void drawMaze(Maze *mazeDraw, float x, float y, float z, bool doBoundingBox=false, float moveZ=0, float moveY=0);
        bool collisionDetected();
        bool checkForExit();
        void setLights();
        void setEmissionMaterial(float r , float g , float b );
        void drawMazeWall();
        void drawCube();
        void setLight(int i, float r, float g, float b);
        void setShinyMaterial();
        void setMatteMaterial();
        void initializeNoExit();
};


#endif // NOEXIT_H_INCLUDED
