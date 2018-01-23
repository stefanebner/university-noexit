/*
 *  QPT1
 *	Stefan Ebner
 *	2.Semester MMT
 *
 *  FH-Salzburg
 *
 *  @ The game itself
*/

#include "NoExit.h"
NoExit::~NoExit()
{
    resetAll();
    deleteAll();
}

NoExit::NoExit()
{
    initializeNoExit();
}

void NoExit::update()
    {
    if (counter<300) counter++;
    playerPositioning();

    if(!collisionDetected() && !rotationStarted && counter >210)
    {
        rotateCube();
        moveCube();
        player1Score+=currentPoints;
    }

    //keeps the rotationangle of the cube between 0 <-> 360
    if(rotatedAngle<0) rotatedAngle+=360;
    if(rotatedAngle%360>=1) rotatedAngle-=360;
    }

void NoExit::draw()
    {

    // set viewport
    int width, height;
    width = ofGetWidth();
    height = ofGetHeight();
    glViewport(0, 0, width, height);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set perspective projection
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
        glEnable(GL_DEPTH_TEST);
//                glDisable(GL_DEPTH);
        glLoadIdentity();
        glOrtho(0, width, height, 0, 0.0f, 30.0f);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            ofSetColor(255,0,0, 1);
            glColor3f(1, 1, 1);
            //countdown and short instruction
            if(counter<210)
                inGameFont.drawString("Goal:\n-reach the exit\n-dont touch the walls", width-330, 30);

            if(counter<60)
            {
                inGameFont2.drawString("3", width/2-26, 50);
            }
            if(counter>60 && counter <120)
            {
                inGameFont2.drawString("2", width/2-26, 50);
            }
            if(counter>120 && counter <180)
            {
                inGameFont2.drawString("1", width/2-26, 50);
            }
            if(counter>180 && counter <210)
            {
                inGameFont2.drawString("Begin", width/2-115, 50);
            }

            else if(counter > 210)
            {
                inGameFont.setLineHeight(30);
                string points = "Current Points: ";
                inGameFont.drawString(points, width/2-150, 20);
                itoa(player1Score, scoreBuffer, 10);
                inGameFont.drawString(scoreBuffer, width/2+150, 20);
            }
//                    ofSetColor(255,255,255);
        glPopMatrix();
    glPopMatrix();

    // clear viewport
    glClearColor(0.0, 0.0, 0.5, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (float)width / height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set camera position
    float time = ofGetElapsedTimef();
    gluLookAt(4.0 , 0.2 , 0.2 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    setLights();

    // place the player in the world
    glPushMatrix();
        glColor3f(1,0,0);
        setLight(2,0.5,0,0);
        glutSolidSphere(0.02,30,30);
    glPopMatrix();

    //check if an exit has been successfully reached
    bool needToSetExits = false;
    if(checkForExit() || rotationStarted)
    {
        rotation+=3;
        glRotatef(rotation,0,1,0);
    }
    {
   //draw mainscene
    glPushMatrix();
        {
        if(rotateCCW==true)
        {
            glRotatef(rotatedLeft+rotatedAngle,1,0,0);
        }
        else if(rotateCW==true)
        {
            glRotatef(rotatedRight+rotatedAngle,1,0,0);
        }
        else
        {
            glRotatef(rotatedAngle,1,0,0);
        }

            glPushMatrix();
            {
                if(rotation==90)
                {
                    increasingMoveSpeed+=0.002;
                    rotationStarted=false;
                    setNewMazes();
                    rotation=0;
                    currentPoints++;
                    glTranslatef(0, moveY, moveZ);
                }
                else glTranslatef(0, moveY,moveZ);

                setMatteMaterial();
                drawCube();
                glColor3f(0.15, 0.15, 0.15);
                drawMaze(current, 0, -1.2, 1.2, true, moveZ, moveY);

                if((rotationStarted && rotatedAngle == 0) || !rotationStarted)
                {
                    glPushMatrix();
//North maze
                        glRotatef(-90,0,1,0);
                        glTranslatef(1.2,0,1.2);
                        drawCube();
                        glColor3f(0.15, 0.15, 0.15);
                        drawMaze(up, 0, -1.2, 1.2);
                    glPopMatrix();
                }

//south maze
                if((rotationStarted && rotatedAngle == -180) || !rotationStarted)
                {
                    glPushMatrix();
                        glRotatef(90,0,1,0);
                        glTranslatef(1.2,0, -1.2);
                        drawCube();
                        glColor3f(0.15, 0.15, 0.15);
                        drawMaze(down, 0, -1.2, 1.2);
                    glPopMatrix();
                }
//EAST maze
                if((rotationStarted && rotatedAngle == -270) || !rotationStarted)
                {
                    glPushMatrix();
                        glRotatef(90,0,0,1);
                        glTranslatef(1.2,1.2,0);
                        drawCube();
                        glColor3f(0.15, 0.15, 0.15);
                        drawMaze(right, 0, -1.2, 1.2);
                    glPopMatrix();
                }

                if((rotationStarted && rotatedAngle == -90) || !rotationStarted)
                {
                    glPushMatrix();
                        glRotatef(-90,0,0,1);
                        glTranslatef(1.2, -1.2 ,0);
                        drawCube();
                        glColor3f(0.15, 0.15, 0.15);
                        drawMaze(left, 0, -1.2, 1.2);
                    glPopMatrix();
                }
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
}

void NoExit::rotateCube()
{
    //rotates the cube when the button is pressed
    if(rotateCCW==true && rotatedLeft >=-90)
    {
        rotatedLeft-=10;
    }
    if(rotatedLeft==-90)
    {
        rotatedLeft=0;
        rotateCCW=false;
        rotatedAngle-=90;
    }

    if(rotateCW== true && rotatedRight <=90)
    {
        rotatedRight+=10;
    }
    if(rotatedRight==90)
    {
        rotateCW=false;
        rotatedRight=0;
        rotatedAngle+=90;
    }
}

int NoExit::returnScore()
{
    return player1Score;
}

void NoExit::keyPressedGame(int key)
{
    switch (key)
        {
            case OF_KEY_LEFT:
                playerPositioning();
                if(!gameStopped && (positionY != 0 || positionY != 12 || positionZ != 0 || positionZ != 12))
                    rotateCCW= true;
                else rotateCCW = false;
                break;
            case OF_KEY_RIGHT:
                if(!gameStopped && (positionY != 0 || positionY != 12 || positionZ != 0 || positionZ != 12))
                    rotateCW = true;
                else rotateCW = false;
                break;
            case OF_KEY_BACKSPACE:
                if(!restart)
                {
                    resetAll();
                }
                break;
        }
}

void NoExit::setCurrentExits()
{
    westExit=current->getExit(WEST);
    eastExit=current->getExit(EAST);
    northExit=current->getExit(NORTH);
    southExit=current->getExit(SOUTH);
}

void NoExit::resetAll()
//resets all the values to standard values
{
    player.y=6.5;
    player.z=6.5;
    increasingMoveSpeed=0.0;
    player1Score=player2Score=0;
    counter=0;

    delete current;
    delete left;
    delete up;
    delete down;
    delete right;

    current = new Maze(13);
    left = new Maze(13);
    up = new Maze(13);
    down = new Maze(13);
    right = new Maze(13);
    current->generateMaze(1,0,NONE);
    current->generateExit(NONE);
    setCurrentExits();
    generateMazes(NONE,NONE);;

    rotatedLeft=rotatedRight=rotatedAngle=0;
    rotateCCW=rotateCW=false;
    moveDown=moveTemp=moveY=moveZ=rotation=0;
    exitRotation=false;
    restart = false;
    gameStopped = false;
    currentPoints=1;
}

void NoExit::generateMazes(directions dir, directions dir2)
//creates the mazes depending on which stay
{
    setCurrentExits();

    if(dir != NORTH || dir2 != NORTH)
    {
        up->generateMaze(2,northExit,SOUTH);
        up->generateExit(SOUTH);
    }

    if(dir != EAST || dir2 !=EAST)
    {
        right->generateMaze(2,eastExit,WEST);
        right->generateExit(WEST);
    }

    if(dir != SOUTH || dir2 !=SOUTH)
    {
        down->generateMaze(2,southExit,NORTH);
        down->generateExit(NORTH);
    }

    if(dir != WEST || dir2 != WEST)
    {
        left->generateMaze(2,westExit,EAST);
        left->generateExit(EAST);
    }
}

void NoExit::setNewMazes()
//deletes the old mazes and creates new ones accordingly
{
    switch((int)rotatedAngle)
    {
        case ROTATEDEAST:
            player.y-=11.0;
            playerPositioning();
            moveY=1.1;
            delete left;
            left=new Maze(*current);
            delete down;
            delete up;
            delete current;
            current=new Maze(*right);
            down=new Maze(13);
            up=new Maze(13);
            delete right;
            right=new Maze(13);
            generateMazes(EAST, WEST);
            break;

        case ROTATEDWEST:
            player.y+=11.0;
            playerPositioning();
            moveY=-1.1;
            delete right;
            right=new Maze(*current);
            delete down;
            delete up;
            delete current;
            current=new Maze(*left);
            down=new Maze(13);
            up=new Maze(13);
            delete left;
            left=new Maze(13);
            generateMazes(WEST, EAST);
            break;

        case ROTATEDNORTH:
            player.z+=11.0;
            playerPositioning();
            moveZ = 1.1;
            delete down;
            down = new Maze(*current);
            delete left;
            delete right;
            delete current;
            current = new Maze(*up);
            left = new Maze(13);
            right = new Maze(13);
            delete up;
            up = new Maze(13);
            generateMazes(NORTH, SOUTH);
            break;

        case ROTATEDSOUTH:
            player.z-=11.0;
            playerPositioning();
            moveZ = -1.1;
            delete up;
            up = new Maze(*current);
            delete left;
            delete right;
            delete current;
            current = new Maze(*down);
            left = new Maze(13);
            right = new Maze(13);
            delete down;
            down = new Maze(13);
            generateMazes(SOUTH, NORTH);
            break;
    }
}

void NoExit::moveCube()
{
    //moves the cube downwards if there is no rotation going on
    if(rotateCW==false && rotateCCW==false)
    moveDown=0.01+increasingMoveSpeed;
    else moveDown=0;

    switch(rotatedAngle)
    {
        case -270:
            moveY-=moveDown;
            player.y+=moveDown*5;
            break;
        case -180:
            moveZ+=moveDown;
            player.z+=moveDown*5;
            break;
        case  -90:
            moveY+=moveDown;
            player.y-=moveDown*5;
            break;
        case    0:
            moveZ-=moveDown;
            player.z-=moveDown*5;
            break;
    }
}

void NoExit::drawMaze(Maze *mazeDraw, float x, float y, float z, bool doBoundingBox, float moveZ, float moveY)
{
    //draws the maze
    for (float a=0;a<13;a++)
    {
        for (float b=0;b<13;b++)
        {
            if (mazeDraw->getWallf(b, a)==true)
            {
                glPushMatrix();
                glTranslatef(x, y+(b/5), z-(a/5));
                    if (a==0 || b== 0 || a== 12 || b==12)
                        glColor3f(0.1, 0.1, 0.1);
                    else glColor3f(0.3, 0.3, 0.3);
                        drawMazeWall();
                glPopMatrix();
            }
            else continue;
        }
    }
}


bool NoExit::collisionDetected()
//collision detections, checks if one of the 4 sides
//of the player is inside a wall
{
    for (int i=1; i<5; i++)
    {
        switch(i)
        {
            case 1:
            playerPositioning(-0.08, +0.08);
            if (current->getWalli(positionY, positionZ) == true)
            {
                playerPositioning();
                gameStopped=true;
                return true;
            }

            else playerPositioning();
            break;

            case 2:
            playerPositioning(+0.08, +0.08);
            if (current->getWalli(positionY, positionZ) == true)
            {
                playerPositioning();
                gameStopped=true;
                return true;
            }
            else playerPositioning();
            break;

            case 3:
            playerPositioning(+0.08, -0.08);
            if (current->getWalli(positionY, positionZ) == true)
            {
                playerPositioning();
                gameStopped=true;
                return true;
            }
            else playerPositioning();
            break;

            case 4:
            playerPositioning(-0.08, -0.08);
            if (current->getWalli(positionY, positionZ) == true)
            {
                playerPositioning();
                gameStopped=true;
                return true;
            }
            else playerPositioning();
            break;

        }
    }
    return false;
}

bool NoExit::getGameStopped()
{
    return gameStopped;
}

void NoExit::setGameStopped()
{
    gameStopped = false;
}


bool NoExit::checkForExit()
//if the player reaches an exit, the rotation start towards a new maze
{
    if(rotationStarted==true)
        return false;

    playerPositioning();

    assert(positionY >= 0 || positionY <= 12 || positionZ <= 12 || positionZ >= 0);

    if( positionY<=11 && positionY>=1 &&
        positionZ<=11 && positionZ>=1)
    {
        rotationStarted=false;
        return false;
    }

    else if (positionY == 0 || positionY == 12 || positionZ == 12 || positionZ == 0)
    {

        if(current->getWalli(positionY, positionZ) == false)
        {
            rotationStarted=true;
            return true;
        }
        return false;
    }
}

void NoExit::playerPositioning(float z, float y)
   //converts the current player position in the maze
   //to the correct maze field
{
    positionZ=(int)floor(player.z+z);
    positionY=(int)floor(player.y+y);
}

void NoExit::setLights()
{
    //light 1
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(1.0, 0.0, 0.0);
        setLight(0, 1.0, 1.0, 1.0);
    glPopMatrix();

    //light 2
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glTranslatef(1.0, 1.0, -1.0);
        setLight(1, 1.0, 1.0, 1.0);
    glPopMatrix();
}


void NoExit::setEmissionMaterial(float r , float g , float b )
{
    float specular[] = { 1.0, 1.0, 1.0, 0.0 };
    float emission[] = { r, g, b, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
    glEnable(GL_COLOR_MATERIAL);
}

void NoExit::drawMazeWall()
{
    float z;
    z=0.1;
    glBegin(GL_QUADS);
        // bottom
        glTexCoord2f(0.0, 0.0);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.1, -0.1, -z);
        glTexCoord2f(1.0, 0.0);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.1, +0.1, -z);
        glTexCoord2f(1.0, 1.0);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(+0.1, +0.1, -z);
        glTexCoord2f(0.0, 1.0);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(+0.1, -0.1, -z);

        // top
        glTexCoord2f(0.0, 0.0);
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(-0.1, -0.1, +z);
        glTexCoord2f(1.0, 0.0);
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(+0.1, -0.1, +z);
        glTexCoord2f(1.0, 1.0);
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(+0.1, +0.1, +z);
        glTexCoord2f(0.0, 1.0);
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(-0.1, +0.1, +z);

        // front
        glTexCoord2f(0.0, 0.0);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.1, -0.1, -z);
        glTexCoord2f(1.0, 0.0);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(+0.1, -0.1, -z);
        glTexCoord2f(1.0, 1.0);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(+0.1, -0.1, +z);
        glTexCoord2f(0.0, 1.0);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.1, -0.1, +z);

        // back
        glTexCoord2f(0.0, 0.0);
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(-0.1, +0.1, -z);
        glTexCoord2f(1.0, 0.0);
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(-0.1, +0.1, +z);
        glTexCoord2f(1.0, 1.0);
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(+0.1, +0.1, +z);
        glTexCoord2f(0.0, 1.0);
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(+0.1, +0.1, -z);

        // top
        glTexCoord2f(0.0, 0.0);
        glNormal3f(+1.0, 0.0, 0.0);
        //original x,y value bottom left
        glVertex3f(+0.1, -0.1, -z);
        glTexCoord2f(1.0, 0.0);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(+0.1, +0.1, -z);
        glTexCoord2f(1.0, 1.0);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(+0.1, +0.1, +z);
        glTexCoord2f(0.0, 1.0);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(+0.1, -0.1, +z);

    glEnd();
}

void NoExit::deleteAll()
{
    delete current;
    delete left;
    delete right;
    delete up;
    delete down;
}

void NoExit::drawCube()
{
    //only draws the ground but no adjacent cube sides
    float x=-0.1;
    glBegin(GL_QUADS);
        // front
        glColor3f(0.75, 0.75, 0.75);

        glNormal3f(+1.0, 0.0, 0.0);
        glTexCoord2f(0,0);
        glVertex3f(x, -1.1, -1.1);

        glTexCoord2f(1,0);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x, +1.1, -1.1);

        glTexCoord2f(1,1);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x, +1.1, +1.1);

        glTexCoord2f(0,1);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x, -1.1, +1.1);
    glEnd();
}

