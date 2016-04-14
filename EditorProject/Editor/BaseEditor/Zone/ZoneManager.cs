using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ManagedGame;

namespace BaseEditor
{
    public partial class ZoneManager : UserControl
    {
        //Valid mode is "Add" or "Edit", anything else will ignored and set mode to Add
        String myMode;
        public ZoneManager(String mode)
        {
            myMode = mode;
            InitializeComponent();
            if (mode == "Edit")
            {
                button3.Text = "Edit";
                AddZoneStruct ads = Program.mg.getZone();
                textBox1.Text = ads.name;
                numericUpDown1.Value = System.Convert.ToDecimal(ads.ID);
                textBox3.Text = ads.background;
                textBox2.Text = ads.loadingScreen;
                textBox4.Text = ads.loadingScreenMessage;
                textBox5.Text = ads.X.ToString();
                textBox6.Text = ads.Y.ToString();
                numericUpDown1.Enabled = false;
                button2.Enabled = false;
            }
            else
            {
                button2.Enabled = true;
                numericUpDown1.Enabled = true;
                button3.Text = "Add";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if(myMode == "Edit")
            {
                AddZoneStruct addZone = new AddZoneStruct();
                addZone.name = textBox1.Text;
                addZone.ID = numericUpDown1.Value;
                addZone.background = textBox3.Text;
                addZone.loadingScreen = textBox2.Text;
                addZone.loadingScreenMessage = textBox4.Text;
                Double tmp;
                Double.TryParse(textBox5.Text, out tmp);
                addZone.X = tmp;
                Double.TryParse(textBox6.Text, out tmp);
                addZone.Y = tmp;
                Program.mg.editZone(addZone, Program.zoneView.zoneView);
            }
            else
            {
                AddZoneStruct addZone = new AddZoneStruct();
                addZone.name = textBox1.Text;
                addZone.ID = numericUpDown1.Value;
                addZone.background = textBox3.Text;
                addZone.loadingScreen = textBox2.Text;
                addZone.loadingScreenMessage = textBox4.Text;
                Double tmp;
                Double.TryParse(textBox5.Text, out tmp);
                addZone.X = tmp;
                Double.TryParse(textBox6.Text, out tmp);
                addZone.Y = tmp;
                Program.mg.addZone(addZone,Program.zoneView.zoneView);
            }
            //UpdateZoneList and create a new zone.
            (this.Parent as Form).Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            (this.Parent as Form).Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog();
            opf.Filter = "Image File (*.png,*.jpg)|*.png;*.jpg|PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
            opf.Multiselect = false;
            opf.ShowDialog(this);
            if (opf.FileName.EndsWith(".png") || opf.FileName.EndsWith(".jpg"))
            {
                textBox3.Text = opf.SafeFileName;
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog();
            opf.Filter = "Image File (*.png,*.jpg)|*.png;*.jpg|PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
            opf.Multiselect = false;
            opf.ShowDialog(this);
            if (opf.FileName.EndsWith(".png") || opf.FileName.EndsWith(".jpg"))
            {
                textBox2.Text = opf.SafeFileName;
            }
        }
    }
}
