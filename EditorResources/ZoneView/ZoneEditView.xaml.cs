using System;
using System.Windows;

namespace EditorResources.ZoneView
{
    /// <summary>
    /// Interaction logic for ZoneEditView.xaml
    /// </summary>
    public partial class ZoneEditView : Window
    {
        bool editInstead;
        string origin = "";
        public ZoneEditView(bool edit = false)
        {
            InitializeComponent();
            editInstead = edit;
            if (editInstead)
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
            Functionality.EditorZoneEditViewAddZoneEventArgs evt = new Functionality.EditorZoneEditViewAddZoneEventArgs();
            evt.ZoneName = zoneName.Text;
            evt.BackgroundPath = backgroundPath.Text;
            evt.LoadingScreenPath = loadingScreenPath.Text;
            evt.LoadingScreenMessage = loadingScreenMessage.Text;
            Functionality.EditorEvents.OnZoneEditViewAddZoneEvent(evt);
            Close();
        }

        private void edit_click(object sender, RoutedEventArgs e)
        {
            Functionality.EditorZoneEditViewAddZoneEventArgs evt = new Functionality.EditorZoneEditViewAddZoneEventArgs();
            evt.ZoneName = zoneName.Text;
            evt.BackgroundPath = backgroundPath.Text;
            evt.LoadingScreenPath = loadingScreenPath.Text;
            evt.LoadingScreenMessage = loadingScreenMessage.Text;
            evt.Origin = origin;
            evt.Id = Convert.ToUInt32(zoneId.Text);
            Functionality.EditorEvents.OnZoneEditViewAddZoneEvent(evt);
            Close();
        }

        private void cancel_click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
