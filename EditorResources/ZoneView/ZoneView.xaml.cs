using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using EditorResources.Functionality;

namespace EditorResources.ZoneView
{
    /// <summary>
    /// Interaction logic for ZoneView.xaml
    /// </summary>
    public partial class ZoneView : UserControl
    {
        public ZoneView()
        {
            InitializeComponent();
            EditorEvents.onModFinishedLoading += ZoneViewOnModFinishedLoading;
        }

        private void ZoneViewOnModFinishedLoading(object sender, ModFinishedLoadedEventArgs e)
        {
            ZoneSelector.Items.Clear();
            foreach(var t in e.zoneFiles)
            {
                ZoneSelector.Items.Add(new ZoneItem(t.Item1, t.Item2, t.Item3));
            }
        }
    }

    internal class ZoneItem
    {
        public string Origin { get; private set; }
        public uint Id { get; private set; }
        public string Name { get; private set; }

        public ZoneItem(string origin, uint id, string name)
        {
            Origin = origin;
            Id = id;
            Name = name;
        }
        void Rename(string newName)
        {
            Name = newName;
        }
    }
}
