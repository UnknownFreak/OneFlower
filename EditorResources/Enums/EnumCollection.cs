using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EditorResources.Enums
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
            Zone,
            Unknown,
        }
    }
}
