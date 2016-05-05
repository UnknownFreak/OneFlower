using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;
using ManagedGame;

namespace BaseEditor.Prefab
{
    public partial class Render : UserControl
    {
        public event EventHandler<_RenderComponentStruct> onEdit;
        _RenderComponentStruct rc = new _RenderComponentStruct();
        public Render()
        {
            InitializeComponent();
            animationType.SelectedIndex = 0;
        }

        public void spriterScene_onListChange(object sender, SpriterScene.AddSpriterModel e)
        {
            if (e.Remove)
                SceneFileDropDown.Items.Remove(e.Name);
            else
                SceneFileDropDown.Items.Add(e.Name);
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
                panel2.Enabled = true;
            else
                panel2.Enabled = false;
            rc.isUsed = checkBox1.Checked;
            edit();
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
            if(animationType.SelectedIndex != -1 && rc.rc != null)
                rc.animationType = animationType.SelectedIndex;
            edit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Program.spriterSceneWindow.ShowDialog();
        }

        private void SceneFileDropDown_SelectedIndexChanged(object sender, EventArgs e)
        {
            EntityNameDropDown.Items.Clear();
            EntityNameDropDown.Items.AddRange(Program.mg.getEntityNames(SceneFileDropDown.SelectedItem.ToString()).ToArray());
            textureMap.Items.Clear();
            textureMap.Items.AddRange(Program.mg.getTextureMaps(SceneFileDropDown.SelectedItem.ToString()).ToArray());
            rc.spriterScene = SceneFileDropDown.SelectedItem.ToString();
            edit();
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
                pictureBox2.Load(opf.FileName);
                rc.textureName = textBox3.Text;
            }
            edit();
        }
        private void edit()
        {
            if (onEdit != null)
                onEdit(this, rc);
        }

        private void EntityNameDropDown_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (EntityNameDropDown.SelectedItem != null)
            {
                rc.spriterEntity = EntityNameDropDown.SelectedItem.ToString();
                AnimationDropDown.Items.Clear();
                AnimationDropDown.Items.AddRange(Program.mg.getAnimations(rc.spriterScene,rc.spriterEntity).ToArray());
            }
            else
                rc.spriterEntity = "";
            edit();


        }

        private void textureMap_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (textureMap.SelectedItem != null)
            {
                String[] splitted = textureMap.SelectedItem.ToString().Split(',');
                rc.textureMapMod = splitted[0];
                rc.textureMapName = splitted[1].Remove(0, 1);
            }
            else
            {
                rc.textureMapName = rc.textureMapMod = "";
            }
            edit();
        }
        public void setRenderEdit(_RenderComponentStruct render)
        {
            rc = render;
            textureMap.SelectedItem = rc.textureMapMod + ", " + rc.textureMapName;
            EntityNameDropDown.SelectedItem = rc.spriterEntity;
            textBox3.Text = rc.textureName;
            if(textBox3.Text.EndsWith(".png"))
            pictureBox2.Load(textBox3.Text);
            SceneFileDropDown.SelectedItem = rc.spriterScene;
            animationType.SelectedIndex = rc.animationType;
            checkBox1.Checked = rc.isUsed;
        }

        private void AnimationDropDown_SelectedIndexChanged(object sender, EventArgs e)
        {
            Program.mg.setPrefabAnimation(AnimationDropDown.SelectedItem.ToString());
        }
    }
    public class _RenderComponentStruct
    {
        public ManagedGame.RenderComponentStruct rc { get; set;}
        public Boolean isUsed { get { return System.Convert.ToBoolean(rc.isUsed); } set { rc.isUsed = value; } }
        public String textureName { get { return rc.textureName; } set { rc.textureName = value; } }
        public int animationType { get { return System.Convert.ToInt32(rc.animationType); } set { rc.animationType = value; } }
        public List<SpriteSheetAnimationStruct> animations { get { return rc.animations; } set { rc.animations = value; } }
        public String spriterScene { get { return rc.spriterScene; } set { rc.spriterScene = value; } }
        public String spriterEntity { get { return rc.spriterEntity; } set { rc.spriterEntity = value; } }
        public String textureMapMod { get { return rc.textureMapMod; } set { rc.textureMapMod = value; } }
        public String textureMapName { get { return rc.textureMapName; } set { rc.textureMapName = value; } }
    };
}
