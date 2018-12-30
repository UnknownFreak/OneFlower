namespace EditorResources.Dto
{
    public class LanguageStringDto : BaseDto
    {
        public string Value { get; set; }
        public string Filename { get; set; }
        public string Language { get; set; }

        public override string ToString() => $"Value={Value}, Filename={Filename}, Language={Language}";
    }

    public class LanguageFileDto : BaseDto
    {
        public string Filename { get; set; }

        public override string ToString() => Filename;
    }
}
