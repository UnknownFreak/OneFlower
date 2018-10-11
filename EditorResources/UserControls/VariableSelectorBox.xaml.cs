using EditorResources.Utils;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using static EditorResources.Utils.EnumCollection;

namespace EditorResources.UserControls
{
    /// <summary>
    /// Interaction logic for VariableSelectorBox.xaml
    /// </summary>
    public partial class VariableSelectorBox : ComboBox
    {
        ObservableCollection<ObjectDataViewModel> objectList = new ObservableCollection<ObjectDataViewModel>();

        IEnumerable<String> FilteredSelection => objectList.DefaultIfEmpty().Where(x => x.Type == Filter).Select(x => ViewAs== ViewType.Name ? x.Name : $"{x.Origin},{x.Id}");

        [Category("Editor")]
        public ObjectType Filter
        {
            get { return (ObjectType)GetValue(FilterProperty); }
            set { SetValue(FilterProperty, value); }
        }
        public static readonly DependencyProperty FilterProperty =
        DependencyProperty.Register("Filter",
                                 typeof(ObjectType),
                                 typeof(VariableSelectorBox),
                                 new PropertyMetadata(ObjectType.Unknown));
        [Category("Editor")]
        public ViewType ViewAs
        {
            get { return (ViewType)GetValue(ViewTypeProperty); }
            set { SetValue(ViewTypeProperty, value); }
        }
        public static readonly DependencyProperty ViewTypeProperty =
        DependencyProperty.Register("ViewAs",
                                 typeof(ViewType),
                                 typeof(VariableSelectorBox),
                                 new PropertyMetadata(ViewType.Name));

        private IEnumerable<String> NOT_SET { get { return null; } }

        public VariableSelectorBox() : base()
        {
            InitializeComponent();
        }

        private void ObjectDataRequested(object sender, InternalEditorEvents.RequestObjectDataListEventArgs e)
        {
            objectList = e.Observable;
        }

        private void ComboBox_Loaded(object sender, System.Windows.RoutedEventArgs e)
        {
            InternalEditorEvents.onRequestObjectDataList += ObjectDataRequested;
            InternalEditorEvents.RequestObjectData();
        }

        private void ComboBox_DropDownOpened(object sender, EventArgs e)
        {
            PopulateView();
        }

        private void PopulateView()
        {
            if (objectList.Count != 0)
                ItemsSource = FilteredSelection;
            else
                ItemsSource = NOT_SET;
        }

        public void TrySelect(string valueToSelect)
        {
            if (string.IsNullOrEmpty(valueToSelect))
            {
                InternalEditorEvents.Log($"Value: '{valueToSelect}' was null or empty. Keeping previous value.", Utils.Message.MsgType.Info);
                return;
            }
            PopulateView();
            SelectedIndex = (ItemsSource as IEnumerable<String>).ToList().FindIndex(x => x == valueToSelect);
            if (SelectedIndex == -1)
                InternalEditorEvents.Log($"Value: {valueToSelect} not found in the view.", Utils.Message.MsgType.Error);
        }

        private void ComboBox_Unloaded(object sender, System.Windows.RoutedEventArgs e)
        {
            InternalEditorEvents.onRequestObjectDataList -= ObjectDataRequested;
        }
    }
}
