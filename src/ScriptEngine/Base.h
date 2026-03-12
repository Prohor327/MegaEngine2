#include <Game/GameObject.h>

namespace scripts
{
    class base
    {
    protected:
        GameObject* gameObject;

    public:
        virtual void Start();
        virtual void Update();
    };
}