/*
===============================================
 Title:  Orthographic projection of cube in cmd.
 Author: Kumar Vaibhav
 Date:   25 Sept 2018
=================================================
*/

/*
        BEFORE COMPILING

        SET YOUR CONSOLE FONT TO CONSOLAS
        FONT SIZE TO 5
        SCREEN WIDTH TO 340 (screenWidth)
        SCREEN HEIGHT TO 120 (screenHeight)
*/
#include <windows.h>
#include <stdio.h>
#include <math.h>

//--PROJECTION MATRIX FOR PROJECTING 3D IN 2D SCREEN--//
float projection[3][3] = {
    {1,0,0},
    {0,1,0},
    {0,0,0}
};
//--ROTATION X MATRIX FOR ROTATION ALONG X AXIS--//
float rotationX[3][3] = {   {1,      0,       0},
                            {0, cos(0), -sin(0)},
                            {0, sin(0),  cos(0)}   };
//--ROTATION Y MATRIX FOR ROTATION ALONG Y AXIS--//
float rotationY[3][3] = {   {cos(0), 0, -sin(0)},
                            {0,      1,       0},
                            {sin(0), 0,  cos(0)}   };
//--ROTATION Z MATRIX FOR ROTATION ALONG Z AXIS--//
float rotationZ[3][3] = {   {cos(0), -sin(0), 0},
                            {sin(0),  cos(0), 0},
                            {0,      0,       1}   };

void draw(float x, float y, char *scr, char p, float xoff, float yoff);
void drawline(float x1, float y1, float x2, float y2, char *scr, char p, float xoff, float yoff);
void clearscr(char *scr);

struct Vec3D{float x,y,z;};//--Vec3D STRUCT FOR STORING 3D COORDINATEDS--//
void matXvec3d(float x[][3], struct Vec3D p, struct Vec3D *result);//--matXvec3d FUNCTION FOR MULTIPLYING A 3X3 MATRIX WITH A 3D VECTOR--//

int screenWidth = 340;
int screenHeight = 120;

int main(){
    system("color 3");

    char screen[screenWidth*screenHeight];
    clearscr(screen);
    screen[screenWidth*screenHeight-1] = '\0';
    //--CREATING HANDLE FOR SCREEN BUFFER--//
    HANDLE buff = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                                            NULL,
                                            CONSOLE_TEXTMODE_BUFFER, NULL);
    //--SETTING ACTIVE CONSOLE SCREEN BUFFER TO buff--//
    SetConsoleActiveScreenBuffer(buff);

    COORD coord = {};
    coord.X = 0;
    coord.Y = 0;

    clearscr(screen);

    struct Vec3D cubeVertex[8];//--INITIAL 8 VERTICIES OF THE CUBE IS STORED IN cubeVertex---------//
    struct Vec3D resultf[8];   //--AFTER ROTATING AND PROJECTING RESULT IS STORED IN resultf---//

    // xoff and yoff is used for shifting the coordinate center where ever it is used int a function you can change them to see the effects.
    int xoff = 0;
    int yoff = 0;
    int cubeSize = 30;
    double angle = 0;
    // character to be printed on screen.
    char q = '*';
    //heart
    struct Vec3D heart[3600];
    struct Vec3D heart1[3600];
    struct Vec3D heart2[3600];
    struct Vec3D heart3[3600];
    struct Vec3D heartR[3600];
    double theta, r = 1;
    int i = 0;

    for(theta = 0; theta <= 360; theta += 0.1, i++){
        heart[i].x = (16 * pow(r*sin(theta),3));
        heart1[i].x = (16 * pow(r*sin(theta),3));

        heart[i].y = (13 * cos(theta) - 5 * cos(2*theta) - 2 * cos(3*theta) - cos(4*theta));
        heart1[i].y = (13 * cos(theta) - 5 * cos(2*theta) - 2 * cos(3*theta) - cos(4*theta));

        heart[i].z = cubeSize;
        heart1[i].z = -cubeSize;
    }
    i = 0;
    for(theta=0;theta<=360;theta+=0.1,i++){
        heart2[i].x = cubeSize;
        heart3[i].x = -cubeSize;

        heart2[i].y = (13 * cos(theta) - 5 * cos(2*theta) - 2 * cos(3*theta) - cos(4*theta));
        heart3[i].y = (13 * cos(theta) - 5 * cos(2*theta) - 2 * cos(3*theta) - cos(4*theta));

        heart2[i].z = (16 * pow(r*sin(theta),3));
        heart3[i].z = (16 * pow(r*sin(theta),3));
    }
