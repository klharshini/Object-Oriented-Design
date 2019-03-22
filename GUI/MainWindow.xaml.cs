///////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - GUI for Project3HelpWPF                      //
// ver 1.0                                                           //
// Author : Lakshmi Harshini Kuchibhotla,                            //
//          CSE687 - Object Oriented Design, Spring 2018             //
// Source : Jim Fawcett, CSE687 - Object Oriented Design             //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package provides a WPF-based GUI for Project 4It's 
 * responsibilities are to:
 * - Provide a selection of test requests.
 * - It provides a view to see the selected dlls.
 * - you can modify the test name and the author
 * - you can see the test result files and run them.
 * - see the current status of the test request
 *   
 * Required Files:
 * ---------------
 * Mainwindow.xaml, MainWindow.xaml.cs
 * Translater.dll
 * 
 * Maintenance History:
 * --------------------
 * ver 1/1 : 07 Aug 2018
 * - fixed bug in DirList_MouseDoubleClick by returning when selectedDir is null
 * ver 1.0 : 30 Mar 2018
 * - first release
 * - Several early prototypes were discussed in class. Those are all superceded
 *   by this package.
 */

// Translater has to be statically linked with CommLibWrapper
// - loader can't find Translater.dll dependent CommLibWrapper.dll
using MsgPassingCommunication;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;

namespace WpfApp1
{
    public class FileItem
    {
        public FileItem(String name, string relPath)
        {
            this.Name = name;
            FullPath = relPath;
        }
        public String Name { get; set; }
        public String FullPath { get; set; }
    }

    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public String currentDirectory;
        public String CurrentDirectory { get { return currentDirectory; } set { currentDirectory = value; RaisePropertyChanged("CurrentDirectory"); } }

        public List<String> testRequestNames = new List<String>();

        public ObservableCollection<FileItem> DirectoryList { get; set; }

        public ObservableCollection<FileItem> SelectedList { get; set; }

        public ObservableCollection<String> ResultList { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        private Stack<string> pathStack_ = new Stack<string>();
        private Translater translater;
        private CsEndPoint endPoint_;
        private CsEndPoint serverEndPoint_;
        private Thread rcvThrd = null;
        private String sendFileDir_;

        //----< process incoming messages on child thread >----------------

        private void processMessages()
        {
            ThreadStart thrdProc = () =>
            {
                while (true)
                {
                    CsMessage msg = translater.getMessage();
                    if (msg.attributes.ContainsKey("log") && msg.attributes.ContainsKey("requestName"))
                    {
                        byte[] data = Convert.FromBase64String(msg.value("log"));
                        string decodedString = Encoding.UTF8.GetString(data);
                        string filePath = msg.value("requestName")+ "-result" + ".txt";
                        decodedString = decodedString.Replace("\n", System.Environment.NewLine);
                        using (var streamWriter = File.CreateText(filePath))
                        {
                            streamWriter.Write(decodedString);

                        }
                        this.Dispatcher.Invoke(() =>
                        {
                            TestStatusText.Text += "Test request " + msg.value("requestName") + " executed \n " + "Find the result in -> " + filePath;
                            ResultList.Add(filePath);
                            string[] args = Environment.GetCommandLineArgs();
                            if (args.Length > 1 && args[1] == "INDEMO")
                                Process.Start(filePath);

                        });
                    }
                }
            };
            rcvThrd = new Thread(thrdProc);
            rcvThrd.IsBackground = true;
            rcvThrd.Start();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            CurrentDirectory = System.IO.Directory.GetCurrentDirectory();

            // start Comm
            endPoint_ = new CsEndPoint();
            endPoint_.machineAddress = "localhost";
            endPoint_.port = 8086;
            translater = new Translater();
            translater.listen(endPoint_);

            serverEndPoint_ = new CsEndPoint();
            serverEndPoint_.machineAddress = "localhost";
            serverEndPoint_.port = 8081;

            // start processing messages
            processMessages();

            sendFileDir_ = CurrentDirectory + "\\SendFiles";
            Directory.CreateDirectory(sendFileDir_);
            translater.SetSendFileDirectory(sendFileDir_);
            //test1();
            DirectoryList = new ObservableCollection<FileItem>();
            SelectedList = new ObservableCollection<FileItem>();
            ResultList = new ObservableCollection<String>();
            UpdateDirectoryFiles();
            DirectoryListBox.ItemsSource = DirectoryList;
            SelectedFilesListBox.ItemsSource = SelectedList;
            ResultFilesListBox.ItemsSource = ResultList;
            string[] args = Environment.GetCommandLineArgs();              
            if(args.Length>1 && args[1] == "INDEMO")
                StartDemo();
        }

        async Task PutTaskDelay(int delay)
        {
            await Task.Delay(delay);
        }

        private async void StartDemo()
        {
            TestStatusText.Text += "In Demo " + "\n";
            await PutTaskDelay(2000);
            CurrentDirectory = System.IO.Directory.GetParent(CurrentDirectory).FullName + "\\Debug";
            UpdateDirectoryFiles();
            await PutTaskDelay(2000);
            DirectoryListBox.SelectedIndex =2;
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SelectFile, new object[0]);
            await PutTaskDelay(2000);
            TestNameTextBox.Text = "Time Taking Test";
            await PutTaskDelay(2000);
            AuthorTextBox.Text = "Harshini";
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SendTest, new object[0]);



