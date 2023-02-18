
#include <array>
#include <glm/glm.hpp>

namespace gfx
{
    class AABB
    {
    public:
        AABB(glm::vec3 v1, glm::vec3 v2) : _vecs{v1, v2}
        {
        }

        glm::vec3 operator[](int index)
        {
            return _vecs[index];
        }

        glm::vec3 GetCenter() const
        {
            return (_vecs[0] + _vecs[1]) * 0.5f;
        }

        static inline glm::vec3 CollisionDepth(AABB a, AABB b)
        {
            glm::vec3 a_c = a.GetCenter();
            glm::vec3 b_c = b.GetCenter();

            return {
                (a_c.x < b_c.x) ? a_c.x - b_c.x : b_c.x - a_c.x,
                (a_c.y < b_c.y) ? a_c.y - b_c.y : b_c.y - a_c.y,
                (a_c.z < b_c.z) ? a_c.z - b_c.z : b_c.z - a_c.z,
            };
        }

        static inline AABB Scale(AABB box, glm::vec3 scale)
        {
            glm::vec3 center = box.GetCenter();
            glm::vec3 size = box[1] - box[0];

            glm::vec3 new_size = size * scale;
            glm::vec3 half_new_size = new_size * 0.5f;

            // scaled AABB centered around same center
            return {-half_new_size + center, half_new_size + center};
        }

        static inline AABB Copy(AABB aabb)
        {
            return {aabb[0], aabb[1]};
        }

    private:
        std::array<glm::vec3, 2> _vecs;
    };

}
