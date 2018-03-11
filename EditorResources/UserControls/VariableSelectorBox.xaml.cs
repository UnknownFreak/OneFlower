using EditorResources.Functionality;
using EditorResources.UserControls;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
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

        public ObjectType Filter { get { return (DataContext as ObjectTypeNotifier).Value; } set { (DataContext as ObjectTypeNotifier).Value = value; } }
        public ViewType ViewAs { get { return (DataContext as ObjectTypeNotifier).ViewAs; } set { (DataContext as ObjectTypeNotifier).ViewAs = value; } }

        private IEnumerable<String> NOT_SET { get { return null; } }

        public enum ViewType
        {
            Name,
            ModOriginAndID,
        }

        public VariableSelectorBox() : base()
        {
            InitializeComponent();
        }

        private void objectDataRequested(object sender, InternalEditorEvents.RequestObjectDataListEventArgs e)
        {
            objectList = e.Observable;
        }

        private void ComboBox_Loaded(object sender, System.Windows.RoutedEventArgs e)
        {
            InternalEditorEvents.onRequestObjectDataList += objectDataRequested;
            InternalEditorEvents.RequestObjectData();
        }

        private void ComboBox_DropDownOpened(object sender, EventArgs e)
        {
            populateView();
        }

        private void populateView()
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
            populateView();
            SelectedIndex = (ItemsSource as IEnumerable<String>).ToList().FindIndex(x => x == valueToSelect);
            if (SelectedIndex == -1)
                InternalEditorEvents.Log($"Value: {valueToSelect} not found in the view.", Utils.Message.MsgType.Error);
        }
    }
    public class ObjectTypeNotifier : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        ObjectType _type = ObjectType.Unknown;
        VariableSelectorBox.ViewType _view = VariableSelectorBox.ViewType.ModOriginAndID;

        string _text = string.Empty;

        public ObjectType Value { get { return _type; } set { _type = value; PropertyChanged(this, new PropertyChangedEventArgs("Value")); } }
        internal VariableSelectorBox.ViewType ViewAs { get { return _view; } set { _view = value; PropertyChanged(this, new PropertyChangedEventArgs("ViewAs")); } }
        public String Text { get { return _text; } set { _text = value; PropertyChanged(this, new PropertyChangedEventArgs("Text")); } }

    }
}
