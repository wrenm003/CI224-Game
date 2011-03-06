#include "TriangularPyramidAsset.h"

TriangularPyramidAsset::TriangularPyramidAsset() {
  // A default "unit" triangular pyramid
  num_vertices = 4;
  num_triangles = 4;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]; // three points per vertex
  g_element_buffer_data = new GLushort[num_triangles * 3]; // three vertices per triangle

  g_vertex_buffer_data[0] = -0.5;
  g_vertex_buffer_data[1] = -0.5;
  g_vertex_buffer_data[2] = 0.5;

  g_vertex_buffer_data[3] = 0.5;
  g_vertex_buffer_data[4] = -0.5;
  g_vertex_buffer_data[5] = 0.5;

  g_vertex_buffer_data[6] = 0.0;
  g_vertex_buffer_data[7] = -0.5;
  g_vertex_buffer_data[8] = -0.5;

  g_vertex_buffer_data[0] = 0.0;
  g_vertex_buffer_data[1] = 0.5;
  g_vertex_buffer_data[2] = 0.0;

  g_element_buffer_data[0] = 0;
  g_element_buffer_data[1] = 1;
  g_element_buffer_data[2] = 3;

  g_element_buffer_data[3] = 1;
  g_element_buffer_data[4] = 2;
  g_element_buffer_data[5] = 3;

  g_element_buffer_data[6] = 2;
  g_element_buffer_data[7] = 0;
  g_element_buffer_data[8] = 3;

  g_element_buffer_data[8] = 2;
  g_element_buffer_data[10] = 0;
  g_element_buffer_data[11] = 1;

  make_resources();
}

TriangularPyramidAsset::~TriangularPyramidAsset() {
  // TODO: do something nice here.
}

void TriangularPyramidAsset::update() {
  // update z-component
  translate[2]+= 1.0f;
}
