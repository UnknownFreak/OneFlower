using EditorResources.UserControls;
using EditorResources.Utils;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for ElementType.xaml
    /// </summary>
    public partial class ElementType : Window
    {
        string modName = string.Empty;
        ObservableCollection<ElementAttributeModifier> objectItems = new ObservableCollection<ElementAttributeModifier>();

        public ElementType(string modName)
        {
            InitializeComponent();
            this.modName = modName;
            ElementAttributes.ItemsSource = objectItems;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            List<Dto.ElementTypeDto.ElementAttributeDto> attributes = new List<Dto.ElementTypeDto.ElementAttributeDto>();

            foreach (ElementAttributeModifier attr in objectItems)
            {
                attributes.Add(new Dto.ElementTypeDto.ElementAttributeDto() { Name = attr.Name, ID = attr.Id, Origin = attr.Origin, Modifier = attr.Modifier });
            }

            EditorEvents.OnObjectEvent(
                new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.Element,
                    Value = new Dto.ElementTypeDto()
                    {
                        Name = ElementName.Text,
                        IconName = ElementIcon.Text,
                        ElementAttribute = attributes,
                        DamageToUnknownType = double.Parse(DamageToUnknownType.Text),
                        Origin = modName
                    }
                }
            );
            Close();
        }

        private void RemoveAttributeButton_Click(object sender, RoutedEventArgs e)
        {
            if(ElementAttributes.SelectedItem != null)
            {
                ElementAttributes.Items.Remove(ElementAttributes.SelectedItem);
            }
        }

        private void AddAttributeButton_Click(object sender, RoutedEventArgs e)
        {
            VariableListSelectorWindow wnd = new VariableListSelectorWindow(EnumCollection.ObjectType.Element);
            bool? b = wnd.ShowDialog();
            if(b.Value)
            {
                IEnumerable<ObjectDataViewModel> selectedItems = wnd.Selected;
            }
        }
    }
    public class ElementAttributeModifier : PropertyNotifier
    {
        private string _origin;
        private uint _id;
        private string _name;
        private double _modifier;
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
        public double Modifier
        {
            get { return _modifier; }
            private set
            {
                _modifier = value;
                NotifyPropertyChanged();
            }
        }

        public ElementAttributeModifier(string origin, uint id, string name, double modifier)
        {
            Origin = origin;
            Id = id;
            Name = name;
            Modifier = modifier;
        }
    }
}
