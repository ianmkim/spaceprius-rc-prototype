#ifndef GEOMETRY_H
#define GEOMETRY_H
class Point2d {
    public:
        int x, y;
        Point2d();
        Point2d(int xa, int ya);
};

class Edge {
    public:
        Edge *nextedge;
        Edge *dualedge;
        int origin;
        int dest;
        int num;
        Triangle *leftface;
        Triangle *rightface;
        Edge();
};

class Triangle {
    public:
        Triangle *child[3];
        Edge *startingEdge;
        int a, b, c;

        Triangle();
        Triangle(int a, int b, int c);
        void insertSite(int p);
        Triangle *locate(int);
};

Triangle *mylocate(Triangle *start, int p);

int inTriangle(int p, Triangle *node);

int ccw(int a, int b, int c);
#endif
