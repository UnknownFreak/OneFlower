using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using EditorResources.Functionality;

namespace EditorResources.MainEditorWindow
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class EditorWindow : Window
    {
        bool closed = false;
        public EditorWindow()
        {
            InitializeComponent();
            createEditorWindow();
            EditorEvents.onLogEvent += LogViewAddEvent;
        }

        private void LogViewAddEvent(object sender, EditorLogEventArgs e)
        {
            Dispatcher.Invoke(new Action(() => {
                messageView.Items.Add(e.logMessage);
            })); 
        }

        void createEditorWindow()
        {
            formhost.Child = new BorderLessForm();
        }
        public IntPtr getGameHost()
        {
            return formhost.Child.Handle;
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            closed = true;
            //Environment.Exit(0);
        }
        public bool isClosed()
        {
            return closed;
        }

        private void TabItem_PreviewMouseMove(object sender, MouseEventArgs e)
        {
            var tabItem = e.Source as TabItem;

            if (tabItem == null)
                return;

            if (Mouse.PrimaryDevice.LeftButton == MouseButtonState.Pressed)
            {
                DragDrop.DoDragDrop(tabItem, tabItem, DragDropEffects.All);
            }
        }

        private void TabItem_Drop(object sender, DragEventArgs e)
        {
            var tabItemTarget = e.Source as TabItem;
            if (tabItemTarget == null)
                return;
            var tabItemSource = e.Data.GetData(typeof(TabItem)) as TabItem;

            if (!tabItemTarget.Equals(tabItemSource))
            {
                var tabControl = tabItemTarget.Parent as TabControl;
                int sourceIndex = tabControl.Items.IndexOf(tabItemSource);
                int targetIndex = tabControl.Items.IndexOf(tabItemTarget);

                tabControl.Items.Remove(tabItemSource);
                tabControl.Items.Insert(targetIndex, tabItemSource);

                tabControl.Items.Remove(tabItemTarget);
                tabControl.Items.Insert(sourceIndex, tabItemTarget);
            }
        }

        private void NewCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            new ModWindow.NewMod().Show();
        }

        private void OpenCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.Filter = "All Data Files |*.mod;*.main|Mod files |*.mod|Master file |*.main";
            // Show open file dialog box
            bool? result = dlg.ShowDialog();

            // Process open file dialog box results
            if (result == true)
            {
                // Open document
                EditorEvents.OnModLoad(new Functionality.ModLoadEventArgs() { modName = dlg.SafeFileName});
            }
        }

        private void ExitCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            this.Close();
        }

        private void SaveCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            EditorEvents.OnModSave(new ModSaveEventArgs());
        }
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            new SpriterScene.SpriterScene().Show();
        }
    }
}
