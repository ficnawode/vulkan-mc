#include "gfx/Shader.hpp"

#include <cstdlib>
#include <cstring>

#include <glm/gtc/type_ptr.hpp>

namespace gfx
{
    Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath, gsl::span<VertexAttr> attributes)
    {
        _vertexShaderHandle = Compile(vertexShaderPath, GL_VERTEX_SHADER);
        _fragmentShaderHandle = Compile(fragmentShaderPath, GL_FRAGMENT_SHADER);
        _handle = glCreateProgram();

        // Link shader program
        glAttachShader(_handle, _vertexShaderHandle);
        glAttachShader(_handle, _fragmentShaderHandle);

        // Bind vertex attributes
        for(VertexAttr attribute: attributes)
        {
            glBindAttribLocation(_handle, attribute.index, attribute.name);
        }

        glLinkProgram(_handle);

        // Check link status
        GLint linked;
        glGetProgramiv(_handle, GL_LINK_STATUS, &linked);

        if(linked == 0)
        {
            char buf[512];
            std::snprintf(
                buf,
                512,
                "[%s, %s]",
                vertexShaderPath.c_str(),
                fragmentShaderPath.c_str());
            LogAndFail(_handle, "linking", buf, glGetProgramInfoLog, glGetProgramiv);
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(_handle);
        glDeleteShader(_vertexShaderHandle);
        glDeleteShader(_fragmentShaderHandle);
    }

    GLint Shader::Compile(std::string path, GLenum type)
    {
        FILE* f;
        char* text;
        long len;

        f = fopen(path.c_str(), "rb");
        if(f == NULL)
        {
            fprintf(stderr, "error loading shader at %s\n", path.c_str());
            exit(1);
        }

        fseek(f, 0, SEEK_END);
        len = ftell(f);
        assert(len > 0);
        fseek(f, 0, SEEK_SET);
        text = (char*)std::calloc(1, len);
        assert(text != NULL);
        fread(text, 1, len, f);
        assert(strlen(text) > 0);
        fclose(f);

        GLuint handle = glCreateShader(type);
        glShaderSource(handle, 1, (const GLchar* const*)&text, (const GLint*)&len);
        glCompileShader(handle);

        GLint compiled;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

        // Check OpenGL logs if compilation failed
        if(compiled == 0)
        {
            LogAndFail(handle, "compiling", path.c_str(), glGetShaderInfoLog, glGetShaderiv);
        }

        free(text);
        return handle;
    }

    void Shader::LogAndFail(
        GLint handle,
        const char* adverb,
        const char* path,
        void (*getlog)(GLuint, GLsizei, GLsizei*, GLchar*),
        void (*getiv)(GLuint, GLenum, GLint*))
    {
        GLint loglen;
        getiv(handle, GL_INFO_LOG_LENGTH, &loglen);

        char* logtext = (char*)std::calloc(sizeof(char), loglen);
        getlog(handle, loglen, NULL, logtext);
        fprintf(stderr, "Error %s shader at %s:\n%s", adverb, path, logtext);

        free(logtext);
        exit(1);
    }
    void Shader::Bind()
    {
        glUseProgram(_handle);
    }

    void Shader::Uniform(std::string name, glm::mat4 m)
    {
        auto location = GetUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(m));
    }

    void Shader::Uniform(std::string name, glm::mat4 view, glm::mat4 proj)
    {
        Uniform("p", proj);
        Uniform("v", view);
    }

    void Shader::Uniform(std::string name, Texture texture, GLuint n)
    {
        glActiveTexture(GL_TEXTURE0 + n);
        texture.Bind();
        auto location = GetUniformLocation(name);
        glUniform1i(location, n);
    }

    void Shader::Uniform(std::string name, float f)
    {
        auto location = GetUniformLocation(name);
        glUniform1f(location, f);
    }

    void Shader::Uniform(std::string name, glm::vec2 v)
    {
        auto location = GetUniformLocation(name);
        glUniform2f(location, v.x, v.y);
    }

    void Shader::Uniform(std::string name, glm::vec3 v)
    {
        auto location = GetUniformLocation(name);
        glUniform3f(location, v.x, v.y, v.z);
    }

    void Shader::Uniform(std::string name, glm::vec4 v)
    {
        auto location = GetUniformLocation(name);
        glUniform4f(location, v.x, v.y, v.z, v.w);
    }

    void Shader::Uniform(std::string name, int d)
    {
        auto location = GetUniformLocation(name);
        glUniform1i(location, d);
    }

    void Shader::Uniform(std::string name, unsigned int u)
    {
        auto location = GetUniformLocation(name);
        glUniform1ui(location, u);
    }

    GLint Shader::GetUniformLocation(std::string name)
    {
        return glGetUniformLocation(_handle, (const GLchar*)name.c_str());
    }
}