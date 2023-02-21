#pragma once
#include <glm/glm.hpp>
#include "entity/Component.hpp"
#include "world/World.hpp"

namespace entity
{
    class PositionComp : public Component
    {
    public:
        PositionComp();
        ~PositionComp() = default;
        virtual void Render(){};
        virtual void Update(){};
        virtual void Tick()
        {
            glm::ivec3 block = world::World::PosToBlock(_position);
            glm::ivec3 offset = world::World::PosToOffset(_position);

            if(block == _block)
            {
                _block = block;
                _blockChanged = true;
            }
            else
            {
                _blockChanged = false;
            }

            if(offset == _offset)
            {
                _offset = offset;
                _offsetChanged = true;
            }
            else
            {
                _offsetChanged = false;
            }
        }

        glm::vec3 GetPosition()
        {
            return _position;
        }
        glm::ivec3 GetBlock()
        {
            return _block;
        }
        glm::ivec3 GetOffset()
        {
            return _offset;
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