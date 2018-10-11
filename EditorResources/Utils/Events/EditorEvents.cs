using EditorResources.Dto;
using EditorResources.UserControls;
using System;
using System.Collections.Generic;
using static EditorResources.Utils.EnumCollection;

namespace EditorResources.Utils
{
    public static class EditorEvents
    {

        #region eventCalls

        public static void OnLogEvent(EditorLogEventArgs args) => onLogEvent?.Invoke(null, args);
        public static void OnModEvent(ModEventArgs args) => onModEvent?.Invoke(null, args);
        public static void OnObjectEvent(ObjectEventArgs args) => onObjectEvent?.Invoke(null, args);
        public static void OnRequestGameVariableMappingVariable(GameVariableMappingEventArgs args) => onRequestGameVariableMapping?.Invoke(null, args);
        public static void OnDragDropEvent(ObjectEventArgs args) => onDragDropEvent?.Invoke(null, args);
        public static void OnBrushChangedEvent(BrushEventArgs args) => onBrushChangedEvent?.Invoke(null, args);
        public static void OnBrushUsedEvent(BrushUsedEventArgs args) => onBrushUsedEvent?.Invoke(null, args);
        public static void OnObjectSelectedEvent(OnObjectSelectedEventArgs args) => onObjectSelectedEvent?.Invoke(null, args);
        #endregion

        #region eventhandlers
        public static EventHandler<EditorLogEventArgs> onLogEvent;
        public static EventHandler<ModEventArgs> onModEvent;
        public static EventHandler<ObjectEventArgs> onObjectEvent;
        public static EventHandler<GameVariableMappingEventArgs> onRequestGameVariableMapping;
        public static EventHandler<ObjectEventArgs> onDragDropEvent;
        public static EventHandler<BrushEventArgs> onBrushChangedEvent;
        public static EventHandler<BrushUsedEventArgs> onBrushUsedEvent;
        public static EventHandler<OnObjectSelectedEventArgs> onObjectSelectedEvent;
        #endregion

        #region EventHandler<Classes>
        public class EditorLogEventArgs : EventArgs
        {
            public Message logMessage;
        }
        
        public class GameVariableMappingEventArgs : EventArgs
        {
            public enum Variable
            {
                Animation,
                MainMenu,
                StartingZone
            }
            public Variable VariableToRequest { get; set; }
        }

        public class ModEventArgs : EventArgs
        {
            public string ModName { get; set; }
            public EventType Type { get; set; }
            public List<String> Dependencies { get; set; }
            public bool CreateMaster { get; set; }
            public enum EventType
            {
                Loaded,
                Saved,
                Created,
                Selected, 
                ViewInfo,
            }
        }

        public class BrushEventArgs : EventArgs
        {
            public BrushType Brush { get; set; }
            public string Texture { get; set; }
            public string PaintMode { get; set; }
        }
        
        public class BrushUsedEventArgs : EventArgs
        {
            public int X { get; set; }
            public int Y { get; set; }
        }

        public class OnObjectSelectedEventArgs : EventArgs
        {
            public ObjectType SelectedType { get; set; }
            public string ModOrigin { get; set; }
            public uint ID { get; set; }
        }

        public class ObjectEventArgs : EventArgs
        {
            public ObjectEventArgs() { }
            public ObjectEventArgs(ObjectDataViewModel viewModelData)
            {
                Value = viewModelData.Value;
                Flag = viewModelData.Flag;
                Type = viewModelData.Type;
            }

            public BaseDto Value { get; set; }
            public ObjectFlag Flag { get; set; }
            public ObjectType Type { get; set; }
        }
        #endregion

    }
}