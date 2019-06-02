using System;

namespace EditorResources.Dto
{
    public class BaseDto
    {
        public string Origin { get; set; } = string.Empty;
        public Guid ID { get; set; } = Guid.NewGuid();
        public string Name { get; set; } = string.Empty;
    }
}
