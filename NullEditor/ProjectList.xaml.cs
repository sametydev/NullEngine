using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Text.RegularExpressions;
using NullEditor.Project;
using System.IO;

namespace NullEditor
{

    public partial class ProjectList : Window
    {
        public ProjectList()
        {
            InitializeComponent();
            
        }

        private void CreateProjectButtonOnClick(object sender, RoutedEventArgs e)
        {
            string projectName = projectNameTextBox.Text;

            if (!Regex.IsMatch(projectName, "^[a-zA-Z0-9]*$"))
            {
                MessageBox.Show("Project Name Contains Spaces or Special Characters!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            Project.Project project = new Project.Project();
            project.Name = projectName;
            project.Description = "A NullEngine Project";
            project.Version = Global.ENGINE_VERSION;

            //If Projects Directory is not exists!
            if (!Directory.Exists("Projects"))
            {
                Directory.CreateDirectory("Projects");
            }
            //If project exists from disk not memory
            if (File.Exists(string.Format("Projects/{0}.json",projectName)))
            {
                MessageBox.Show("Project Exists on Disk!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            //If everything is ok;
            File.Create(string.Format("Projects/{0}.json", projectName));
            //Copy Default Template of Project (In Future)
            //File.Copy()

            //Go To Editor;
        }
    }
}
