using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Diagnostics;
namespace BaseEditor.SpriterScene
{
  
    public partial class SpriterScene : UserControl
    {
        ManagedGame.TextureMapPointStruct ps;
        public event EventHandler<AddSpriterModel> onListChange = null;
        public SpriterScene()
        {
            ps = new ManagedGame.TextureMapPointStruct();
            InitializeComponent();
            openFileDialog1.InitialDirectory = Directory.GetCurrentDirectory();
            addTextureMap.Enabled = false;
            removeTextureMap.Enabled = false;
            xPos.Enabled = false;
            yPos.Enabled = false;
            width.Enabled = false;
            height.Enabled = false;
            rotated.Enabled = false;
            button1.Enabled = false;
        }
        public void init()
        {
            sceneFilesList.Items.Clear();
            List<String> list = Program.mg.getSceneFiles();
            foreach (var item in list)
            {
                sceneFilesList.Items.Add(item, item);
                if(onListChange != null)
                    onListChange(this, new AddSpriterModel() { Name = item, Remove = false });
            }
        }
        private void addSpriterSceneFile_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            textureMapPoints.Items.Clear();
            if (TextureMap.SelectedItem != null)
            {
                if (TextureMap.SelectedItem.ToString() == "DEFAULT, Default")
                {
                    removeTextureMap.Enabled = false;
                    panel3.Enabled = false;
                    button1.Enabled = false;
                }
                else
                {
                    removeTextureMap.Enabled = true;
                    panel3.Enabled = true;
                    button1.Enabled = true;
                }
                if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null)
                {
                    String []splitted = TextureMap.SelectedItem.ToString().Split(',');
                    splitted[1] = splitted[1].Remove(0, 1);
                    var v = Program.mg.getTextureMapPoints(sceneFilesList.SelectedItems[0].Text, splitted[0], splitted[1]);
                    foreach (var item in v)
                    {
                        String[] itms = { item.Key, item.Value.pos.Item1.ToString(),item.Value.pos.Item2.ToString(), 
                                        item.Value.size.Item1.ToString(),item.Value.size.Item2.ToString()
                                        , item.Value.rotated.ToString(), item.Value.r.ToString(), item.Value.g.ToString()
                                        , item.Value.b.ToString()};
                        textureMapPoints.Items.Add(new ListViewItem(itms, 0));
                    }
                }
            }
        }

        private void sceneFilesList_SelectedIndexChanged(object sender, EventArgs e)
        {
            TextureMap.Items.Clear();
            if (sceneFilesList.SelectedItems.Count != 0)
            {
                TextureMap.Items.AddRange(Program.mg.getTextureMaps(sceneFilesList.SelectedItems[0].Text).ToArray());
                addTextureMap.Enabled = true;
                removeTextureMap.Enabled = true;
            }
            else
            {
                addTextureMap.Enabled = false;
                removeTextureMap.Enabled = false;
                textureMapPoints.Items.Clear();
                TextureMap.SelectedItem = null;
            }
        }

        private void addTextureMap_Click(object sender, EventArgs e)
        {
            AddAttachmentPoint pt = new AddAttachmentPoint(true);
            pt.onAdd += pt_onAdd;
            pt.ShowDialog(this);
        }

        void pt_onAdd(object sender, AttachmentPointsEventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0)
            {
                Program.mg.addTextureMap(sceneFilesList.SelectedItems[0].Text, e.Name);
                TextureMap.Items.Add(Program.mg.getLoadedMod()+ ", "+ e.Name);
            }
        }

        private void removeTextureMap_Click(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null)
            {
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);
                Program.mg.removeTextureMap(sceneFilesList.SelectedItems[0].Text, splitted[0],splitted[1]);
                TextureMap.Items.Remove(TextureMap.SelectedItems[0]);
            }
        }

        private void removeSpriterSceneFile_Click(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0)
            {
                if (onListChange != null)
                    onListChange(this, new AddSpriterModel() { Name = sceneFilesList.SelectedItems[0].Text, Remove = true });
                Program.mg.removeSpriterModel(sceneFilesList.SelectedItems[0].Text);
                sceneFilesList.Items.RemoveByKey(sceneFilesList.SelectedItems[0].Text);
            }
        }
        private void textureMapPoints_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (textureMapPoints.SelectedItems.Count != 0)
            {
                xPos.Enabled = true;
                yPos.Enabled = true;
                width.Enabled = true;
                height.Enabled = true;
                rotated.Enabled = true;

                pointName.Text = textureMapPoints.SelectedItems[0].SubItems[0].Text;
                xPos.Value = System.Convert.ToDecimal(textureMapPoints.SelectedItems[0].SubItems[1].Text);
                yPos.Value = System.Convert.ToDecimal(textureMapPoints.SelectedItems[0].SubItems[2].Text);
                width.Value = System.Convert.ToDecimal(textureMapPoints.SelectedItems[0].SubItems[3].Text);
                height.Value = System.Convert.ToDecimal(textureMapPoints.SelectedItems[0].SubItems[4].Text);
                rotated.Checked = System.Convert.ToBoolean(textureMapPoints.SelectedItems[0].SubItems[5].Text);
            }
            else
            {
                xPos.Enabled = false;
                yPos.Enabled = false;
                width.Enabled = false;
                height.Enabled = false;
                rotated.Enabled = false;
            }
        }

        private void xPos_ValueChanged(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null && textureMapPoints.SelectedItems.Count != 0)
            {
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);
                textureMapPoints.SelectedItems[0].SubItems[1].Text = xPos.Value.ToString();

                ps.pos = new Tuple<int,int>((int)xPos.Value, ps.pos.Item2);

                Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                    splitted[0], splitted[1],
                    textureMapPoints.SelectedItems[0].SubItems[0].Text,
                    ps);
            }
        }

        private void yPos_ValueChanged(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null && textureMapPoints.SelectedItems.Count != 0)
            {
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);
                textureMapPoints.SelectedItems[0].SubItems[2].Text = yPos.Value.ToString();

                ps.pos = new Tuple<int, int>(ps.pos.Item1, (int)yPos.Value);

                Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                    splitted[0], splitted[1],
                    textureMapPoints.SelectedItems[0].SubItems[0].Text,
                    ps);
            }
        }

        private void rotated_CheckedChanged(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null && textureMapPoints.SelectedItems.Count != 0)
            {
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);
                textureMapPoints.SelectedItems[0].SubItems[5].Text = rotated.Checked.ToString();

                ps.rotated = rotated.Checked;

                Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                        splitted[0], splitted[1],
                        textureMapPoints.SelectedItems[0].SubItems[0].Text,
                        ps);
            }
        }

        private void width_ValueChanged(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null && textureMapPoints.SelectedItems.Count != 0)
            {
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);
                textureMapPoints.SelectedItems[0].SubItems[3].Text = width.Value.ToString();

                ps.size = new Tuple<int, int>((int)width.Value, ps.size.Item2);

                Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                    splitted[0], splitted[1],
                    textureMapPoints.SelectedItems[0].SubItems[0].Text,
                    ps);
            }
        }

        private void height_ValueChanged(object sender, EventArgs e)
        {
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null && textureMapPoints.SelectedItems.Count != 0)
            {
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);
                textureMapPoints.SelectedItems[0].SubItems[4].Text = height.Value.ToString();

                ps.size = new Tuple<int, int>(ps.size.Item1, (int)height.Value);
                Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                    splitted[0], splitted[1],
                    textureMapPoints.SelectedItems[0].SubItems[0].Text,
                    ps);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog opf = new OpenFileDialog();
            opf.InitialDirectory = Directory.GetCurrentDirectory();
            opf.Filter = "JSON file|*.json";
            opf.Multiselect = false;
            opf.ShowDialog(this);
            if (sceneFilesList.SelectedItems.Count != 0 && TextureMap.SelectedItem != null)
            {

                String str = opf.FileName.Remove(0, Directory.GetCurrentDirectory().Length + 1);
                String[] splitted = TextureMap.SelectedItem.ToString().Split(',');
                splitted[1] = splitted[1].Remove(0, 1);

                StreamReader sr = new StreamReader(str);

                Queue<String> lines = new Queue<string>();
                String line;
                while((line = sr.ReadLine()) != null)
                {
                    lines.Enqueue(line);
                }
                TexturePoints pts = ParseJson(lines);
                Console.WriteLine("woop");
                foreach (var iter in pts.frames)
                {
                    ps.pos = new Tuple<int, int>(iter.Value.frame.x, iter.Value.frame.y);
                    ps.size = new Tuple<int, int>(iter.Value.frame.w, iter.Value.frame.h);
                    ps.rotated = iter.Value.rotated;
                    Program.mg.setPointPosition(sceneFilesList.SelectedItems[0].Text,
                    splitted[0], splitted[1],
                    "\\"+iter.Key,
                    ps);
                }
                var v = Program.mg.getTextureMapPoints(sceneFilesList.SelectedItems[0].Text, splitted[0], splitted[1]);
                textureMapPoints.Items.Clear();
                foreach (var item in v)
                {
                    String[] itms = { item.Key, item.Value.pos.Item1.ToString(),item.Value.pos.Item2.ToString(), 
                                        item.Value.size.Item1.ToString(),item.Value.size.Item2.ToString()
                                        , item.Value.rotated.ToString(), item.Value.r.ToString(), item.Value.g.ToString()
                                        , item.Value.b.ToString()};
                    textureMapPoints.Items.Add(new ListViewItem(itms, 0));
                }
            }
        }
        private TexturePoints ParseJson(Queue<String> jsonQueue)
        {
            TexturePoints pts = new TexturePoints();
            String line = jsonQueue.Dequeue();
            while(!line.Contains("}"))
            {
                if(line.Contains("{"))
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
            if(line.Contains("frames") && line.Contains("{"))
            {
                pts.frames = ParseFrames(jsonQueue);
            }
            while(!line.Contains("meta"))
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
            while(!line.Contains("}"))
            {
                if(line.Contains("app"))
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
                if(line.Contains("h"))
                    p.Y = System.Convert.ToInt32(line.Split(':')[1].Split(',')[0]);
                else if(line.Contains("w"))
                    p.X = System.Convert.ToInt32(line.Split(':')[1]);
                line = jsonQueue.Dequeue();
            }
            return p;
        }

        private Dictionary<String, Frame> ParseFrames(Queue<string> jsonQueue)
        {
            Dictionary<String, Frame> frames = new Dictionary<string, Frame>();
            String line = jsonQueue.Dequeue();
            while(!line.Contains("}"))
            {
                String key = line.Split('"')[1];
                while(!line.Contains("{"))
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
                if(line.Contains("frame"))
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

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            if (!e.Cancel)
            {
                String str = openFileDialog1.FileName.Remove(0, Directory.GetCurrentDirectory().Length + 1);
                if (!sceneFilesList.Items.ContainsKey(str))
                {
                    sceneFilesList.Items.Add(str, str, 0);
                    sceneFilesList.Update();
                    if (onListChange != null)
                        onListChange(this, new AddSpriterModel() { Name = str, Remove = false });
                }
                else
                    Program.messages.addInfoMessage("File already added.");
            }
        }
        class TexturePoints
        {
            public Dictionary<String, Frame> frames = new Dictionary<string,Frame>();
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
    public class AddSpriterModel : EventArgs
    {
        public String Name { get; set; }
        public Boolean Remove { get; set; }
    }
}
