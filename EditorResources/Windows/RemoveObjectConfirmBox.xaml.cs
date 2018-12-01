using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for RemoveObjectConfirmBox.xaml
    /// </summary>
    public partial class RemoveObjectConfirmBox : Window
    {
        private bool Result { get; set; } = false;
        private string deleteString = "Are you sure you want to delete ";

        private RemoveObjectConfirmBox() : this("")
        {
        }

        private RemoveObjectConfirmBox(string objectToDeleteName, string additionalInfoText="")
        {
            InitializeComponent();
            box.Text = deleteString + objectToDeleteName + "?\n" + additionalInfoText;
        }

        public static bool ShowAndGetResult(string objectName, string additionalInfoText = "")
        {
            RemoveObjectConfirmBox box = new RemoveObjectConfirmBox(objectName, additionalInfoText);
            box.ShowDialog();
            return box.Result;
        }

        private void Yes_click(object sender, RoutedEventArgs e)
        {
            Result = true;
            Close();
        }

        private void No_click(object sender, RoutedEventArgs e)
        {
            Result = false;
            Close();
        }
    }
}
