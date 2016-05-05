using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BaseEditor
{
    class DragableTabControl : System.Windows.Forms.TabControl
    {
        public static List<DragableTabControl> tabs = new List<DragableTabControl>();
        const int WM_NCHITTEST = 0x0084;
        const int HTTRANSPARENT = -1;
        const int HTCLIENT = 1;

        //The default hit-test for a TabControl's
        //background is HTTRANSPARENT, preventing
        //me from receiving mouse and drag events
        //over the background.  I catch this and 
        //replace HTTRANSPARENT with HTCLIENT to 
        //allow the user to drag over us when we 
        //have no TabPages.
        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (m.Msg == WM_NCHITTEST)
            {
                if (m.Result.ToInt32() == HTTRANSPARENT)
                    m.Result = new IntPtr(HTCLIENT);
            }
        }
        /// 
        /// Summary description for DraggableTabPage.
        /// 
        private System.ComponentModel.Container components = null;
        private Rectangle m_rectDragBoxFromMouseDown;
        private Point m_dragOffset;
        public DragableTabControl()
        {
            // This call is required by the Windows.Forms Form Designer.
            InitializeComponent();
            AllowDrop = true;
            tabs.Add(this);
            // TODO: Add any initialization after the InitForm call
        }
        protected override void OnSelectedIndexChanged(EventArgs e)
        {
            base.OnSelectedIndexChanged(e);
        }
        ///  
        /// Clean up any resources being used.
        /// 
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                tabs.Remove(this);
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code
        ///  
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// 
        private void InitializeComponent()
        {
        }
        #endregion
        protected override void OnDragLeave(EventArgs e)
        {
            base.OnDragLeave(e);
        }
        protected override void OnDragEnter(DragEventArgs e)
        {
            base.OnDragEnter(e);
            Point pt = new Point(e.X, e.Y);
            pt = PointToClient(pt);

            TabPage hover_tab = GetTabPageByTab(pt);

            if (hover_tab == null)
            {
                if (e.Data.GetDataPresent(typeof(TabPage)))
                {
                    //Drags tab to a new DragableTabControl
                    TabPage drag_tab = (TabPage)e.Data.GetData(typeof(TabPage));
                    var item_drag_index = FindIndex(drag_tab);
                    TabPage selTabPage = item_drag_index.Item1.TabPages[item_drag_index.Item2];
                    TabPages.Add(selTabPage);
                    item_drag_index.Item1.TabPages.Remove(selTabPage);
                    SelectedTab = selTabPage;
                }
            }
        }
        public DragDropEffects dragDrop(Point pt,IDataObject Data)
        {

            //Get the tab we are hovering over.
            TabPage hover_tab = GetTabPageByTab(pt);

            //Make sure we are on a tab.
            if (hover_tab != null)
            {
                //Make sure there is a TabPage being dragged.
                if (Data.GetDataPresent(typeof(TabPage)))
                {
                    TabPage drag_tab = (TabPage)Data.GetData(typeof(TabPage));
                    var item_drag_index = FindIndex(drag_tab);
                    var drop_location_index = FindIndex(hover_tab);
                    TabPage selTabPage = item_drag_index.Item1.TabPages[item_drag_index.Item2];
                    TabPage repTabPage = drop_location_index.Item1.TabPages[drop_location_index.Item2];
                    if (selTabPage != repTabPage)
                        if (item_drag_index.Item1 == drop_location_index.Item1)
                        {
                            drop_location_index.Item1.TabPages[drop_location_index.Item2] = selTabPage;
                            item_drag_index.Item1.TabPages[item_drag_index.Item2] = repTabPage;
                            drop_location_index.Item1.SelectedTab = selTabPage;
                        }
                }
            }

            return DragDropEffects.Move;
        }
        protected override void OnDragOver(System.Windows.Forms.DragEventArgs e)
        {
            base.OnDragOver(e);
            Point pt = new Point(e.X,e.Y);
            pt = PointToClient(pt);
            e.Effect = dragDrop(pt, e.Data);
        }
        protected override void OnDragDrop(DragEventArgs drgevent)
        {
            base.OnDragDrop(drgevent);
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            // Handle Mouse move only if left button is pressed
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                // If the mouse moves outside the rectangle, start the drag.
                if (m_rectDragBoxFromMouseDown != Rectangle.Empty &&
                        !m_rectDragBoxFromMouseDown.Contains(e.X, e.Y))
                {
                    m_dragOffset = new Point(e.X, e.Y);
                    Invalidate();

                    Point pt = new Point(e.X, e.Y);
                    TabPage tp = GetTabPageByTab(pt);
                    // Proceed with the drag and drop
                    if (tp != null)
                    {
                        DragDropEffects dropEffect = DoDragDrop(tp, DragDropEffects.Move);
                   
                        // Reset the drag box to avoid reentry of drag
                        CalcRectDragBox(e.X, e.Y);

                        m_dragOffset = Point.Empty;
                        Invalidate();
                    }
                }

            }
        }
        protected void CalcRectDragBox(int x, int y)
        {
            // Remember the point where the mouse down occurred. The DragSize indicates
            // the size that the mouse can move before a drag event should be started.                        
            Size dragSize = SystemInformation.DragSize;
            // Create a rectangle using the DragSize, with the mouse position being
            // at the center of the rectangle.
            m_rectDragBoxFromMouseDown = new Rectangle(
                    new Point(x - (dragSize.Width / 2),
                    y - (dragSize.Height / 2)), dragSize);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            CalcRectDragBox(e.X, e.Y);
        }

        private TabPage GetTabPageByTab(Point pt)
        {
            for (int i =0; i < TabPages.Count; i++)
                if (GetTabRect(i).Contains(pt))
                    return TabPages[i];
            return null;
        }
        private Tuple<DragableTabControl,int> FindIndex(TabPage page)
        {
            foreach(DragableTabControl d in tabs)
                for (int i = 0; i < d.TabPages.Count; i++)
                    if (d.TabPages[i] == page)
                        return new Tuple<DragableTabControl,int>(d,i);

            return new Tuple<DragableTabControl,int>(null,-1);
        }
        public static Tuple<DragableTabControl, int> FindIndexStatic(TabPage page)
        {
            foreach (DragableTabControl d in tabs)
                for (int i = 0; i < d.TabPages.Count; i++)
                    if (d.TabPages[i] == page)
                        return new Tuple<DragableTabControl, int>(d, i);

            return new Tuple<DragableTabControl, int>(null, -1);
        }
    }
}
