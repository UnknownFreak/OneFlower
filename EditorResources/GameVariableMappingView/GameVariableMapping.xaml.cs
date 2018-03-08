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
            engineOnSendVariableMapping += EnigineOnSendAnimationVariableSubscriber;

            OnRequestGameVariableMappingVariable(new GameVariableMappingEventArgs() {VariableToRequest = GameVariableMappingEventArgs.Variable.Animation});
            OnRequestGameVariableMappingVariable(new GameVariableMappingEventArgs() {VariableToRequest = GameVariableMappingEventArgs.Variable.MainMenu});
            OnRequestGameVariableMappingVariable(new GameVariableMappingEventArgs() {VariableToRequest = GameVariableMappingEventArgs.Variable.StartingZone});

        }

        private void EnigineOnSendAnimationVariableSubscriber(object sender, VariableMappingEventArgs e)
        {
            if (e.GetType() == typeof(AnimationVariableMappingEventArgs))
                AssignAnimationVariable(e as AnimationVariableMappingEventArgs);
        }

        private void AssignAnimationVariable(AnimationVariableMappingEventArgs args)
        {
            AnimationVariableName.TrySelect(args.AnimationVariable);
        }
    }
}
