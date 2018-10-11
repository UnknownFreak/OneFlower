namespace EditorResources.Dto
{
    public class VeterancyDto : BaseDto
    {
        public bool HideName { get; set; } = false;
        public double BonusHealth { get; set; } = 0.0;
        public double BonusDamage { get; set; } = 0.0;
    }
}
