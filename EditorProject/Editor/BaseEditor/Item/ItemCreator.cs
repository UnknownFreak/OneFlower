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
using System.Threading;

namespace BaseEditor
{
    public partial class ItemCreator : UserControl
    {
        public event EventHandler<ItemStruct> onAdd = null;
        Bitmap empty;
        Bitmap tmp;
        Bitmap mySelectedBitmap;
        Bitmap selected;
        Bitmap regularPoint;
        String selectedName = null;
        Tuple<Point, Boolean> selectedPoint;
        Dictionary<String, Tuple<Point,Boolean>> pointsToDraw;
        public ItemCreator()
        {
            InitializeComponent();
            pointsToDraw = new Dictionary<String, Tuple<Point, Boolean>>();
            tmp = new Bitmap(256,256);
            empty = new Bitmap(256, 256);
            selected = new Bitmap("selectedPoint.png");
            regularPoint = new Bitmap("regularPoint.png");
            pictureBox1.Image = tmp;
            attachmentPoints1.onChangedIndex += onSelected;
            attachmentPoints1.onCheckedChange += onCheckedChange;
            attachmentPoints1.onRemoved += onRemovedFromList;
            itemTypeField.SelectedItem = itemTypeField.Items[8];
            rarityField.SelectedIndex = 0;

            onAdd += ItemCreator_onAdd;

            Program.mg.setTooltipPreview(panel4.Handle);
        }

        void ItemCreator_onAdd(object sender, ItemStruct e)
        {
            throw new NotImplementedException();
        }
        private void onSelected(object sender,PointEventArgs args)
        {
            if (selectedName == null && pointsToDraw.ContainsKey(args.Name))
            {
                selectedPoint = pointsToDraw[args.Name];
                selectedPoint = new Tuple<Point, bool>(new Point(selectedPoint.Item1.X, selectedPoint.Item1.Y), true);
                pointsToDraw[args.Name] = selectedPoint;

                selectedName = args.Name;
            }
            else if (selectedName == null)
            {
                //
            }
            else if (pointsToDraw.ContainsKey(selectedName) && pointsToDraw.ContainsKey(args.Name))
            {

                selectedPoint = pointsToDraw[selectedName];
                selectedPoint = new Tuple<Point, bool>(new Point(selectedPoint.Item1.X, selectedPoint.Item1.Y), false);
                pointsToDraw[selectedName] = selectedPoint;
                selectedPoint = pointsToDraw[args.Name];
                selectedPoint = new Tuple<Point, bool>(new Point(selectedPoint.Item1.X, selectedPoint.Item1.Y), true);
                pointsToDraw[args.Name] = selectedPoint;

                selectedName = args.Name;
            }
            else if (pointsToDraw.ContainsKey(selectedName))
            {
                selectedPoint = pointsToDraw[selectedName];
                selectedPoint = new Tuple<Point, bool>(new Point(selectedPoint.Item1.X, selectedPoint.Item1.Y), false);
                pointsToDraw[selectedName] = selectedPoint;

                selectedName = null;
                selectedPoint = null;
            }
            setUpImage();
        }
        private void onRemovedFromList(object sender, PointEventArgs args)
        {
            if (pointsToDraw.ContainsKey(args.Name))
                pointsToDraw.Remove(args.Name);
            if (selectedName.Equals(args.Name))
            {
                selectedName = null;
                selectedPoint = null;
            }
            setUpImage();

        }
        private void onCheckedChange(object sender, PointCheckedEventArgs args)
        {
            if (args.Checked)
                pointsToDraw.Add(args.Name, new Tuple<Point, Boolean>(args.Position, false));
            else
            {
                pointsToDraw.Remove(args.Name);
                if (args.Name.Equals(selectedName))
                {
                    selectedName = null;
                    selectedPoint = null;
                }
            }
            setUpImage();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (selectedName != null)
            {
                selectedPoint = new Tuple<Point, bool>(new Point(e.X, e.Y), true);
                pointsToDraw[selectedName] = selectedPoint;
                attachmentPoints1.updatePoint(selectedName, selectedPoint.Item1);
                setUpImage();
            }
        }
        private void setUpImage()
        {
            using (var canvas = Graphics.FromImage(tmp))
            {
                canvas.Clear(Color.White);
                if(mySelectedBitmap != null)
                    canvas.DrawImage(mySelectedBitmap, new Point(0, 0));
                foreach (var v in pointsToDraw)
                {
                    canvas.DrawString(v.Key, SystemFonts.DefaultFont, SystemBrushes.ControlDark, new Point(v.Value.Item1.X - 8, v.Value.Item1.Y + 10));
                    if (v.Value.Item2 == true)
                        canvas.DrawImage(selected, new Point(v.Value.Item1.X - 8, v.Value.Item1.Y - 8));
                    else
                        canvas.DrawImage(regularPoint, new Point(v.Value.Item1.X - 8, v.Value.Item1.Y - 8));
                }
            }
            pictureBox1.Image = tmp;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog();
            opf.Filter = "Image File (*.png,*.jpg)|*.png;*.jpg|PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
            opf.Multiselect = false;
            opf.ShowDialog(this);
            if (opf.FileName.EndsWith(".png") || opf.FileName.EndsWith(".jpg"))
            {
                textureField.Text = opf.SafeFileName;
                mySelectedBitmap = (Bitmap)Bitmap.FromFile(opf.FileName);
                setUpImage();
            }
        }


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(itemTypeField.SelectedItem == itemTypeField.Items[0])
            {
                subTypeField.Items.Clear();
                subTypeField.Items.Add("Arrow");
                subTypeField.Items.Add("Bolt");
                panel1.Enabled = true;
            }
            else if(itemTypeField.SelectedItem == itemTypeField.Items[1])
            {
                subTypeField.Items.Clear();
                subTypeField.Items.Add("Helm");
                subTypeField.Items.Add("Gloves");
                subTypeField.Items.Add("Chest");
                subTypeField.Items.Add("Leggings");
                subTypeField.Items.Add("Boots");
                panel1.Enabled = true;
            }
            else if (itemTypeField.SelectedItem == itemTypeField.Items[7])
            {
                subTypeField.Items.Clear();
                subTypeField.Items.Add("Bow");
                subTypeField.Items.Add("Crossbow");
                subTypeField.Items.Add("Axe");
                subTypeField.Items.Add("Dagger");
                subTypeField.Items.Add("Fist");
                subTypeField.Items.Add("Mace");
                subTypeField.Items.Add("Polearm");
                subTypeField.Items.Add("Shield");
                subTypeField.Items.Add("Sword");
                subTypeField.Items.Add("Grimiore");
                subTypeField.Items.Add("Staff");
                subTypeField.Items.Add("Stick/ Wand");
                panel1.Enabled = true;
            }
            else
            {
                subTypeField.Items.Clear();
                textureField.Text = "";
                pictureBox1.Image = empty;
                panel1.Enabled = false;
            }
            if (itemTypeField.SelectedItem == itemTypeField.Items[7] || itemTypeField.SelectedItem == itemTypeField.Items[1] || itemTypeField.SelectedItem == itemTypeField.Items[2])
                stackableFeld.Checked = false;
            else
                stackableFeld.Checked = true;

