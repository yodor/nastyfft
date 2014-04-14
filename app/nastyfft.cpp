

#include "nastyfft.h"
#include "scenepreset.h"


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <QTimer>


//#ifndef GL_MULTISAMPLE
//#define GL_MULTISAMPLE  0x809D
//#endif


NastyFFT::NastyFFT(ScenePreset *m_priv) : QGLWidget(), obj(0), priv(m_priv), is_locked(false)
{
    setAutoFillBackground(false);

    cout << "NastyFFT: CTOR ... " << endl;

    xRot = 0;
    yRot = 0;
    zRot = 0;

	for (int z=0;z<SCOPE_DEPTH;z++)
	{
		for (int a=0;a<NUM_BANDS;a++)
		{
			fftdata[z][a]=0.0f;
		}
	}


    cout << "NastyFFT: CTOR_Finished" << endl;

    obj = gluNewQuadric();
}

NastyFFT::~NastyFFT()
{

    cout << "NastyFFT: DTOR_Finished" << endl;
	
	if (obj) {
	  gluDeleteQuadric(obj);
	  obj=0;
	}
	

}
void NastyFFT::render()
{
    paintGL();
    //qDebug("Time elapsed: %d ms", tim.elapsed());
    //tim.restart();
      /* generate secret number: */


//        int y,a;

//    for (y=SCOPE_DEPTH-1;y>0;y--)
//    {
//        for (a=0;a<NUM_BANDS;a++)
//            fftdata[y][a]=fftdata[y-1][a];
//    }


//        for (int a=0;a<NUM_BANDS;a++)
//        {

//            fftdata[0][a]= rand() % 10 + 1;
//        }
//        updateGL();

//  initializeGL();
//  resizeGL(width, height);
//  paintGL();
  
}

//void NastyFFT::setSize(int w, int h)
//{
//    width = w;
//    height = h;
//}

void NastyFFT::scopeEvent(const FrequencySpectrum &m_spectrum)
{


    register int i, c;

	register int index=0;
	register int y=0;
	register int a=0;

	float maxval=0;
	
  
	for (y=SCOPE_DEPTH-1;y>0;y--)
	{
		for (a=0;a<NUM_BANDS;a++)
			fftdata[y][a]=fftdata[y-1][a];
	}


 //   cout <<m_spectrum.count()<< endl;
//    float data[m_spectrum.count()];

//    FrequencySpectrum::const_iterator itr = m_spectrum.begin();
//    const FrequencySpectrum::const_iterator end = m_spectrum.end();
//    a=0;
//    for ( ; itr != end; ++itr) {
//        const FrequencySpectrum::Element e = *itr;
//        qreal mag = e.magnitude;
//        if (mag>0) {
//            fftdata[0][a] = mag * 10;
//        }
//        else {
//            fftdata[0][a] = 0;
//        }
//        //cout <<e.magnitude<< endl;
//        a++;

//        //if (e.frequency >= m_lowFreq && e.frequency < m_highFreq) {
//        //   Bar &bar = m_bars[barIndex(e.frequency)];
//        //    bar.value = qMax(bar.value, e.amplitude);
//        //    bar.clipped |= e.clipped;
//        //}
//    }


    int xscale[] = {0, 1, 2, 3, 5, 7, 10, 14, 20, 28, 40, 54, 74, 101, 137, 187, 255};

    GLdouble val = 0;

    for (i=0; i<NUM_BANDS; i++) {
	  
	int num_bins = 0;
	val = 0;
	
      for(c = (xscale[i]); c < (xscale[i+1]); c++)
      {
        if (c<256)
        {
            qreal mag = priv->use_magnitude ? m_spectrum[c].magnitude : m_spectrum[c].amplitude;

            if(mag > val)val = mag;
            //val+=mag;
            num_bins++;
        }
        else
            continue;
            
      }
      
    //val = val / num_bins * 1.0;
    //val = sqrt(val);
      if (priv->use_magnitude) {

          val =  priv->scale * log(val);
      }
      else {

          val =   priv->scale * (val * 0.15);
      }
	
      if(val > 0) {
            fftdata[0][i] = val;
          // (val * (priv->use_magnitude ? 1/priv->scale : priv->scale) ) > 10 ? 10 : (val * (priv->use_magnitude ? 1/priv->scale : priv->scale) );
          //fftdata[0][i] = val*16;
      }
      else {

        fftdata[0][i] =  0;
      }
  


	  
    }

	
//    if (priv->light_x>NUM_BANDS)
//        priv->light_dir=-1;
			
//    if (priv->light_x<0)
//        priv->light_dir=1;
			
//    priv->light_x+=priv->light_dir;

    // repaint();
//     qDebug("Time elapsed: %d ms", tim.elapsed());
    // tim.restart();

     updateGL();
}



