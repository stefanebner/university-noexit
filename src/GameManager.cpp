/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ GameManager class to handle the different gamestates
*/

#include"GameManager.h"

using namespace std;

string GameManager::getLocalFile()
{

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, path);
    string filePath = path;
    filePath +="\\scores.dat";
    if(!checkForFile(filePath))
    {
        createFile(filePath);
    }
    return filePath;

}

bool GameManager::checkForFile(string fName)
{
      struct stat stFileInfo;
      bool blnReturn;
      int intStat;
      intStat = stat(fName.c_str(),&stFileInfo);
      if(intStat == 0) blnReturn = true;
      else blnReturn = false;


      return(blnReturn);
return true;
}

void GameManager::createFile(string localPath)
{
    ofstream myFile;

    char abcd[localPath.size()+1];
    strcpy(abcd, localPath.c_str());

    myFile.open(abcd);
    myFile<<"5000 ARU\n";
    myFile<<"4500 ARU\n";
    myFile<<"4000 ARU\n";
    myFile<<"3500 ARU\n";
    myFile<<"3000 ARU\n";
    myFile<<"2500 ARU\n";
    myFile<<"2000 ARU\n";
    myFile<<"1500 ARU\n";
    myFile<<"1337 ARU\n";
    myFile<<"1000 ARU\n";

    myFile.close();
}

void GameManager::setup()
{
    game = new NoExit();
    game->resetAll();

    ofBackground(255, 255, 255);
    ofNoFill();
    ofSetVerticalSync(true);

    //loading the font
    gameFont.loadFont("rou.TTF", 18, true, true);
    gameFont2.loadFont("rou.TTF", 52, true, true);
    menuFont.loadFont("verdana.ttf", 18, true, true);

    gameState = STARTMENU;

    //load highscores
    string highscore = getLocalFile();

    char abcd[highscore.size()+1];
    strcpy(abcd, highscore.c_str());

    scoreManager = new HighScoreManager(abcd);

    startText = "Start 1P Game";
    controlsText = "Controls";
    controls = CONTROLSTEXT;
    scoresText = "Highscores";
    highScores = scoreManager->getScores();

    enterName += "You entered the top ten!\n";
    enterName += " Please enter your initials, min 3:";

    restartButtonText = "Restart";
    player1Name = "";
    exitText = "EXIT";
    backText = "Back";
    welcomeText = "noExit?";

    nameEntered = true;

    bool result = logo.loadImage("logo.jpg");
    if (!result) ofLog(OF_LOG_ERROR, "Failed to load image floor");
}


void GameManager::update()
{
    if(game->getGameStopped())
    {
        gameState = GAMEOVER;
    }

    switch(gameState)
    {
        case STARTMENU:
            ofShowCursor();

            startButton = menuFont.getStringBoundingBox(startText, ofGetWidth()-30, ofGetHeight()/2);
            startButton.x -= (startButton.width + 5);
            startButton.y -= (startButton.height/2 -50 + 5);
            startButton.width += 5;
            startButton.height += 5;

            controlsButton = menuFont.getStringBoundingBox(controlsText, ofGetWidth()-30, ofGetHeight()/2);
            controlsButton.x -= (controlsButton.width + 5);
            controlsButton.y -= (controlsButton.height/2 -90 + 5);
            controlsButton.width += 5;
            controlsButton.height += 5;

            scoresButton = menuFont.getStringBoundingBox(scoresText, ofGetWidth()-30, ofGetHeight()/2);
            scoresButton.x -= (scoresButton.width + 5);
            scoresButton.y -= (scoresButton.height/2 - 130 + 5);
            scoresButton.width += 5;
            scoresButton.height += 5;

            exitButton = menuFont.getStringBoundingBox(exitText, ofGetWidth()-30, ofGetHeight()/2);
            exitButton.x -= (exitButton.width + 5);
            exitButton.y -= exitButton.height/2 - 160 -5;
            exitButton.width += 5;
            exitButton.height += 5;
            break;

        case CONTROLS:
            ofShowCursor();
            backButton = menuFont.getStringBoundingBox(backText, ofGetWidth()-50, ofGetHeight()/2-80);
            backButton.x -= (backButton.width/2 + 5);
            backButton.y += 5;
            backButton.width += 5;
            backButton.height += 5;

            controlsBox = menuFont.getStringBoundingBox(controls, 0, 0);
            break;

        case SCORES:
            ofShowCursor();
            backButton = menuFont.getStringBoundingBox(backText, ofGetWidth()-50, ofGetHeight()/2-80);
            backButton.x -= (backButton.width/2 + 5);    backButton.y += 5;
            backButton.width += 5; backButton.height += 5;
            highScoresBox = menuFont.getStringBoundingBox(highScores, 0, 0);
            break;

        case GAMEOVER:
            ofShowCursor();
            backButton = menuFont.getStringBoundingBox(backText, ofGetWidth()-55, ofGetHeight()/2-80);
            backButton.x -= (backButton.width/2 + 5);
            backButton.y += 5;
            backButton.width += 5;
            backButton.height += 5;
            highScoresBox = menuFont.getStringBoundingBox(highScores, 0, 0);
            exitButton = menuFont.getStringBoundingBox(exitText, ofGetWidth()-55, ofGetHeight()/2 - 130);
            exitButton.x -= (exitButton.width/2 + 5);
            exitButton.width += 5;
            exitButton.height += 5;
            restartButton = menuFont.getStringBoundingBox(restartButtonText, ofGetWidth()-70, ofGetHeight()/2-110);
            restartButton.x -= (restartButton.width/2 + 5);    restartButton.y += 5;
            restartButton.width += 5; restartButton.height += 5;
            break;

        case GAME1P:
            game->update();
            break;
    }
}