//---------------------------------------------MAKING CUBE---------------------------------------------------------------------------//    
                    cubeVertex[0].x = -cubeSize;    cubeVertex[1].x = -cubeSize;
                    cubeVertex[0].y = -cubeSize;    cubeVertex[1].y =  cubeSize;
                    cubeVertex[0].z =  cubeSize;    cubeVertex[1].z =  cubeSize;

                    cubeVertex[2].x =  cubeSize;    cubeVertex[3].x =  cubeSize;
                    cubeVertex[2].y =  cubeSize;    cubeVertex[3].y = -cubeSize;
                    cubeVertex[2].z =  cubeSize;    cubeVertex[3].z =  cubeSize;

                    cubeVertex[4].x = -cubeSize;    cubeVertex[5].x = -cubeSize;
                    cubeVertex[4].y = -cubeSize;    cubeVertex[5].y =  cubeSize;
                    cubeVertex[4].z = -cubeSize;    cubeVertex[5].z = -cubeSize;

                    cubeVertex[6].x =  cubeSize;    cubeVertex[7].x =  cubeSize;
                    cubeVertex[6].y =  cubeSize;    cubeVertex[7].y = -cubeSize;
                    cubeVertex[6].z = -cubeSize;    cubeVertex[7].z = -cubeSize;
//----------------------------------------RENDERING LOOP STARTS----------------------------------------------------------------------//
    while(1){
                    cubeVertex[0].x = -cubeSize;    cubeVertex[1].x = -cubeSize;
                    cubeVertex[0].y = -cubeSize;    cubeVertex[1].y =  cubeSize;
                    cubeVertex[0].z =  cubeSize;    cubeVertex[1].z =  cubeSize;

                    cubeVertex[2].x =  cubeSize;    cubeVertex[3].x =  cubeSize;
                    cubeVertex[2].y =  cubeSize;    cubeVertex[3].y = -cubeSize;
                    cubeVertex[2].z =  cubeSize;    cubeVertex[3].z =  cubeSize;

                    cubeVertex[4].x = -cubeSize;    cubeVertex[5].x = -cubeSize;
                    cubeVertex[4].y = -cubeSize;    cubeVertex[5].y =  cubeSize;
                    cubeVertex[4].z = -cubeSize;    cubeVertex[5].z = -cubeSize;

                    cubeVertex[6].x =  cubeSize;    cubeVertex[7].x =  cubeSize;
                    cubeVertex[6].y =  cubeSize;    cubeVertex[7].y = -cubeSize;
                    cubeVertex[6].z = -cubeSize;    cubeVertex[7].z = -cubeSize;

        rotationX[1][1] = cos(angle); rotationX[1][2] = -sin(angle);    rotationX[2][1] = sin(angle); rotationX[2][2] = cos(angle);
        rotationY[0][0] = cos(angle); rotationY[0][2] = -sin(angle);    rotationY[2][0] = sin(angle); rotationY[2][2] = cos(angle);
        rotationZ[0][0] = cos(angle); rotationZ[0][1] = -sin(angle);    rotationZ[1][0] = sin(angle); rotationZ[1][1] = cos(angle);

        for(int i=0;i<8;i++){
            matXvec3d( rotationX, cubeVertex[i], &resultf[i]);
            matXvec3d( rotationY,    resultf[i], &resultf[i]);
            matXvec3d( rotationZ,    resultf[i], &resultf[i]);
            matXvec3d(projection,    resultf[i], &resultf[i]);
        }

        for(int i=0; i<4;i++){
            drawline(  resultf[i].x,   resultf[i].y,     resultf[(i+1)%4].x,     resultf[(i+1)%4].y, screen, q, xoff, yoff);
            drawline(resultf[i+4].x, resultf[i+4].y, resultf[((i+1)%4)+4].x, resultf[((i+1)%4)+4].y, screen, q, xoff, yoff);
            drawline(  resultf[i].x,   resultf[i].y,         resultf[i+4].x, resultf[i+4].y,         screen, q, xoff, yoff);
        }

        for(int h=0;h<360;h++){
            matXvec3d( rotationX, heart[h], &heartR[h]);
            matXvec3d( rotationY, heartR[h], &heartR[h]);
            matXvec3d( rotationZ, heartR[h], &heartR[h]);
            matXvec3d( projection, heartR[h], &heartR[h]);

            draw(heartR[h].x,heartR[h].y,screen,q,0,0);

            matXvec3d( rotationX, heart1[h], &heartR[h]);
            matXvec3d( rotationY, heartR[h], &heartR[h]);
            matXvec3d( rotationZ, heartR[h], &heartR[h]);
            matXvec3d( projection, heartR[h], &heartR[h]);

            draw(heartR[h].x,heartR[h].y,screen,q,0,0);

            matXvec3d( rotationX, heart2[h], &heartR[h]);
            matXvec3d( rotationY, heartR[h], &heartR[h]);
            matXvec3d( rotationZ, heartR[h], &heartR[h]);
            matXvec3d( projection, heartR[h], &heartR[h]);

            draw(heartR[h].x,heartR[h].y,screen,q,0,0);

            matXvec3d( rotationX, heart3[h], &heartR[h]);
            matXvec3d( rotationY, heartR[h], &heartR[h]);
            matXvec3d( rotationZ, heartR[h], &heartR[h]);
            matXvec3d( projection, heartR[h], &heartR[h]);

            draw(heartR[h].x,heartR[h].y,screen,q,0,0);
        }

        angle += 0.004;

        DWORD dwBytesWritten = 0;
        WriteConsoleOutputCharacter(buff, screen, screenWidth*screenHeight, coord, &dwBytesWritten);
        clearscr(screen);
    }
    //---------------------------------------------LOOP ENDS-----------------------------------------------------//
    return 0;
}

