/***************************************************************************
 *   Copyright (C) 2005 by yodor   *
 *   yodor@developer.bg   *
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
#ifndef SCENEPRESET
#define SCENEPRESET

#include <QtOpenGL>

#include <iostream>
#include <string>
using namespace std;

#define NUM_BANDS 16
#define SCOPE_DEPTH 16


typedef struct Coords {
	GLdouble x;
	GLdouble y;
	GLdouble z;
} Coords;

typedef struct ScenePreset {
	GLfloat beat;
	
	GLfloat light_x;
	GLint   light_dir;

	GLfloat  shiness;
	
// 	GLfloat cam_y;
    GLfloat rot_x;
    GLfloat step_z;
    GLfloat scale; //1.0

	GLdouble step_x;
	GLfloat fdist_z;

	bool cinvert;
	bool cammove;
	bool tranzient;
	bool flatten;
	
    bool use_magnitude;

	Coords		cam_coords;
	Coords		cam_focus;
	int			cam_dir;

    GLint obj_slices;

	string name;

} ScenePreset;



#endif
