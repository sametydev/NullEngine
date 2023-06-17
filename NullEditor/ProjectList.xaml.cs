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
#pragma warning disable CS8604

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
            foreach (var item in ProjectManager.Instance.GetProjectList().ProjectListItems)
            {
                this.projectListView.Items.Add(item);
            }
        }
        void OpenEditor(Project.ProjectListItem projectList)
        {
            this.Hide();
            EditorWindow.EditorWindow editorWindow = new EditorWindow.EditorWindow(
                ProjectManager.Instance.GetProjectFromPath(projectList.Path)
                );
            editorWindow.Show();
        }
        private void OnProjectCreated(Project.ProjectListItem project) => OpenEditor(project);

        private void ProjectListItemClick(object sender, MouseButtonEventArgs e)
        {
            var item = (sender as ListViewItem);
            if (item != null && item.IsSelected)
            {

                Project.ProjectListItem project = (Project.ProjectListItem)item.Content;

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
