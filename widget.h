#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

/** The Widget class
 * @brief Create an empty window with an OpenGL Widget
 * @details Create a ready to use window (QWindow) with an OpenGL Widget
 * Initialize parameters when it starts
 */

class Widget : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    /**
     * @brief Create the widget
     * @details Create the window
     * Initialize attributs
     * Set the surface type to an OpenGL surface
     */
    explicit Widget(QWindow *parent = nullptr);

    /**
     * @brief Delete dynamics objects
     * @details Delete dynamics objects allocated to draw on the window
     * Delete OpenGL Paint device
     * Delete the Widget seen in the Ui
     */
    ~Widget();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    /**
     * @brief Update the window to render
     * @param event
     * @return true
     */
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override ;

private:
    Ui::Widget *ui;

    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};
#endif // WIDGET_H
