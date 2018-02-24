using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using static EditorResources.Resources.NameValidator;

namespace EditorResources.GlobalVariableView
{
    /// <summary>
    /// Interaction logic for GlobalVarialeView.xaml
    /// </summary>
    public partial class GlobalVariableView : Window
    {

        public GlobalVariableView()
        {
            InitializeComponent();
            name.Text = "";
            value.Text = "";
        }

        public GlobalVariableView(ValidationType type)
        {
            InitializeComponent();
            value.ValidateAs = type;
            name.Text = "";
            value.Text = "";
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Functionality.BaseObjectEventArgs.ObjectType type;
            switch (value.ValidateAs)
            {
                case ValidationType.Double:
                    type = Functionality.BaseObjectEventArgs.ObjectType.DoubleVariable;
                    break;
                case ValidationType.Int:
                    type = Functionality.BaseObjectEventArgs.ObjectType.IntVariable;
                    break;
                case ValidationType.String:
                    type = Functionality.BaseObjectEventArgs.ObjectType.StringVariable;
                    break;
                default:
                    Functionality.EditorEvents.OnLogEvent(new Functionality.EditorLogEventArgs() {
                        logMessage = new Message.Message() {
                            type = Message.Message.MsgType.Error, message =$"Invalid value for enum {value.ValidateAs}" }
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
