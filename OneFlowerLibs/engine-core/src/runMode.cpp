#include <engine/runMode.hpp>

#include <module/logger/OneLogger.hpp>

namespace of::engine
{
    static RunMode mode = RunMode::NORMAL;
    static bool locked = false;

    RunMode of::engine::getRunMode()
    {
        return mode;
    }

    void setRunMode(const RunMode& runMode)
    {
        if (locked == false)
        {
            mode = runMode;
        }
        else
        {
            of::engine::GetModule<of::module::logger::OneLogger>().Warning("Trying to set run mode after it has been locked!");
        }
    }

    void lockRunMode()
    {
        locked = true;
    }
}