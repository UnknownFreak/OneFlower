using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor
{
    public partial class AddAttachmentPoint : Form
    {
        public event EventHandler<AttachmentPointsEventArgs> onAdd = null;
        public AddAttachmentPoint(bool TextureMap = false)
        {
            InitializeComponent();
            if(TextureMap)
            {
                Text = "Add Texture Map";
                buttonAdd.Text = "Add Map";
            }
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            AttachmentPointsEventArgs args = new AttachmentPointsEventArgs();
            args.Name = textBox1.Text;
            onClick(args);
            this.Close();
        }
        private void onClick(AttachmentPointsEventArgs e)
        {
            if(onAdd != null)
            {
                onAdd(this, e);
            }
        }
    }
    public class AttachmentPointsEventArgs : EventArgs
    {
        public String Name { get; set; }
    }
}