void GameManager::draw()
{
    ofSetColor(1,1,1);
    switch (gameState)
    {
    case STARTMENU:
        drawLogo();
        menuFont.drawString(startText, startButton.x, startButton.y + startButton.height - 5);
        menuFont.drawString(controlsText, controlsButton.x, controlsButton.y + controlsButton.height - 5);
        menuFont.drawString(scoresText, scoresButton.x, scoresButton.y + scoresButton.height - 5);
        menuFont.drawString(exitText, exitButton.x, exitButton.y + exitButton.height - 5);
        gameFont2.drawString(welcomeText, ofGetWidth()-300, ofGetHeight()/2);
        break;

    case CONTROLS:
        drawLogo();
        menuFont.drawString(controls, ofGetWidth() -370 , ofGetHeight()/2 +50);
        menuFont.drawString(backText, backButton.x, backButton.y + backButton.height - 5);
        gameFont2.drawString(welcomeText, ofGetWidth()-300, ofGetHeight()/2);
        break;

    case SCORES:
        drawLogo();
        menuFont.drawString(highScores, ofGetWidth() -195 , ofGetHeight()/2 +50);
        menuFont.drawString(backText, backButton.x, backButton.y + backButton.height - 5);
        gameFont2.drawString(welcomeText, ofGetWidth()-300, ofGetHeight()/2);
        break;

    case GAMEOVER:
        drawLogo();
        if(scoreManager->checkForNewHighscore(game->returnScore()) == true)
        {
            menuFont.drawString(enterName, ofGetWidth()-650, ofGetHeight()/2 +50);
            menuFont.drawString(player1Name, ofGetWidth()-285, ofGetHeight()/2 +130);
        }
        else if(nameEntered == true)
            menuFont.drawString(restartButtonText, restartButton.x, restartButton.y + restartButton.height - 5);
        menuFont.drawString(backText, backButton.x, backButton.y + backButton.height - 5);
        menuFont.drawString(highScores, ofGetWidth() -195 , ofGetHeight()/2 +50);
        menuFont.drawString(exitText, exitButton.x, exitButton.y + exitButton.height - 5);
        gameFont2.drawString(welcomeText, ofGetWidth()-300, ofGetHeight()/2);
        break;

    case GAME1P:
        game->draw();
        break;
    }
}

void GameManager::drawLogo()
{
    bool result = logo.loadImage("logo.jpg");
    if (!result) ofLog(OF_LOG_ERROR, "Failed to load image floor");
    ofNoFill();
    ofSetColor(255, 255, 255);
    logo.draw(ofGetWidth()-158, ofGetHeight()-80);
    ofSetColor(1,1,1);
}

