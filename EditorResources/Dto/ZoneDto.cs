using System;
using System.Collections.Generic;

namespace EditorResources.Dto
{
    public class ZoneDto : BaseDto
    {
        public List<ZoneObjectDto> ObjectList { get; set; } = new List<ZoneObjectDto>();
        public String Background { get; set; } = string.Empty;
        public String LoadingScreen { get; set; } = string.Empty;
        public String LoadingScreenMessage { get; set; } = string.Empty;
        public uint ChunkCountX { get; set; } = 0;
        public uint ChunkCountY { get; set; } = 0;

        public List<ChunkDto> ChunkList { get; set; } = new List<ChunkDto>();

        public ZoneDto()
        {
        }
    }
}
