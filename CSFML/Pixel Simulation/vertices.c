#include "vertices.h"

void initVertexArray() {
	m_vertices = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(m_vertices, sfQuads);
	sfVertexArray_resize(m_vertices, W_WIDTH * W_HEIGHT * 4);
}