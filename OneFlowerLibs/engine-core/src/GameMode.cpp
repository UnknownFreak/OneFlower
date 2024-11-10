#include <resource/GameMode.hpp>


of::common::uuid of::asset::Trait<of::resource::GameMode>::typeId = of::common::uuid("655f83d2-bd83-4065-9b47-3109c4e57d5c");

namespace of::resource
{
    void GameMode::loadTranslation()
    {
        //gameModeName = of::engine::GetModule<of::file::Handler>().getLanguage().getString(gameModeNameStringTranslation);
    }
    of::asset::TypeInfo GameMode::getTrait() const
    {
        return { of::asset::Trait<of::resource::GameMode>::typeId };
    }
}