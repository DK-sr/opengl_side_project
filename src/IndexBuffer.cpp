#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
: count_(count) {

    GLCall(glGenBuffers(1, &renderer_id_));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &renderer_id_));
}

void IndexBuffer::Bind() const  {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_));
}

void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}