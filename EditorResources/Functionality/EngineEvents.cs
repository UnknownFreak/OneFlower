using System;

namespace EditorResources.Functionality
{
    public static class EngineEvents
    {

        public static EventHandler<VariableMappingEventArgs> engineOnSendVariableMapping;

        public static void EngineOnSendVariableMapping(VariableMappingEventArgs args)
        {
            engineOnSendVariableMapping?.Invoke(null, args);
        }

        public class VariableMappingEventArgs : EventArgs
        {
        }

        public class AnimationVariableMappingEventArgs : VariableMappingEventArgs
        {
            public string AnimationVariable { get; set; }
        }
    }
}
