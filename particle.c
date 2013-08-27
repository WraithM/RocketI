#include "main.h"
#include "particle.h"
#include <math.h>


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

