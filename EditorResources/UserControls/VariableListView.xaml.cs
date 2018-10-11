using EditorResources.Dto;
using EditorResources.Resources;
using EditorResources.Utils;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using static EditorResources.Resources.NameValidator;
using static EditorResources.Utils.EnumCollection;

namespace EditorResources.UserControls
{
    /// <summary>
    /// Interaction logic for VariableListView.xaml
    /// </summary>
    public partial class VariableListView : ListView
    {
        [Category("Editor")]
        public ObjectType Filter
        {
            get => (ObjectType)GetValue(FilterProperty);
            set => SetValue(FilterProperty, value);
        }
        public static readonly DependencyProperty FilterProperty =
        DependencyProperty.Register("Filter",
                                 typeof(ObjectType),
                                 typeof(VariableListView),
                                 new PropertyMetadata(ObjectType.Achievement));

        ObservableCollection<ObjectDataViewModel> objectList = new ObservableCollection<ObjectDataViewModel>();
        
        IEnumerable<ObjectDataViewModel> FilteredSelection => objectList.DefaultIfEmpty().Where(x => x.Type == Filter);
        
        private IEnumerable<ObjectDataViewModel> NOT_SET => new ObservableCollection<ObjectDataViewModel>();

        public VariableListView() : base()
        {
            InitializeComponent();
        }

        private void ListView_Loaded(object sender, RoutedEventArgs e)
        {
            InternalEditorEvents.onRequestObjectDataList += ObjectDataRequested;
            InternalEditorEvents.RequestObjectData();
        }

        private void ObjectDataRequested(object sender, InternalEditorEvents.RequestObjectDataListEventArgs e)
        {
            objectList = e.Observable;
            Dispatcher.Invoke(() => PopulateView());
        }

        private void PopulateView()
        {
            if (objectList.Count != 0)
                ItemsSource = FilteredSelection;
            else
                ItemsSource = NOT_SET;
        }
        private void ListView_Unloaded(object sender, RoutedEventArgs e) => InternalEditorEvents.onRequestObjectDataList -= ObjectDataRequested;

        public void RefreshView(ObjectType filter)
        {
            Filter = filter;
            ListView_Loaded(null, null);
        }

        public IEnumerable<ObjectDataViewModel> GetSelectedItems()
        {
            return SelectedItems.Cast<ObjectDataViewModel>();
        }
    }
}