void NoExit::setLight(int i, float r, float g, float b)
{
    glEnable(GL_LIGHT0 + i);
    float diffuse[] = { r, g, b, 1.0 };
    float specular[] = { r, g, b, 1.0 };
    float ambient[] = { 0.1 * r, 0.1 * g, 0.1 * b, 1.0 };
    float position[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0 + i, GL_POSITION, position);
    glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 0.8);
    glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.2);
    glMaterialfv(GL_FRONT, GL_EMISSION, diffuse);
}

void NoExit::setShinyMaterial()
{
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float emission[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 40);
    glEnable(GL_COLOR_MATERIAL);
}

void NoExit::setMatteMaterial()
{
    float specular[] = { 0.0, 0.0, 0.0, 1.0 };
    float emission[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 1);
    // material diffuse & ambient color should track current vertex color
    glEnable(GL_COLOR_MATERIAL);
}

void NoExit::initializeNoExit()
{
    ofSetVerticalSync(true);
    //generate Mazes
    current = new Maze(13);
    left = new Maze(13);
    up = new Maze(13);
    down = new Maze(13);
    right = new Maze(13);

    current->generateMaze(1,0,NONE);

    current->generateExit(NONE);
    setCurrentExits();
    generateMazes(NONE, NONE);
    player.y=6.5;
    player.z=6.5;

    rotatedLeft=rotatedRight=rotatedAngle=0;
    moveDown=moveTemp=moveY=moveZ=0;
    exitRotation=restart=false;
    rotation=0;
    gameStopped=false;

    inGameFont.loadFont("rou.ttf", 18, true, true);
    inGameFont2.loadFont("rou.ttf", 52, true, true);
}
