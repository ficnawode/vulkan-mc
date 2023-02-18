#include "gfx/Vbo.hpp"

namespace gfx
{
    VBO::VBO(GLint type, bool dynamic)
    {
        _type = type;
        _dynamic = dynamic;
        glGenBuffers(1, &_handle);
    }

    VBO::~VBO()
    {
        glDeleteBuffers(1, &_handle);
    }

    void VBO::Bind()
    {
        glBindBuffer(_type, _handle);
    }

    void VBO::Buffer(void* data, size_t offset, size_t count)
    {
        Bind();
        glBufferData(_type, count - offset, data, _dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    GLuint VBO::GetHandle() const
    {
        return _handle;
    }
    GLint VBO::GetType() const
    {
        return _type;
    }

}