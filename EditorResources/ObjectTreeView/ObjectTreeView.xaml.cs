using EditorResources.Functionality;
using System.Windows;
using System.Windows.Controls;

namespace EditorResources.ObjectView
{
    /// <summary>
    /// Interaction logic for ObjectTreeView.xaml
    /// </summary>
    public partial class ObjectTreeView : UserControl
    {
        public ObjectTreeView()
        {
            InitializeComponent();
        }

        public void OnObjectLoaded(OnObjectLoadEventArgs arg)
        {

        }

        private void NewIntegerVariable_Click(object sender, RoutedEventArgs e)
        {
            var window = new GlobalVariableView.GlobalVariableView(EditorResources.Resources.NameValidator.ValidationType.Int);
            window.Owner = Window.GetWindow(this);
            window.Show();
        }

        private void NewFoatingPointVariable_Click(object sender, RoutedEventArgs e)
        {
            var window = new GlobalVariableView.GlobalVariableView(EditorResources.Resources.NameValidator.ValidationType.Double);
            window.Owner = Window.GetWindow(this);
            window.Show();
        }

        private void NewStringVariable_Click(object sender, RoutedEventArgs e)
        {
            var window = new GlobalVariableView.GlobalVariableView(EditorResources.Resources.NameValidator.ValidationType.String);
            window.Owner = Window.GetWindow(this);
            window.Show();
        }
    }
}
