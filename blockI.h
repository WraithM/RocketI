// The maximum number of verts per instruction in my drawsection type
#define MAXVERTS 1024

// Number of elements in an array
#define LENGTH(x) (int) (sizeof(x) / sizeof(*(x)))

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

void drawModesVerts(drawsection choices[], int n, GLfloat verts[][3]);
void drawModesColorsVerts(drawsectionc choices[], int n, GLfloat verts[][3]);
void drawBlockI();
void drawBlockILines();
