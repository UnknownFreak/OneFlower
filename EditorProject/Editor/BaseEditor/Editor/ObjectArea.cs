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
    public partial class ObjectArea : UserControl
    {
        public ObjectArea()
        {
            InitializeComponent();
            backgroundWorker1.WorkerSupportsCancellation = true;
            Program.questCreatorField.addQuest += questCreatorField_addQuest;
            Program.creatorField.onAdd += creatorField_onAdd;
        }

        void creatorField_onAdd(object sender, ManagedGame.ItemStruct e)
        {
            if (treeView1.SelectedNode.FullPath.Contains("Items"))
            {
                ListViewItem itm = Program.mg.addItem(e.name, e.ID);
                if (itm != null)
                    listView1.Items.Add(itm);
            }
        }

        void questCreatorField_addQuest(object sender, AddQuestEvent e)
        {
            if(treeView1.SelectedNode.FullPath.Contains("Quests"))
            {
                ListViewItem itm = Program.mg.addQuest(e.Name, e.ID);
                if (itm != null)
                    listView1.Items.Add(itm);
            }
        }
        public void init()
        {
            BaseEditor.Program.mg.setUpList(treeView1);
            BaseEditor.Program.mg.setUpDetailedList(treeView1.SelectedNode.Text, treeView1.SelectedNode.FullPath, listView1);
        }
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            BaseEditor.Program.mg.setUpDetailedList(e.Node.Text, e.Node.FullPath, listView1);
        }

        private void addToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(Program.mg.isModLoaded())
            { 
                Program.prefabCreator.Text = "Add Prefab";
                Program.prefabCreator.Visible = true;
            }
        }

        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(Program.mg.isModLoaded())
            {
                Program.messages.addInfoMessage("<EDIT> This component is not added yet");
            }
        }

        private void duplicateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Program.mg.isModLoaded())
            {
                Program.messages.addInfoMessage("<DUPLICATE> This component is not added yet");
            }
        }

        private void removeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Program.mg.isModLoaded())
            {
                if(listView1.SelectedItems.Count != 0)
                {
                    var v = listView1.SelectedItems[0];
                    if (v.SubItems[4].Text == "Quest")
                    {
                        int _return = Program.mg.removeQuest(v.SubItems[3].Text, System.Convert.ToUInt32(v.SubItems[1].Text));
                        if (1 == _return)
                            v.SubItems[5].Text = "D";
                        else if (2 == _return)
                            v.SubItems[5].Text = "E";
                    }
                    else if (v.SubItems[4].Text == "Item")
                    {
                        int _return = Program.mg.removeItem(v.SubItems[3].Text, System.Convert.ToUInt32(v.SubItems[1].Text));
                        if (1 == _return)
                            v.SubItems[5].Text = "D";
                        else if (2 == _return)
                            v.SubItems[5].Text = "E";
                    }
                }
            }
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (Program.mg.isModLoaded())
            {
                Program.itemCreator.Text = "Add Item";
                Program.itemCreator.Visible = true;
            }
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (Program.mg.isModLoaded())
            {
                Program.questCreator.Text = "Add Quest";
                Program.questCreator.Visible = true;
            }
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            if (Program.mg.isModLoaded())
            {
                Program.messages.addInfoMessage("<MUSIC> This component is not added yet");
            }
        }

        private void listView1_DragLeave(object sender, EventArgs e)
        {

        }
        private void listView1_ItemDrag(object sender, ItemDragEventArgs e)
        {
            if((e.Item as ListViewItem).SubItems[4].Text == "Prefab"
                ||
                (e.Item as ListViewItem).SubItems[4].Text == "Item")
                if(backgroundWorker1.IsBusy != true)
                backgroundWorker1.RunWorkerAsync(e);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            bool moving = true;
            if (e.Argument.GetType() != typeof(ItemDragEventArgs))
            {
                e.Cancel = true;
                moving = false;
            }
            while(moving)
            {
                bool inside = false;
                this.Invoke((MethodInvoker)(() =>
                {
                    Rectangle r = Program.renderWindow.addOnPanel.RectangleToScreen(Program.renderWindow.addOnPanel.ClientRectangle);
                    Point Mpos = MousePosition;
                    inside = r.Contains(Mpos);
                    if (inside)
                    {
                        Program.main.Cursor = Cursors.Default;
                    }
                    else
                        Program.main.Cursor = Cursors.No;
                }));
                if (MouseButtons != MouseButtons.Left)
                {
                    moving = false;
                    if (inside)
                    {
                        this.Invoke((MethodInvoker)(() =>
                        {
                            Program.main.Cursor = Cursors.Default;
                        }));
                        break;
                    }
                    else
                    {
                        e.Cancel = true;
                    }
                }
            }
            this.Invoke((MethodInvoker)(() =>
            {
                Program.main.Cursor = Cursors.Default;
            }));
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if ((e.Cancelled == true))
            {
            }

            else if (!(e.Error == null))
            {
            }
            else
            {
                Program.mg.addObjectToGame(listView1.SelectedItems[0],Program.zoneView.listView2);
            }
        }
        private void contextMenuStrip1_Opened(object sender, EventArgs e)
        {
            Rectangle r = treeView1.RectangleToScreen(treeView1.ClientRectangle);
            Point Mpos = MousePosition;
            bool inside = r.Contains(Mpos);
            if (inside)
            {
                editToolStripMenuItem.Enabled = false;
                duplicateToolStripMenuItem.Enabled = false;
                removeToolStripMenuItem.Enabled = false;
            }
            else
            {
                editToolStripMenuItem.Enabled = true;
                duplicateToolStripMenuItem.Enabled = true;
                removeToolStripMenuItem.Enabled = true;
            }
            if (listView1.SelectedItems.Count != 0)
                if (listView1.SelectedItems[0].SubItems[5].Text == "R")
                    removeToolStripMenuItem.Text = "Undo Remove";
                else
                    removeToolStripMenuItem.Text = "Remove";
            else
                removeToolStripMenuItem.Text = "Remove";

        }
    }
}
