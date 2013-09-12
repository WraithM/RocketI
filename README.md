RocketI
=======

Author: Matthew Wraith

Compilation instructions
------------------------
I've included a Makefile. To compile, simply run make. To run, ./main

If for some reason make does not work, this should:

gcc -lGL -lGLU -lglut main.c blockI.c -o main

Again, to run: ./main

Instructions on use
-------------------
This program has a tiny Newtonian Physics simulation in it. The I starts out
with an initial velocity going up and to the right, and starts in the upper left
hand corner of the window. From there, it bounces off the walls with a certain
amount of elasticity. You can control the I with the keyboard. The controls are
sort of like a rocket.

Keyboard commands
-----------------
    ESC or Q:   Quit the program
    Space:      Give the particle a bounce upward
    W:          Turn the model into a wireframe, to show that I've used no
                    T-junctions  
    A:          Give the particle a bounce to the left
    S:          Give the particle a bounce to the right
    D:          Flip the direction of gravity (this also flips the direction that
                    Space gives you a boost in

Mouse commands
--------------
Clicking the mouse sends the block to where you clicked, and it stops. 