void NastyFFT::initializeGL1()
{
    printf("NastyFFT: initializeGL\n");
	
	
  //  glEnable(GL_DEPTH_TEST);
//
//    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);


   // glDepthFunc(GL_LEQUAL);
  //  glEnable(GL_DEPTH_TEST);
//    glEnable(GL_NORMALIZE);
	
	
    if (priv->cinvert==true)
    {
       // glBlendFunc (GL_SRC_ALPHA, GL_SRC_ALPHA);
    }
    else
    {
        //glBlendFunc (GL_SRC_ALPHA, GL_DST_ALPHA);
     //   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
    }


	
//    glShadeModel (GL_SMOOTH);
	
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	


	
	
   // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	
    //glEnable(GL_CULL_FACE);
	
	


    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    GLfloat light_position1[] = { (NUM_BANDS/2), 12.0, 0, 4.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
		
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
//    glEnable(GL_MULTISAMPLE);


    GLfloat LightAmbient[]= { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat LightDiffuse[]= { 1.0f, 0.8f, 0.8f, 1.0f };


    glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient);
    glLightfv(GL_LIGHT2,GL_AMBIENT,LightAmbient);

    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);


    GLfloat light_position0[] = {(NUM_BANDS*priv->step_x), 1, (SCOPE_DEPTH*priv->step_z)/2, 1 };
    GLfloat light_position1[] = {(NUM_BANDS*priv->step_x), 1, (SCOPE_DEPTH*priv->step_z)/2, 1 };

    GLfloat light_position2[] = {0, 1, 0, 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);


    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);

    //obj = gluNewQuadric();

//    gluQuadricNormals(obj, GLU_SMOOTH);



}

void NastyFFT::resizeGL(int width, int height)
{

        //cout << "Resize GL" << endl;
// 	printf("NastyFFT: resizeGL (%d,%d)\n", width, height);
	
    GLdouble defFOVY = 60; // field-of-view in degrees in up direction

	glViewport(0, 0, width, height);
	
	GLdouble aspect = (width > height) ? width/height : height/width;
	// field-of-view
	GLdouble fov = defFOVY/aspect;
	
    float nearDist = 1.0f;
    float farDist = 60.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, aspect, nearDist, farDist);
    glMatrixMode(GL_MODELVIEW);

}
void NastyFFT::initializeGL()
{
    cout << "initializeGL" << endl;

    //depth
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    //alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// GL_ONE_MINUS_SRC_ALPHA);


    glDisable(GL_CULL_FACE);

    //material
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat difuseMaterial[] = { .5, .5, .5, 1.0 };
    GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_BACK, GL_DIFFUSE, difuseMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glShadeModel(GL_FLAT);


    //glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT,GL_FASTEST);


    setupLight();

}
void NastyFFT::setupLight()
{

    GLfloat LightAmbient[]= { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat LightDiffuse[]= { 1,1,1,1 };


    glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient);
    glLightfv(GL_LIGHT2,GL_AMBIENT,LightDiffuse);

    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);

    //flashlight0
    GLfloat light_position0[] = {(NUM_BANDS*priv->step_x), 10, (SCOPE_DEPTH*priv->step_z)/2, 1 };

//    GLfloat light_position1[] = {(NUM_BANDS*priv->step_x)/2, 1, (SCOPE_DEPTH*priv->step_z)/2, 1 };

    GLfloat light_position1[] = {0,20,20, 1 };

  //  GLfloat light_position2[] = {0, 1, 0, 1 };
    GLfloat light_position2[] = {0, 1, (SCOPE_DEPTH*priv->step_z), 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);


    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);


   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


}
void NastyFFT::setupCamera()
{


    float center_x = ((NUM_BANDS*priv->step_x)/2.0f)-(priv->step_x/2.0f);
	
    if (priv->cam_coords.x < -(center_x/2))
	{
            priv->cam_dir=1;
	}
    if (priv->cam_coords.x> (center_x*2))
	{
            priv->cam_dir=-1;
	}
	
    if (priv->cammove)
	{
        priv->cam_coords.x=priv->cam_coords.x + (0.05*priv->cam_dir);
	}

    gluLookAt(
      priv->cam_coords.x,
      priv->cam_coords.y,
      priv->cam_coords.z,
	  
      priv->cam_focus.x,
      priv->cam_focus.y,
      priv->cam_focus.z,
		   
		   0,1,0);
	
}

