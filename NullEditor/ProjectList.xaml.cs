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
            UpdateProjectListView();

            ProjectManager.Instance.OnProjectCreated += UpdateProjectListView;
        }

        private void CreateProjectButtonOnClick(object sender, RoutedEventArgs e)
        {
            string projectName = projectNameTextBox.Text;

            if (!Regex.IsMatch(projectName, Global.PROJECT_NAME_REGEX))
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
            string projectFileJson = string.Format("Projects/{0}/{0}.json", projectName);

            Directory.CreateDirectory(string.Format("Projects/{0}", projectName));
            File.Create(projectFileJson);
            FileInfo finfo = new FileInfo(projectFileJson);
            project.Path = finfo.FullName;
            ProjectManager.Instance.CreateProject(project);
            
            //Copy Default project

            //Go To Editor;
        }

        public void UpdateProjectListView()
        {
            // Populate list
            foreach (var item in ProjectManager.Instance.GetProjectList().Projects)
            {
                this.projectListView.Items.Add(item);
            }
            
        }
    }
}
