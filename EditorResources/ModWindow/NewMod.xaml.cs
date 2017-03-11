using EditorResources.Functionality;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace EditorResources.ModWindow
{
    /// <summary>
    /// Interaction logic for NewMod.xaml
    /// </summary>
    public partial class NewMod : Window
    {
        internal static Dictionary<string, ModDependencyList> keyedMods = new Dictionary<string, ModDependencyList>();
        public NewMod()
        {
            InitializeComponent();

            createList();
            
            modName.Focus();
            EditorEvents.engineOnModSelectedLoaded += PopulateDepencenycyList;
        }

        private void createList()
        {
            IEnumerable<string> files = Directory.EnumerateFiles("Data").Where(f => f.ToLower().EndsWith("mod") || f.ToLower().EndsWith("main"));
            foreach (string f in files)
                listBox.Items.Add(new BoolString() { IsSelected = false, TheText = f});

            DataContext = keyedMods;
        }

        private void PopulateDepencenycyList(object sender, EngineOnModSelectedLoadedEventArgs e)
        {
            dependencyView.Items.Clear();
            foreach (ModDependencyList l in e.Dependencies.dependencies)
            {
                dependencyView.Items.Add(new TextBlock() { Text = l.Mod });
                populateInternal(l.dependencies);
            }
            if (dependencyView.Items.Count == 0)
                dependencyView.Items.Add(new TextBlock() { Text = "<No Dependency Objects>" });
            if(!keyedMods.ContainsKey(e.Dependencies.Mod))
                keyedMods.Add(e.Dependencies.Mod,e.Dependencies);
        }

        private void populateInternal(List<ModDependencyList> list, int indent = 1)
        {
            foreach (ModDependencyList l in list)
            {
                dependencyView.Items.Add(new TextBlock() { Text = new String('-', indent) + ' ' + l.Mod });
                populateInternal(l.dependencies, indent+1);
            }
        }

        private void createClick(object sender, RoutedEventArgs e)
        {
            OnNewModCreate(modName.Text);
        }

        private void OnNewModCreate(String modName)
        {
            NewModCreateEventArgs args = new NewModCreateEventArgs();
            args.modName = modName;
            args.createMaster = createMaster.IsChecked;
            args.dependencies = (from x in listBox.Items.Cast<BoolString>() where x.IsSelected == true select x.TheText).ToList();
           
            EditorEvents.OnModCreate(args);
            Close();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void createMaster_Checked(object sender, RoutedEventArgs e)
        {
            bool? chked = createMaster.IsChecked;
            if ((bool)chked)
                Extension.Content = ".main";
            else
                Extension.Content = ".mod";
        }

        private void listBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string s = (e.AddedItems[0] as BoolString).TheText;
            if (keyedMods.ContainsKey(s))
                EditorEvents.EngineOnModSelectedLoaded(new EngineOnModSelectedLoadedEventArgs() { Dependencies = keyedMods[s] });
            else
                EditorEvents.OnModSelected(new ModFileSelectedEventArgs() { fileName = s });
        }

        private class BoolString
        {
            public bool IsSelected { get; set; }
            public string TheText { get; set; }
        }
    }
}