            DirectoryListBox.SelectedIndex = 0;
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SelectFile, new object[0]);
            await PutTaskDelay(2000);
            TestNameTextBox.Text = "Demo Req";
            await PutTaskDelay(2000);
            AuthorTextBox.Text = "Harshini";
            await PutTaskDelay(2000);
            typeof(System.Windows.Controls.Primitives.ButtonBase).GetMethod("OnClick", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(SendTest, new object[0]);
            await PutTaskDelay(5000);
            //ResultFilesListBox.SelectedIndex = 0;
            //await PutTaskDelay(2000);
            //Process.Start(ResultFilesListBox.SelectedItem.ToString());
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public void SelectFile_Click(object sender, EventArgs e)
        {

            //List<FileItem> tempList = new List<FileItem>(DirectoryListBox.SelectedItems.Count);
            foreach (FileItem item in DirectoryListBox.SelectedItems)
            {
                bool isExisting = false;
                foreach (var selectedFileItem in SelectedList)
                {
                    if (selectedFileItem.Name == item.Name)
                        isExisting = true;
                }
                if (isExisting)
                {
                    System.Windows.Forms.MessageBox.Show("File with same name already exists, please try another file");
                    return;
                }
                SelectedList.Add(item);
            }
            SelectedFilesListBox.ItemsSource = SelectedList;
            DirectoryListBox.SelectedIndex = -1;
        }


        public void DeSelectFile_Click(object sender, EventArgs e)
        {
            List<FileItem> temp = new List<FileItem>();
            foreach (FileItem item in SelectedList)
            {
                temp.Add(item);
            }
            foreach (FileItem item in SelectedFilesListBox.SelectedItems)
            {
                temp.Remove(item);
            }
            SelectedList.Clear();
            temp.ForEach((item) => { SelectedList.Add(item); });
        }

        private void SendTestFiles(List<String> dllFiles)
        {
            foreach (var item in dllFiles)
            {
                CsMessage message = new CsMessage();
                message.add("to", CsEndPoint.toString(serverEndPoint_));
                message.add("from", CsEndPoint.toString(endPoint_));
                message.add("sendingFile", item);
                message.add("name", "DLL File - " + item);
                translater.postMessage(message);
                TestStatusText.Text += "File " + item + " sent \n";
            }
        }

        private void PostTestRequest(String Name, String Author, List<String> dllFiles)
        {
            TestStatusText.Text += "Sending files to server \n";

            SendTestFiles(dllFiles);

            CsMessage message = translater.GetTestRequestMessage(Author, Name, dllFiles);
            message.add("to", CsEndPoint.toString(serverEndPoint_));
            message.add("from", CsEndPoint.toString(endPoint_));
            translater.postMessage(message);
            TestStatusText.Text += "Test request "+ Name +" sent \n";

        }

        private void SelectDirectory_Click(object sender, RoutedEventArgs e)
        {
            using (var fbd = new FolderBrowserDialog())
            {
                fbd.SelectedPath = CurrentDirectory;
                System.Windows.Forms.DialogResult result = fbd.ShowDialog();

                if (result == System.Windows.Forms.DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {
                    CurrentDirectory = fbd.SelectedPath;

                    UpdateDirectoryFiles();
                }
            }
        }

        private void UpdateDirectoryFiles()
        {
            string[] files = System.IO.Directory.GetFiles(this.CurrentDirectory);
            DirectoryList.Clear();
            foreach (string fullFile in files)
            {
                string[] split = fullFile.Split('\\');
                string file = split[split.Length - 1];
                string ext = Path.GetExtension(file);
                if (ext.ToLower() == ".dll")
                {
                    DirectoryList.Add(new FileItem(file, this.CurrentDirectory +"\\" +file));
                }
            }
        }

        private void GetFilesToSendingDirectory()
        {
            foreach (var file in SelectedList)
            {
                File.Copy(file.FullPath, sendFileDir_ + "\\" + file.Name, true);
            }
        }

        private void SendTest_Click(object sender, RoutedEventArgs e)
        {
            String Author = AuthorTextBox.Text.Trim(' ');
            String Name = TestNameTextBox.Text.Trim(' ');
            if (SelectedList.Count < 1 || Author == "" || Name == "")
            {
                System.Windows.Forms.MessageBox.Show("The test request is not complete yet, please verify");
                return;
            }
            if (testRequestNames.Contains(Name))
            {
                System.Windows.Forms.MessageBox.Show("A Request with the same name is already executed, please choose a unique name.");
                return;
            }
            TestStatusText.Text += "Copying files to send \n";
            GetFilesToSendingDirectory();
            

            List<String> dlls = new List<string>();
            foreach (var item in SelectedList)
            {
                dlls.Add(item.Name);
            }
            PostTestRequest(Name, Author, dlls);
            SelectedList.Clear();
            testRequestNames.Add(Name);
        }

        private void ListBoxItem_MouseDoubleClick(object sender, RoutedEventArgs e)
        {

            if (ResultFilesListBox.SelectedItem != null)
            {
                Process.Start(ResultFilesListBox.SelectedItem.ToString());
            }

        }
    }
}
