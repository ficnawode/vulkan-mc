#include "gfx/Vao.hpp"

namespace gfx
{

    VAO::VAO()
    {
        glGenVertexArrays(1, &_handle);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &_handle);
    }

    void VAO::Bind()
    {
        glBindVertexArray(_handle);
    }

    void VAO::Attr(VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
    {
        Bind();
        vbo.Bind();

        // glVertexAttribPointer AUTO-CONVERTS integer values to floating point.
        // Why would anyone design a system like this?
        // Need to be knee deep in the debugger to even notice this
        switch(type)
        {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(index, size, type, stride, (void*)offset);
            break;
        default:
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
            break;
        }
        glEnableVertexAttribArray(index);
    }
}
