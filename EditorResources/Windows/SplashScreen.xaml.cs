using System.Windows;

namespace EditorResources.Windows
{
    /// <summary>
    /// Interaction logic for SplashScreen.xaml
    /// </summary>
    public partial class SplashScreen : Window
    {
        public SplashScreen()
        {
            InitializeComponent();
        }
        public void setProgressValue(double percent)
        {
            InitBar.Value = percent;
        }
        public bool isFullyInitialized()
        {
            return InitBar.Value == InitBar.Maximum;
        }
    }
}
