#include <resource/GameMode.hpp>
#include <file/Handler.hpp>

of::common::uuid of::file::archive::Trait<of::resource::GameMode>::typeId = of::common::uuid("655f83d2-bd83-4065-9b47-3109c4e57d5c");

namespace of::resource
{
    void GameMode::loadTranslation()
    {
        //gameModeName = of::engine::GetModule<of::file::Handler>().getLanguage().getString(gameModeNameStringTranslation);
    }
    of::file::archive::TypeInfo GameMode::getTrait() const
    {
        return { of::file::archive::Trait<of::resource::GameMode>::typeId };
    }
}