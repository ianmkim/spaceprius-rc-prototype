#ifndef RENDER_H
#define RENDER_H

#include <Fade_2D.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <list>
#include <vector>

using namespace GEOM_FADE25D;

void init(){
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
}


float zoom = 0;
int theta = 45, phi = 45;
int gluLookAt_On = 1;
int width, height;
const double radianFactor = 2 * 3.1415926535 / 360; 

void changeSize(int w, int h){
    width = w;
    height = h;
    
    if(h == 0) h = 1;
    float ratio = 1.0 * w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    
    glViewport(0, 0, w, h);
	
	gluPerspective(45, ratio, 1, 1000000);	
	
	float r = 5.0f;
	float eyeX = r * sin(theta * radianFactor) * cos(phi * radianFactor);
	float eyeY = r * sin(theta * radianFactor) * sin(phi * radianFactor);
	float eyeZ = r * cos(radianFactor * theta);

	float centerX = 0, centerY = 0, centerZ = 0;
	float upX = 0, upY = 1.0f, upZ = 0;
	
	if(gluLookAt_On) {
		gluLookAt(eyeX, eyeY, eyeZ, 
				  centerX, centerY, centerZ,
				  upX, upY, upZ); 
	}

	glScalef(zoom, zoom, zoom);
	glMatrixMode(GL_MODELVIEW);		
}


void inputKey(unsigned char c, int x, int y){
    switch (c) {			
			case '+' : zoom = zoom+5; break;
			case '-' : zoom = zoom -5; break;
            case 'k' : theta++; if(theta > 360) theta = 1; break;
            case 'j' : phi++; if(phi > 360) phi = 1; break;
            case 'l' : theta--; if(theta < 0) theta = 359; break;
            case 'h' : phi--; if(phi < 0) phi = 359; break;
            case 'g' : gluLookAt_On = !gluLookAt_On;; break;
    }
        changeSize(width, height);
}


#endif
