using EditorResources.Functionality;
using System;
using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for ZoneEditView.xaml
    /// </summary>
    public partial class ZoneEditWindow : Window
    {
        string origin = String.Empty;
        public ZoneEditWindow(bool edit = false)
        {
            InitializeComponent();
            if (edit)
            {
                add_edit_button.Click -= Add_click;
                add_edit_button.Click += Edit_click;
                add_edit_button.Content = "Edit";

            }
        }

        public void SetEditFields(string zonename, string origin, string id, string background, string loadingscreen, string loadingscreenmessage)
        {
            zoneName.Text = zonename;
            this.origin = origin;
            zoneId.Text = id;
            backgroundPath.Text = background;
            loadingScreenPath.Text = loadingscreen;
            loadingScreenMessage.Text = loadingscreenmessage;
        }

        private void Add_click(object sender, RoutedEventArgs e)
        {
            EditorEvents.OnZoneEditViewAddZoneEvent(createBaseZoneEventArgs());
            Close();
        }

        private void Edit_click(object sender, RoutedEventArgs e)
        {

            EditorZoneEditViewAddZoneEventArgs evt = createBaseZoneEventArgs();
            evt.IsEdit = true;
            EditorEvents.OnZoneEditViewAddZoneEvent(evt);
            Close();
        }

        private void Cancel_click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private EditorZoneEditViewAddZoneEventArgs createBaseZoneEventArgs()
        {
            return new EditorZoneEditViewAddZoneEventArgs()
            {
                ZoneName = zoneName.Text,
                BackgroundPath = backgroundPath.Text,
                LoadingScreenPath = loadingScreenPath.Text,
                LoadingScreenMessage = loadingScreenMessage.Text,
                Origin = origin,
                Id = Convert.ToUInt32(zoneId.Text)
            };
        }

    }
}
