#include "GameMode.hpp"
#include <File/Asset/Manager.hpp>

of::common::uuid Interfaces::Trait<Resource::GameMode>::typeId = of::common::uuid("655f83d2-bd83-4065-9b47-3109c4e57d5c");

namespace Resource
{
    void GameMode::loadTranslation()
    {
        gameModeName = Engine::GetModule<File::Asset::Manager>().getLanguage().getString(gameModeNameStringTranslation);
    }
    Interfaces::TypeInfo GameMode::getTrait() const
    {
        return { Interfaces::Trait<Resource::GameMode>::typeId };
    }
}