/*
 * GameObject.cpp
 *
 *  Created on: 03-Mar-2009
 *      Author: balor
 */

#include "GameObject.h"

GameObject::GameObject(const string &filename) {
        rotate_x_theta=0;
  
        import_md2_asset(filename);
        make_resources();

	// make the objects to display
	if(0 == make_resources()) {
	  cout << "Can't make the required OpenGL resources for GameObject." << endl;
	  // TODO: exit nicely here
	}

}

void GameObject::import_md2_asset(const string &filename) {
	ifstream md2file;
	md2file.open(filename.c_str(), ios::in|ios::binary);

	// C stuff
	md2_header_t * md2header = (struct md2_header_t *)
		malloc(sizeof(struct md2_header_t));
	// it involves evil casting.
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

	// Turn the triangle information into an index buffer
	this->g_element_buffer_data = new GLushort[this->num_triangles * 3]; // 3 vertices per triangle
	for(int i=0; i<num_triangles;i++) {
	  this->g_element_buffer_data[(i*3)] = triangles[i].vertex[0];
	  this->g_element_buffer_data[(i*3) + 1] = triangles[i].vertex[1];
	  this->g_element_buffer_data[(i*3) + 2] = triangles[i].vertex[2];
	}

	// Get the vertices/indices of the first frame only.
	// Note: this is dangerous, we _really_
	// should populate the whole structure as documented in
	// http://tfc.duke.free.fr/coding/md2-specs-en.html
	this->g_vertex_buffer_data = new GLfloat[this->num_vertices * 3]; // 3 points per vertex

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

	// Unpack vertices - put them in a 1d array.
	for(int i=0; i<this->num_vertices;i++) {
		this->g_vertex_buffer_data[i * 3] = (c_vertices[i].v[0] * (*scale)[0]) + (*translate)[0];
		this->g_vertex_buffer_data[(i*3)+1] = (c_vertices[i].v[1] * (*scale)[1]) + (*translate)[1];
		this->g_vertex_buffer_data[(i*3)+2] = (c_vertices[i].v[2] * (*scale)[2]) + (*translate)[2];
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
  glUseProgram(program);

  glUniform1f(rotate_x, rotate_x_theta++);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(
			position,                         /* attribute */
			3,                                /* size */
			GL_FLOAT,                         /* type */
			GL_FALSE,                         /* normalized? */
			0,                                /* stride */
			(void*)0                          /* array buffer offset */
			);
  glEnableVertexAttribArray(position);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glDrawElements(
		 GL_TRIANGLES,
		 3 * this->num_triangles,
		 GL_UNSIGNED_SHORT,
		 (GLvoid*) 0
		 );
  
  glDisableVertexAttribArray(position);
}

/*
 * Functions for general purpose stuff
 */
GLchar * GameObject::shader_file_contents(const string &filename, GLint * length)
{
  ifstream input_file;
  input_file.open(filename.c_str(), ios::in);

  input_file.seekg(0, ios::end);  // go to the end of the file
  *length = input_file.tellg();  // get length of the file
  input_file.seekg(0, ios::beg);  // go to beginning of the file

  GLchar * buffer = new GLchar[(*length)+1];
  input_file.read(buffer, *length);
  buffer[(*length)+1]='\0';  // Ensure null terminated

  input_file.close();
  return buffer;
}

/*
 * Functions for creating OpenGL objects:
 */
GLuint GameObject::make_buffer(
    GLenum target,
    const void *buffer_data,
    GLsizei buffer_size
) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    return buffer;
}

GLuint GameObject::make_shader(GLenum type, const char *filename)
{
    GLint length;
    GLchar *source = shader_file_contents(filename, &length);
    GLuint shader;
    GLint shader_ok;

    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    delete(source);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        cerr << "Failed to compile" << filename << " with error code " << shader_ok << endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint GameObject::make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;

    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        cerr<< "Failed to link shader program:" << endl;
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

/*
 * Load and create all of our resources:
 */
int GameObject::make_resources(void)
{
    vertex_buffer = make_buffer(
        GL_ARRAY_BUFFER,
        g_vertex_buffer_data,
        3 * sizeof(GLfloat) * this->num_vertices
    );
    element_buffer = make_buffer(
        GL_ELEMENT_ARRAY_BUFFER,
        g_element_buffer_data,
        3 *  sizeof(GLushort) * this->num_triangles
    );

    vertex_shader = make_shader(
        GL_VERTEX_SHADER,
        "hello-gl.v.glsl"
    );
    if (vertex_shader == 0)
        return 0;

    fragment_shader = make_shader(
        GL_FRAGMENT_SHADER,
        "hello-gl.f.glsl"
    );
    if (fragment_shader == 0)
        return 0;
    
    program = make_program(vertex_shader, fragment_shader);
    if (program == 0)
        return 0;

    position = glGetAttribLocation(program, "position");    
    rotate_x = glGetUniformLocation(program, "rotate_x_theta");

    return 1;
}
