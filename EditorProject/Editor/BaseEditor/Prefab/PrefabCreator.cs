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
    public partial class PrefabCreator : UserControl
    {
        ManagedGame.PrefabStruct prefab;
        public PrefabCreator()
        {
            prefab = new ManagedGame.PrefabStruct();
            InitializeComponent();
            renderPanel.setRenderEdit(new Prefab._RenderComponentStruct() { rc = new ManagedGame.RenderComponentStruct() });
            Program.mg.setPrefabPreview(previewPanel.Handle);
            renderPanel.onEdit += renderPanel_onEdit;
        }

        void renderPanel_onEdit(object sender, Prefab._RenderComponentStruct e)
        {
            prefab.rc = e.rc;
            Program.mg.previewPrefab(prefab);
        }

        private void button1_Click(object sender, EventArgs e)
        {
          
        }
    }
}
