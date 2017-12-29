using System.Collections.ObjectModel;
using System.ComponentModel;
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
        ObservableCollection<ZoneItem> zoneItems = new ObservableCollection<ZoneItem>();
        public ZoneView()
        {
            lastSelected = null;
            InitializeComponent();
            EditorEvents.onModFinishedLoading += ZoneViewOnModFinishedLoading;
            EditorEvents.onGetZoneInfoEvent += GetZoneInfoEvent;
            ZoneSelector.ItemsSource = zoneItems;
            ZoneSelector.IsSynchronizedWithCurrentItem = true;
            ZoneSelector.ContextMenu.IsEnabled = false;
        }

        private void GetZoneInfoEvent(object sender, EditorGetZoneInfoEvent e)
        {
            info = e;
        }

        private void ZoneViewOnModFinishedLoading(object sender, ModFinishedLoadedEventArgs e)
        {
            zoneItems.Clear();
            foreach(var t in e.zoneFiles)
            {
                zoneItems.Add(new ZoneItem(t.Item1, t.Item2, t.Item3, ZoneFlags.None));
            }
            ZoneSelector.ContextMenu.IsEnabled = true;
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
            if (lastSelected.Flag == ZoneFlags.Deleted)
            {
                lastSelected.Flag = ZoneFlags.Edited;
                // TODO: Send event to apply this in the actual data as well.
            }
            else
            {
                lastSelected.Flag = ZoneFlags.Deleted;
                // TODO: Send event to apply this in the actual data as well.
            }
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

    internal class ZoneItem : INotifyPropertyChanged
    {
        private ZoneFlags _flag;
        private string _origin;
        private uint _id;
        private string _name;

        public string Origin {
            get { return _origin; }
            private set
            {
                _origin = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Origin"));
            }
        }
        public uint Id {
            get { return _id; }
            private set {
                _id = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Id"));
            }
        }
        public string Name
        {
            get { return _name; }
            private set
            {
                _name = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Name"));
            }
        }
        public ZoneFlags Flag {
            get { return _flag; }
            set {
                _flag = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Flag"));
            }
        }

        public ZoneItem(string origin, uint id, string name, ZoneFlags flag)
        {
            Origin = origin;
            Id = id;
            Name = name;
            Flag = flag;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        void Rename(string newName)
        {
            Name = newName;
        }
    }

    internal enum ZoneFlags
    {
        Added,
        Deleted,
        Edited,
        None
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
