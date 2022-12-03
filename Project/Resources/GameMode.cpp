#include "GameMode.hpp"
#include <file/Handler.hpp>

of::common::uuid of::file::archive::Trait<Resource::GameMode>::typeId = of::common::uuid("655f83d2-bd83-4065-9b47-3109c4e57d5c");

namespace Resource
{
    void GameMode::loadTranslation()
    {
        //gameModeName = of::engine::GetModule<of::file::Handler>().getLanguage().getString(gameModeNameStringTranslation);
    }
    of::file::archive::TypeInfo GameMode::getTrait() const
    {
        return { of::file::archive::Trait<Resource::GameMode>::typeId };
    }
}