using EditorResources.Dto;
using EditorResources.Utils;
using Microsoft.Win32;
using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for ZoneEditView.xaml
    /// </summary>
    public partial class ZoneEditWindow : Window
    {
        ZoneDto dto = new ZoneDto();

        EnumCollection.ObjectFlag _mode = EnumCollection.ObjectFlag.Added;
        public ZoneEditWindow(bool edit = false)
        {
            InitializeComponent();
            if (edit)
            {
                _mode = EnumCollection.ObjectFlag.Edited;
                add_edit_button.Content = "Edit";
            }
        }

        public void SetEditFields(ZoneDto dto, string zoneName)
        {
            this.dto = dto;
            this.zoneName.Text = zoneName;
        }


        private void Add_click(object sender, RoutedEventArgs e)
        {
            dto.LoadingScreen = loadingScreenPath.Text;
            dto.Background = backgroundPath.Text;
            dto.LoadingScreen = loadingScreenMessage.Text;
            dto.Name = zoneName.Text;

            EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
            {
                Type = EnumCollection.ObjectType.Zone,
                Flag = _mode,
                Value = dto
            });
            Close();
        }

        private void Cancel_click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void SetBackgroundImagePath(object sender, RoutedEventArgs e)
        {
            backgroundPath.Text = ShowFileDialog();
        }

        string ShowFileDialog()
        {
            OpenFileDialog diag = new OpenFileDialog()
            {
                DefaultExt = "*.png",
                Filter = "PNG Files (*.png)|*.png|JPEG Files (*.jpeg)|*.jpeg|JPG Files (*.jpg)|*.jpg|All (*.*)|*.*"
            };
            if (diag.ShowDialog() == false)
                return string.Empty;
            return diag.SafeFileName;
        }

        private void SetLoadingScreenImagePath(object sender, RoutedEventArgs e)
        {
            loadingScreenPath.Text = ShowFileDialog();
        }
    }
}
