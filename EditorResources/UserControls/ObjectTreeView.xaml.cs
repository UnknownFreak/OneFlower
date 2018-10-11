using System.Windows;
using System.Windows.Controls;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Media;
using static EditorResources.Utils.EnumCollection;
using System;
using EditorResources.Utils;
using static EditorResources.Utils.EditorEvents;
using System.Collections.Generic;
using EditorResources.Dto;
using System.Windows.Input;

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
            EditorEvents.onObjectEvent += OnObjectLoaded;
            EditorEvents.onObjectEvent += OnObjectCreated;
            EditorEvents.onObjectEvent += OnObjectEdited;
            EditorEvents.onObjectEvent += OnObjectDeleted;
            InternalEditorEvents.requestObjectData += OnDataObjectRequested;
            EditorEvents.onModEvent += ClearListOnLoad;

            treeView.IsEnabled = false;
            ObjectList.ItemsSource = objectItems;
        }

        private void OnDataObjectRequested(object sender, EventArgs e)
        {
            InternalEditorEvents.OnRequsetObjectDataListEvent(new InternalEditorEvents.RequestObjectDataListEventArgs() { Observable = objectItems });
        }

        private void ClearListOnLoad(object sender, ModEventArgs e)
        {
            if(e.Type == ModEventArgs.EventType.Loaded)
            {
                loadedMod = e.ModName;
                treeView.IsEnabled = true;
                objectItems.Clear();
            }
        }

        private void OnObjectCreated(object sender, ObjectEventArgs e)
        {
            if (e.Flag != ObjectFlag.Added || e.Type == ObjectType.Zone)
                return;
            // This method is registered before any engine event so we can set the mod origin here.
            e.Value.Origin = loadedMod;
            e.Value.ID = GetId(e.Type);
            objectItems.Add(new ObjectDataViewModel(e.Value.Origin, e.Value.ID, ObjectFlag.Added, e.Type, e.Value));
        }

        public void OnObjectLoaded(object sender, ObjectEventArgs arg)
        {
            if (arg.Type == ObjectType.Zone)
                return;
            if (arg.Flag == ObjectFlag.Default)
                objectItems.Add(new ObjectDataViewModel(arg.Value.Origin, arg.Value.ID, ObjectFlag.Default, arg.Type, arg.Value));
        }

        private void OnObjectEdited(object sender, ObjectEventArgs arg)
        {
            if (arg.Type == ObjectType.Zone)
                return;
            if (arg.Flag == ObjectFlag.Edited)
            {
                IEnumerable<ObjectDataViewModel> enumerable = objectItems.Where(x => (x.Origin == arg.Value.Origin && x.Id == arg.Value.ID));
                enumerable.ElementAt(0).Value = arg.Value;
                enumerable.ElementAt(0).Flag = ObjectFlag.Edited;
            }
        }

        private void OnObjectDeleted(object sender, ObjectEventArgs arg)
        {
            if (arg.Type == ObjectType.Zone)
                return;
            if (arg.Flag == ObjectFlag.Deleted)
            {
                IEnumerable<ObjectDataViewModel> enumerable = objectItems.Where(x => (x.Origin == arg.Value.Origin && x.Id == arg.Value.ID));
                enumerable.ElementAt(0).Flag = arg.Flag;
            }
        }

        private void NewIntegerVariable_Click(object sender, RoutedEventArgs e) => CreateVariableView(EditorResources.Resources.NameValidator.ValidationType.Int).Show();

        private void NewFoatingPointVariable_Click(object sender, RoutedEventArgs e) => CreateVariableView(EditorResources.Resources.NameValidator.ValidationType.Double).Show();

        private void NewStringVariable_Click(object sender, RoutedEventArgs e) => CreateVariableView(EditorResources.Resources.NameValidator.ValidationType.String).Show();

        private Windows.CreateGlobalVariableWindow CreateVariableView(Resources.NameValidator.ValidationType validation)
        {
            return new Windows.CreateGlobalVariableWindow(validation)
            {
                Owner = Window.GetWindow(this)
            };
        }

        private uint GetId(ObjectType type)
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

        private void ObjectList_MouseMove(object sender, MouseEventArgs e)
        {
            base.OnMouseMove(e);
            if (e.LeftButton == MouseButtonState.Pressed && ObjectList.SelectedItem != null)
            {
                // Package the data.
                DataObject data = new DataObject();
                ObjectDataViewModel mdl = (ObjectDataViewModel)ObjectList.SelectedItem;
                data.SetData("GameObject", mdl);
                data.SetData("Object", this);

                // Inititate the drag-and-drop operation.
                DragDrop.DoDragDrop(this, data, DragDropEffects.Copy);
            }
        }

        private void NewElement_Click(object sender, RoutedEventArgs e)
        {
            new Windows.ElementType(modName: loadedMod)
            {
                Owner = Window.GetWindow(this)
            }.Show();
        }
    }
    public class ObjectDataViewModel : PropertyNotifier
    {
        private string _origin;
        private uint _id;
        private ObjectFlag _flag;
        private ObjectType _type;
        private BaseDto _value;

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
            get { return Value.Name; }
            private set
            {
                Value.Name = value;
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

        public BaseDto Value
        {
            get { return _value; }
            set
            {
                _value = value;
                NotifyPropertyChanged();
            }
        }

        public ObjectDataViewModel(string origin, uint id, ObjectFlag flag, ObjectType type, BaseDto value)
        {
            Origin = origin;
            Id = id;
            Flag = flag;
            Type = type;
            Value = value;
        }

        public override string ToString()
        {
            return $"{{Origin={Origin}, Id={Id}, Name={Name}, Flag={Flag}, Type={Type}, Value={Value}}}";
        }
    }
}
