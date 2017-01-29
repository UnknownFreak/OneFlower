using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
                if (value == MsgType.Info)
                    brush = Brushes.Gray;
                else if (value == MsgType.Warning)
                {
                    brush = Brushes.Goldenrod;
                }
                else
                    brush = Brushes.DarkRed;
            }
        }
        public Brush brush {get; set;}

        public enum MsgType
        {
            Info,
            Warning,
            Error
        }
    }
}
