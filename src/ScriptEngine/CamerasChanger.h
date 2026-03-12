#include "Base.h"
#include "Game/Camera.h"

namespace scripts
{
    class CamerasChanger : Base
    {
    private:
        void ChangeCamera();

    public:
        override void Start();
    };
}