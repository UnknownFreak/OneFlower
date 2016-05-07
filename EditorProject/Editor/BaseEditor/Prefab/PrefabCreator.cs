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
using BaseEditor.Prefab;

namespace BaseEditor
{
    public partial class PrefabCreator : UserControl
    {
        ManagedGame.PrefabStruct prefab;
        public PrefabCreator()
        {
            prefab = new ManagedGame.PrefabStruct();
            prefab.hitbox = new Hitbox_RigidComponentStruct();
            prefab.rc = new ManagedGame.RenderComponentStruct();
            InitializeComponent();
            renderPanel.setRenderEdit(new _RenderComponentStruct() { rc = new ManagedGame.RenderComponentStruct() });
            Program.mg.setPrefabPreview(previewPanel.Handle);
            renderPanel.onEdit += renderPanel_onEdit;
            panelRigid.Enabled = false;
            rigidProperties.Enabled = false;
        }

        void renderPanel_onEdit(object sender, _RenderComponentStruct e)
        {
            prefab.rc = e.rc;
            Program.mg.previewPrefab(prefab);
        }
        void renderPanel_onEditHitbox_Rigid()
        {
            Program.mg.previewPrefab(prefab);
        }
        private void useHitbox_CheckedChanged(object sender, EventArgs e)
        {
            if (useRigid.Checked && useHitbox.Checked)
                useRigid.Checked = false;
            panelRigid.Enabled = useHitbox.Checked || useRigid.Checked;
            rigidProperties.Enabled = useRigid.Checked;
            prefab.hitbox.isUsed = useHitbox.Checked || useRigid.Checked;
            prefab.hitbox.isHitbox = useHitbox.Checked;
            renderPanel_onEditHitbox_Rigid();
        }

        private void useRigid_CheckedChanged(object sender, EventArgs e)
        {
            if (useHitbox.Checked && useRigid.Checked)
                useHitbox.Checked = false;
            panelRigid.Enabled = useHitbox.Checked || useRigid.Checked;
            rigidProperties.Enabled = useRigid.Checked;
            prefab.hitbox.isUsed = useHitbox.Checked || useRigid.Checked;
            prefab.hitbox.isHitbox = useHitbox.Checked;
            renderPanel_onEditHitbox_Rigid();
        }

        private void positionX_ValueChanged(object sender, EventArgs e)
        {
            prefab.hitbox.posX = (int)positionX.Value;
            renderPanel_onEditHitbox_Rigid();
        }

        private void positionY_ValueChanged(object sender, EventArgs e)
        {
            prefab.hitbox.posY = (int)positionY.Value;
            renderPanel_onEditHitbox_Rigid();
        }

        private void sizeX_ValueChanged(object sender, EventArgs e)
        {
            prefab.hitbox.sizeX = (int)sizeX.Value;
            renderPanel_onEditHitbox_Rigid();
        }

        private void sizeY_ValueChanged(object sender, EventArgs e)
        {
            prefab.hitbox.sizeY= (int)sizeY.Value;
            renderPanel_onEditHitbox_Rigid();
        }

        private void mass_ValueChanged(object sender, EventArgs e)
        {
            prefab.hitbox.mass = (int)mass.Value;
            renderPanel_onEditHitbox_Rigid();
        }

        private void material_SelectedIndexChanged(object sender, EventArgs e)
        {
            prefab.hitbox.Material = material.SelectedIndex;
            renderPanel_onEditHitbox_Rigid();
        }
    }
}
