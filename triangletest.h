#ifndef TRIANGLETEST_H
#define TRIANGLETEST_H

#include "widget.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

/** @class TriangleTest
 * @brief The TriangleTest class is a test to check OpenGL functions
 * @details It is in Qt examples
 */
class TriangleTest: public Widget
{
public:
    TriangleTest();

    void initialize() override;
    void render() override;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};


#endif // TRIANGLETEST_H
