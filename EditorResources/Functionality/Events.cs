using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EditorResources.Functionality
{
    public static class EditorEvents
    {
        public static EventHandler<NewModCreateEventArgs> onModCreate;
        public static EventHandler<ModLoadEventArgs> onModLoad;
        public static EventHandler<ModFinishedLoadedEventArgs> onModFinishedLoading;


        public static void OnModCreate(NewModCreateEventArgs args)
        {
            onModCreate?.Invoke(null,args);
        }
        public static void OnModLoad(ModLoadEventArgs args)
        {
            onModLoad?.Invoke(null, args);
        }
        public static void OnModFinishedLoading(ModFinishedLoadedEventArgs args)
        {
            onModFinishedLoading?.Invoke(null, args);
        }
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
        public List<Tuple<String, UInt32, String>> zoneFiles = new List<Tuple<string, uint, string>>{ new Tuple<String, UInt32, String> ("test",1,"Test") };
        public List<Message.Message> errorsAndWarnings;
    }
}
