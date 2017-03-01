using EditorResources.Functionality;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace EditorResources.ModWindow
{
    /// <summary>
    /// Interaction logic for NewMod.xaml
    /// </summary>
    public partial class NewMod : Window
    {
        public NewMod()
        {
            InitializeComponent();
        }

        private void createClick(object sender, RoutedEventArgs e)
        {
            OnNewModCreate(modName.Text);
        }

        private void OnNewModCreate(String modName)
        {
            NewModCreateEventArgs args = new NewModCreateEventArgs();
            args.modName = modName;
            args.createMaster = createMaster.IsChecked;
            EditorEvents.OnModCreate(args);
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void createMaster_Checked(object sender, RoutedEventArgs e)
        {
            bool? chked = createMaster.IsChecked;
            if ((bool)chked)
                Extension.Content = ".main";
            else
                Extension.Content = ".mod";
        }
    }
}
