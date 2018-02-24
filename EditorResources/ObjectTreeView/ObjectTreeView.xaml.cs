using EditorResources.Functionality;
using System.Windows;
using System.Windows.Controls;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows.Media;

namespace EditorResources.ObjectView
{
    /// <summary>
    /// Interaction logic for ObjectTreeView.xaml
    /// </summary>
    public partial class ObjectTreeView : UserControl
    {

        ObservableCollection<ObjectDataViewModel> objectItems = new ObservableCollection<ObjectDataViewModel>();
        string loadedMod = "";
        public ObjectTreeView()
        {
            InitializeComponent();
            EditorEvents.onModFinishedLoading += OnModLoaded;
            EditorEvents.onOVariableCreatedEvent += OnVariableCreated;
            treeView.IsEnabled = false;
            ObjectList.ItemsSource = objectItems;
        }

        private void OnVariableCreated(object sender, OnVariableCreatedEventArgs e)
        {
            // This method is registered before any other event so we can set the mod origin here.
            e.Origin = loadedMod;
            e.ID = getId(e.Type);
            objectItems.Add(new ObjectDataViewModel(e.Origin, e.ID, e.Name, 
                ObjectDataViewModel.ObjectFlag.Added, e.Type, e.Value));
        }

        public void OnObjectLoaded(OnObjectLoadEventArgs arg)
        {
        }

        private void OnModLoaded(object sender, ModFinishedLoadedEventArgs args)
        {
            loadedMod = args.modName;
            treeView.IsEnabled = true;
        }

        private void NewIntegerVariable_Click(object sender, RoutedEventArgs e)
        {
            var window = new GlobalVariableView.GlobalVariableView(EditorResources.Resources.NameValidator.ValidationType.Int);
            window.Owner = Window.GetWindow(this);
            window.Show();
        }

        private void NewFoatingPointVariable_Click(object sender, RoutedEventArgs e)
        {
            var window = new GlobalVariableView.GlobalVariableView(EditorResources.Resources.NameValidator.ValidationType.Double);
            window.Owner = Window.GetWindow(this);
            window.Show();
        }

        private void NewStringVariable_Click(object sender, RoutedEventArgs e)
        {
            var window = new GlobalVariableView.GlobalVariableView(EditorResources.Resources.NameValidator.ValidationType.String);
            window.Owner = Window.GetWindow(this);
            window.Show();
        }

        private uint getId(BaseObjectEventArgs.ObjectType type)
        {
            uint lastId = 0;
            try
            {
                lastId = objectItems.Where(x => x.Type == type).Select(x => x.Id).Max();
            }
            catch (System.ArgumentNullException)
            { }
            catch (System.InvalidOperationException)
            { }
            finally
            { lastId++; }
            return lastId;
        }
    }
    internal class ObjectDataViewModel : INotifyPropertyChanged
    {
        private string _origin;
        private uint _id;
        private string _name;
        private ObjectFlag _flag;
        private BaseObjectEventArgs.ObjectType _type;
        private string _value;

        public Brush brush { get; set; }

        public string Origin
        {
            get { return _origin; }
            private set
            {
                _origin = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Origin"));
            }
        }
        public uint Id
        {
            get { return _id; }
            private set
            {
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
        public ObjectFlag Flag
        {
            get { return _flag; }
            set
            {
                _flag = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Flag"));
            }
        }

        public BaseObjectEventArgs.ObjectType Type
        {
            get { return _type; }
            set
            {
                _type = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Type"));
            }
        }

        public string Value
        {
            get { return _value; }
            set
            {
                _value = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Value"));
            }
        }

        public ObjectDataViewModel(string origin, uint id, string name, ObjectFlag flag, BaseObjectEventArgs.ObjectType type, string value)
        {
            Origin = origin;
            Id = id;
            Name = name;
            Flag = flag;
            Type = type;
            Value = value;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        internal enum ObjectFlag
        {
            Added,
            Deleted,
            Edited,
            None
        }
    }
}
