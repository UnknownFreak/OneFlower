using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor.Prefab
{
    public partial class Render : UserControl
    {
        public Render()
        {
            InitializeComponent();
            animationType.SelectedIndex = 0;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
                panel2.Enabled = true;
            else
                panel2.Enabled = false;
        }

        private void animationType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(animationType.SelectedItem.ToString() == "Static")
            {
                spriteSheet.Enabled = false;
                armatureAnimation.Enabled = false;
            }
            else if (animationType.SelectedItem.ToString() == "SpriteSheet")
            {
                spriteSheet.Enabled = true;
                armatureAnimation.Enabled = false;
            }
            else
            {
                spriteSheet.Enabled = false;
                armatureAnimation.Enabled = true;
            }
        }
    }
}
