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
vector<pair<int, int> > cvec, lvec, evec;

void inline putPoint(int x, int  y){
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

/* Called back when there is no other event to be handled */
void idle() {
   glutPostRedisplay();   // Post a re-paint request to activate display()
}


void midPointEllipse(int a, int b){
    int x=0,y=b,reg2=0;
    long int d,p,n,m;
    d= (b*b-a*a*b+a*a/4)/10;
    evec.clear();
    while(y>=0)
    {
        if(b*b*x<a*a*y)
        {
            evec.pb(mp(x, y));
            evec.pb(mp(x, -y));
            evec.pb(mp(-x, y));
            evec.pb(mp(-x, -y));
            if(d<=0) d+=b/10*b*(2*x+3);
            else
            {
                d+=b/10*b*(2*x+3)+a/10*a*(2-2*y);
                y--;
            }
            x++;
        }
        else
        {
            if(reg2==0)
            {
                m=b/10*b*(x*x+x+.25);
                n=a/10*a*(y*y-2*y+1);
                p=a/10*a*b*b;
                d= m+n-p;
                reg2=1;
            }
            evec.pb(mp(x, y));
            evec.pb(mp(x, -y));
            evec.pb(mp(-x, y));
            evec.pb(mp(-x, -y));
            if(d>=0)
            {
                d+=a*a*(3-2*y)/10;
            }
            else
            {
                d+=a*a*(3-2*y)/10+ b*b*(2*x+2)/10;
                x++;
            }
            y--;
        }
    }
}

void drawEllipse(int h, int k, int a, int b){
    glColor3f(0.8, 0.5, 0.0);
    midPointEllipse(a, b);
    for(int i=0; i<evec.size(); i++){
        putPoint(h+evec[i].ff, k+evec[i].ss);
    }
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
    //glColor3f(0.1, 0.1, 0.1);
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
    //glColor3f(0.8, 0.5, 0.0);
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

void drawGolok(int xc, int yc, int r){
    //glColor3f(0.1, 0.1, 0.1);
    drawCircle(xc, yc, r);
    drawLine(xc-r, yc, xc+r, yc);
    drawLine(xc, yc-r, xc, yc+r);
}

bool func(const pair<int, int> &x, const pair<int, int> &y){
    if(x.ss>=0 && y.ss>=0) return x.ff > y.ff;
    else if(x.ss <0 &&  y.ss<0) return x.ff < y.ff;
    return x.ss > y.ss;
}

void delay(long long x){
    x *= 1000000;
    for(long long i=0; i<x; i++);
}

int mn = -500, mx = 500;
void drawball(int xc, int yc, int r){
    int t;
    if(fabs(xc-mn)<r){
        t = fabs(xc-mn);
        drawEllipse(xc, yc, t, 2*r-t);
    }
    else if(fabs(mx-xc)<r){
        t = fabs(mx-xc);
        drawEllipse(xc, yc, t, 2*r-t);
    }
    else if(fabs(yc-mn)<r){
        t = fabs(yc-mn);
        drawEllipse(xc, yc, 2*r-t, t);
    }
    else if(fabs(yc-mx)<r){
        t = fabs(yc-mx);
        drawEllipse(xc, yc, 2*r-t, t);
    }
    else{
        drawGolok(xc, yc, r);
    }
}

vector<int> vecx(4, 0), vecy(4, 0);
vector<int> ix, iy;
//int ix1=1, iy1=2, ix2=1, iy2=-2, ix3=-1, iy3=-2, ix4=-1, iy4=2;

void control(){
    for(int i=0; i<4; i++){
        vecx[i] += ix[i];
        if(fabs(mx-vecx[i])>10) ix[i] = -ix[i];
        if(fabs(mn-vecx[i])>10) ix[i] = -ix[i];
        vecy[i] += iy[i];
        if(fabs(mx-vecy[i])>10) iy[i] = -iy[i];
        if(fabs(mn-vecy[i])>10) iy[i] = -iy[i];

        drawball(vecx[i], vecy[i], 50);
    }
    delay(3);
    glutSwapBuffers();
    resetScreen;
}

void draw(){
    ix = {1, 1, -1, -1};
    iy = {2, -2, -2, 2};
//    for(int i=0; i<4; i++){
//        printf("Center of circle %d: ", i+1);
//        cin >> vecx[i] >> vecy[i];
//    }
    while(true){
        control();
    }


}

void init(int argc, char** argv){
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("MIDPOINT ALGO"); // Create a window with the given title
    glutInitWindowSize(1500, 1500);   // Set the window's initial width & height
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    gluOrtho2D(-mx, mx, -mx, mx);
    glutInitDisplayMode (GLUT_DOUBLE);
    glEnable( GL_POINT_SMOOTH );
    glutIdleFunc(idle);

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glColor3f(0.8, 0.5, 0.0);
    glPointSize(2.0f);
    resetScreen;
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

   init(argc, argv);
   glutDisplayFunc(draw); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}
