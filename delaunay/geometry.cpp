#include "geometry.h"

int ccw(int a, int b, int cc){
    return (triArea(a, b, c) > 0);
}

int inTriangle(int p, Triangle *node){
    if(ccw(node->a, node->b, p) && ccw(node->b, node->c, p) && ccw(node->c, node->a, p))
        return 1;
    return 0;
}

Triangle *mylocate(Triangle *start, int p){
    if(start->child[0] == NULL && start->child[1] == NULL && start->child[2] == NULL){
        return start;
    }
    
    Triangle *e;
    Triangle *current;
    current = start;

    for(int i = 0; i < 3; ++i){
        if(current->child[i] != NULL){
            if(inTriangle(p, current->child[i])){
                e = mylocate(current->child[i], p);
                return e;
            }
        }
    }
}

Point2d::Point2d(){
    x = 0;
    y = 0;
}

Point2d::Point2d(int xa, int ya){
    x = xa;
    y = ya;
}

Triangle* Triangle::locate(int x){
    return mylocate(start, x);
}

Triangle::Triangle(){
    a = 0; b = 0; c = 0;
    startingEdge = NULL;
    for(int i = 0; i < 3; i++){
        child[i] == NULL;
    }
}

Triangle::Triangle(int a1, int b1, int c1){
    if(!ccw(a1, b1, c1)){	// check if the three points are in ccw sense
		int temp;
		temp = b1;
		b1   = c1;
		c1   = temp;		
	}

	a = a1;
	b = b1;
	c = c1;

	Edge *e1, *e2, *e3;
	e1 = new Edge();
	e2 = new Edge();
	e3 = new Edge();

	e1->nextedge = e2;		e2->nextedge = e3;		e3->nextedge = e1;
	e1->dualedge = NULL;	e2->dualedge = NULL;	e3->dualedge = NULL;
	e1->leftface = this;	e2->leftface = this;	e3->leftface = this;	
	e1->rightface= NULL;	e2->rightface= NULL;	e3->rightface= NULL;
	
	e1->origin = a1; e1->dest = b1;
	e2->origin = b1; e2->dest = c1;
	e3->origin = c1; e3->dest = a1;

	startingEdge = e1;

	for(int i=0;i<3;++i)
		child[i] = NULL;

}
