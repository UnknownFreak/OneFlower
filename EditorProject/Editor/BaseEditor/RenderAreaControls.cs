using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor
{
    public partial class RenderAreaControls : Component
    {
        public RenderAreaControls()
        {
            InitializeComponent();
            toolStripMenuItem2.Click += renderMenuStrip_ItemClicked;
        }
        private void renderMenuStrip_ItemClicked(object sender, EventArgs e)
        {
            Program.mg.showHideHitboxes();
        }
        public RenderAreaControls(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
        }
    }
}
