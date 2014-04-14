#ifndef _PLUGIN_NASTYFFT_H_
#define _PLUGIN_NASTYFFT_H_

#include "scenepreset.h"

#include <QGLWidget>
#include <QTime>
#include <QMouseEvent>

#include <GL/glu.h>

#include "frequencyspectrum.h"

class NastyFFT  : public QGLWidget
{
Q_OBJECT

public:
    NastyFFT(ScenePreset *m_priv);
    ~NastyFFT();





signals:
    void presetChanged();
    void needUnlock();

public slots:
    void scopeEvent(const FrequencySpectrum &m_spectrum);
    void render();


    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setLocked(bool mode);

protected:
    void initDefault();
	
	void setupCamera();
	
	void initializeGL();
    void initializeGL1();
    void setupLight();

	void resizeGL(int w, int h);
	void paintGL();


    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

	GLUquadric *obj;
	
    ScenePreset *priv;


	int width;
	int height;
	
	GLdouble fftdata[SCOPE_DEPTH][NUM_BANDS];



    QTime tim;

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    bool is_locked;
};

#endif // _PLUGIN_NASTYFFT_H_


