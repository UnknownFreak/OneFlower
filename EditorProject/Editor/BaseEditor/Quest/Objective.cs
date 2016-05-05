using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace BaseEditor.Quest
{
    public partial class ObjectiveField : UserControl
    {
        public event EventHandler<OnModifyObjectiveEventArgs> onModify = null;
        private _Objective myObjective;
        public ObjectiveField()
        {
            InitializeComponent();
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
            if (myObjective != null)
            {
                myObjective.Type = types.SelectedItem.ToString();
                myObjective.TypeIndex = types.SelectedIndex;
                onModify(this, new OnModifyObjectiveEventArgs() { Text = myObjective.Type, index = 1 });
            }
        }
        private void onClick(OnModifyObjectiveEventArgs e)
        {
            if (onModify != null)
            {
                onModify(this, e);
            }
        }
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if(myObjective != null)
                myObjective.Count = (UInt32)repeatCount.Value;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (myObjective != null)
            {
                myObjective.Name = nameBox.Text;
                onModify(this, new OnModifyObjectiveEventArgs() { Text = myObjective.Name, index = 0 });
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (myObjective != null)
            {
                myObjective.IsBonusObjective = bonusObjective.Checked;
                onModify(this, new OnModifyObjectiveEventArgs() { Text = myObjective.IsBonusObjective.ToString(), index = 2 });
            }
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
                if (myObjective != null)
                    myObjective.Target = new Tuple<string, uint>(name, id);
                targetBox.Text = "("+name+","+id+")";
            }
        }
        private void s_onSelectEventB2(object sender, SelectedItemEvent e)
        {
            if (e.item != null)
            {
                String name = e.item.SubItems[3].Text;
                uint id = Convert.ToUInt32(e.item.SubItems[1].Text);
                if (myObjective != null)
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
                if (myObjective != null)
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
            if (myObjective != null)
                myObjective.Description = descriptionBox.Text;
        }
        public void setEditObjective(_Objective edit)
        {
            myObjective = edit;
            nameBox.Text = edit.Name;
            descriptionBox.Text = edit.Description;
            if (edit.Target != null)
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
    public class OnModifyObjectiveEventArgs : EventArgs
    {
        public String Text { get; set; }
        public int index { get; set; }
    }
    public class _Objective
    {
        public ManagedGame.Objective obj { get; set; }
        public String Type { get { return this.obj.Type; } set { this.obj.Type = value; } }
        public int TypeIndex { get { return System.Convert.ToInt32(this.obj.TypeIndex); } set { this.obj.TypeIndex = value; } }
        public String Name { get { return this.obj.Name; } set { this.obj.Name = value; } }
        public String Description { get{ return this.obj.Description;} set{this.obj.Description = value;} }
        public Tuple<String, UInt32> Target { get { return this.obj.Target; } set { this.obj.Target = value; } }
        public Tuple<String, UInt32> DestinationZone { get { return this.obj.DestinationZone; } set { this.obj.DestinationZone = value; } }
        public Tuple<String, UInt32> TargetDestination { get { return this.obj.TargetDestination; } set { this.obj.TargetDestination = value; } }
        public UInt32 Count { get { return System.Convert.ToUInt32(this.obj.Count); } set { this.obj.Count = value; } }
        public Boolean IsBonusObjective { get { return System.Convert.ToBoolean(this.obj.IsBonusObjective); } set { this.obj.IsBonusObjective = value; } }
    }
}
