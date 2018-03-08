using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using static EditorResources.Enums.EnumCollection;
using static EditorResources.Functionality.RequestEvents;
using static EditorResources.Resources.NameValidator;

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
                    OnLogEvent(new EditorLogEventArgs() {
                        logMessage = new Utils.Message() {
                            type = Utils.Message.MsgType.Error, message =$"Invalid value for enum: '{value.ValidateAs}'" }
                    });
                    throw new ValueUnavailableException();
            }
            Functionality.EditorEvents.OnVariableCreatedEvent(new Functionality.OnVariableCreatedEventArgs()
            {
                Name = name.Text,
                VariableType = value.ValidateAs,
                Value = value.Text,
                Type = type });
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
