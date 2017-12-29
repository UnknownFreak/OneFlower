using System.Windows;
using System.Windows.Controls;
using EditorResources.Functionality;

namespace EditorResources.ZoneView
{
    /// <summary>
    /// Interaction logic for ZoneView.xaml
    /// </summary>
    public partial class ZoneView : UserControl
    {
        ZoneItem lastSelected;
        EditorGetZoneInfoEvent info;
        public ZoneView()
        {
            lastSelected = null;
            InitializeComponent();
            EditorEvents.onModFinishedLoading += ZoneViewOnModFinishedLoading;
            EditorEvents.onGetZoneInfoEvent += GetZoneInfoEvent;
        }

        private void GetZoneInfoEvent(object sender, EditorGetZoneInfoEvent e)
        {
            info = e;
        }

        private void ZoneViewOnModFinishedLoading(object sender, ModFinishedLoadedEventArgs e)
        {
            ZoneSelector.Items.Clear();
            foreach(var t in e.zoneFiles)
            {
                ZoneSelector.Items.Add(new ZoneItem(t.Item1, t.Item2, t.Item3));
            }
        }

        private void ZoneSelector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

            lastSelected = ZoneSelector.SelectedItem as ZoneItem;
            //ListView can return null on selected item.
            if (lastSelected is null)
                return;
            EditorEvents.OnZoneSelectedEvent(new EditorZoneSelectedEventArgs() { ZoneName = lastSelected.Name, ModOrigin = lastSelected.Origin, ZoneID = lastSelected.Id });
        }

        private void AddZoneClick(object sender, RoutedEventArgs e)
        {
            new ZoneEditView().Show();
        }

        private void ZoneSelector_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            if (lastSelected is null)
            {
                editZoneContextMenu.IsEnabled = false;
                deleteZoneContextMenu.IsEnabled = false;
            }
            else
            {
                editZoneContextMenu.IsEnabled = true;
                deleteZoneContextMenu.IsEnabled = true;
            }
        }

        private void DeleteZoneClick(object sender, RoutedEventArgs e)
        {
            
        }

        private void EditZoneClick(object sender, RoutedEventArgs e)
        {
            //Nullcheck that can shadow problems...
            //if (info is null)
            //    return;
            ZoneEditView v = new ZoneEditView(true);
            v.setEditFields(info.ZoneName, info.Origin, info.Id.ToString(), info.BackgroundPath, info.LoadingScreenPath, info.LoadingScreenMessage);
            v.Show();
        }
    }

    internal class ZoneItem
    {
        public string Origin { get; private set; }
        public uint Id { get; private set; }
        public string Name { get; private set; }

        public ZoneItem(string origin, uint id, string name)
        {
            Origin = origin;
            Id = id;
            Name = name;
        }
        void Rename(string newName)
        {
            Name = newName;
        }
    }
    internal class ZoneObjectItem
    {
        public string Origin { get; private set; }
        public uint Id { get; private set; }
        public string Dependency { get; private set; }
        public uint PrefabId { get; private set; }
        public string Name { get; private set; }

        public ZoneObjectItem(string origin, uint id, string dependency, uint prefabid, string name)
        {
            Origin = origin;
            Id = id;
            Dependency = dependency;
            PrefabId = prefabid;
            Name = name;
        }

    }
}
