using NullEditor.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.IO;
using System.Text.Json.Serialization;
using NullEditor.Engine;
using System.Windows;
using System.Runtime.Serialization;

namespace NullEditor.Project
{
    [Serializable]public class Project {
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Version { get; set; }
        public EngineConfig @EngineConfig { get; set; }
        public string? Path { get; set; }

    }

    [Serializable]public class ProjectList {
        public List<Project> Projects { get; set; } = new List<Project>();
    }
    internal class ProjectManager : Singleton<ProjectManager>
    {
        public ProjectManager() { LoadProjectList(); }
        private ProjectList projectList = new ProjectList();

        private string projectsFileData = "Projects.json";
        
        public ProjectList GetProjectList() => projectList;


        //Events;
        public event Action? OnProjectCreated;

        public void CreateProject(Project project)
        {
            projectList.Projects.Add(project);
            SaveProjectList();

            OnProjectCreated.Invoke();
        }

        public void SaveProjectList()
        {
            string fileName = projectsFileData;
            string jsonString = JsonSerializer.Serialize<ProjectList>(projectList);
            File.WriteAllText(fileName, jsonString);
        }

        public void LoadProjectList()
        {
            string fileName = projectsFileData;
            if (!File.Exists(fileName)) return;
            string jsonString = File.ReadAllText(fileName);
            projectList = JsonSerializer.Deserialize<ProjectList>(jsonString)!;
        }

        public void UpdateProjectList()
        {
            projectList.Projects.Clear();

            LoadProjectList();
        }

    }
}
