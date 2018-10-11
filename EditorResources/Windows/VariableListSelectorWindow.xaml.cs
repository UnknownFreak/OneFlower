using EditorResources.UserControls;
using EditorResources.Utils;
using System.Collections.Generic;
using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class VariableListSelectorWindow : Window
    {
        public IEnumerable<ObjectDataViewModel> Selected { get; set; } = new List<ObjectDataViewModel>();

        public VariableListSelectorWindow(EnumCollection.ObjectType filterType) : base()
        {
            InitializeComponent();
            ListView.RefreshView(filterType);
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            Selected = ListView.GetSelectedItems();
            Close();
        }
    }
}
