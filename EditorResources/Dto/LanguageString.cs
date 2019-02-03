namespace EditorResources.Dto
{
    public class LanguageStringDto : BaseDto
    {
        public string Value { get; set; }
        public string Filename { get; set; }
        public string Language { get; set; }
        public string Font { get; set; }

        public new string Origin { get { return Filename; } set { Filename = value; } }
        public new string Name { get { return Value; } set { Value = value; } }

        public override string ToString() => $"Value={Value}, Filename={Filename}, Language={Language}";
    }

    public class LanguageFileDto : BaseDto
    {
        public string Filename { get; set; }

        public new string Origin { get { return Filename; } set { Filename = value; } }

        public override string ToString() => Filename;
    }
}
