/*
 * GameObject.h
 *
 *  Created on: 03-Mar-2009
 *      Author: balor
 */
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef GAMEASSET_H_
#define GAMEASSET_H_

class GameAsset {
public:
	GameAsset(const string &filename);
	virtual ~GameAsset();

	virtual void draw();
private:
	/* functions */
	void import_md2_asset(const string &filename);
	int make_resources();
	GLchar* shader_file_contents(const string &filename, GLint * length);
	GLuint make_buffer(GLenum target, const void *buffer_data, GLsizei buffer_size);
	GLuint make_shader(GLenum type, const char *filename);
	GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);

	
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

	//vec3_t * vertices;
	int num_vertices;
	md2_triangle_t * triangles;
	int num_triangles;

	/* For keeping track of OpenGL VBOs */
	GLuint vertex_buffer, element_buffer;
	GLuint vertex_shader, fragment_shader, program;
	GLint position;
	GLint rotate_x;

	GLfloat * g_vertex_buffer_data;
	GLushort * g_element_buffer_data;
	GLfloat rotate_x_theta;

};

#endif /* GAMEASSET_H_ */
