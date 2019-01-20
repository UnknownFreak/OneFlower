using System.Collections.Generic;
using System.Windows.Media;

namespace EditorResources.Dto
{
    public class BaseDto
    {
        public string Origin { get; set; } = string.Empty;
        public uint ID { get; set; } = 0;
        public string Name { get; set; } = string.Empty;

        public Brush brush { get; set; }
    }

    public class BatchDto : BaseDto
    {
        public List<BaseDto> DtoList { get; set; } = new List<BaseDto>();
    }
}
