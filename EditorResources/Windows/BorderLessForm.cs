using System;
using System.Windows.Forms;
using EditorResources.Resources;
using EditorResources.UserControls;
using EditorResources.Utils;
using static EditorResources.Utils.EditorEvents;

namespace EditorResources
{
    public partial class BorderLessForm : UserControl
    {
        bool MousePressedInside = false;
        public bool PaintModeEnabled { get; set; }

        public BorderLessForm()
        {
            InitializeComponent();
            onBrushChangedEvent += BrushChangedListener;
            AllowDrop = true;
        }

        private void BrushChangedListener(object sender, BrushEventArgs e)
        {
            if (e.PaintMode == "Paint")
                PaintModeEnabled = true;
            else
                PaintModeEnabled = false;
        }

        protected override void OnDragDrop(DragEventArgs e)
        {
            base.OnDragDrop(e);
            if (e.Data.GetDataPresent("GameObject"))
            {
                ObjectDataViewModel dataValue = ((DataObject)e.Data).GetObject<ObjectDataViewModel>("GameObject");
                OnDragDropEvent(new ObjectEventArgs(dataValue));
            }
        }

        protected override void OnDragOver(DragEventArgs e)
        {
            base.OnDragOver(e);
            e.Effect = DragDropEffects.None;
            if (e.Data.GetDataPresent("GameObject"))
            {
                e.Effect = DragDropEffects.Copy;
            }
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left && PaintModeEnabled)
            {
                MousePressedInside = true;
                OnBrushUsedEvent(new BrushUsedEventArgs() { X = e.X, Y = e.Y });
            }
            base.OnMouseDown(e);
            
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left && MousePressedInside && PaintModeEnabled)
            {
                InternalEditorEvents.Log("Mouse Move", Utils.Message.MsgType.Info);
                OnBrushUsedEvent(new BrushUsedEventArgs() { X = e.X, Y = e.Y });
            }
            base.OnMouseMove(e);
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            InternalEditorEvents.Log("Mouse Up", Utils.Message.MsgType.Info);
            ResetMouseState();
            base.OnMouseUp(e);
        }
        public void ResetMouseState()
        {
            InternalEditorEvents.Log("Reset Mouse State", Utils.Message.MsgType.Info);
            MousePressedInside = false;
        }
    }
}
