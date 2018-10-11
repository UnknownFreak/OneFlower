using System;
using System.Collections.Generic;

namespace EditorResources.Functionality
{
    public static class EditorEvents_old
    {
        #region TextureMap

        public static EventHandler<OnTextureMapLoadedFromFileEventArgs> onTextureMapLoadedFromFile;

        public static void OnTextureMapLoadedFromFileEvent(OnTextureMapLoadedFromFileEventArgs args)
        {
            onTextureMapLoadedFromFile?.Invoke(null, args);
        }

        #endregion

    }

    #region EventArgs

    public class OnTextureMapLoadedFromFileEventArgs : EventArgs
    {
        public class Point
        {
            public int X { get; set; } = 0;
            public int Y { get; set; } = 0;
            public int H { get; set; } = 0;
            public int W { get; set; } = 0;
            public bool Rotated { get; set; } = false;
            public short R { get; set; } = 255;
            public short G { get; set; } = 255;
            public short B { get; set; } = 255;
        }
        public Dictionary<string, Point> MapPoints { get; set; }
    }

    #endregion
}
