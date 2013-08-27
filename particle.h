#define HEIGHT 0.4f // Distance to the center point from the bottom
#define WIDTH  0.2f // Distance to the center from the side

//Some physics constansts
#define TSTEP   0.03
#define G       2.0
#define ELASTIC 0.7
#define SMALL   0.2

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

particle stepParticle(bool gravUp, particle p);
particle bounceParticle(float strength, particle p);
particle moveHorizontalParticle(float strength, particle p);
void translateToParticle(particle p);
