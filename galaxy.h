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

/** @class Galaxy
 * @brief Window simulating a galaxy
 * @todo Render using multithreading
 */
class Galaxy : public Widget
{
public:
    Galaxy();

    /**
     * @brief Initialialize things
     * @details Initialize OpenGL to render
     * Initialize the galaxy
     */
    void initialize() override;

    /**
     * @brief render the galaxy in the viewport
     * @details Render all the stars in the viewport
     * Create blocks (Barnes-Hut algorithm)
     * Update acceleration, density, position and speed of each star
     * @warning It may not work with other values of parameters
     * @note The render is slow
     */
    void render() override;

    /**
     * @brief Reshape the camera of the viewport
     * @param w width
     * @param h hight
     * @warning It is not used
     */
    void reshape(int w, int h);
private:
    /**
     * @brief Draw the stars on the viewport
     * @param galaxy galaxy containing all the stars
     * @details Get the position of every stars
     * Use only x and y (no z) to improve performance
     * Display a point on the viewport
     * @todo Add blured points around a star
     */
    void drawStars(Star::range & galaxy);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    ///
    /// Parameters to initialize the galaxy
    ///
    static constexpr double area = 1000. * LIGHT_YEAR;
    static constexpr double galaxyThickness = 0.05;
    static constexpr int nbStars = 10000;
    static constexpr double speedInit = 10000.;
    static constexpr bool isBlackHole = false;
    static constexpr double blackHoleMass = 0.;
    static constexpr double step = 100000. * YEAR;
    static constexpr double precision = 2.;
    static constexpr bool verletIntegration = true;

    static constexpr Views view = DEFAULT;
    static constexpr double zoom = 2.0/(LIGHT_YEAR * 1000);
    static constexpr bool realColors = false;


    QOpenGLShaderProgram *m_program;
    int m_frame;

    Star::list galaxy;
    Block block;
    Star::range aliveGalaxy;

};


#endif // GALAXY_H
