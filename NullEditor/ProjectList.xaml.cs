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

            ProjectManager.Instance.OnProjectCreated += OnProjectCreated;
            ProjectManager.Instance.OnProjectListLoaded += UpdateProjectListView;
        }



        private void CreateProjectButtonOnClick(object sender, RoutedEventArgs e)
        => ProjectManager.Instance.CreateProjectOnDisk(projectNameTextBox.Text);

        //Callbacks;
        public void UpdateProjectListView()
        {
            // Populate list
            foreach (var item in ProjectManager.Instance.GetProjectList().Projects)
            {
                this.projectListView.Items.Add(item);
            }
        }
        void OpenEditor(Project.Project project)
        {
            this.Hide();
            EditorWindow.EditorWindow editorWindow = new EditorWindow.EditorWindow(project);
            editorWindow.Show();
        }
        private void OnProjectCreated(Project.Project project) => OpenEditor(project);

        private void ProjectListItemClick(object sender, MouseButtonEventArgs e)
        {
            var item = (sender as ListViewItem);
            if (item != null && item.IsSelected)
            {

                Project.Project project = (Project.Project)item.Content;

                OpenEditor(project);
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            Application.Current.Shutdown();
        }
    }
}
