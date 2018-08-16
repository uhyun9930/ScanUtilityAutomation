using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
namespace ScanUtility_Automation
{
    class FileTracking : Form
    {

        public delegate void view(string value, string type);
        public view view_event;
        public int num = 0;

        public void InitWatcher()
        {

            System.IO.FileSystemWatcher watcher = new System.IO.FileSystemWatcher();
            watcher.Path = @"C:\Users\Woohyun\Desktop\논병아리";
            watcher.NotifyFilter = System.IO.NotifyFilters.FileName | System.IO.NotifyFilters.DirectoryName | System.IO.NotifyFilters.Size;

            watcher.Changed += new System.IO.FileSystemEventHandler(Watcher_Created);
            watcher.EnableRaisingEvents = true;

        }
        public void Watcher_Created(object sender, System.IO.FileSystemEventArgs e)
        {

            string filePath = System.IO.Path.GetDirectoryName(e.FullPath);
            string fileExe = System.IO.Path.GetExtension(e.FullPath);
            num++;
            System.IO.File.Move(e.FullPath, System.IO.Path.Combine(filePath, "newfil" + num.ToString() + fileExe));

        }
    }

}
