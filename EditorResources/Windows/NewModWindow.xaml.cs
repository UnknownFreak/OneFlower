using EditorResources.Functionality;
using EditorResources.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using static EditorResources.Utils.EditorEvents;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for NewMod.xaml
    /// </summary>
    public partial class NewModWindow : Window
    {
        internal static Dictionary<string, ModDependencyList> keyedMods = new Dictionary<string, ModDependencyList>();
        public NewModWindow()
        {
            InitializeComponent();

            CreateList();
            
            modName.Focus();
            EngineEvents.onDependencyListEvent += PopulateDepencenycyList;
        }

        private void CreateList()
        {
            IEnumerable<string> files = Directory.EnumerateFiles("Data").Where(f => f.ToLower().EndsWith("mod") || f.ToLower().EndsWith("main"));
            foreach (string f in files)
                listBox.Items.Add(new BoolString() { IsSelected = false, TheText = f});

            DataContext = keyedMods;
        }

        private void PopulateDepencenycyList(object sender, EngineEvents.DependencyListEventArgs e)
        {
            dependencyView.Items.Clear();
            for (int i =0; i < e.Dependencies.dependencies.Count; i++)
            {
                PopulateInternal(e.Dependencies.dependencies[i],"  ", i == e.Dependencies.dependencies.Count -1);
            }
            if (dependencyView.Items.Count == 0)
                dependencyView.Items.Add(new TextBlock() { Text = "<No Dependency Objects>" });
            if(!keyedMods.ContainsKey(e.Dependencies.Mod))
                keyedMods.Add(e.Dependencies.Mod,e.Dependencies);
        }

        private void PopulateInternal(ModDependencyList depList, string indent = "", bool last = true)
        {
            if(last)
            {
                dependencyView.Items.Add(new TextBlock() { Text = indent + "└─" + depList.Mod, Margin = new Thickness(0, 0, 0, -9), IsHitTestVisible = false });
                indent += "  ";
            }
            else
            {
                dependencyView.Items.Add(new TextBlock() { Text = indent + "├─" + depList.Mod, Margin = new Thickness(0, 0, 0, -9), IsHitTestVisible = false });
                indent += "│ ";
            }
            for (int i = 0; i < depList.dependencies.Count; i++) 
            {
                PopulateInternal(depList.dependencies[i], indent, i == depList.dependencies.Count - 1);
            }
        }

        private void CreateClick(object sender, RoutedEventArgs e) => OnNewModCreate(modName.Text);

        private void OnNewModCreate(String modName)
        {
            ModEventArgs args = new ModEventArgs
            {
                ModName = modName,
                CreateMaster = createMaster.IsChecked.Value,
                Dependencies = (from x in listBox.Items.Cast<BoolString>() where x.IsSelected == true select x.TheText.Split("\\".ToCharArray(), 2)[1]).ToList(),
                Type = ModEventArgs.EventType.Created
            };

            EditorEvents.OnModEvent(args);
            Close();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e) => Close();

        private void CreateMaster_Checked(object sender, RoutedEventArgs e)
        {
            if (createMaster.IsChecked.Value)
                Extension.Content = ".main";
            else
                Extension.Content = ".mod";
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string s = (e.AddedItems[0] as BoolString).TheText;
            if (!keyedMods.ContainsKey(s))
                EditorEvents.OnModEvent(new ModEventArgs() { ModName = s.Split("\\".ToCharArray(), 2)[1] , Type=ModEventArgs.EventType.Selected});
        }

        private class BoolString
        {
            public bool IsSelected { get; set; }
            public string TheText { get; set; }
        }
    }
}
