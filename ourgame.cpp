
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


#define FROM_RIGHT      1 
#define FROM_LEFT       2 
#define FROM_TOP        3 
#define FROM_BOTTOM     4 
 
static int WINDOW_WIDTH ,WINDOW_HEIGHT;

//Variable to store the player score.
int playerResult=0;
//Variable to store the number of remaining chances.
int remainingChances = 5;
//Variable to store position of x and y coordinates changing from frame to frame.
static float xRePos=2,yRePos=2; 

//variable to store position changing after striking a surface.
static float delta=5;
//variable to store position changing after striking a surface.
static float deltaSlow=1;


int tempLevel = 5;
int level=1;


//Variable to track the x coordinate value of mouse.
static int mouse_x=0;
//Variable to store charachters to draw the text.
char string [200];

struct RECTA
{ 
        float left,top,right,bottom; 
};

RECTA ball={100,100,120,120};
RECTA protector ={0,490,40,500}; 
RECTA wall ;
RECTA slow={100,50,200,300};

//Function to draw rctangles.
void DrawRectangle(RECTA  rect) 
{ 
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom);      
        glVertex2f(rect.right,rect.bottom); 
        glVertex2f(rect.right,rect.top); 
        glVertex2f(rect.left,rect.top); 
        glEnd(); 
          
}



//Timer.
void Timer(int v) 
{ 
        ball.left+=xRePos; 
        ball.right+=xRePos; 
        ball.top+=yRePos; 
        ball.bottom+=yRePos; 
        glutTimerFunc(1,Timer,1); 
} 


//Text in normal size.
void drawText(char*string,int x,int y)
{
	char *c;

	glPushMatrix();
	glTranslatef(x, y,0);
	glScalef(0.1,-0.1,1);

        for (c=string; *c != '\0'; c++){
                glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
        }
        
        glPopMatrix();
}

//Text in a larger size.
void drawTextL(char*string,int x,int y)
{
	char *c;

	glPushMatrix();
	glTranslatef(x, y,0);
	glScalef(0.3,-0.3,1);

        for (c=string; *c != '\0'; c++){
                glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
        }
        
        glPopMatrix();
}


//Function to end the game.
void gameOver()
{
        yRePos=0;
        xRePos=0;

        sprintf(string,"Game Over");
	drawTextL(string,305,200);

        sprintf(string,"Score : %d ",playerResult);
	drawText(string,390,270);

        sprintf(string,"type ' x ' to exit");
	drawText(string,355,300);

        sprintf(string,"----- Created By - Yasika | Oshi | Sachini ----");
	drawText(string,235,350);
        
        mouse_x=10000;
}



int Test_ball_Wall(RECTA  ball , RECTA wall) 
{ 
        if(ball.right >=wall.right) 
                return FROM_RIGHT;  
        if(ball.left <=wall.left) 
                return FROM_LEFT;  
        if(ball.top <=wall.top) 
                return FROM_TOP;  
        if(ball.bottom >=wall.bottom) 
                if(remainingChances>0){
                        return FROM_BOTTOM;
                        remainingChances--;
                }
                else{
                        gameOver();
                }
                
        else return 0 ; 
}



bool Test_ball_Player(RECTA ball,RECTA protector) { 
     
	if(ball.bottom >= protector.top && ball.left>= protector.left && ball.right <=protector.right ) 
        {
                playerResult++;
                return true;  
	}
        return false;  
}


/* int Test_ball_slow(RECTA ball, RECTA slow){

        if(ball.right <=slow.right) 
                return FROM_RIGHT;  
        if(ball.left >=slow.left) 
                return FROM_LEFT;  
        if(ball.top >=slow.top) 
                return FROM_TOP;  
        if(ball.bottom <=slow.bottom) 
                return FROM_BOTTOM;
                     
        else return 0 ;

} */


 
//Keyboard Functions.
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'x':
         exit(0);
         break;
   }
} 

//Mouse Motions.
void MouseMotion(int x,int y)
{
	mouse_x=x;
}


// OpenGL Setting.
void Setting(void) 
{
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

 
//Window Resize. 
void reshape (int w, int h)
{
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT =h ;
 
        glViewport (0, 0, (GLsizei) w, (GLsizei) h);

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (0, w, h, 0);

        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity (); 

} 



void Render()
{
	glClear(GL_COLOR_BUFFER_BIT );
	glLoadIdentity();

        /* //slow bump
        if(playerResult>=5){
                //Color purple.
                glColor3f(0.5f,0.0f,0.5f);
                DrawRectangle(slow);

                if(Test_ball_slow(ball,slow)== FROM_RIGHT) 
                        xRePos=-deltaSlow; 

                if(Test_ball_slow(ball,slow)== FROM_LEFT) 
                        xRePos=deltaSlow; 

                if(Test_ball_slow(ball,slow)== FROM_TOP) 
                        yRePos=deltaSlow;

                if(Test_ball_slow(ball,slow)== FROM_BOTTOM){
                        yRePos=-deltaSlow;  
                } 
     
        } */
        
        //Color white.
        glColor3f(1.0f,1.0f,1.0f);

        sprintf(string,"Level : %d ",level);
	drawTextL(string,10,40);
	sprintf(string,"Remaining Chances : %d ",remainingChances);
	drawText(string,10,80);
	sprintf(string,"Player Score: %d ",playerResult);
	drawText(string,10,120);
        
	wall.left=wall.top=0;
	wall.right=WINDOW_WIDTH;
	wall.bottom=WINDOW_HEIGHT;

        if(tempLevel == playerResult) {
                tempLevel+=5;
                delta += 2;
                level++;
        }
             

        //Color red.
        glColor3f(1.0f,0.0f,0.0f);
        DrawRectangle(ball);
        
        if(Test_ball_Wall(ball,wall)== FROM_RIGHT) 
                xRePos=-delta; 

        if(Test_ball_Wall(ball,wall)== FROM_LEFT) 
                xRePos=delta; 

        if(Test_ball_Wall(ball,wall)== FROM_TOP) 
                yRePos=delta; 

        if(Test_ball_Wall(ball,wall)== FROM_BOTTOM){
                yRePos=-delta; 
	        remainingChances--;  
        }


        //Color green.
        glColor3f(0.0f,1.0f,0.0f);
	DrawRectangle(protector);
        
        protector.left=mouse_x-80; 
        protector.right=mouse_x+80;

        if(Test_ball_Player(ball,protector)==true){
                yRePos=-delta;
        } 

                 
	glutSwapBuffers();
}


int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (795, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("Game Development Project - The Vertex");
   Setting ();
   glutDisplayFunc(Render); 
   glutIdleFunc(Render);
   glutTimerFunc(1,Timer,1);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutPassiveMotionFunc(MouseMotion);
   glutMainLoop();
   return 0;
}
