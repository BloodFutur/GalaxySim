#ifndef GALAXY_H
#define GALAXY_H

#include "widget.h"

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
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

#endif // GALAXY_H
