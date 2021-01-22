#ifndef GALAXY_H
#define GALAXY_H

#include "widget.h"
#include "block.h"
#include "utils.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

//TODO Comment this class

//TODO add a file for simulation parameters
//TODO render on multithreads
class Galaxy : public Widget
{
public:
    Galaxy();

    void initialize() override;
    void render() override;
    void reshape(int w, int h);
private:
    void drawStars(Star::range & galaxy);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    // Parameters
    static constexpr double area = 1000. * LIGHT_YEAR;
    static constexpr double galaxyThickness = 0.05;
    static constexpr int nbStars = 10000;
    static constexpr double speedInit = 10000.;
    static constexpr bool isBlackHole = false;
    static constexpr double blackHoleMass = 0.;
    static constexpr double step = 100000. * YEAR;
    static constexpr double precision = 1.;
    static constexpr bool verletIntegration = true;

    static constexpr Views view = DEFAULT;
    static constexpr double zoom = 1.0/(LIGHT_YEAR * 1000);
    static constexpr bool realColors = false;

    QOpenGLShaderProgram *m_program;
    int m_frame;

    Star::list galaxy;
    Block block;
    Star::range aliveGalaxy;

};


#endif // GALAXY_H
