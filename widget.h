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

//TODO Comment this class

class Widget : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit Widget(QWindow *parent = nullptr);
    ~Widget();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override ;

private:
    Ui::Widget *ui;

    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};
#endif // WIDGET_H
