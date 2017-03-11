using System;
using System.Collections.Generic;

namespace EditorResources.ModWindow
{
    public class ModDependencyList
    {
        public List<ModDependencyList> dependencies { get; set; }
        public String Mod { get; set; }
        public ModDependencyList()
        {
            dependencies = new List<ModDependencyList>();
        }
    }
}
