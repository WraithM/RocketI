// The maximum number of verts per instruction in my drawsection type
#define MAXVERTS 1024

// Number of elements in an array
#define LENGTH(x) (int) (sizeof(x) / sizeof(*(x)))

#define HEIGHT 0.4f // Distance to the center point from the bottom
#define WIDTH  0.2f // Distance to the center from the side

//Some physics constansts
#define TSTEP   0.03
#define G       2.0
#define ELASTIC 0.7
#define SMALL   0.2

/* A structure to help draw objects.
 * You define a mode, the number of vertecies to draw out of vertsToDraw,
 * and the vertecies one wishes to draw. */
typedef struct drawsection {
    GLenum mode;
    int numVerts;
    int vertsToDraw[MAXVERTS];
} drawsection;

/* A structure to help draw objects with colors!
 * You define a mode, the number of vertecies to draw out of vertsToDraw,
 * and the vertecies one wishes to draw. Each vertex is associated with a color
 * as well. */
typedef struct drawsectionc {
    GLenum mode;
    int numVerts;
    GLfloat color[3];
    int vertsToDraw[MAXVERTS];
} drawsectionc;

/* A simple 2-vector. */
typedef struct vec {
    float x;
    float y;
} vec;

/* All of the physics goes on in here. I have an Euler integration in blockI.c
 * You need mass, position, and velocity to simulate a particle. */
typedef struct particle {
    float mass;
    vec position;
    vec velocity;
} particle;

void drawModesVerts(drawsection choices[], int n, GLfloat verts[][3]);
void drawModesColorsVerts(drawsectionc choices[], int n, GLfloat verts[][3]);
void drawBlockI();
void drawBlockILines();

particle stepParticle(bool gravUp, particle p);
particle bounceParticle(float strength, particle p);
particle moveHorizontalParticle(float strength, particle p);
void translateToParticle(particle p);
