using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using EditorResources.Functionality;
using EditorResources.Utils;
using EditorResources.Windows;
using static EditorResources.Functionality.EditorEvents;
using static EditorResources.Utils.EnumCollection;

namespace EditorResources.UserControls
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
            EditorEvents_old.onModFinishedLoading += ZoneViewOnModFinishedLoading;
            EditorEvents_old.onGetZoneInfoEvent += GetZoneInfoEvent;
            EditorEvents.onObjectLoadEvent += OnObjectLoaded;
            EditorEvents.onModLoaded += ClearListOnLoad;
            ZoneSelector.ItemsSource = zoneItems;
            ZoneSelector.IsSynchronizedWithCurrentItem = true;
            ZoneSelector.ContextMenu.IsEnabled = false;
        }

        private void ClearListOnLoad(object sender, EventArgs e)
        {
            zoneItems.Clear();
            ZoneSelector.ContextMenu.IsEnabled = true;
        }

        private void GetZoneInfoEvent(object sender, EditorGetZoneInfoEvent e)
        {
            info = e;
        }

        public void OnObjectLoaded(object sender, OnObjectLoadEventArgs arg)
        {
            if (arg.Type != ObjectType.Zone)
                return;
            zoneItems.Add(new ZoneItem(arg.Origin, arg.ID, arg.Name, ObjectFlag.Default));
        }

        private void ZoneViewOnModFinishedLoading(object sender, ModFinishedLoadedEventArgs e)
        {
            //zoneItems.Clear();
            //foreach(var t in e.zoneFiles)
            //{
            //    zoneItems.Add(new ZoneItem(t.Item1, t.Item2, t.Item3, ObjectFlag.Default));
            //}
            //ZoneSelector.ContextMenu.IsEnabled = true;
        }

        private void ZoneSelector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

            lastSelected = ZoneSelector.SelectedItem as ZoneItem;
            //ListView can return null on selected item.
            if (lastSelected == null)
                InternalEditorEvents.Log("Unselected last selected item.", Message.MsgType.Info);
            EditorEvents_old.OnZoneSelectedEvent(new EditorZoneSelectedEventArgs() { ZoneName = lastSelected.Name, ModOrigin = lastSelected.Origin, ZoneID = lastSelected.Id });
        }

        private void AddZoneClick(object sender, RoutedEventArgs e)
        {
            new ZoneEditWindow().Show();
        }

        private void ZoneSelector_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            if (lastSelected == null)
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
            if (lastSelected.Flag == ObjectFlag.Deleted)
            {
                lastSelected.Flag = ObjectFlag.Edited;
                // TODO: Send event to apply this in the actual data as well.
            }
            else
            {
                lastSelected.Flag = ObjectFlag.Deleted;
                // TODO: Send event to apply this in the actual data as well.
            }
        }

        private void EditZoneClick(object sender, RoutedEventArgs e)
        {
            ZoneEditWindow v = new ZoneEditWindow(true);
            v.SetEditFields(info.ZoneName, info.Origin, info.Id.ToString(), info.BackgroundPath, info.LoadingScreenPath, info.LoadingScreenMessage);
            v.Show();
        }
    }

    internal class ZoneItem : PropertyNotifier
    {
        private ObjectFlag _flag;
        private string _origin;
        private uint _id;
        private string _name;

        public string Origin {
            get { return _origin; }
            private set
            {
                _origin = value;
                NotifyPropertyChanged();
            }
        }
        public uint Id {
            get { return _id; }
            private set {
                _id = value;
                NotifyPropertyChanged();
            }
        }
        public string Name
        {
            get { return _name; }
            private set
            {
                _name = value;
                NotifyPropertyChanged();
            }
        }
        public ObjectFlag Flag {
            get { return _flag; }
            set {
                _flag = value;
                NotifyPropertyChanged();
            }
        }

        public ZoneItem(string origin, uint id, string name, ObjectFlag flag)
        {
            Origin = origin;
            Id = id;
            Name = name;
            Flag = flag;
        }
        public Brush brush { get; set; }

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
