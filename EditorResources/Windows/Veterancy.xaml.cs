using EditorResources.Utils;
using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for Veterancy.xaml
    /// </summary>
    public partial class Veterancy : Window
    {
        string modName = string.Empty;
        public Veterancy(string modName)
        {
            InitializeComponent();
            this.modName = modName;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            EditorEvents.OnObjectEvent(
                new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.Veterancy,
                    Value = new Dto.VeterancyDto()
                    {
                        Name = NameTextBox.Text,
                        HideName = (bool)HideRankName.IsChecked,
                        BonusDamage = double.Parse(BonusDamage.Text),
                        BonusHealth = double.Parse(BonusHealth.Text),
                        Origin = modName,
                    }
                });
        }
    }
}
