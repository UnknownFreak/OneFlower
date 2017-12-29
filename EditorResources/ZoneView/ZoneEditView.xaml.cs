using EditorResources.Functionality;
using System;
using System.Windows;

namespace EditorResources.ZoneView
{
    /// <summary>
    /// Interaction logic for ZoneEditView.xaml
    /// </summary>
    public partial class ZoneEditView : Window
    {
        string origin = "";
        public ZoneEditView(bool edit = false)
        {
            InitializeComponent();
            if (edit)
            {
                add_edit_button.Click -= add_click;
                add_edit_button.Click += edit_click;
                add_edit_button.Content = "Edit";

            }
        }

        public void setEditFields(string zonename, string origin, string id, string background, string loadingscreen, string loadingscreenmessage)
        {
            zoneName.Text = zonename;
            this.origin = origin;
            zoneId.Text = id;
            backgroundPath.Text = background;
            loadingScreenPath.Text = loadingscreen;
            loadingScreenMessage.Text = loadingscreenmessage;
        }

        private void add_click(object sender, RoutedEventArgs e)
        {
            EditorEvents.OnZoneEditViewAddZoneEvent(createBaseZoneEventArgs());
            Close();
        }

        private void edit_click(object sender, RoutedEventArgs e)
        {

            EditorZoneEditViewAddZoneEventArgs evt = createBaseZoneEventArgs();
            evt.isEdit = true;
            EditorEvents.OnZoneEditViewAddZoneEvent(evt);
            Close();
        }

        private void cancel_click(object sender, RoutedEventArgs e)
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
