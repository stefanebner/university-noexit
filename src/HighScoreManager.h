/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ Manages the highscore list saved in the data/scores.dat file
*/

#ifndef HIGHSCOREMANAGER_H_INCLUDED
#define HIGHSCOREMANAGER_H_INCLUDED

#include "ofMain.h"
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include <shlobj.h>

using namespace std;

class HighScoreManager
{
public:

    HighScoreManager(char* filePath) :
    path(filePath)
    {
        scoresFile = new int[10];
        namesFile = new string[10];
        getScoresAndNamesFromFile();
    }
    ~HighScoreManager()
    {
        delete path;
        delete scoresFile;
        delete namesFile;
    }
    string getScores();
    int checkScore(int score);
    void addScore(int score, string name);
    bool checkForNewHighscore(int score);

private:

    char* path;
    char* fileP;
    void getScoresAndNamesFromFile();
    int* scoresFile;
    string* namesFile;
    string getFilePath();
    TCHAR p[MAX_PATH];

};

#endif // HIGHSCOREMANAGER_H_INCLUDED
