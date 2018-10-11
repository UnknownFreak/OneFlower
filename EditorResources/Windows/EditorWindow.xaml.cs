using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using static EditorResources.Utils.EditorEvents;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class EditorWindow : Window
    {
        public bool IsClosed { get; private set; } = false;

        String modName = String.Empty;
        public EditorWindow()
        {
            InitializeComponent();
            CreateEditorWindow();
            onLogEvent += LogViewAddEvent;
            onModEvent += OnModLoaded;
            AllowDrop = true;
            new Veterancy(modName).Show();
        }

        private void OnModLoaded(object sender, ModEventArgs e)
        {
            if (e.Type == ModEventArgs.EventType.Loaded)
                modName = e.ModName;
        }

        private void LogViewAddEvent(object sender, EditorLogEventArgs e)
        {
            Dispatcher.Invoke(new Action(() => {
                messageView.Items.Add(e.logMessage);
            })); 
        }

        void CreateEditorWindow() => formhost.Child = new BorderLessForm();
        public IntPtr GetGameHost() => formhost.Child.Handle;
        private void Window_Closed(object sender, EventArgs e) => IsClosed = true;
        private void NewCommand_Executed(object sender, ExecutedRoutedEventArgs e) => new NewModWindow().Show();
        private void ExitCommand_Executed(object sender, ExecutedRoutedEventArgs e) => Close();
        private void GameVariableMappingClick(object sender, RoutedEventArgs e) => new GameVariableMapping().Show();

        private void TabItem_PreviewMouseMove(object sender, MouseEventArgs e)
        {

            if (!(e.Source is TabItem tabItem))
                return;

            if (Mouse.PrimaryDevice.LeftButton == MouseButtonState.Pressed)
            {
                DragDrop.DoDragDrop(tabItem, tabItem, DragDropEffects.All);
            }
        }

        private void TabItem_Drop(object sender, DragEventArgs e)
        {
            if (!(e.Source is TabItem tabItemTarget))
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


        private void OpenCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog
            {
                Filter = "All Data Files |*.mod;*.main|Mod files |*.mod|Master file |*.main"
            };
            bool? result = dlg.ShowDialog();

            if (result == true)
            {
                OnModEvent(new ModEventArgs() { ModName = dlg.SafeFileName, Type = ModEventArgs.EventType.Loaded });
            }
        }

        private void SaveCommand_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OnModEvent(new ModEventArgs() { ModName = modName, Type = ModEventArgs.EventType.Saved });
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            new SpriterScene.SpriterScene().Show();
            new ModelViewer().Show();
        }

        private void Window_MouseUp(object sender, MouseButtonEventArgs e)
        {
            (formhost.Child as BorderLessForm).ResetMouseState();
        }
    }
}
