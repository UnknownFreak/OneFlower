using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EditorResources.Functionality
{
    public static class RequestEvents
    {
        #region log
        public static EventHandler<EditorLogEventArgs> onLogEvent;

        public static void OnLogEvent(EditorLogEventArgs args)
        {
            onLogEvent?.Invoke(null, args);
        }
        #endregion

        public static EventHandler<GameVariableMappingEventArgs> onRequestGameVariableMapping;

        public static void OnRequestGameVariableMappingVariable(GameVariableMappingEventArgs args)
        {
            onRequestGameVariableMapping?.Invoke(null, args);
        }

        #region EventClasses
        public class GameVariableMappingEventArgs : EventArgs
        {
            public enum Variable
            {
                Animation,
                MainMenu,
                StartingZone,
            }
            public Variable VariableToRequest { get; set; }
        }

        public class EditorLogEventArgs : EventArgs
        {
            public Message.Message logMessage;
        }
        #endregion
    }
}
