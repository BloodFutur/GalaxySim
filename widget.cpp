#include "widget.h"
#include "ui_widget.h"
#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

Widget::Widget(QWindow *parent)
    : QWindow(parent)
    , ui(new Ui::Widget)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
{
    //ui->setupUi(this);
    setSurfaceType(QWindow::OpenGLSurface);

}

Widget::~Widget()
{
    delete m_device;
    delete ui;
}

void Widget::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void Widget::initialize()
{
}

void Widget::render() {
    if(!m_device)
        m_device = new QOpenGLPaintDevice;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(this->size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    QPainter painter(m_device);
    render(&painter);
}

void Widget::renderLater() {
    requestUpdate();
}

bool Widget::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::UpdateRequest :
            renderNow();
            return true;
    default:
        return QWindow::event(event);
    }
}

void Widget::exposeEvent(QExposeEvent *event) {
    Q_UNUSED(event);

    if(isExposed())
        renderNow();
}

void Widget::renderNow() {
    if(!isExposed())
        return;

    bool needsInitialise = false;

    if(!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialise = true;
    }

    m_context->makeCurrent(this);

    if(needsInitialise) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if(m_animating)
        renderLater();
}

void Widget::setAnimating(bool animating) {
    m_animating = animating;
    if(animating)
         renderLater();
}
