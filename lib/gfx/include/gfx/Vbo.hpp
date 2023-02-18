
#pragma once
#include "gfx/gfx.hpp"

namespace gfx
{

    class VBO
    {
    public:
        VBO(GLint type, bool dynamic);
        ~VBO();

        void Bind();
        void Buffer(void* data, size_t offset, size_t count);

        GLuint GetHandle() const;
        GLint GetType() const;

    private:
        GLuint _handle = 0;
        GLint _type;
        bool _dynamic;
    };

}