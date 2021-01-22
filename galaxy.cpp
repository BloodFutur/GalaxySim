#include "galaxy.h"
Galaxy::Galaxy()
    : m_program(0)
    , m_frame(0)
{

}


void Galaxy::initialize()
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,1000,1000);

    constexpr size_t nbThreads = 8;


    initializeGalaxy(galaxy, nbStars, area, speedInit, step, isBlackHole, blackHoleMass, galaxyThickness);
    aliveGalaxy = { galaxy.begin(), galaxy.end()};

}

void Galaxy::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(2); // Star size


    createBlocks(area, block, aliveGalaxy);

    // Update all stars
    for(auto itStar = aliveGalaxy.begin; itStar != aliveGalaxy.end; itStar++) {
        itStar->updateAccelerationDensity(block, precision);
        if(!verletIntegration)
            itStar->updateSpeed(step, area);

        itStar->updatePosition(step, verletIntegration);
        if(!isIn(block, *itStar))
            itStar->isAlive = false;
        else if(!realColors)
            itStar->updateColor();

    }


    aliveGalaxy.end = std::partition(aliveGalaxy.begin, aliveGalaxy.end, [](const Star & star) { return star.isAlive;});


    drawStars(aliveGalaxy);


    //m_program->release(); // Crash there
    glFlush();
    ++m_frame;
}


void Galaxy::drawStars(Star::range &galaxy)
{
    double x,y;
    for(auto itStar = galaxy.begin; itStar != galaxy.end; itStar++) {
        x = (itStar->position).x() * zoom;
        y = itStar->position.y() * zoom;
        //z = itStar->position.z() * zoom; // We only display in 2D

        double R,G,B;
        R = itStar->color.x();
        G = itStar->color.y();
        B = itStar->color.z();
        glBegin(GL_POINTS);
            glColor4d(R, G, B, 255);    // Star color
            glVertex2d(x,y);            // Star position
            //glColor4d(R,G,B,255*05.);
        glEnd();

    }
}
