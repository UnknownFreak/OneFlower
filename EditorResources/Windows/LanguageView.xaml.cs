using EditorResources.Utils;
using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for LanguageView.xaml
    /// </summary>
    public partial class LanguageView : Window
    {
        public LanguageView()
        {
            InitializeComponent();
        }

        private void AddLanguageFile_Click(object sender, RoutedEventArgs e)
        {
            string s;
            if ((s = AddObjectNameBox.ShowAndGetResult()) != string.Empty)
            {
                Dto.LanguageFileDto dto = new Dto.LanguageFileDto() {Filename=s, Name="",Origin="NotUsed"};
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.TranslationFile,
                    Value = dto
                });
                LanguageFileList.Items.Add(dto);
            }
        }

        private void RemoveLanguageFile_Click(object sender, RoutedEventArgs e)
        {
            if (LanguageFileList.SelectedItem != null && RemoveObjectConfirmBox.ShowAndGetResult(LanguageFileList.SelectedItem.ToString()))
            {
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Deleted,
                    Type = EnumCollection.ObjectType.TranslationFile,
                    Value = LanguageFileList.SelectedItem as Dto.LanguageStringDto
                });
                LanguageFileList.Items.Remove(LanguageFileList.SelectedItem);
            }
        }
    }
}
