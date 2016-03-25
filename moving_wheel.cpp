#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

#define FIRST 1
#define SECOND 2
#define THIRD 3
#define FOURTH 4

#define DB(x) cerr << #x << " = " << x << endl
#define DBII(x, y) cerr << #x << " = " << x  << " " << #y << " = " << y << endl

///------------------------------------------------------------------///
#define resetScreen glClear( GL_COLOR_BUFFER_BIT );
vector<pair<int, int> > cvec, lvec;

void inline putPoint(int x, int  y){
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

/* Called back when there is no other event to be handled */
void idle() {
   glutPostRedisplay();   // Post a re-paint request to activate display()
}

void init(int argc, char** argv){
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("MIDPOINT ALGO"); // Create a window with the given title
    glutInitWindowSize(1500, 1500);   // Set the window's initial width & height
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    gluOrtho2D(-360, 360, -360, 360);
    glutInitDisplayMode (GLUT_DOUBLE);
    glEnable( GL_POINT_SMOOTH );
    glutIdleFunc(idle);

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glColor3f(0.8, 0.5, 0.0);
    glPointSize(2.0f);
    resetScreen;
}

void midPointCircle(int r)
{
    int d=1.25-r;
    int x=0;
    int y=r;
    cvec.clear();
    do
    {
        if(d<0)
        {
            x=x+1;
            d=d+2*x+1;
        }
        else
        {
            x=x+1;
            y=y-1;
            d=d+2*x-2*y+10;
        }
        cvec.pb(mp(x, y));
        cvec.pb(mp(y, x));
        cvec.pb(mp(-y, x));
        cvec.pb(mp(-x, y));

        cvec.pb(mp(-x, -y));
        cvec.pb(mp(-y, -x));
        cvec.pb(mp(y, -x));
        cvec.pb(mp(x, -y));
    }while(x<y);
}

void drawCircle(int xc, int yc, int r){
    midPointCircle(r);
    for(int i=0; i<cvec.size(); i++){
        putPoint(xc+cvec[i].ff, yc+cvec[i].ss);
    }
}


void midPointLine(int x1, int y1, int x2, int y2)
{
    int dx, dy, d, incrE, incrNE;
    dx=x2-x1; dy=y2-y1;
    d=2*dy-dx;

    incrE=2*dy;
    incrNE=2*(dy-dx);

    lvec.clear();
    while(x1<=x2)
    {
        lvec.pb(mp(x1, y1));
        if(d<=0)
            d+=incrE;
        else
        {
            d+=incrNE;
            y1++;
        }
        x1++;
    }
}

void drawLine(int x1, int y1, int x2, int y2){
    int cx=x1, cy=y1;
    x1-=cx, x2-=cx, y1-=cy, y2-=cy;

    if(x2>=0 && y2>=0){
        if(x2>=y2){
            midPointLine(x1, y1, x2, y2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx+lvec[i].ff, cy+lvec[i].ss);
            }
            //glFlush();
        }
        else{
            midPointLine(x1, y1, y2, x2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx+lvec[i].ss, cy+lvec[i].ff);
            }
            //glFlush();
        }
    }
    else if(x2<0 && y2>=0){
        if(-x2>=y2){
            midPointLine(x1, y1, -x2, y2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx-lvec[i].ff, cy+lvec[i].ss);
            }
            //glFlush();
        }
        else{
            midPointLine(x1, y1, y2, -x2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx-lvec[i].ss, cy+lvec[i].ff);
            }
            //glFlush();
        }
    }
    else if(x2<0 && y2<0){
        if(-x2>=-y2){
            midPointLine(x1, y1, -x2, -y2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx-lvec[i].ff, cy-lvec[i].ss);
            }
            //glFlush();
        }
        else{
            midPointLine(x1, y1, -y2, -x2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx-lvec[i].ss, cy-lvec[i].ff);
            }
            //glFlush();
        }
    }
    else{
        if(x2>=-y2){
            midPointLine(x1, y1, x2, -y2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx+lvec[i].ff, cy-lvec[i].ss);
            }
            //glFlush();
        }
        else{
            midPointLine(x1, y1, -y2, x2);
            for(int i=0; i<lvec.size(); i++){
                putPoint(cx+lvec[i].ss, cy-lvec[i].ff);
            }
            //glFlush();
        }
    }
}

void delay(long long x){
    x *= 1000000;
    for(long long i=0; i<x; i++);
}

#define INNER_RADIOUS 100
#define OUTER_RADIOUS 150

int xc=-360, yc=0;

void drawWheel(){
    drawCircle(xc, yc, INNER_RADIOUS);
    drawCircle(xc, yc, OUTER_RADIOUS);

    double pi = acos(-1), theta;
    int angle = xc, n = 12, x, y;
    if(angle<0) angle += 360;
    for(int i=0; i<n; i++){
        theta = (angle/360.0) * 2 * pi;
        x = INNER_RADIOUS * sin(theta);
        y = INNER_RADIOUS * cos(theta);
        //DBII(angle, theta);
        //DBII(x, y);
        //getchar();
        drawLine(xc, yc, xc+x, yc+y);
        angle += 360.0/n;
        angle %= 360;
        //glutSwapBuffers();
    }
   //getchar();
   drawLine(-360, -OUTER_RADIOUS-1, 360, -OUTER_RADIOUS-1);

    glutSwapBuffers();
    resetScreen;
}


void draw(){


        while(xc<360){
            drawWheel();
            delay(3);
            xc++;
        }
        while(xc>-360){
            drawWheel();
            delay(3);
            xc--;
        }

}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

   init(argc, argv);
   glutDisplayFunc(draw); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}
