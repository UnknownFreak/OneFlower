using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EditorResources.Functionality
{
    public static class RequestEvents
    {

        public static EventHandler<GameVariableMappingEventArgs> onRequestGameVariableMapping;

        public static void OnRequestGameVariableMappingVariable(GameVariableMappingEventArgs args)
        {
            onRequestGameVariableMapping?.Invoke(null, args);
        }
    }

    public class GameVariableMappingEventArgs : EventArgs
    {
        public enum Variable
        {
            Animation,
            MainMenu,
            StartingZone,
        }
        public Variable VariableToRequest{ get; set; }
    }
}
