using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace EditorResources.SpriterScene
{
    /// <summary>
    /// Interaction logic for SpriterScene.xaml
    /// </summary>

    using _PointDef = Functionality.OnTextureMapLoadedFromFileEventArgs.Point;
    public partial class SpriterScene : Window
    {
        private OpenFileDialog opf;
        public SpriterScene()
        {
            InitializeComponent();
            opf = new OpenFileDialog()
            {
                InitialDirectory = Directory.GetCurrentDirectory(),

                Title = "Add File",
                Filter = "Spriter XML files|*.scml"
            };
            opf.FileOk += Opf_FileOk;

            addTextureMap.IsEnabled = false;
            removeTextureMap.IsEnabled = false;

            xPos.IsEnabled = false;
            yPos.IsEnabled = false;
            pointWidth.IsEnabled = false;
            pointHeight.IsEnabled = false;
            rotated.IsEnabled = false;
            setPointsFromFile.IsEnabled = false;

            FileSystemWatcher watcher = new FileSystemWatcher();
            watcher.Path = Directory.GetCurrentDirectory() + "/Spriter";
            watcher.Created += Watcher_Created;
            watcher.Deleted += Watcher_Deleted;
            watcher.Renamed += Watcher_Renamed;

            watcher.Filter = "*.scml";
            watcher.NotifyFilter = NotifyFilters.FileName;
            watcher.EnableRaisingEvents = true;
        }

        private void Watcher_Renamed(object sender, RenamedEventArgs e)
        {
            Functionality.EditorEvents.OnLogEvent(new Functionality.EditorLogEventArgs() { logMessage = new Message.Message() { type = Message.Message.MsgType.Info, message = $"{e.OldName} renamed to {e.Name}" } });
        }

        private void Watcher_Deleted(object sender, FileSystemEventArgs e)
        {
            Functionality.EditorEvents.OnLogEvent(new Functionality.EditorLogEventArgs() { logMessage = new Message.Message() { type = Message.Message.MsgType.Info, message = $"{e.Name} deleted" } });
        }

        private void Watcher_Created(object sender, FileSystemEventArgs e)
        {
            Functionality.EditorEvents.OnLogEvent(new Functionality.EditorLogEventArgs() { logMessage = new Message.Message() { type = Message.Message.MsgType.Info, message = $"{e.Name} created" } });
        }

        private void Opf_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (!e.Cancel)
            {
                String str = opf.FileName.Remove(0, Directory.GetCurrentDirectory().Length + 1);
                if (!sceneFilesList.Items.Contains(str))
                {
                    sceneFilesList.Items.Add(str);
                    // Add to events file -> SpriterModelUpdatedArgs(name, removed);
                    //if (onListChange != null)
                    //    onListChange(this, new AddSpriterModel() { Name = str, Remove = false });
                }
                else
                    Functionality.EditorEvents.OnLogEvent(new Functionality.EditorLogEventArgs() {
                        logMessage = new Message.Message()
                        { message = "Spriter Scene file already added", type = Message.Message.MsgType.Info
                        }
                    });
            }
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

        private void removeSpriterSceneFile_Click(object sender, RoutedEventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0)
            {
                //if (onListChange != null)
                //    onListChange(this, new AddSpriterModel() { Name = sceneFilesList.SelectedItems[0].Text, Remove = true });

                //         Program.mg.removeSpriterModel(sceneFilesList.SelectedItems[0].Text);
                sceneFilesList.Items.Remove(sceneFilesList.SelectedItem);
            }
        }

        private void addSpriterSceneFile_Click(object sender, RoutedEventArgs e)
        {
            if(opf.ShowDialog() == true)
            {

            }
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
                    texturemappoints.Add("\\"+iter.Key, p);
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
