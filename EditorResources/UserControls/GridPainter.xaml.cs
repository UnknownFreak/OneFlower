using EditorResources.Utils;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace EditorResources.UserControls
{
    /// <summary>
    /// Interaction logic for GridPainter.xaml
    /// </summary>
    public partial class GridPainter : UserControl
    {
        List<EnumCollection.BrushType> brushTypes = new List<EnumCollection.BrushType>();

        EnumCollection.BrushType selectedBrush = EnumCollection.BrushType.None;
        string selectedTexture = string.Empty;
        string selectedMode = string.Empty;

        public GridPainter()
        {
            InitializeComponent();
            LoadBrushTextures();
            TileDrawType.ItemsSource = brushTypes;
            brushTypes.Add(EnumCollection.BrushType.None);
            brushTypes.Add(EnumCollection.BrushType.No_Collider);
            brushTypes.Add(EnumCollection.BrushType.Box_Collider);
            brushTypes.Add(EnumCollection.BrushType.Slope_Left);
            brushTypes.Add(EnumCollection.BrushType.Slope_Right);
            brushTypes.Add(EnumCollection.BrushType.Jump_Trough);
            brushTypes.Add(EnumCollection.BrushType.Can_Fall_Trough);
            TileDrawType.SelectedIndex = 0;
        }

        private void LoadBrushTextures()
        {
            foreach (string file in Directory.EnumerateFiles(Directory.GetCurrentDirectory() + "/Data/Textures/Tiles"))
            {
                BrushSelector.Items.Add(new Image() { Source = new BitmapImage(uriSource: new Uri(file)), Stretch = Stretch.None});
            }
            BrushSelector.SelectedIndex = 0;
        }

        private void PaintType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            selectedMode = (PaintType.SelectedItem as Image).Name;
            SendBrushChangedEvent();
            e.Handled = true;
        }

        private void TileDrawType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            selectedBrush = brushTypes[TileDrawType.SelectedIndex];
            SendBrushChangedEvent();
            e.Handled = true;
        }

        private void BrushSelector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            selectedTexture = ((BrushSelector.SelectedItem as Image).Source as BitmapImage).UriSource.OriginalString;
            selectedTexture = selectedTexture.Split('\\')[selectedTexture.Split('\\').Length-1];
            SendBrushChangedEvent();
            e.Handled = true;
        }

        private void SendBrushChangedEvent()
        {
            EditorEvents.OnBrushChangedEvent(new EditorEvents.BrushEventArgs() { PaintMode = selectedMode, Brush = selectedBrush, Texture = selectedTexture });
        }
    }

    [ValueConversion(typeof(object), typeof(EnumCollection.BrushType))]
    public class StringFormatConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter,
                          CultureInfo culture)
        {
            bool b = Enum.TryParse(value.ToString(), true, out EnumCollection.BrushType t);
            if (b)
                return t.GetDescription();
            return null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return null;
        }
    }
}
