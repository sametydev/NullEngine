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
using NullEditor.Engine;
using NullEditor.Other;

namespace NullEditor
{

    public partial class ProjectList : Window
    {
        public ProjectList()
        {
            InitializeComponent();
            UpdateProjectListView();

            ProjectManager.Instance.OnProjectCreated += UpdateProjectListView;
            ProjectManager.Instance.OnProjectListLoaded += UpdateProjectListView;
        }

        private void CreateProjectButtonOnClick(object sender, RoutedEventArgs e)
        => ProjectManager.Instance.CreateProjectOnDisk(projectNameTextBox.Text);

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
