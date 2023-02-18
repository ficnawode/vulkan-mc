#pragma once
#include <glm/glm.hpp>
#include "entity/Component.hpp"

namespace entity
{
    class PositionComp : public Component
    {
    public:
        PositionComp();
        ~PositionComp() = default;
        virtual void Render(){};
        virtual void Update(){};
        virtual void Tick(){
            glm::ivec3 block = 

        };

        glm::vec3 GetPosition()
        {
            return _position;
        }
        glm::ivec3 GetBlock(){return _block} glm::ivec3 GetOffset()
        {
            return _offset
        }
        bool isBlockChanged()
        {
            return _blockChanged;
        }
        bool isOffsetChanged()
        {
            return _offsetChanged;
        }

    private:
        glm::vec3 _position;
        glm::ivec3 _block;
        glm::ivec3 _offset;
        bool _blockChanged;
        bool _offsetChanged;
    };
}