using System;
using System.Collections;
using System.Reflection;
using System.Windows.Forms;

namespace EditorResources.Resources
{
    public static class IDataObjectExtension
    {

        public static T GetObject<T>(this DataObject obj, string objectName)
        {
            object o = typeof(DataObject).GetField("innerData", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(obj);
            object o2 = o.GetType().GetField("innerData", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(o);
            object o3 = o2.GetType().GetField("_innerData", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(o2);
            Hashtable o4 = (Hashtable)o3.GetType().GetField("_data", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(o3);
            object o5 = ((Array)o4[objectName]).GetValue(0);
            return (T)o5.GetType().GetField("_data", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(o5);
        }
    }
}
