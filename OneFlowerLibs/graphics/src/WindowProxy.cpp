#include <module/window/WindowProxy.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<of::module::window::WindowProxy>::type = of::module::EngineResourceType::Graphics;

namespace of::module::window
{

    of::module::EngineResourceType& WindowProxy::getType() const
    {
        return type;
    }

}