// ------------------------------------------------MAIN FUNCTION END-----------------------------------------------------------------//

void draw(float x, float y, char *scr, char p, float xoff, float yoff){
    x += xoff;
    y += yoff;
    x = 2*x;
    y = -y;

    int drawon = (((int)y+screenHeight/2) * screenWidth) + ((int)x+screenWidth/2);

    if(drawon < screenWidth*screenHeight && drawon >= 0){
        scr[drawon] = p;
    }
}
//===========================================================================================
void clearscr(char *scr){
    int j;
    for(j=0;j<screenWidth*screenHeight;j++){
        scr[j]=' ';
    }
}
//===========================================================================================
void drawline(float x1, float y1, float x2, float y2, char *scr, char p, float xoff, float yoff){
    // equation of a line is y = mx +b // slope = (y2-y1)/(x2-x1)

    float slope = (y2-y1)/(x2-x1);
    float rslope = (y1-y2)/(x1-x2);

    if(slope>1){

        float x = x1;
        for(int y = y1; y <= y2; y++){
            draw(x,y,scr,p,xoff,yoff);
            x += 1/slope;
        }
    }else if(slope == 1){
        float x = x1;
        for(int y = y1;y <= y2; y++){
            draw(x,y,scr,p,xoff,yoff);
            x++;
        }
    }else if(slope<1){
            float y = y1;
            for(int x = x1; x <= x2; x++){
                draw(x,y,scr,p,xoff,yoff);
                y += slope;
            }
    }
// ==================REVERSE LINE========================== //
    if(rslope>1){
        float rx = x2;
        for(int ry = y2; ry <= y1; ry++){
            draw(rx,ry,scr,p,xoff,yoff);
            rx += 1/rslope;
        }
    }else if(rslope==1){
        float rx = x2;
        for(int ry = y2;ry <= y1; ry++){
            draw(rx,ry,scr,p,xoff,yoff);
            rx++;
        }
    }else if(rslope<1){
        float ry = y2;
            for(int rx = x2; rx <= x1; rx++){
            draw(rx,ry,scr,p,xoff,yoff);
            ry += rslope;
        }
    }
}
//=====================================================================
void matXvec3d(float x[][3], struct Vec3D p, struct Vec3D *result){

    float a[3][1] = {   {p.x},
                        {p.y},
                        {p.z}   };
    float b[3][1] ;

    for(int i=0;i<3;i++){
        for(int j=0;j<1;j++){
            float sum = 0;
            for(int k=0;k<3;k++){
                sum += x[i][k] * a[k][j];
            }
            b[i][j] = sum;
        }
    }

    result->x = b[0][0];
    result->y = b[1][0];
    result->z = b[2][0];
}

