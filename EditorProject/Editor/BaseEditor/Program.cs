using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using ManagedGame;
using System.Threading;
using BaseEditor.Editor;
using System.IO;
namespace BaseEditor
{
    static class Program
    {
        public static Thread mainDrawThread;
        public static ManagedGame.ManagedGame mg;

        public static DragNDropWindow renderWindow;
        public static RenderAreaControls renderControls;

        public static DragNDropWindow itemCreator;
        public static ItemCreator creatorField;

        public static DragNDropWindow messageWindow;
        public static MessageWindow messages;

        public static DragNDropWindow objectViewWindow;
        public static ObjectArea objectView;

        public static DragNDropWindow prefabCreator;
        public static PrefabCreator prefabField;

        public static DragNDropWindow questCreator;
        public static QuestCreator questCreatorField;

        public static DragNDropWindow zoneViewWindow;
        public static zonefield zoneView;

        public static DragNDropWindow spriterSceneWindow;
        public static SpriterScene.SpriterScene spriterScene;

        public static MainEditorWindow main;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

        	String str = Directory.GetCurrentDirectory();
		    str = str.Replace("EditorProject\\Editor\\BaseEditor\\bin\\Debug","");
		    Directory.SetCurrentDirectory(str);

            main = new MainEditorWindow();
            main.loadMod("Demo.main");
            mainDrawThread.Start();
            Application.Run(main);
        }
    }
}
