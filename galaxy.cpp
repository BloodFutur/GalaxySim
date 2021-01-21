#include "galaxy.h"
#include <QDebug>
Galaxy::Galaxy()
    : m_program(0)
    , m_frame(0)
{
    // Parameters
    area = 1000.;
    galaxyThickness = 0.01;
    nbStars = 100;
    speedInit = 10000.;
    isBlackHole = false;
    blackHoleMass = 0.;
    step = 10000;
    precision = 1.;
    verletIntegration = true;

    view = DEFAULT;
    zoom = 1.;
    realColors = true;
}


void Galaxy::initialize()
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,1920,1080);

    area *= LIGHT_YEAR;
    step *= YEAR;

    initializeGalaxy(galaxy, nbStars, area, speedInit, step, isBlackHole, blackHoleMass, galaxyThickness);




}

void Galaxy::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);


    Star::range aliveGalaxy { galaxy.begin(), galaxy.end()};

    for(auto itStar = aliveGalaxy.begin; itStar != aliveGalaxy.end; itStar++) {
        itStar->updateAccelerationDensity(block, precision);
        if(!verletIntegration)
            itStar->updateSpeed(step, area);

        //itStar->updatePosition(step, verletIntegration); //BUG App crashes there
        itStar->updatePosition(step, false);
        if(!isIn(block, *itStar))
            itStar->isAlive = false;
        else if(!realColors)
            itStar->updateColor();

    }

    qDebug() << "Wsh";
    createBlocks(area, block, aliveGalaxy);
    drawStars(aliveGalaxy, block.massCenter, area, zoom, view);


    //m_program->release();
    glFlush();
    ++m_frame;
}



void Galaxy::drawStars(Star::range &galaxy, const Vector &centerMass, const double &area, const double &zoom, Views view)
{
    double x,y,z,
            xP,yP,zP;
    double zo = 1.0/(LIGHT_YEAR * 1000);
    int t = 0;
    for(auto itStar = galaxy.begin; itStar != galaxy.end; itStar++, t++) {
        x = (itStar->position).x();
        y = itStar->position.y();
        z = itStar->position.z();

        xP = x * zo;
        yP = y * zo;
        zP = z * zo;
        qDebug() << xP << " " << yP << ' ' << zP << '\n';

        glColor4d(itStar->color.x(), itStar->color.y(), itStar->color.z(), 255);
        glPointSize(5);
        glBegin(GL_POINTS);


            glColor4d(255, itStar->color.y() * zo, itStar->color.z() * zo, 255 * 0.5);
            glVertex3d(xP,yP,zP);

        glEnd();
    }
}
