using System;
using System.ComponentModel;
using System.Reflection;

namespace EditorResources.Utils
{
    public static class EnumCollection
    {
        public enum ObjectFlag
        {
            Added,
            Default,
            Deleted,
            Edited,
            None
        }

        public enum ObjectType
        {
            Achievement,
            BoolVariable,
            DoubleVariable,
            GameObject,
            IntVariable,
            Item,
            ListVariable,
            Model,
            Quest,
            StringVariable,
            Sound,
            TextureMap,
            Trigger,
            TranslationString,
            Zone,
            Veterancy,
            Element,
            Unknown,
        }

        public enum ViewType
        {
            Name,
            ModOriginAndID,
        }

        public enum BrushType
        {
            [Description("None")]
            None,
            [Description("No Collider")]
            No_Collider,
            [Description("Box Collider")]
            Box_Collider,
            [Description("Left Slope")]
            Slope_Left,
            [Description("Right Slope")]
            Slope_Right,
            [Description("Jump Trough")]
            Jump_Trough,
            [Description("Can Fall Trough")]
            Can_Fall_Trough,
        }
        public static string GetDescription<T>(this T enumerationValue) where T : struct
        {
            Type type = enumerationValue.GetType();
            if (!type.IsEnum)
            {
                throw new ArgumentException("EnumerationValue must be of Enum type", "enumerationValue");
            }

            //Tries to find a DescriptionAttribute for a potential friendly name
            //for the enum
            MemberInfo[] memberInfo = type.GetMember(enumerationValue.ToString());
            if (memberInfo != null && memberInfo.Length > 0)
            {
                object[] attrs = memberInfo[0].GetCustomAttributes(typeof(DescriptionAttribute), false);

                if (attrs != null && attrs.Length > 0)
                {
                    //Pull out the description value
                    return ((DescriptionAttribute)attrs[0]).Description;
                }
            }
            //If we have no description attribute, just return the ToString of the enum
            return enumerationValue.ToString();
        }
    }
}
