using System.Windows;
using System.Windows.Controls;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for ModelViewer.xaml
    /// </summary>
    public partial class ModelViewer : Window
    {
        bool initialized = false;
        public ModelViewer()
        {
            InitializeComponent();
            initialized = true;
            HideAllModelDataViews();
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (initialized == false)
            {
                e.Handled = true;
                return;
            }
            if(e.RemovedItems.Count > 0)
            {
                if(e.RemovedItems[0] == ModelSelector.Items[1])
                    StaticModel.Visibility = Visibility.Hidden;
                else if (e.RemovedItems[0] == ModelSelector.Items[2])
                    SpriteSheetModel.Visibility = Visibility.Hidden;
                else if (e.RemovedItems[0] == ModelSelector.Items[3])
                    SpriterModel.Visibility = Visibility.Hidden;
            }

            if (e.AddedItems[0] == ModelSelector.Items[0])
                HideAllModelDataViews();
            else if (e.AddedItems[0] == ModelSelector.Items[1])
                StaticModel.Visibility = Visibility.Visible;
            else if (e.AddedItems[0] == ModelSelector.Items[2])
                SpriteSheetModel.Visibility = Visibility.Visible;
            else if (e.AddedItems[0] == ModelSelector.Items[3])
                SpriterModel.Visibility = Visibility.Visible;

            createModelButton.IsEnabled = (e.AddedItems[0] != ModelSelector.Items[0]);

        }

        private void HideAllModelDataViews()
        {
            StaticModel.Visibility = Visibility.Hidden;
            SpriteSheetModel.Visibility = Visibility.Hidden;
            SpriterModel.Visibility = Visibility.Hidden;
        }

    }
}
