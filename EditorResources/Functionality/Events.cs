using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EditorResources.Functionality
{
    public static class EditorEvents
    {
        #region ModLoadSave
        public static EventHandler<NewModCreateEventArgs> onModCreate;
        public static EventHandler<ModFileSelectedEventArgs> onModSelected;
        public static EventHandler<ModLoadEventArgs> onModLoad;
        public static EventHandler<ModFinishedLoadedEventArgs> onModFinishedLoading;

        public static EventHandler<EngineOnModSelectedLoadedEventArgs> engineOnModSelectedLoaded;


        public static void OnModCreate(NewModCreateEventArgs args)
        {
            onModCreate?.Invoke(null,args);
        }

        public static void OnModSelected(ModFileSelectedEventArgs args)
        {
            onModSelected?.Invoke(null, args);
        }

        public static void OnModLoad(ModLoadEventArgs args)
        {
            onModLoad?.Invoke(null, args);
        }

        public static void OnModFinishedLoading(ModFinishedLoadedEventArgs args)
        {
            onModFinishedLoading?.Invoke(null, args);
        }

        public static void EngineOnModSelectedLoaded(EngineOnModSelectedLoadedEventArgs args)
        {
            engineOnModSelectedLoaded?.Invoke(null, args);
        }

        #endregion

        public static EventHandler<EditorLogEventArgs> onLogEvent;

        public static void OnLogEvent(EditorLogEventArgs args)
        {
            onLogEvent?.Invoke(null, args);
        }
    }

    public class EngineOnModSelectedLoadedEventArgs : EventArgs
    {
        public ModWindow.ModDependencyList Dependencies;
    }

    public class ModFileSelectedEventArgs : EventArgs
    {
        public String fileName;
    }

    public class EditorLogEventArgs : EventArgs
    {
        public Message.Message logMessage;
    }

    public class ModLoadEventArgs : EventArgs
    {
        public String modName;
    }

    public class NewModCreateEventArgs : EventArgs
    {
        public String modName;
        public List<String> dependencies;
        public bool? createMaster;
    }

    public class ModFinishedLoadedEventArgs : EventArgs
    {
        public List<Tuple<String, UInt32, String>> zoneFiles = new List<Tuple<string, uint, string>>();
        public List<Message.Message> errorsAndWarnings = new List<Message.Message>();
    }
}
