using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using EditorResources.Dto;
using EditorResources.Functionality;
using EditorResources.Utils;
using EditorResources.Windows;
using static EditorResources.Utils.EnumCollection;

namespace EditorResources.UserControls
{
    /// <summary>
    /// Interaction logic for ZoneView.xaml
    /// </summary>
    public partial class ZoneView : UserControl
    {
        ZoneItem lastSelected;
        ObservableCollection<ZoneItem> zoneItems = new ObservableCollection<ZoneItem>();
        ObservableCollection<ZoneObjectDto> ZoneObjects { get; set; } = new ObservableCollection<ZoneObjectDto>(); 
        private string loadedMod;

        public ZoneView()
        {
            lastSelected = null;
            InitializeComponent();
            EditorEvents.onObjectEvent += OnObjectLoaded;
            EditorEvents.onObjectEvent += OnObjectCreated;
            EditorEvents.onObjectEvent += OnObjectEdited;
            EditorEvents.onObjectEvent += OnObjectDeleted;
            EditorEvents.onModEvent += ClearListOnLoad;
            EngineEvents.onModFinishedLoadingEvent += OnModFinishedLoading;
            ZoneSelector.ItemsSource = zoneItems;
            ZoneSelector.IsSynchronizedWithCurrentItem = true;
            ZoneSelector.ContextMenu.IsEnabled = false;
        }

        private void OnModFinishedLoading(object sender, EventArgs e)
        {
            InternalEditorEvents.Log("Zone finsished loading.", Message.MsgType.Info);
            ObjectList.IsEnabled = true;
        }

        private void OnObjectEdited(object sender, EditorEvents.ObjectEventArgs arg)
        {
            if (arg.Type == ObjectType.Zone && arg.Flag == ObjectFlag.Edited)
            {
                IEnumerable<ZoneItem> enumerable = zoneItems.Where(x => (x.Origin == arg.Value.Origin && x.Id == arg.Value.ID));
                enumerable.ElementAt(0).Value = arg.Value as ZoneDto;
                enumerable.ElementAt(0).Flag = ObjectFlag.Edited;
            }
        }

        private void OnObjectDeleted(object sender, EditorEvents.ObjectEventArgs arg)
        {
            if (arg.Type == ObjectType.Zone)
                return;
            if (arg.Flag == ObjectFlag.Deleted)
            {
                IEnumerable<ZoneItem> enumerable = zoneItems.Where(x => (x.Origin == arg.Value.Origin && x.Id == arg.Value.ID));
                enumerable.ElementAt(0).Flag = arg.Flag;
            }
        }

        private void OnObjectCreated(object sender, EditorEvents.ObjectEventArgs e)
        {
            if (e.Flag == ObjectFlag.Added && e.Type == ObjectType.Zone && e.Value.Name != string.Empty)
            {
                e.Value.Origin = loadedMod;
                e.Value.ID = GetId(e.Type);
                zoneItems.Add(new ZoneItem(e.Value as ZoneDto, ObjectFlag.Added));
            }
        }

        private void ClearListOnLoad(object sender, EditorEvents.ModEventArgs e)
        {
            if (e.Type == EditorEvents.ModEventArgs.EventType.Loaded)
            {
                zoneItems.Clear();
                ZoneSelector.ContextMenu.IsEnabled = true;
                loadedMod = e.ModName;
            }
        }

        public void OnObjectLoaded(object sender, EditorEvents.ObjectEventArgs arg)
        {
            if (arg.Type != ObjectType.Zone)
                return; // Everything is thrown away except zones.
            else if (arg.Flag == ObjectFlag.Added)
                return;
            zoneItems.Add(new ZoneItem(arg.Value as ZoneDto, ObjectFlag.Default));
        }

        private void ZoneSelector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            lastSelected = ZoneSelector.SelectedItem as ZoneItem;
            //ListView can return null on selected item.
            if (lastSelected == null)
            {
                InternalEditorEvents.Log("Unselected last selected item.", Message.MsgType.Info);
                return;
            }
            ObjectList.IsEnabled = false;
            EditorEvents.OnObjectSelectedEvent(new EditorEvents.OnObjectSelectedEventArgs() { ID = lastSelected.Id, ModOrigin = lastSelected.Origin, SelectedType = ObjectType.Zone });
        }

        private void AddZoneClick(object sender, RoutedEventArgs e) => new ZoneEditWindow().Show();

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
            lastSelected.Flag = lastSelected.Flag == ObjectFlag.Deleted ? ObjectFlag.Edited : ObjectFlag.Deleted;

            EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
            {
                Flag = ObjectFlag.Deleted,
                Type = ObjectType.Zone,
                Value = lastSelected.Value
            });
        }

        private void EditZoneClick(object sender, RoutedEventArgs e)
        {
            ZoneEditWindow v = new ZoneEditWindow(true);
            v.SetEditFields(lastSelected.Value, lastSelected.Name);
            v.Show();
        }

        private uint GetId(ObjectType type)
        {
            uint lastId = 0;
            try
            {
                lastId = zoneItems.Where(x => x.Origin == loadedMod).Select(x => x.Id).Max();
            }
            catch (ArgumentNullException)
            { }
            catch (InvalidOperationException)
            { }
            finally
            { lastId++; }
            return lastId;
        }
    }

    internal class ZoneItem : PropertyNotifier
    {
        private ObjectFlag _flag;
        private ZoneDto _value;

        public string Origin
        {
            get => _value.Origin;
            private set
            {
                _value.Origin = value;
                NotifyPropertyChanged();
            }
        }
        public uint Id
        {
            get => _value.ID;
            private set
            {
                _value.ID = value;
                NotifyPropertyChanged();
            }
        }
        public string Name
        {
            get => _value.Name;
            private set
            {
                _value.Name = value;
                NotifyPropertyChanged();
            }
        }
        public ObjectFlag Flag
        {
            get => _flag;
            set
            {
                _flag = value;
                NotifyPropertyChanged();
            }
        }
        public ZoneDto Value
        {
            get => _value;
            set
            {
                _value = value;
                NotifyPropertyChanged();
            }
        }

        public ZoneItem(ZoneDto dto, ObjectFlag flag)
        {
            Value = dto;
            Flag = flag;
        }

        public Brush brush { get; set; }

        private void Rename(string newName) => Name = newName;
    }
}
