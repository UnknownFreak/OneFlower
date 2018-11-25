using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for RemoveObjectConfirmBox.xaml
    /// </summary>
    public partial class AddObjectNameBox : Window
    {
        private string Result { get; set; } = string.Empty;
        private string deleteString = "Are you sure you want to delete {objectName}?";

        private AddObjectNameBox()
        {
            InitializeComponent();
        }

        public static string ShowAndGetResult()
        {
            AddObjectNameBox box = new AddObjectNameBox();
            box.ShowDialog();
            return box.Result;
        }

        private void Yes_click(object sender, RoutedEventArgs e)
        {
            Result = box.Text;
            Close();
        }

        private void No_click(object sender, RoutedEventArgs e)
        {
            Result = string.Empty;
            Close();
        }
    }
}
