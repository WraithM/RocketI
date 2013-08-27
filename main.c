/* Author: Matthew Wraith
 *
 * Compilation instructions: I've included a Makefile. Simply, make && ./main to
 * run this. If for some reason the Makefile does not work, this should:
 *
 * gcc -lGL -lGLU -lglut main.c blockI.c -o main
 *
 * Block I physics - This program makes an orange I bounce around using
 * Newtonian Physics. 
 *
 */

#include "main.h"
#include "blockI.h"

int nFPS = 30;
float fRotateAngle = 0.f;
bool drawWireFrame = false;
bool gravUp = false;

/* The particle struct is described in blockI.h
 * This does all the physics. */
particle blockI = { 
    1.0,         // Mass
    {-0.8, 0.5}, // Starting position
    {0.6, 0.2}   // Starting velocity
};


/* My initialization function
 * All initializations go here */
void init(void) {
    glClearColor(0.2,0.2,0.2,1.0); // clear color is gray       
}

/* My display function
 * All parts of the displaying of objects goes here */
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // reset OpenGL transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // reset transformation matrix to identity

    blockI = stepParticle(gravUp, blockI); // Find the next 

    translateToParticle(blockI);
    glScalef(HEIGHT,HEIGHT,0.0f);
    //glRotatef(fRotateAngle, 0.0f, 0.0f, 1.0f); // If I want to rotate my I

    // If drawWireFrame, draw the wireframe, else draw the normal model.
    drawWireFrame ? drawBlockILines() : drawBlockI();

    //glFlush(); // glutSwapBuffers calls glFlush
    glutSwapBuffers(); // swap front/back framebuffer to avoid flickering
}

// My reshape function
void reshape (int w, int h) {
    // reset viewport ( drawing screen ) size
    glViewport(0, 0, w, h);
    // reset OpenGL projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

/* Keyboard functions
 *
 * ESC and q: Quit the program.
 * Space: Gives the I a little bounce up! Try it! 
 * W: Turns the blockI into a wireframe. It shows how I built the full model. No
 *    T-sections. 
 * A: Gives the I a little bounce to the left. 
 * S: Gives the I a little bounce to the right. 
 * D: Flip the direction of gravity! */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case ESCKEY:
        case QKEY:
            printf("Demonstration finished...\n");
            exit(0);
            break;
        case SPACEKEY:
            blockI = bounceParticle(gravUp ? -1.0f : 1.0f, blockI);
            break;
        case WKEY:
            drawWireFrame = !drawWireFrame;
            break;
        case SKEY:
            blockI = moveHorizontalParticle(1.0f, blockI);
            break;
        case AKEY:
            blockI = moveHorizontalParticle(-1.0f, blockI);
            break;
        case DKEY:
            gravUp = !gravUp;
            break;
        default:
            // Print out in hex what key is pressed
            printf("key = 0x%x\n",key);
            break;
    }
}

/* The mouse function, if you click the left mouse button, the I will be placed
 * where you clicked. */
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        float w, h;
        GLint m_viewport[4];

        glGetIntegerv(GL_VIEWPORT, m_viewport);

        w = (float) m_viewport[2];
        h = (float) m_viewport[3];

        // Convert mouse positions from input to model coords for the physics
        // part to understand.
        blockI.position.x = (2.0f*(float) x) / w - 1.0f;
        blockI.position.y = (-2.0f*(float) y ) / h + 1.0f;

        blockI.velocity.x = 0.0f;
        blockI.velocity.y = 0.0f;
    }
}

// The time keeping function
void timer(int v) {
    fRotateAngle += 1.f; // change rotation angles

    // trigger display function by sending redraw into message queue
    glutPostRedisplay();    
    glutTimerFunc(1000/nFPS,timer,v); // restart timer again
}

int main(int argc, char* argv[]) {
    glutInit(&argc, (char**)argv);
    // set up for double-buffering & RGB color buffer
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ((const char*)"OpenGL");

    init(); // setting up user data & OpenGL environment
    
    // set up the call-back functions 
    glutDisplayFunc(display);  // called when drawing 
    glutReshapeFunc(reshape);  // called when change window size
    glutKeyboardFunc(keyboard); // called when received keyboard interaction
    glutMouseFunc(mouse);       // called when received mouse interaction
    glutTimerFunc(100,timer,nFPS);  // a timer. Usually for updating animation

    glutMainLoop(); // start the main message-callback loop

    return 0;
}