void NastyFFT::paintGL()
{
//    printf("paintGL\n");
//   glViewport(0, 0, width, height);
//   glLoadIdentity();
  
// glClearColor( 0.0, 0.0, 0.0, 0.0);

// glColor3f(1.0, 1.0, 1.0);
// glDisable(GL_BLEND);

// glTranslatef(0,150,-1.0);
// glBegin(GL_LINES);
// for (int a=16;a<NUM_BANDS-16;a++) {
//   glVertex2f(a,150);
//   GLdouble val = fftdata[0][a];

//   if (val>0) {

// // 	  val /= fftdata[1][0];
// // 	  val *= 128;
//    val/=10000000.0f;

//    val*=128;
//    if (val>128)val=128;

//    glVertex2f(a,150 - val);
//   }
//   else {
//    glVertex2f(a,150);

//   }
//   //glVertex2f(,50);
// }
// glEnd();
// glEnable(GL_BLEND);
// glPopMatrix();

  

// 	



    glLoadIdentity();



    glClearColor( 0.0, 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMaterialf(GL_FRONT, GL_SHININESS, priv->shiness);
	

	setupCamera();
    if (priv->cinvert==true)
    {
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHT0);
    }
	

    //glRotatef(priv->rot_x,1,0,0);



    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

 glTranslatef(-(NUM_BANDS*priv->step_x)/2.0f,-5,-(SCOPE_DEPTH*priv->step_z)/2.0f);



// 	glTranslatef(0,-5,0);
	
	GLdouble alpha=1.0;
	GLdouble s = 0.0;
	GLdouble xx=0.0;


	
	
	GLint a,z ;
	

	
    for (z=SCOPE_DEPTH-1;z>=0;z--)
	{

		xx=0.0;

        alpha=1.0-sqrt(z*(1.0f/SCOPE_DEPTH));//1.0 - (log10(sqrt(z*z)));//

		
		for (a=0;a<NUM_BANDS;a++)
		{
		  

			s=fftdata[z][a] ;

			register GLdouble d = a/(NUM_BANDS-1.0);
				
            register GLdouble t_alpha = alpha;
            if (priv->flatten)t_alpha=alpha*s;
			

			
            if (priv->flatten) {
				if (s>0.1)s=0.1;
				else s=0;
			}
			
			
			
			glPushMatrix();

                glColor4d(d,0.1,1.0-d,t_alpha);

                //glColor3d(d,0.1,1.0-d);

				glRotatef(90,1,0,0);
				glTranslatef(0,0,-s);
				


  glRotatef(-90,0,0,1);
                gluDisk(obj, 0,  0.5f , priv->obj_slices,  1);
  glRotatef(90,0,0,1);
				
                if (!priv->flatten) {
					glScaled(1,1,s);
					glRotatef(90.0f,0,0,1);
	
                    gluCylinder(obj, 0.5f, 0.5f, 1 , priv->obj_slices ,1);
				}
				
			glPopMatrix();
			

			
			
            glTranslated(priv->step_x,0,0);
            xx+=priv->step_x;
		}
		glTranslated(-xx,0,0);
        glTranslated(0,0,priv->step_z);


  	}



}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

//! [5]
void NastyFFT::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        //emit xRotationChanged(angle);
        updateGL();
    }
}
//! [5]

void NastyFFT::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        //emit yRotationChanged(angle);
        updateGL();
    }
}

void NastyFFT::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        //emit zRotationChanged(angle);
        updateGL();
    }
}
void NastyFFT::mousePressEvent(QMouseEvent *event)
{
    if (!this->is_locked) {
        lastPos = event->pos();
    }
    else {
        QGLWidget::mousePressEvent(event);
    }
}
//! [9]

//! [10]
void NastyFFT::mouseMoveEvent(QMouseEvent *event)
{
    if (!this->is_locked) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        if (event->buttons() & Qt::LeftButton) {
            setXRotation(xRot + 8 * dy);
            setYRotation(yRot + 8 * dx);
        } else if (event->buttons() & Qt::RightButton) {
            setXRotation(xRot + 8 * dy);
            setZRotation(zRot + 8 * dx);
        }
        lastPos = event->pos();
    }
    else {
        QGLWidget::mouseMoveEvent(event);
    }
}
void NastyFFT::setLocked(bool mode)
{
    this->is_locked = mode;

}
void NastyFFT::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (this->is_locked) {
        emit needUnlock();
    }
    else {
        QGLWidget::mouseDoubleClickEvent(event);
    }
}
