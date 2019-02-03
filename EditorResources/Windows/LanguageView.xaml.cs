using EditorResources.Utils;
using System;
using System.Windows;
using System.Linq;
using static EditorResources.Utils.EnumCollection;
using System.Collections.ObjectModel;
using System.Collections.Generic;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for LanguageView.xaml
    /// </summary>
    public partial class LanguageView : Window
    {
        ObservableCollection<Dto.LanguageStringDto> objectList = new ObservableCollection<Dto.LanguageStringDto>();

        public LanguageView()
        {
            InitializeComponent();
            InternalEditorEvents.onRequestObjectDataList += ObjectDataRequested;
            InternalEditorEvents.RequestObjectData();
            EditorEvents.onObjectEvent += OnObjectLoaded;
            EditorEvents.onObjectEvent += OnObjectCreated;
            EditorEvents.onObjectEvent += OnObjectEdited;
            EditorEvents.onObjectEvent += OnObjectDeleted;
            translationStringList.ItemsSource = objectList;
        }

        ~LanguageView()
        {
            InternalEditorEvents.onRequestObjectDataList -= ObjectDataRequested;
            EditorEvents.onObjectEvent -= OnObjectLoaded;
            EditorEvents.onObjectEvent -= OnObjectCreated;
            EditorEvents.onObjectEvent -= OnObjectEdited;
            EditorEvents.onObjectEvent -= OnObjectDeleted;
        }

        private void OnObjectDeleted(object sender, EditorEvents.ObjectEventArgs e)
        {
            if (e.Flag == ObjectFlag.Deleted)
            {
                if(e.Type == ObjectType.TranslationString)
                {
                    objectList.Remove(e.Value as Dto.LanguageStringDto);
                }
                else if (e.Type == ObjectType.LanguageString)
                {
                    Dto.BatchDto dto = e.Value as Dto.BatchDto;
                    foreach (Dto.LanguageStringDto o in dto.DtoList)
                    {
                        objectList.Remove(o);
                    }
                }
                else if (e.Type == ObjectType.TranslationFile)
                {

                }
            }
        }

        private void OnObjectEdited(object sender, EditorEvents.ObjectEventArgs arg)
        {
            if (arg.Flag == ObjectFlag.Edited)
            {
                if (arg.Type == ObjectType.TranslationString)
                {
                    IEnumerable<Dto.LanguageStringDto> enumerable = objectList.Where(x => (x.Language == (arg.Value as Dto.LanguageStringDto).Language && x.ID == arg.Value.ID));
                    foreach (Dto.LanguageStringDto o in enumerable)
                    {
                        o.Value = (arg.Value as Dto.LanguageStringDto).Value;
                    }
                }
            }
        }

        private void OnObjectCreated(object sender, EditorEvents.ObjectEventArgs e)
        {
            if (e.Flag == ObjectFlag.Added)
            {
                if (e.Type == ObjectType.TranslationString)
                {
                    if (e.Value is Dto.BatchDto)
                        foreach (Dto.LanguageStringDto dto in (e.Value as Dto.BatchDto).DtoList)
                            objectList.Add(dto as Dto.LanguageStringDto);
                    else
                    {
                        Dto.LanguageStringDto langstr = e.Value as Dto.LanguageStringDto;
                        e.Value.ID = GetId(langstr.Language, langstr.Filename);
                        objectList.Add(e.Value as Dto.LanguageStringDto);
                    }
                }
            }
        }

        private void OnObjectLoaded(object sender, EditorEvents.ObjectEventArgs arg)
        {
            if (arg.Flag == ObjectFlag.Default)
            {
                if (arg.Type == ObjectType.LanguageString)
                    LanguageFileList.Items.Add(arg.Value);
                if (arg.Type == ObjectType.TranslationString)
                    LanguageFileList.Items.Add(arg.Value);
                if (arg.Type == ObjectType.TranslationFile)
                    LanguageFileList.Items.Add(arg.Value);
            }
        }

        private void Clear()
        {
            LanguageFileList.Items.Clear();
            LanguageList.Items.Clear();
            translationStringList.Items.Clear();
        }

        private IEnumerable<Dto.LanguageStringDto> CreateEmptyStringsFor(string language, string defaultLanguage, string filename)
        {
            List < Dto.LanguageStringDto > langDto = new List<Dto.LanguageStringDto>();
            foreach (Dto.LanguageStringDto dto in objectList.Where(x => x.Filename == filename).Where(x => x.Language == defaultLanguage))
            {
                langDto.Add(new Dto.LanguageStringDto()
                {
                    Language =language,
                    ID =dto.ID,
                    Value =$"{LanguageFileList.SelectedItem.ToString()}:{dto.ID}:{language}:#ERR_INVALID_VALUE",
                    Filename = LanguageFileList.SelectedItem.ToString()
                });
            }
            return langDto;
        }

        private IEnumerable<Dto.LanguageStringDto> CreateEmptyStringsFor(uint id, string languageToIgnore)
        {
            List<Dto.LanguageStringDto> langDto = new List<Dto.LanguageStringDto>();

            foreach (Dto.LanguageFileDto dto in LanguageList.Items)
            {
                if (dto.Filename!= languageToIgnore)
                {

                    langDto.Add(new Dto.LanguageStringDto()
                    {
                        Language = dto.Filename,
                        ID = id,
                        Value = $"{LanguageFileList.SelectedItem.ToString()}:{id}:{dto.Filename}:#ERR_INVALID_VALUE",
                        Filename = LanguageFileList.SelectedItem.ToString()
                    });
                }
            }
            return langDto;
        }

        private string GetAnyDefaultLanguage(string languageToIgnore)
        {
            foreach (Dto.LanguageFileDto dto in LanguageList.Items)
                if (dto.Filename != languageToIgnore)
                    return dto.Filename;
            return string.Empty;
        }

        private uint GetId(string language, string filename)
        {
            uint lastId = 0;
            try
            {
                lastId = objectList.Where(x => x.Filename == filename).Where(x => x.Language == language).Select(x => x.ID).Max();
            }
            catch (ArgumentNullException)
            { }
            catch (InvalidOperationException)
            { }
            finally
            { lastId++; }
            return lastId;
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

        #region Language File
        private void AddLanguageFile_Click(object sender, RoutedEventArgs e)
        {
            string s;
            if ((s = AddObjectNameBox.ShowAndGetResult()) != string.Empty)
            {
                Dto.LanguageFileDto dto = new Dto.LanguageFileDto() {Filename=s};
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

        private void AddLanguageFilePatch_Click(object sender, RoutedEventArgs e)
        {

        }

        #endregion
        #region Language string

        private void AddLanguageButton_Click(object sender, RoutedEventArgs e)
        {
            string s;
            if (LanguageFileList.SelectedItem != null && (s = AddObjectNameBox.ShowAndGetResult()) != string.Empty)
            {
                Dto.LanguageFileDto dto = new Dto.LanguageFileDto() { Filename = s};
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.LanguageString,
                    Value = dto
                });
                LanguageList.Items.Add(dto);

                IEnumerable<Dto.LanguageStringDto> dtoList = CreateEmptyStringsFor(s, GetAnyDefaultLanguage(languageToIgnore: s), LanguageFileList.SelectedItem.ToString());

                Dto.BatchDto batch = new Dto.BatchDto
                {
                    DtoList = dtoList.ToList<Dto.BaseDto>()
                };
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.TranslationString,
                    Value = batch
                });
                InternalEditorEvents.Log($"Added [{batch.DtoList.Count}] strings for language [{s}]", Message.MsgType.Info);
            }
        }

        private void RemoveLanguageButton_Click(object sender, RoutedEventArgs e)
        {
            if(LanguageList.SelectedItem != null && RemoveObjectConfirmBox.ShowAndGetResult(LanguageList.SelectedItem.ToString(),
                "Info: Removing a language will remove all strings associated with that language."))
            {
                Dto.BatchDto batch = new Dto.BatchDto();
                foreach (Dto.LanguageStringDto dto in objectList)
                {
                    if (dto.Language == LanguageList.SelectedItem.ToString())
                    {
                        batch.DtoList.Add(dto as Dto.LanguageStringDto);
                    }
                }
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Deleted,
                    Type = EnumCollection.ObjectType.LanguageString,
                    Value = batch
                });
                LanguageList.Items.Remove(LanguageList.SelectedItem);
            }
        }
        #endregion
        #region Translation string
        private void RemoveTranslationString_Click(object sender, RoutedEventArgs e)
        {
            if(translationStringList.SelectedItem != null && RemoveObjectConfirmBox.ShowAndGetResult(translationStringList.SelectedItem.ToString()))
            {
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Deleted,
                    Type = EnumCollection.ObjectType.TranslationString,
                    Value = translationStringList.SelectedItem as Dto.LanguageStringDto
                });
            }
        }

        private void AddTranslationString_Click(object sender, RoutedEventArgs e)
        {
            string s;
            if (LanguageFileList.SelectedItem != null && LanguageList.SelectedItem != null && (s = AddObjectNameBox.ShowAndGetResult()) != string.Empty)
            {
                Dto.LanguageStringDto dto = new Dto.LanguageStringDto() { Filename = LanguageFileList.SelectedItem.ToString()};
                dto.Value = s;
                dto.Language = LanguageList.SelectedItem.ToString();

                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.TranslationString,
                    Value = dto
                });

                System.Threading.Thread.Sleep(50);

                IEnumerable<Dto.LanguageStringDto> dtoList = CreateEmptyStringsFor(dto.ID, LanguageList.SelectedItem.ToString());

                Dto.BatchDto batch = new Dto.BatchDto
                {
                    DtoList = dtoList.ToList<Dto.BaseDto>()
                };
                EditorEvents.OnObjectEvent(new EditorEvents.ObjectEventArgs()
                {
                    Flag = EnumCollection.ObjectFlag.Added,
                    Type = EnumCollection.ObjectType.TranslationString,
                    Value = batch
                });
                InternalEditorEvents.Log($"Added [{batch.DtoList.Count}] strings for language [{LanguageList.SelectedItem.ToString()}]", Message.MsgType.Info);

            }
        }
        #endregion
    }
}
