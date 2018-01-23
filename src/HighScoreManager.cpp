/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ Manages the highscore list saved in the data/scores.dat file
*/

#include "HighScoreManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string HighScoreManager::getFilePath()
{

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, p);
    string filePath = p;
    filePath +="\\scores.dat";
    return filePath;

}

string HighScoreManager::getScores()
{
    string highScores;
    for(int i = 0; i < 10; i++)
    {
        string line;
        if(i<9) line+="0";
        line += ofToString(i+1) + ". ";
        if(scoresFile[i] < 1000) line += "0";
        line += ofToString(scoresFile[i]) + " ";
        line += namesFile[i];
        line += "\n";
        highScores += line;
    }
    return highScores;
}

int HighScoreManager::checkScore(int score)
{
    int index = -1;
    for(int i = 0; i < 10; i++)
    {
        if(score > scoresFile[i])
        {
            index = i;
            break;
        }
    }
    return index;
}

bool HighScoreManager::checkForNewHighscore(int score)
{
    for(int i = 0; i< 10; i++)
    {
        if (score > scoresFile[i])
            return true;
    }
    return false;

}

void HighScoreManager::addScore(int score, string name)
{
    int index  = checkScore(score);

    for(int i = 8; i >= index; i--) {
        scoresFile[i + 1] = scoresFile[i];
        namesFile[i + 1] = namesFile[i];
    }
    scoresFile[index] = score;
    namesFile[index] = name;

    string tempPath = getFilePath();

    char abcd[tempPath.size()+1];
    strcpy(abcd, tempPath.c_str());

    fstream file;
    file.open(abcd);
    if (!file.good()) cerr << "could not open file";

    for(int i = 0; i < 10; i++)
    {
        file << scoresFile[i] << " ";
        file << namesFile[i] << "\n";
    }
    file.close();
}



void HighScoreManager::getScoresAndNamesFromFile()
{
    ifstream file;
    file.open(path);

    int index = 0;
    for(int i = 1; i <= 10 && !file.eof(); i++)
    {
        string line = "";
        int points;
        string name;
        getline(file, line);
        points=ofToInt(line.substr(0, 4));
        name = line.substr(5, 3);
        scoresFile[index] = points;
        namesFile[index] = name;
        index++;
    }
    file.close();
}
