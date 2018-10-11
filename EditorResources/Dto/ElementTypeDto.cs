using System.Collections.Generic;

namespace EditorResources.Dto
{
    public class ElementTypeDto : BaseDto
    {
        public string IconName { get; set; }
        public double DamageToUnknownType { get; set; }
        public List<ElementAttributeDto> ElementAttribute { get; set; } = new List<ElementAttributeDto>();

        public class ElementAttributeDto : BaseDto
        {
            public double Modifier { get; set; }
        }
    }
}
