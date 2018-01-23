/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ Main - opens th gameManager and the window
*/

//my own headers
#include "HighScoreManager.h"
#include "NoExit.h"
#include "Maze.h"
#include "GameManager.h"
//OF specific headers
#include "ofMain.h"
#include "ofTrueTypeFont.h"
//rest of the headers
#include <cctype>
#include <string>
#include <cmath>

class QPT1Game: public ofBaseApp
{
    private:
        GameManager *gameManager;

	public:
        void setup()
        {
            gameManager = new GameManager;
            gameManager->setup();
        }

        void update()
        {
            gameManager->update();
        }

		void draw()
		{
		    gameManager->draw();
		    string str = "framerate is ";
            str += ofToString(ofGetFrameRate(), 2)+"fps";
            ofSetWindowTitle(str);
		}

		void mouseReleased(int x, int y, int button)
		{
            gameManager->mouseReleasedInManager(x, y, button);
		}

		void keyPressed(int key)
		{
		    gameManager->keyPressedInManager(key);
		}

};


//========================================================================

int main() {
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofBaseApp *application;

    application = new QPT1Game();
    ofRunApp(application);
}

