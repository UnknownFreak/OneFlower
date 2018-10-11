using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using static EditorResources.Utils.EditorEvents;

namespace EditorResources.SpriterScene
{
    /// <summary>
    /// Interaction logic for SpriterScene.xaml
    /// </summary>

    using _PointDef = Functionality.OnTextureMapLoadedFromFileEventArgs.Point;
    public partial class SpriterScene : Window
    {
        public class NameField
        {
            private ObservableCollection<NameField> _textureMaps = new ObservableCollection<NameField>();
            // This is a filename string it will be unique.
            public string FileName { get; set; }

            public ObservableCollection<NameField> textureMaps { get { return _textureMaps; } set { _textureMaps = value; } }

            public override bool Equals(Object obj)
            {
                // Check for null values and compare run-time types.
                if (obj == null || GetType() != obj.GetType())
                    return false;

                NameField p = (NameField)obj;
                return (FileName == p.FileName);
            }
            public override int GetHashCode()
            {
                return FileName.GetHashCode();
            }
        }
        private const string spriterFolder = "/Spriter";
        private string cwd;
        private FileSystemWatcher watcher;
        private ObservableCollection<NameField> spriterFiles;
        public SpriterScene()
        {
            InitializeComponent();

            cwd = Directory.GetCurrentDirectory();

            spriterFiles = new ObservableCollection<NameField>();

            addTextureMap.IsEnabled = false;
            removeTextureMap.IsEnabled = false;

            xPos.IsEnabled = false;
            yPos.IsEnabled = false;
            pointWidth.IsEnabled = false;
            pointHeight.IsEnabled = false;
            pointName.IsEnabled = false;
            rotated.IsEnabled = false;
            setPointsFromFile.IsEnabled = false;

            InitializeWatcher();
            PopulateView();

            sceneFilesList.ItemsSource = spriterFiles;
            sceneFilesList.IsSynchronizedWithCurrentItem = true;
            TextureMap.IsSynchronizedWithCurrentItem = true;

        }

        private void InitializeWatcher()
        {
            watcher = new FileSystemWatcher();

            watcher.IncludeSubdirectories = true;
            watcher.Path = cwd + spriterFolder;
            watcher.Created += Watcher_Created;
            watcher.Deleted += Watcher_Deleted;
            watcher.Renamed += Watcher_Renamed;

            watcher.Filter = "*.scml";
            watcher.NotifyFilter = NotifyFilters.FileName;
            watcher.EnableRaisingEvents = true;
        }
        private void PopulateView()
        {
            string path = cwd + spriterFolder;
            foreach (string s in Directory.GetFiles(path, "*.scml", SearchOption.AllDirectories))
                spriterFiles.Add(new NameField() { FileName = s.Remove(0, path.Length + 1) });
        }

