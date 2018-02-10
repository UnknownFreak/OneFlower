using System;
using System.ComponentModel;
using System.Windows.Controls;
using static EditorResources.Resources.NameValidator;

namespace EditorResources.Resources
{
    /// <summary>
    /// Interaction logic for ValidatedTextBox.xaml
    /// </summary>
    public partial class ValidatedTextBox : TextBox
    {
        public ValidationType ValidateAs { get { return (DataContext as ValidateNotifier).Value; } set { (DataContext as ValidateNotifier).Value = value; } }
        public ValidatedTextBox() : base()
        {
            InitializeComponent();
        }
    }

    public class ValidateNotifier : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        ValidationType _type = ValidationType.String;
        
        string _text = "";

        public ValidationType Value { get { return _type; } set { _type= value; PropertyChanged(this, new PropertyChangedEventArgs("Value")); } }
        public String Text { get { return _text; } set { _text = value; PropertyChanged(this, new PropertyChangedEventArgs("Text")); } }

    }
}
