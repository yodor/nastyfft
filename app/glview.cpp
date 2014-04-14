/***************************************************************************
 *   Copyright (C) 2008 by yodor   *
 *   yodor@macmini   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "glview.h"
#include <QTimer>



int clearbits;

#define BOARDSIZE 9
#define HALFTHICK 0.04
double M_PI=22.0/7.0;
float reldist=1;
double theta=0.0;

#include "pulseaudiomonitor.h"

GLView::GLView(QWidget *parent)
    : QGLWidget(parent), sq_index(0),ypos(0),angle(-90)
{
//	QTimer *timer = new QTimer(this);
//	connect(timer, SIGNAL(timeout()), this, SLOT(updateBoard()));
//	timer->start(300);


//    PulseAudioMonitor test;
//    test.start();

}


GLView::~GLView()
{

}

void GLView::initializeGL()
{
	glClearColor(0.0,0.0,0.0,0.0);
	clearbits = GL_COLOR_BUFFER_BIT;
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	setupLights();
	glEnable(GL_DEPTH_TEST);
	clearbits |= GL_DEPTH_BUFFER_BIT;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
}

void GLView::resizeGL(int width, int height)
{
	GLfloat h = (GLfloat) height / (GLfloat) width;
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1/h, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}

void GLView::paintGL()
{
	GLfloat amb[] = {0.8,0.8,0.8,1.0 };
	glClear(clearbits);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.2);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15/BOARDSIZE);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.15/BOARDSIZE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);


 	glTranslatef(0.0, 0.0, -reldist*BOARDSIZE);
  	glRotatef(22.5, 1.0, 0.0, 0.0);
	// gltrackball_rotate (c->trackball);
	glRotatef(theta*100, 0.0, 1.0, 0.0);
	glTranslatef(-0.5*BOARDSIZE, 0.0, -0.5*BOARDSIZE);

	for (int x=0;x<BOARDSIZE;x++){
		for (int z=0;z<BOARDSIZE;z++){
			GLfloat cred = ((x+z)%3 == 0)||((x+z+1)%3 == 0);
			GLfloat cgreen = ((x+z+1)%3 == 0);
			GLfloat cblue = ((x+z+2)%3 == 0);

			glColor3f(cred, cgreen, cblue);
			glPushMatrix();
			GLfloat y = 0;

			glTranslatef(x,y,z);
			if (angle!=0 && sq_index==((z*BOARDSIZE)+x))
			{
				
				glRotatef(180-angle*180/M_PI,1,0,0);
				
			}
			drawSquare();
			glPopMatrix();
		}
	}
}

void GLView::setupLights()
{
	GLfloat position0[] =  { 0, BOARDSIZE * 0.3, 0, 1.0 };
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION, position0);
	glEnable(GL_LIGHT0);

}

void GLView::drawSquare()
{
	glBegin( GL_QUADS );

  glNormal3f( 0, -1, 0 );
  glVertex3f( HALFTHICK,  -HALFTHICK,  HALFTHICK );
  glVertex3f( 1-HALFTHICK,   -HALFTHICK, HALFTHICK );
  glVertex3f( 1-HALFTHICK, -HALFTHICK,  1-HALFTHICK);
  glVertex3f( HALFTHICK, -HALFTHICK, 1-HALFTHICK );

  //if (wire) { glEnd(); glBegin (GL_LINE_LOOP); }

  /* back */
  glNormal3f( 0, 1, 0 );
  glVertex3f( HALFTHICK, HALFTHICK, 1-HALFTHICK );
  glVertex3f( 1-HALFTHICK, HALFTHICK,  1-HALFTHICK);
  glVertex3f( 1-HALFTHICK,   HALFTHICK, HALFTHICK );
  glVertex3f( HALFTHICK,  HALFTHICK,  HALFTHICK );

 // if (wire) { glEnd(); return; }

  /* 4 edges!!! weee.... */
  glNormal3f( 0, 0, -1 );
  glVertex3f( HALFTHICK, HALFTHICK, HALFTHICK );
  glVertex3f( 1-HALFTHICK, HALFTHICK, HALFTHICK );
  glVertex3f( 1-HALFTHICK, -HALFTHICK, HALFTHICK );
  glVertex3f( HALFTHICK, -HALFTHICK, HALFTHICK );
  glNormal3f( 0, 0, 1 );
  glVertex3f( HALFTHICK, HALFTHICK, 1-HALFTHICK );
  glVertex3f( HALFTHICK, -HALFTHICK, 1-HALFTHICK );
  glVertex3f( 1-HALFTHICK, -HALFTHICK, 1-HALFTHICK );
  glVertex3f( 1-HALFTHICK, HALFTHICK, 1-HALFTHICK );
  glNormal3f( 1, 0, 0 );
  glVertex3f( 1-HALFTHICK, HALFTHICK, 1-HALFTHICK );
  glVertex3f( 1-HALFTHICK, -HALFTHICK, 1-HALFTHICK );
  glVertex3f( 1-HALFTHICK, -HALFTHICK, HALFTHICK );
  glVertex3f( 1-HALFTHICK, HALFTHICK, HALFTHICK );
  glNormal3f( -1, 0, 0 );
  glVertex3f( HALFTHICK, HALFTHICK, 1-HALFTHICK );
  glVertex3f( HALFTHICK, HALFTHICK, HALFTHICK );
  glVertex3f( HALFTHICK, -HALFTHICK, HALFTHICK );
  glVertex3f( HALFTHICK, -HALFTHICK, 1-HALFTHICK );
  glEnd();

}

void GLView::updateBoard()
{



	if (angle!=0){
		angle=0;
	}
	else {
		sq_index++;
		
		angle=-45.0;
		
	}
	if (sq_index==(BOARDSIZE*BOARDSIZE))sq_index=0;

	//theta++;
    repaint();
}

void GLView::drawFFT(QByteArray fftdata)
{
    updateBoard();
}