            if (itemTypeField.SelectedItem == itemTypeField.Items[1])
                defenseField.Enabled = true;
            else
                defenseField.Enabled = false;

            if (itemTypeField.SelectedItem == itemTypeField.Items[2])
                BagSlotField.Enabled = true;
            else
                BagSlotField.Enabled = false;

            if (itemTypeField.SelectedItem == itemTypeField.Items[7] || itemTypeField.SelectedItem == itemTypeField.Items[0])
                damageField.Enabled = true;
            else
                damageField.Enabled = false;

            DoTooltip();
        }
        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (subTypeField.SelectedItem != null)
            {
                if (subTypeField.SelectedItem.ToString() == "Sword" || subTypeField.SelectedItem.ToString() == "Axe")
                    twoHandedField.Enabled = true;
                else
                    twoHandedField.Enabled = false;

                if (subTypeField.SelectedItem.ToString() == "Shield" || itemTypeField.SelectedItem == itemTypeField.Items[1])
                    defenseField.Enabled = true;
                else
                    defenseField.Enabled = false;
            }
            DoTooltip();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog();
            opf.Filter = "Image File (*.png,*.jpg)|*.png;*.jpg|PNG (*.png)|*.png|JPG (*.jpg)|*.jpg";
            opf.Multiselect = false;
            opf.ShowDialog(this);
            if (opf.FileName.EndsWith(".png") || opf.FileName.EndsWith(".jpg"))
            {
                inventoryIconField.Text = opf.SafeFileName;
                pictureBox2.LoadAsync(opf.FileName);
            }
        }
        private void DoTooltip()
        {
            ManagedGame.ItemStruct itm = new ManagedGame.ItemStruct();
            itm.name = nameField.Text;
            itm.Description = descriptionField.Text;
            itm.type = itemTypeField.SelectedItem.ToString();
            if (subTypeField.SelectedItem != null)
                itm.secondType = subTypeField.SelectedItem.ToString();
            else
                itm.secondType = "";
            itm.damage = damageField.Value;
            itm.defense = defenseField.Value;
            itm.slots = BagSlotField.Value;
            itm.weight = weightField.Value;
            itm.price = priceField.Value;
            Program.mg.setTooltipText(itm);
        }

        private void _TextChanged(object sender, EventArgs e)
        {
            DoTooltip();
        }

        private void ValueChanged(object sender, EventArgs e)
        {
            DoTooltip();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            DoTooltip();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            ItemStruct itm = new ItemStruct();
            itm.name = nameField.Text;
            itm.Description = descriptionField.Text;
            itm.type = itemTypeField.SelectedItem.ToString();
            if (subTypeField.SelectedItem != null)
                itm.secondType = subTypeField.SelectedItem.ToString();
            else
                itm.secondType = "";
            itm.damage = damageField.Value;
            itm.defense = defenseField.Value;
            itm.slots = BagSlotField.Value;
            itm.weight = weightField.Value;
            itm.price = priceField.Value;
            itm.rarity = rarityField.SelectedIndex;
            itm.TextureName = textureField.Text;
            itm.IconName = inventoryIconField.Text;
            itm.attachPoints = new Dictionary<string,Point>();
            foreach (var v in pointsToDraw)
            {
                itm.attachPoints.Add(v.Key, v.Value.Item1);
            }
            
        }
        private void add(ItemStruct item)
        {
            if (onAdd != null)
                onAdd(this, item);
        }
    }
}
