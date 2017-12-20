using System;
using System.Windows.Media;

namespace EditorResources.Message
{
    public class Message
    {
        private MsgType m_type;
        public String message { get; set; }
        public MsgType type {
            get { return m_type; }
            set {
                m_type = value;
                switch (m_type)
                {
                    case MsgType.Info:
                        brush = Brushes.Gray;
                        break;
                    case MsgType.Debug:
                        brush = Brushes.Khaki;
                        break;
                    case MsgType.Fine:
                        brush = Brushes.DarkGreen;
                        break;
                    case MsgType.Warning:
                       brush = Brushes.Goldenrod;
                        break;
                    case MsgType.Error:
                        brush = new BrushConverter().ConvertFromString("#ad0000") as Brush;
                        break;
                    case MsgType.Critical:
                        brush = new BrushConverter().ConvertFromString("#990000") as Brush;
                        break;
                }
            }
        }
        public Brush brush {get; set;}

        public enum MsgType
        {
            None,
            Debug,
            Info,
            Fine,
            Warning,
            Error,
            Critical
        }

    }
}
