
#pragma once

namespace entity
{
    class Component
    {
    public:
        Component();
        ~Component() = default;
        virtual void Init(){};
        virtual void Render(){};
        virtual void Update(){};
        virtual void Tick(){};

    private:
    };
}