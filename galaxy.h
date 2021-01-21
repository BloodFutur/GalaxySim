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
    void drawStars(Star::range & galaxy, const Vector & centerMass, const double & area, const double & zoom, Views view);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    // Parameters
    double area;
    double galaxyThickness;
    int nbStars;
    double speedInit;
    bool isBlackHole;
    double blackHoleMass;
    double step;
    double precision;
    bool verletIntegration;

    Views view;
    double zoom;
    bool realColors;

    QOpenGLShaderProgram *m_program;
    int m_frame;

    Star::list galaxy;
    Block block;
};


#endif // GALAXY_H
