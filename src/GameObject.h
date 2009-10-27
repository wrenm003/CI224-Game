/*
 * GameObject.h
 *
 *  Created on: 03-Mar-2009
 *      Author: balor
 */
#include <GL/gl.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class GameObject {
public:
	GameObject();
	GameObject(const char * filename);
	virtual ~GameObject();

	virtual void draw();
private:
	/* MD2 header from http://tfc.duke.free.fr/coding/md2-specs-en.html */
	struct md2_header_t
	{
	  int ident;                  /* magic number: "IDP2" */
	  int version;                /* version: must be 8 */

	  int skinwidth;              /* texture width */
	  int skinheight;             /* texture height */

	  int framesize;              /* size in bytes of a frame */

	  int num_skins;              /* number of skins */
	  int num_vertices;           /* number of vertices per frame */
	  int num_st;                 /* number of texture coordinates */
	  int num_tris;               /* number of triangles */
	  int num_glcmds;             /* number of opengl commands */
	  int num_frames;             /* number of frames */

	  int offset_skins;           /* offset skin data */
	  int offset_st;              /* offset texture coordinate data */
	  int offset_tris;            /* offset triangle data */
	  int offset_frames;          /* offset frame data */
	  int offset_glcmds;          /* offset OpenGL command data */
	  int offset_end;             /* offset end of file */
	};

	/* Compressed vertex */
	struct md2_vertex_t
	{
	  unsigned char v[3];         /* position */
	  unsigned char normalIndex;  /* normal vector index */
	};

	/* Triangle info */
	struct md2_triangle_t
	{
	  unsigned short vertex[3];   /* vertex indices of the triangle */
	  unsigned short st[3];       /* tex. coord. indices */
	};

	/* Vector */
	typedef float vec3_t[3];

	vec3_t * vertices;
	int num_vertices;
	md2_triangle_t * triangles;
	int num_triangles;
};

#endif /* GAMEOBJECT_H_ */