        private void Watcher_Renamed(object sender, RenamedEventArgs e)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                string path = cwd + spriterFolder;
                NameField oldField = new NameField() { FileName = e.OldFullPath.Remove(0, path.Length) };
                if (spriterFiles.Contains(oldField))
                    spriterFiles.Remove(oldField);
                spriterFiles.Add(new NameField() { FileName = e.FullPath.Remove(0, path.Length) });

            }));
        }

        private void Watcher_Deleted(object sender, FileSystemEventArgs e)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                string path = cwd + spriterFolder;
                spriterFiles.Remove(new NameField() { FileName = e.FullPath.Remove(0, path.Length) });
            }));
        }

        private void Watcher_Created(object sender, FileSystemEventArgs e)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                string path = cwd + spriterFolder;
                spriterFiles.Add(new NameField() { FileName = e.FullPath.Remove(0, path.Length) });
            }));
        }

        private TexturePoints ParseJson(Queue<String> jsonQueue)
        {
            TexturePoints pts = new TexturePoints();
            String line = jsonQueue.Dequeue();
            while (!line.Contains("}"))
            {
                if (line.Contains("{"))
                {
                    pts = ParseRoot(jsonQueue);
                }
                line = jsonQueue.Dequeue();
            }
            return pts;
        }
        private TexturePoints ParseRoot(Queue<String> jsonQueue)
        {
            TexturePoints pts = new TexturePoints();
            String line = jsonQueue.Dequeue();
            while (!line.Contains("frames"))
                line = jsonQueue.Dequeue();
            if (line.Contains("frames") && line.Contains("{"))
            {
                pts.frames = ParseFrames(jsonQueue);
            }
            while (!line.Contains("meta"))
                line = jsonQueue.Dequeue();
            if (line.Contains("meta") && line.Contains("{"))
            {
                pts.meta = ParseMeta(jsonQueue);
            }
            return pts;
        }

        private Meta ParseMeta(Queue<string> jsonQueue)
        {
            Meta meta = new Meta();

            String line = jsonQueue.Dequeue();
            while (!line.Contains("}"))
            {
                if (line.Contains("app"))
                    meta.app = line.Split('"')[3];
                else if (line.Contains("format"))
                    meta.format = line.Split('"')[3];
                else if (line.Contains("image"))
                    meta.image = line.Split('"')[3];
                else if (line.Contains("scale"))
                    meta.scale = System.Convert.ToInt32(line.Split(':')[1].Split(',')[0]);
                else if (line.Contains("size"))
                    meta.size = parseSize(jsonQueue);
                else if (line.Contains("version"))
                    meta.version = line.Split('"')[3];
                line = jsonQueue.Dequeue();
            }
            return meta;
        }

        private Point parseSize(Queue<string> jsonQueue)
        {
            Point p = new Point();
            String line = jsonQueue.Dequeue();
            while (!line.Contains("}"))
            {
                if (line.Contains("h"))
                    p.Y = System.Convert.ToInt32(line.Split(':')[1].Split(',')[0]);
                else if (line.Contains("w"))
                    p.X = System.Convert.ToInt32(line.Split(':')[1]);
                line = jsonQueue.Dequeue();
            }
            return p;
        }

        private Dictionary<String, Frame> ParseFrames(Queue<string> jsonQueue)
        {
            Dictionary<String, Frame> frames = new Dictionary<string, Frame>();
            String line = jsonQueue.Dequeue();
            while (!line.Contains("}"))
            {
                String key = line.Split('"')[1];
                while (!line.Contains("{"))
                    line = jsonQueue.Dequeue();
                if (line.Contains("{"))
                {
                    Frame frame = parseFrame(jsonQueue);
                    frames.Add(key, frame);
                }
                line = jsonQueue.Dequeue();
            }
            return frames;
        }

        private Frame parseFrame(Queue<string> jsonQueue)
        {
            Frame f = new Frame();
            String line = jsonQueue.Dequeue();
            while (!line.Contains("}"))
            {
                if (line.Contains("frame"))
                    f.frame = ParseFrameSize(jsonQueue);
                else if (line.Contains("rotated"))
                    f.rotated = System.Convert.ToBoolean(line.Split('"')[3]);
                else if (line.Contains("sourceSize"))
                    f.sourceSize = parseSize(jsonQueue);
                else if (line.Contains("spriteSourceSize"))
                    f.spriteSourceSize = ParseFrameSize(jsonQueue);
                else if (line.Contains("trimmed"))
                    f.trimmed = System.Convert.ToBoolean(line.Split('"')[3]); ;
                line = jsonQueue.Dequeue();
            }
            return f;
        }

        private FrameSize ParseFrameSize(Queue<string> jsonQueue)
        {
            FrameSize framesize = new FrameSize();
            String line = jsonQueue.Dequeue();
            while (!line.Contains("}"))
            {
                if (line.Contains("h"))
                {
                    framesize.h = System.Convert.ToInt32(line.Split(':')[1].Split(',')[0]);
                }
                else if (line.Contains("w"))
                {
                    framesize.w = System.Convert.ToInt32(line.Split(':')[1].Split(',')[0]);
                }
                else if (line.Contains("x"))
                    framesize.x = System.Convert.ToInt32(line.Split(':')[1].Split(',')[0]);
                else if (line.Contains("y"))
                    framesize.y = System.Convert.ToInt32(line.Split(':')[1]);
                line = jsonQueue.Dequeue();
            }
            return framesize;
        }

        private void setPointsFromFile_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog()
            {
                InitialDirectory = Directory.GetCurrentDirectory(),
                Filter = "JSON file|*.json",
                Multiselect = false
            };
            opf.ShowDialog();
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null && opf.ShowDialog() == true)
            {

                String str = opf.FileName.Remove(0, Directory.GetCurrentDirectory().Length + 1);
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);

                StreamReader sr = new StreamReader(str);

                Queue<String> lines = new Queue<string>();
                String line;
                while ((line = sr.ReadLine()) != null)
                {
                    lines.Enqueue(line);
                }
                TexturePoints pts = ParseJson(lines);
                Dictionary<string, _PointDef> texturemappoints = new Dictionary<string, _PointDef>();
                foreach (var iter in pts.frames)
                {
                    _PointDef p = new _PointDef()
                    {
                        X = iter.Value.frame.x,
                        Y = iter.Value.frame.y,
                        W = iter.Value.frame.w,
                        H = iter.Value.frame.h,
                        Rotated = iter.Value.rotated
                    };
                    texturemappoints.Add("\\" + iter.Key, p);
                    //Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                    //splitted[0], splitted[1],
                    //"\\"+iter.Key,
                    //ps);
                }
                //var v = Program.mg.getTextureMapPoints(sceneFilesList.SelectedItems[0].Text, splitted[0], splitted[1]);
                //textureMapPoints.Items.Clear();
                //foreach (var item in v)
                //{
                //    String[] itms = { item.Key, item.Value.pos.Item1.ToString(),item.Value.pos.Item2.ToString(), 
                //                        item.Value.size.Item1.ToString(),item.Value.size.Item2.ToString()
                //                        , item.Value.rotated.ToString(), item.Value.r.ToString(), item.Value.g.ToString()
                //                        , item.Value.b.ToString()};
                //    textureMapPoints.Items.Add(new ListViewItem(itms, 0));
                //}
            }
        }

        private void sceneFilesList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count != 0)
            {
                NameField nf = e.AddedItems[0] as NameField;

                OnLogEvent(new EditorLogEventArgs() { logMessage = new Utils.Message() { message = nf.FileName,
                    type = Utils.Message.MsgType.Info } });
                addTextureMap.IsEnabled = true;
                TextureMap.ItemsSource = nf.textureMaps;
            }
            else
            {
                TextureMap.ItemsSource = null;
                addTextureMap.IsEnabled = false;
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            watcher.Dispose();
        }

        private void addTextureMap_Click(object sender, RoutedEventArgs e)
        {
            NameField nf = sceneFilesList.SelectedItem as NameField;
            nf.textureMaps.Add(new NameField() { FileName = "New Item" });
        }
    }
    class TexturePoints
    {
        public Dictionary<String, Frame> frames = new Dictionary<string, Frame>();
        public Meta meta;
    }
    class Meta
    {
        public String app;
        public String format;
        public String image;
        public int scale;
        public Point size;
        public String version;
    }
    class FrameSize
    {
        public int w, h, x, y;
    }
    class Frame
    {
        public FrameSize frame;
        public bool rotated;
        public Point sourceSize;
        public FrameSize spriteSourceSize;
        public bool trimmed;
    }
}
