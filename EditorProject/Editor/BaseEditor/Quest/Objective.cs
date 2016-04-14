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

namespace BaseEditor.Quest
{
    
    public partial class ObjectiveField : UserControl
    {
        String mode;
        public event EventHandler<AddObjectiveEventArgs> onAdd = null;
        private Objective myObjective;
        public ObjectiveField(Form window,String mode)
        {
            myObjective = new Objective() { Count = 1 , IsBonusObjective = false};
            this.mode = mode;
            InitializeComponent();
            window.AcceptButton = button4;
            window.CancelButton = button3;
            types.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (types.SelectedItem.ToString() == "Escort")
            {
                repeatCount.Enabled = false;
                button2.Enabled = true;
                button1.Enabled = true;
                button5.Enabled = true;
                button6.Enabled = true;
                button7.Enabled = true;

            }
            else if (types.SelectedItem.ToString() == "Explore")
            {
                repeatCount.Enabled = false;
                button1.Enabled = false;
                button2.Enabled = true;
                button5.Enabled = true;
                button6.Enabled = true;
                button7.Enabled = true;
            }
            else
            {
                repeatCount.Enabled = true;
                button2.Enabled = false;
                button1.Enabled = true;
                button5.Enabled = false;
                button6.Enabled = false;
                button7.Enabled = false;
            }
            myObjective.Type = types.SelectedItem.ToString();
            myObjective.TypeIndex = types.SelectedIndex; 
        }
        private void button4_Click(object sender, EventArgs e)
        {
            AddObjectiveEventArgs obj = new AddObjectiveEventArgs();
            obj.Objective = myObjective;
            onClick(obj);
            (Parent as Form).Close();
        }
        private void onClick(AddObjectiveEventArgs e)
        {
            if (onAdd != null)
            {
                onAdd(this, e);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            (Parent as Form).Close();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            myObjective.Count = (UInt32)repeatCount.Value;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            myObjective.Name = nameBox.Text;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            myObjective.IsBonusObjective = bonusObjective.Checked;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Selector s = null;
            if(types.SelectedItem.ToString() == "Escort")
            {
                s = new Selector("Prefabs");
            }
            else if(types.SelectedItem.ToString() == "Explore")
            {
                s = new Selector("Zone");
            }
            else if(types.SelectedItem.ToString() == "Kill")
            {
                s = new Selector("Prefabs");
            }
            else if (types.SelectedItem.ToString() == "Fetch")
            {
                s = new Selector("Items");
            }
            s.onSelectEvent += s_onSelectEvent;
            s.ShowDialog();
        }

        void s_onSelectEvent(object sender, SelectedItemEvent e)
        {
            if(e.item != null)
            {
                String name = e.item.SubItems[3].Text;
                uint id = Convert.ToUInt32(e.item.SubItems[1].Text);
                myObjective.Target = new Tuple<string, uint>(name,id);
                targetBox.Text = "("+name+","+id+")";
            }
        }
        private void s_onSelectEventB2(object sender, SelectedItemEvent e)
        {
            if (e.item != null)
            {
                String name = e.item.SubItems[3].Text;
                uint id = Convert.ToUInt32(e.item.SubItems[1].Text);
                myObjective.DestinationZone = new Tuple<string, uint>(name, id);
                destinationBox.Text = "(" + name + "," + id + ")";
            }
        }
        private void s_onSelectEventB3(object sender, SelectedItemEvent e)
        {
            if (e.item != null)
            {
                String name = e.item.SubItems[3].Text;
                uint id = Convert.ToUInt32(e.item.SubItems[1].Text);
                myObjective.TargetDestination = new Tuple<string, uint>(name, id);
                targetDestinationBox.Text = "(" + name + "," + id + ")";
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            Selector s = new Selector("Zone");
            s.onSelectEvent += s_onSelectEventB2;
            s.ShowDialog();
        }
        private void button5_Click(object sender, EventArgs e)
        {
            Selector s = new Selector("ZoneObj");
            s.onSelectEvent += s_onSelectEventB3;
            s.ShowDialog();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            //TODO
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //TODO
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            myObjective.Description = descriptionBox.Text;
        }
        public void setEditObjective(Objective edit)
        {
            button4.Text = "Edit";
            nameBox.Text = edit.Name;
            descriptionBox.Text = edit.Description;
            if(edit.Target != null)
                targetBox.Text = "(" + edit.Target.Item1 + "," + edit.Target.Item2 + ")";
            if (edit.DestinationZone != null)
                destinationBox.Text = "(" + edit.DestinationZone.Item1 + "," + edit.DestinationZone.Item2 + ")";
            if (edit.DestinationZone != null)
                targetDestinationBox.Text = "(" + edit.TargetDestination.Item1 + "," + edit.TargetDestination.Item2 + ")";
            bonusObjective.Checked = (Boolean)edit.IsBonusObjective;
            repeatCount.Value = (UInt32)edit.Count;
            types.SelectedIndex = (int)edit.TypeIndex;
        }
    }
    public class AddObjectiveEventArgs : EventArgs
    {
        public Objective Objective { get; set; }
    }
    /*public class Objective
    {
        public String Type { get; set; }
        public int TypeIndex { get; set; }
        public String Name { get; set; }
        public String Description { get; set; }
        public Tuple<String, UInt32> Target { get; set; }
        public Tuple<String, UInt32> DestinationZone { get; set; }
        public Tuple<String, UInt32> TargetDestination { get; set; }
        public UInt32 Count { get; set; }
        public Boolean IsBonusObjective { get; set; }
    }*/
}