void GameManager::keyPressedInManager(int key)
{
    if (gameState == GAMEOVER || gameState == STARTMENU || gameState == SCORES || gameState == CONTROLS)
    {
        if(key==OF_KEY_ESC)
        {
            delete game;
            OF_EXIT_APP(0);
        }
    }

    if (gameState == GAME1P)
    {
        if(key==OF_KEY_RETURN)
        {
            gameState=STARTMENU;
            game->resetAll();
        }
        else
            game->keyPressedGame(key);
    }

    else if (gameState == GAMEOVER && scoreManager->checkForNewHighscore(game->returnScore())==true )
    {
        nameEntered = false;
        if (key==8 && player1Name.size()==0)
            player1Name="";
        else if(key==8 && player1Name.size()>0)
        { // backspace
            player1Name = player1Name.substr(0, player1Name.size()-1); // delete one character
        }
        else if (player1Name.size() > 3)
        {
            player1Name = player1Name.substr(0, player1Name.size()-1);
        }
        else if (player1Name.size()<3)
        {
            char upper = (char)key;
            upper = toupper(upper);
            player1Name.append (1, upper );
        }
        else if (key==OF_KEY_RETURN && player1Name.size()==3)
        {
            scoreManager->addScore(game->returnScore(), player1Name);
            highScores = scoreManager->getScores();
            gameState = GAMEOVER;
            player1Name = "";
            game->resetAll();
            nameEntered = true;
        }

    }
}

void GameManager::mouseReleasedInManager(int x, int y, int button)
{
    switch(gameState)
    {
        case STARTMENU:
        {
            if((x >= startButton.x && x <= startButton.x + startButton.width) &&
                (y >= startButton.y && y <= startButton.y + startButton.height))
            {
                gameState = GAME1P;
                game->setup();
            }

            else if((x >= controlsButton.x && x <= controlsButton.x + controlsButton.width) &&
                (y >= controlsButton.y && y <= controlsButton.y + controlsButton.height))
            {
                gameState = CONTROLS;
            }

            else if((x >= scoresButton.x && x <= scoresButton.x + scoresButton.width) &&
                (y >= scoresButton.y && y <= scoresButton.y + scoresButton.height))
            {
                gameState = SCORES;
            }
            else if((x >= exitButton.x && x <= exitButton.x + exitButton.width) &&
                    (y >= exitButton.y && y <= exitButton.y + exitButton.height))
            {
                delete game;
                OF_EXIT_APP(0);
            }
        }

        case CONTROLS: case SCORES:
            if((x >= backButton.x && x <= backButton.x + backButton.width) &&
               (y >= backButton.y && y <= backButton.y + backButton.height))
                {
                    gameState = STARTMENU;
                }
            break;

        case GAMEOVER:
            if((x >= restartButton.x && x <= restartButton.x + restartButton.width) &&
                (y >= restartButton.y && y <= restartButton.y + restartButton.height)
                && nameEntered == true)
            {
                game->resetAll();
                gameState = GAME1P;
            }

            else if((x >= backButton.x && x <= backButton.x + backButton.width) &&
             (y >= backButton.y && y <= backButton.y + backButton.height))
            {
                game->resetAll();
                gameState = STARTMENU;
            }

            else if((x >= exitButton.x && x <= exitButton.x + exitButton.width) &&
                    (y >= exitButton.y && y <= exitButton.y + exitButton.height))
            {
                delete game;
                exit();
                OF_EXIT_APP(0);
            }
            break;
    }
}

bool GameManager::animateNextFrame(int desiredFrameRate)
{
	static float lastTime = GetTickCount() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f; // Get the time (milliseconds = seconds * .001)
	float deltaTime = currentTime - lastTime; // Get the slice of time
	float desiredFPS = 1.0f / desiredFrameRate; // Store 1 / desiredFrameRate

	elapsedTime += deltaTime; // Add to the elapsed time
	lastTime = currentTime; // Update lastTime

	// Check if the time since we last checked is greater than our desiredFPS
	if( elapsedTime > desiredFPS )
	{
		elapsedTime -= desiredFPS; // Adjust the elapsed time

		// Return true, to animate the next frame of animation
		return true;
	}

	// We don't animate right now.
	return false;
}
