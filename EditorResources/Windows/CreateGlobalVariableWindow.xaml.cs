using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using static EditorResources.Utils.EnumCollection;
using static EditorResources.Utils.InternalEditorEvents;
using static EditorResources.Resources.NameValidator;
using EditorResources.Dto;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for GlobalVarialeView.xaml
    /// </summary>
    public partial class CreateGlobalVariableWindow : Window
    {

        public CreateGlobalVariableWindow()
        {
            InitializeComponent();
            name.Text = string.Empty;
            value.Text = string.Empty;
        }

        public CreateGlobalVariableWindow(ValidationType type) : this()
        {
            value.ValidateAs = type;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            ObjectType type;
            switch (value.ValidateAs)
            {
                case ValidationType.Double:
                    type = ObjectType.DoubleVariable;
                    break;
                case ValidationType.Int:
                    type = ObjectType.IntVariable;
                    break;
                case ValidationType.String:
                    type = ObjectType.StringVariable;
                    break;
                default:
                    Log($"Invalid value for enum: '{value.ValidateAs}'", Utils.Message.MsgType.Error);
                    throw new ValueUnavailableException();
            }
            Utils.EditorEvents.OnObjectEvent(new Utils.EditorEvents.ObjectEventArgs()
            {
                Flag = ObjectFlag.Added,
                Value = new VariableDto() { Value = value.Text, Name=name.Text },
                Type = type
            });
            Close();
        }

        private void cancelButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void value_Error(object sender, ValidationErrorEventArgs e)
        {
            var v = e.Error.BindingInError as BindingExpression;
            
            if (e.Action == ValidationErrorEventAction.Added)
                create.IsEnabled = false;
            else if (e.Action == ValidationErrorEventAction.Removed && !v.HasError)
                create.IsEnabled = true;
            e.Handled = true;
        }
    }
}
