#include "gfx/gfx.hpp"

#include "camera/OrthoCamera.hpp"
#include "camera/PerspectiveCamera.hpp"
#include "camera/types.hpp"

#include "gfx/Texture.hpp"
#include "gfx/gfx.hpp"

namespace gfx
{
    struct VertexAttr
    {
        GLuint index;
        const GLchar* name;
    };

    struct Shader
    {
    public:
        Shader(std::string vertexShaderPath, std::string fragmentShaderPath, gsl::span<VertexAttr> attributes);
        Shader() : Shader("", "", {}){};
        ~Shader();

        void Bind();
        void Uniform(std::string name, glm::mat4 m);
        void Uniform(glm::mat4 view, glm::mat4 proj);
        void Uniform(std::string name, Texture texture, GLuint n);
        void Uniform(std::string name, float f);
        void Uniform(std::string name, glm::vec2 v);
        void Uniform(std::string name, glm::vec3 v);
        void Uniform(std::string name, glm::vec4 v);
        void Uniform(std::string name, int d);
        void Uniform(std::string name, unsigned int u);

    private:
        GLint Compile(std::string path, GLenum type);
        void LogAndFail(
            GLint handle,
            const char* adverb,
            const char* path,
            void (*getlog)(GLuint, GLsizei, GLsizei*, GLchar*),
            void (*getiv)(GLuint, GLenum, GLint*));

        GLint GetUniformLocation(std::string name);

        GLuint _handle;
        GLuint _vertexShaderHandle;
        GLuint _fragmentShaderHandle;
    };

}

// struct Shader shader_create(char* vs_path, char* fs_path, size_t n, struct VertexAttr attributes[]);
// void shader_destroy(struct Shader self);
// void shader_bind(struct Shader self);
// void shader_uniform_mat4(struct Shader self, char* name, mat4s m);
// void shader_uniform_view_proj(struct Shader self, struct ViewProj view_proj);
// void shader_uniform_texture2D(struct Shader self, char* name, struct Texture texture, GLuint n);
// void shader_uniform_float(struct Shader self, char* name, f32 f);
// void shader_uniform_vec2(struct Shader self, char* name, vec2s v);
// void shader_uniform_vec3(struct Shader self, char* name, vec3s v);
// void shader_uniform_vec4(struct Shader self, char* name, vec4s v);
// void shader_uniform_int(struct Shader self, char* name, int v);
// void shader_uniform_uint(struct Shader self, char* name, unsigned int v);
