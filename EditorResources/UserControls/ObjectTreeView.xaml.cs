using EditorResources.Functionality;
using System.Windows;
using System.Windows.Controls;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Media;
using static EditorResources.Utils.EnumCollection;
using System;
using System.Runtime.CompilerServices;
using EditorResources.Utils;
using static EditorResources.Functionality.EditorEvents;

namespace EditorResources.UserControls
{
    /// <summary>
    /// Interaction logic for ObjectTreeView.xaml
    /// </summary>
    public partial class ObjectTreeView : UserControl
    {

        ObservableCollection<ObjectDataViewModel> objectItems = new ObservableCollection<ObjectDataViewModel>();
        string loadedMod = string.Empty;
        public ObjectTreeView()
        {
            InitializeComponent();
            EditorEvents_old.onModFinishedLoading += OnModLoaded;
            EditorEvents_old.onOVariableCreatedEvent += OnVariableCreated;
            EditorEvents.onObjectLoadEvent += OnObjectLoaded;
            InternalEditorEvents.requestObjectData += OnDataObjectRequested;
            EditorEvents.onModLoaded += ClearListOnLoad;
            treeView.IsEnabled = false;
            ObjectList.ItemsSource = objectItems;
        }

        private void OnDataObjectRequested(object sender, EventArgs e)
        {
            InternalEditorEvents.OnRequsetObjectDataListEvent(new InternalEditorEvents.RequestObjectDataListEventArgs() { Observable = objectItems });
        }

        private void ClearListOnLoad(object sender, EventArgs e)
        {
            objectItems.Clear();
        }

        private void OnVariableCreated(object sender, OnVariableCreatedEventArgs e)
        {
            // This method is registered before any other event so we can set the mod origin here.
            e.Origin = loadedMod;
            e.ID = getId(e.Type);
            objectItems.Add(new ObjectDataViewModel(e.Origin, e.ID, e.Name, ObjectFlag.Added, e.Type, e.Value.ToString()));
        }

        public void OnObjectLoaded(object sender, OnObjectLoadEventArgs arg)
        {
            if (arg.Type == ObjectType.Zone)
                return;
            objectItems.Add(new ObjectDataViewModel(arg.Origin, arg.ID, arg.Name, ObjectFlag.Default, arg.Type, arg.Value.ToString()));
        }

        private void OnModLoaded(object sender, ModFinishedLoadedEventArgs args)
        {
            loadedMod = args.ModName;
            treeView.IsEnabled = true;
        }

        private void NewIntegerVariable_Click(object sender, RoutedEventArgs e)
        {
            CreateVariableView(EditorResources.Resources.NameValidator.ValidationType.Int).Show();
        }

        private void NewFoatingPointVariable_Click(object sender, RoutedEventArgs e)
        {
            CreateVariableView(EditorResources.Resources.NameValidator.ValidationType.Double).Show();
        }

        private void NewStringVariable_Click(object sender, RoutedEventArgs e)
        {
            CreateVariableView(EditorResources.Resources.NameValidator.ValidationType.String).Show();
        }

        private Windows.CreateGlobalVariableWindow CreateVariableView(Resources.NameValidator.ValidationType validation)
        {
            return new Windows.CreateGlobalVariableWindow(validation)
            {
                Owner = Window.GetWindow(this)
            };
        }

        private uint getId(ObjectType type)
        {
            uint lastId = 0;
            try
            {
                lastId = objectItems.Where(x => x.Type == type).Select(x => x.Id).Max();
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
    internal class ObjectDataViewModel : PropertyNotifier
    {
        private string _origin;
        private uint _id;
        private string _name;
        private ObjectFlag _flag;
        private ObjectType _type;
        private string _value;

        public Brush brush { get; set; }

        public string Origin
        {
            get { return _origin; }
            private set
            {
                _origin = value;
                NotifyPropertyChanged();
            }
        }
        public uint Id
        {
            get { return _id; }
            private set
            {
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
        public ObjectFlag Flag
        {
            get { return _flag; }
            set
            {
                _flag = value;
                NotifyPropertyChanged();
            }
        }

        public ObjectType Type
        {
            get { return _type; }
            set
            {
                _type = value;
                NotifyPropertyChanged();
            }
        }

        public string Value
        {
            get { return _value; }
            set
            {
                _value = value;
                NotifyPropertyChanged();
            }
        }

        public ObjectDataViewModel(string origin, uint id, string name, ObjectFlag flag, ObjectType type, string value)
        {
            Origin = origin;
            Id = id;
            Name = name;
            Flag = flag;
            Type = type;
            Value = value;
        }
    }
}
