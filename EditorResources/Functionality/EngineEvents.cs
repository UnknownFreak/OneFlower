using EditorResources.Utils;
using System;

namespace EditorResources.Functionality
{
    public static class EngineEvents
    {

        public static EventHandler<VariableMappingEventArgs> engineOnSendVariableMapping;

        public static EventHandler<DependencyListEventArgs> onDependencyListEvent;

        public static EventHandler onModFinishedLoadingEvent;

        public static void OnDependencyListEvent(DependencyListEventArgs args) => onDependencyListEvent?.Invoke(null, args);

        public static void EngineOnSendVariableMapping(VariableMappingEventArgs args) => engineOnSendVariableMapping?.Invoke(null, args);

        public static void OnModFinishedLoadingEvent() => onModFinishedLoadingEvent?.Invoke(null, EventArgs.Empty);


        public class VariableMappingEventArgs : EventArgs
        {
        }

        public class AnimationVariableMappingEventArgs : VariableMappingEventArgs
        {
            public string AnimationVariable { get; set; }
        }

        public class DependencyListEventArgs : EventArgs
        {
            public ModDependencyList Dependencies { get; set; } = new ModDependencyList();
        }
    }
}
