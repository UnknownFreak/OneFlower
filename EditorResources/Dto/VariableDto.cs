namespace EditorResources.Dto
{
    public class VariableDto : BaseDto
    {
        public string Value { get; set; } = string.Empty;

        public new string ToString()
        {
            return Value;
        }
    }
}
