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
            Functionality.EditorEvents.OnVariableCreatedEvent(new Functionality.OnVariableCreatedEventArgs()
            { Name = name.Text, VariableType = value.ValidateAs, Value = value.Text });
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
