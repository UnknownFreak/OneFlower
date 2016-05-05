using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor
{
    public partial class AttachmentPoints : UserControl
    {
        private Dictionary<String, Point> points;
        public event EventHandler<PointEventArgs> onChangedIndex = null;
        public event EventHandler<PointEventArgs> onRemoved = null;
        public event EventHandler<PointCheckedEventArgs> onCheckedChange = null;

        public AttachmentPoints()
        {
            InitializeComponent();
            points = new Dictionary<string,Point>();
        }
        private void addToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddAttachmentPoint pts = new AddAttachmentPoint();
            pts.onAdd += addPoint;
            pts.ShowDialog();
        }
        private void removeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count != 0)
            {
                PointEventArgs args = new PointEventArgs();
                Point p;
                points.TryGetValue(listView1.SelectedItems[0].Text, out p);
                if (p != null)
                {
                    args.Name = listView1.SelectedItems[0].Text;
                    args.Position = p;
                    onRemove(args);
                }
                points.Remove(listView1.SelectedItems[0].Text);
                listView1.Items.Remove(listView1.SelectedItems[0]);

            }
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            PointEventArgs args = new PointEventArgs();
            Point p;
            if (listView1.SelectedItems.Count != 0)
            {
                String n = listView1.SelectedItems[0].Text;
                points.TryGetValue(n, out p);
                if (p != null)
                {
                    args.Name = n;
                    args.Position = p;
                    onChange(args);
                }
            }
        }
        private void onRemove(PointEventArgs args)
        {
            if (onRemoved != null)
                onRemoved(this, args);
        }
        private void onChange(PointEventArgs args)
        {
            if (onChangedIndex != null)
                onChangedIndex(this, args);
        }
        private void listView1_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            PointCheckedEventArgs args = new PointCheckedEventArgs();
            Point p;
            String n = e.Item.Text;
            points.TryGetValue(n, out p);
            if (p != null)
            {
                args.Name = n;
                args.Position = p;
                args.Checked = e.Item.Checked;
                onChecked(args);
            }
        }
        private void onChecked(PointCheckedEventArgs args)
        {
            if (onCheckedChange != null)
                onCheckedChange(this, args);
        }
        public void updatePoint(String name, Point p)
        {
            if (listView1.SelectedItems.Count != 0)
                if(listView1.SelectedItems[0].Name.Equals(name))
                {
                    listView1.SelectedItems[0].SubItems[1].Text = "(" + p.X + "," + p.Y + ")";
                    points[name] = p;
                }
        }
        private void addPoint(object sender, AttachmentPointsEventArgs e)
        {
            ListViewItem item = new ListViewItem(e.Name,e.Name);
            item.Name = e.Name;
            if(listView1.Items.ContainsKey(e.Name))
            {
                MessageBox.Show(this,"Point already exists!", "Err",MessageBoxButtons.OK,MessageBoxIcon.Error);
                return;
            }
            else if(e.Name.Equals(""))
            {
                MessageBox.Show(this, "Name not allowed!", "Err", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            item.SubItems.Add("(" + Point.Empty.X + "," + Point.Empty.Y + ")");
            listView1.Items.Add(item);
            points.Add(e.Name, Point.Empty);
        }
        public Dictionary<String,Point> getPoints()
        {
            return points;
        }
    }
    public class PointEventArgs : EventArgs
    {
        public String Name { get; set; }
        public Point Position { get; set; }
    }
    public class PointCheckedEventArgs : EventArgs
    {
        public String Name { get; set; }
        public Point Position { get; set; }
        public bool Checked { get; set; }
    }
}
