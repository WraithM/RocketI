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

