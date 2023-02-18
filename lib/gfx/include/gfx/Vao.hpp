#pragma once

#include "gfx/Vbo.hpp"

namespace gfx
{
    class VAO
    {
    public:
        VAO();
        ~VAO();
        void Bind();
        void Attr(VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

    private:
        GLuint _handle;
    };

}
