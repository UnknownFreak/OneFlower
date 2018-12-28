using EditorResources.Utils;
using System;
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
            InternalEditorEvents.onRequestObjectDataList += ObjectDataRequested;
            InternalEditorEvents.RequestObjectData();
        }

        private void Clear()
        {
            LanguageFileList.Items.Clear();
            LanguageList.Items.Clear();
            listView.Items.Clear();
        }

        private void ObjectDataRequested(object sender, InternalEditorEvents.RequestObjectDataListEventArgs e)
        {
            Clear();
            foreach ( var v in e.Observable)
            {
                if(v.Type == EnumCollection.ObjectType.TranslationString)
                {

                }
                else if(v.Type == EnumCollection.ObjectType.TranslationFile)
                {
                    LanguageFileList.Items.Add(v.Value);
                }
            }
        }

        private void OnModLoaded(object sender, EditorEvents.ModEventArgs e)
        {
            if (e.Type == EditorEvents.ModEventArgs.EventType.Loaded)
            {
                InternalEditorEvents.RequestObjectData();
            }
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
            if (LanguageFileList.SelectedItem != null && RemoveObjectConfirmBox.ShowAndGetResult(LanguageFileList.SelectedItem.ToString(),
                "Info: Removing a language file will remove all strings associated with that file."))
            {
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Deleted,
                    Type = EnumCollection.ObjectType.TranslationFile,
                    Value = LanguageFileList.SelectedItem as Dto.LanguageFileDto
                });
                LanguageFileList.Items.Remove(LanguageFileList.SelectedItem);
            }
        }

        private void AddLanguageButton_Click(object sender, RoutedEventArgs e)
        {
            if (LanguageFileList.SelectedItem != null)
            {

            }
        }

        private void RemoveLanguageButton_Click(object sender, RoutedEventArgs e)
        {
            if(LanguageList.SelectedItem != null && RemoveObjectConfirmBox.ShowAndGetResult(LanguageList.SelectedItem.ToString(),
                "Info: Removing a language will remove all strings associated with that language."))
            {
                Dto.BatchDto batch = new Dto.BatchDto();
                foreach (Dto.LanguageStringDto dto in listView.Items)
                {
                    if (dto.Language == LanguageList.SelectedItem.ToString())
                    {
                        batch.DtoList.Add(dto as Dto.LanguageStringDto);
                    }
                }

                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Deleted,
                    Type = EnumCollection.ObjectType.TranslationString,
                    Value = batch
                });
                LanguageFileList.Items.Remove(LanguageFileList.SelectedItem);
            }
        }
    }
}
