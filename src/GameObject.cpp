/*
 * GameObject.cpp
 *
 *  Created on: 03-Mar-2009
 *      Author: balor
 */

#include "GameObject.h"

GameObject::GameObject() {
	this->num_vertices = 0;
	this->vertices = NULL;

}

GameObject::GameObject(const char * filename) {
	ifstream md2file;
	md2file.open(filename, ios::in|ios::binary);

	// C stuff
	md2_header_t * md2header = (struct md2_header_t *)
		malloc(sizeof(struct md2_header_t));
	// it involves evil casting.  Would be much happier if this was byte *.
	md2file.read((char *) md2header, sizeof (struct md2_header_t));

	if ((md2header->ident != 844121161) ||
			(md2header->version != 8)) {
		/* Error! */
		cerr << "Error: bad version or identifier" << endl;
	}

	// Get the triangle data.
	this->triangles = (md2_triangle_t *)
			calloc(md2header->num_tris, sizeof (struct md2_triangle_t));
	this->num_triangles = md2header->num_tris;

	md2file.seekg(md2header->offset_tris, ios::beg);
	md2file.read((char *) triangles, sizeof (struct md2_triangle_t) * md2header->num_tris);

	// Get the vertices of the first frame only.
	// Note: this is dangerous, we _really_
	// should populate the whole structure as documented in
	// http://tfc.duke.free.fr/coding/md2-specs-en.html
	this->vertices = (vec3_t *)
		calloc (md2header->num_vertices, sizeof (vec3_t));

	md2file.seekg(md2header->offset_frames, ios::beg);

	/* Read first frame data */
	vec3_t * scale = (vec3_t *) malloc(sizeof(vec3_t));
	md2file.read((char *) scale, sizeof (vec3_t));
	cout << (*scale)[0] << " " << (*scale)[1] << " " << (*scale)[2] << endl;

	vec3_t * translate = (vec3_t *) malloc(sizeof(vec3_t));
	md2file.read((char *) translate, sizeof (vec3_t));
	cout << (*translate)[0] << " " << (*translate)[1] << " " << (*translate)[2] << endl;

	// beware the magic number
	char * name = (char *) calloc(16, sizeof(char));
	md2file.read((char *) name, 16);
	cout << name << endl;

	md2_vertex_t * c_vertices = (md2_vertex_t *) calloc(md2header->num_vertices, sizeof (struct md2_vertex_t));
	md2file.read((char *) c_vertices, (sizeof (struct md2_vertex_t)) *
			md2header->num_vertices);
	this->num_vertices = md2header->num_vertices;

	// Unpack vertices
	this->vertices = (vec3_t *) calloc(this->num_vertices, sizeof(vec3_t));
	for(int i=0; i<this->num_vertices;i++) {
		this->vertices[i][0] = (c_vertices[i].v[0] * (*scale)[0]) + (*translate)[0];
		this->vertices[i][1] = (c_vertices[i].v[1] * (*scale)[1]) + (*translate)[1];
		this->vertices[i][2] = (c_vertices[i].v[2] * (*scale)[2]) + (*translate)[2];
	}

	// Hopefully we now have vertices.  Note: No error checking.
	// cleanup
	md2file.close();
	free(c_vertices);
	free(scale);
	free(translate);
	free(name);
	free(md2header);
}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}

void GameObject::draw() {

	glBegin(GL_TRIANGLES);
		for(int i=0; i<this->num_triangles;i++) {
			for(int j=0; j<3; j++) {
				glVertex3fv(this->vertices[this->triangles[i].vertex[j]]);
			}
		}
	glEnd();
}
