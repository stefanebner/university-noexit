#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "HighScoreManager.h"
#include "NoExit.h"
#include "Maze.h"
#include "Variables.h"

#include "ofMain.h"
#include "ofTrueTypeFont.h"

#include <cctype>
#include <string>
#include <cmath>
#include <iostream>
#include "windows.h"
#include <shlobj.h>
//#include <stdlib.h>
#include <sys/stat.h>



enum GameState {STARTMENU, GAME1P, GAMEOVER, CONTROLS, SCORES};

class GameManager: public ofBaseApp
{
    public:
    GameManager()
        {}

    ~GameManager()
    {
        delete game;
    }

	private:
        NoExit *game;
        //both fonts ill be using
        ofTrueTypeFont::ofTrueTypeFont gameFont;
        ofTrueTypeFont::ofTrueTypeFont gameFont2;
        ofTrueTypeFont::ofTrueTypeFont menuFont;
        //determines current gamestate
        GameState gameState;
        //manipulate the highscore
        HighScoreManager* scoreManager;
		//miscellaneous buttons
		string welcomeText;
		string startText;
		string controlsText;
		string controls;
		string exitText;
		string scoresText;
		string highScores;
		string restartButtonText;
		string player1Name;
		string backText;
		string enterName;
        //Boxes to check for mouse clicks
		ofRectangle controlsButton;
		ofRectangle controlsBox;
		ofRectangle exitButton;
		ofRectangle scoresButton;
		ofRectangle highScoresBox;
		ofRectangle restartButton;
		ofRectangle backToMenuButton;
		ofRectangle backButton;
		ofRectangle playerNameBox;
		ofRectangle startButton;
		//FH-Logo
		ofImage logo;
        bool animateNextFrame(int desiredFrameRate);
        void drawLogo();
        TCHAR path[MAX_PATH];
        bool nameEntered;

	public:
        void setup();
        void update();
        void draw();
        void keyPressedInManager(int key);
		void mouseReleasedInManager(int x, int y, int button);
		string getLocalFile();
		bool checkForFile(string fName);
		void createFile(string localPath);


};

#endif // GAMEMANAGER_H_INCLUDED
