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

namespace NullEditor.Project
{
    public class Project {
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Version { get; set; }
        public EngineConfig @EngineConfig { get; set; }
        public string? Path { get; set; }

    }

    public class ProjectList { public List<Project> Projects = new List<Project>(); }
    internal class ProjectManager : Singleton<ProjectManager>
    {
        private ProjectList projectList = new ProjectList();

        private string projectsFileData = "Projects.json";

        public void CreateProject(Project project)
        {
            projectList.Projects.Add(project);
            SaveProjectList();
        }

        public void SaveProjectList()
        {
            string fileName = projectsFileData;
            string jsonString = JsonSerializer.Serialize(projectList.Projects);
            File.WriteAllText(fileName, jsonString);
        }

        public void LoadProjectList()
        {
            string fileName = projectsFileData;
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
