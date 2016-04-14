using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace BaseEditor
{
    public partial class DragNDropWindow : Form
    {

        private const int WM_NCLBUTTONDOWN = 0xA1;
        private const int HT_CAPTION = 0x2;
        private const int SC_SIZE = 0xF000;
        private const int WM_SYSCOMMAND = 0x0112;

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        public DragNDropWindow()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
        }

        private void toolStripDropDownButton1_Click(object sender, EventArgs e)
        {
            Hide();
        }
        public void setWindowName(String str)
        {
            windowName.Text = str;
        }
        public void addComponent(Component component)
        {
            if (component == null)
            {
                addOnPanel.Controls.Add(new AttachmentPoints());
                return;
            }
            if (component.GetType() == typeof(RenderAreaControls))
            {
                RenderAreaControls draw = component as RenderAreaControls;
                addOnPanel.Controls.Add(draw.renderPanel);
                draw.renderPanel.Dock = DockStyle.Fill;
                menuStrip1.Items.Clear();
                menuStrip1.Items.AddRange(draw.renderMenuStrip.Items);
            }
        }

        private void DragNDropWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason != CloseReason.UserClosing)
                return;
            e.Cancel = true;
            Hide();
        }
    }
}
