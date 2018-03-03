using System.Windows;
using EditorResources.Functionality;
using static EditorResources.Functionality.EngineEvents;
using static EditorResources.Functionality.RequestEvents;

namespace EditorResources.GameVariableMappingView
{
    /// <summary>
    /// Interaction logic for GameVariableMapping.xaml
    /// </summary>
    public partial class GameVariableMapping : Window
    {
        public GameVariableMapping()
        {
            InitializeComponent();
            RequestEvents.OnRequestGameVariableMappingVariable(new GameVariableMappingEventArgs() {VariableToRequest = GameVariableMappingEventArgs.Variable.Animation});
            RequestEvents.OnRequestGameVariableMappingVariable(new GameVariableMappingEventArgs() {VariableToRequest = GameVariableMappingEventArgs.Variable.MainMenu});
            RequestEvents.OnRequestGameVariableMappingVariable(new GameVariableMappingEventArgs() {VariableToRequest = GameVariableMappingEventArgs.Variable.StartingZone});

            EngineEvents.engineOnSendVariableMapping += enigineOnSendAnimationVariableSubscriber;
        }

        private void enigineOnSendAnimationVariableSubscriber(object sender, VariableMappingEventArgs e)
        {
            if (e.GetType() == typeof(AnimationVariableMappingEventArgs))
                assignAnimationVariable(e as AnimationVariableMappingEventArgs);
        }

        private void assignAnimationVariable(AnimationVariableMappingEventArgs args)
        {
            AnimationVariableName.Text = args.AnimationVariable;
        }
    }
}
