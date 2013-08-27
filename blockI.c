#include "main.h"
#include "blockI.h"
#include <math.h>

/* The vertex array for the block I. The vertecies are in clockwise order 
 * starting from the upper left vertex. blockIDrawCommands
 * calls the indecies of this vertex array to plot vertecies. */
static GLfloat blockIvs[][3] = {
    {-0.6, 1.0, 0.0},
    {-0.6, 0.6, 0.0},
    {-0.2, 0.6, 0.0},
    {-0.2, -0.6, 0.0},
    {-0.6, -0.6, 0.0},
    {-0.6, -1.0, 0.0},
    { 0.6, -1.0, 0.0},
    { 0.6, -0.6, 0.0},
    { 0.2, -0.6, 0.0},
    { 0.2, 0.6, 0.0},
    { 0.6, 0.6, 0.0},
    { 0.6, 1.0, 0.0}
};

/* My drawsection type is defined in blockI.h
 * Here I've given drawModesVerts() instructions to draw 16 verticies. 
 * This contains calls to blockIvs. */
static drawsection blockIDrawCommands[] = {
    {GL_TRIANGLE_FAN, 7, {2, 1, 0, 11, 9, 8, 3}},
    {GL_TRIANGLE_FAN, 6, {6, 5, 4, 3, 8, 7}},
    {GL_TRIANGLES, 3, {10, 9, 11}}
};

// Instructions to draw the outline
static drawsection blockIOutlineCommands[] = {
    {GL_LINE_STRIP, 13, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0}}
};

/* This drawsectionc (as defined in blockI.h) gives the instructions to do the
 * same thing as the triangles in blockIDrawCommands, only I've made it more
 * explicitly draw each section as to see that I've correctly implemented the
 * blockI without T-sections. */ 
static drawsectionc blockILines[] = {
    {GL_LINE_STRIP, 3, {1, 0, 0}, {2, 1, 0}},
    {GL_LINE_STRIP, 3, {1, 0, 0}, {2, 0, 11}},
    {GL_LINE_STRIP, 3, {1, 0, 0}, {2, 11, 9}},
    {GL_LINE_STRIP, 3, {1, 0, 0}, {2, 9, 8}},
    {GL_LINE_STRIP, 3, {1, 0, 0}, {2, 9, 8}},
    {GL_LINE_STRIP, 4, {1, 0, 0}, {2, 8, 3, 2}},
   
    {GL_LINE_STRIP, 3, {0, 1, 0}, {6, 5, 4}},
    {GL_LINE_STRIP, 3, {0, 1, 0}, {6, 4, 3}},
    {GL_LINE_STRIP, 3, {0, 1, 0}, {6, 3, 8}},
    {GL_LINE_STRIP, 4, {0, 1, 0}, {6, 8, 7, 6}},
    
    {GL_LINE_STRIP, 4, {0, 0, 1}, {11, 9, 10, 11}}
};

/* drawModesVerts() takes a drawsection struct array, which gives the 
 * modes, number of verticies to draw out of the following index array,
 * vertsToDraw. */
void drawModesVerts(drawsection choices[], int n, GLfloat verts[][3]) {
    int i, j;
    int indexVerts;

    for (i = 0; i < n; i++) {
        glBegin(choices[i].mode);
        for (j = 0; j < choices[i].numVerts; j++) {
            indexVerts = choices[i].vertsToDraw[j];

            glVertex3fv(verts[indexVerts]);
        }
        glEnd();
    }
}

/* This is very similar to drawModesVerts, only I've included a color at each
 * vertex as defined in the drawsectionc type. */
void drawModesColorsVerts(drawsectionc choices[], int n, GLfloat verts[][3]) {
    int i, j;
    int indexVerts;

    for (i = 0; i < n; i++) {
        glBegin(choices[i].mode);
        for (j = 0; j < choices[i].numVerts; j++) {
            indexVerts = choices[i].vertsToDraw[j];

            glColor3fv(choices[i].color);
            glVertex3fv(verts[indexVerts]);
        }
        glEnd();
    }
}

/* Draws blockILines. This shows that I don't have any T-sections. */
void drawBlockILines() {
    drawModesColorsVerts(blockILines, LENGTH(blockILines), blockIvs);
}

/* This simply sets the color to orange and calls upon blockIDrawCommands and
 * blockIvs to draw the block I. */
void drawBlockI() {
    glColor3f(0.6, 0.2, 0.0); // Set current color to Orange
    drawModesVerts(blockIDrawCommands, LENGTH(blockIDrawCommands), blockIvs);
    glColor3f(1.0, 1.0, 1.0); // White outline
    drawModesVerts(blockIOutlineCommands, 
            LENGTH(blockIOutlineCommands), 
            blockIvs);
}

/* This translates to a 2D position from a particle. This just makes the drawing
 * easier. */
void translateToParticle(particle p) {
    glTranslatef(p.position.x, p.position.y, 0.0f);
}

/* This does my Euler integration. I produce a new particle with the Euler
 * integration of a force on particle p. a = F/m, dv = a*dt, dp = v*dt */
particle moveParticle(particle p, vec force) {
    p.velocity.x += (force.x / p.mass) * TSTEP;
    p.velocity.y += (force.y / p.mass) * TSTEP;

    p.position.x += p.velocity.x * TSTEP;
    p.position.y += p.velocity.y * TSTEP;

    return p;
}

/* This function gives the space key (as defined in the keyboard function) the
 * ability to give the I a little boost of magnitude strength upwards */
particle bounceParticle(float strength, particle p) {
    p.velocity.y += strength;

    return p;
}

/* This function gives the a and s keys (as defined in the keyboard function) 
 * the ability to give the I a little boost of magnitude strength to the left or
 * right. */
particle moveHorizontalParticle(float strength, particle p) {
    p.velocity.x += strength;

    return p;
}

/* This bounces the particle off the walls and floors 
 * elastic makes the walls more or less bouncy. A value of 1 is perfectly
 * elastic. A value below that gives an inelastic collision */
float bounceVelocity(float elastic, float v) {
    if (fabs(v) <= SMALL)
        return 0.0;
    else
        return -elastic*v;
}

/* This gives the sign of a floating point number. */
float sign(float x) {
    return (x > 0.0) ? 1.0 : ((x < 0.0) ? -1.0 : 0.0);
}

// Makes the walls and floors a little closer to the center of blockI such that
// it will look like a real collision.
#define FLOOR (1.0f - HEIGHT)
#define WALLS (1.0f - WIDTH)

static vec zeroVec = {0.0f, 0.0f}; // Zero vector
static vec gravDownVec = {0.0f, -G}; // Down gravity
static vec gravUpVec = {0.0f, G}; // Up gravity

/* This calculates the force from gravity and the walls. It calls upon
 * moveParticle to do the integration after the calculation of the forces. 
 * F = ma */
particle stepParticle(bool gravUp, particle p) {
    vec forceSum;
    vec grav;
    
    grav = gravUp ? gravUpVec : gravDownVec;

    forceSum = grav;

    if (fabs(p.position.y) >= FLOOR) {
        p.position.y = sign(p.position.y)*FLOOR;
        p.velocity.y = bounceVelocity(ELASTIC, p.velocity.y);

        if(gravUp)
            p = bounceParticle(0.1f, p);
        else
            p = bounceParticle(-0.1f, p);

        forceSum = zeroVec;
    } 
    
    if (fabs(p.position.x) >= WALLS) {
        p.position.x = sign(p.position.x)*WALLS;
        p.velocity.x = bounceVelocity(ELASTIC, p.velocity.x);
    }

    return moveParticle(p, forceSum);
}

