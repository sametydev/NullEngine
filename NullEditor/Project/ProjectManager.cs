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
using NullEditor.Other;
using System.Text.RegularExpressions;
using System.Diagnostics.CodeAnalysis;

#pragma warning disable CS8604

namespace NullEditor.Project
{
    [Serializable]public class Project {
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Version { get; set; }
        public EngineConfig @EngineConfig { get; set; }
        public string? Path { get; set; }

    }

    [Serializable] public class ProjectListItem
    {
        public string? Name { get; set; }
        public string? Description { get; set; }
        public string? Version { get; set; }
        public string? Path { get; set; }
    }

    

    [Serializable]public class ProjectList {
        public List<ProjectListItem> ProjectListItems { get; set; } = new List<ProjectListItem>();
    }

    internal class ProjectManager : Singleton<ProjectManager>
    {

        public ProjectManager() { LoadProjectList(); }

        //public List<Project> mProjects = new List<Project>();

        private ProjectList projectList = new ProjectList();

        private string projectsFileData = "Projects.json";
        
        public ProjectList GetProjectList() => projectList;


        //Events;
        public event Action<ProjectListItem>? OnProjectCreated;
        public event Action? OnProjectListLoaded;
        public event Action? OnProjectListSaved;

        public void CreateProject(ProjectListItem projectListItem)
        {
            projectList.ProjectListItems.Add(projectListItem);

            SaveProjectList();

            OnProjectCreated?.Invoke(projectListItem);
        }

        public void CreateProjectOnDisk(string ProjectName)
        {
            string projectName = ProjectName;

            if (!Regex.IsMatch(projectName, Global.PROJECT_NAME_REGEX))
            {
                Helper.MessageError("Project Name Contains Spaces or Special Characters!");
                return;
            }

            //Creating Project on Memory
            Project project = new Project();
            project.Name = projectName;
            project.Description = "A NullEngine Project";
            project.Version = Global.ENGINE_VERSION;

            //If Projects Directory is not exists!
            if (!Directory.Exists("Projects"))
            {
                Directory.CreateDirectory("Projects");
            }
            string projectFileJson = Helper.GenerateProjectPath(projectName);
            //If project exists from disk not memory
            if (File.Exists(projectFileJson))
            {
                Helper.MessageError("Project Exists on Disk!");
                return;
            }

            //If everything is ok;

            //Create Project Directory and Proj File
            Directory.CreateDirectory(Helper.GenerateProjectBaseDirPath(projectName));
            var stream = File.Create(projectFileJson);
            stream.Close();
            FileInfo finfo = new FileInfo(projectFileJson);

            //Create Engine Config;
            EngineConfig engineConfig = new EngineConfig();
            engineConfig.graphicAPI = GraphicAPI.DirectX11; //Default is DX11
            engineConfig.vSync = true;
            engineConfig.fpsLimit = 60.0f;

            //Update Project
            project.Path = finfo.FullName;
            project.@EngineConfig = engineConfig;

            //Its for init of editor window, its UI thing
            ProjectListItem projectListItem = new ProjectListItem();
            projectListItem.Name = project.Name;
            projectListItem.Description = project.Description;
            projectListItem.Path = project.Path;
            projectListItem.Version = project.Version;

            //Add Project into our Program
            ProjectManager.Instance.SaveProject(project);
            ProjectManager.Instance.CreateProject(projectListItem);

            //TODO : Copy Default project

            //TODO : Go To Editor;

            Helper.MessageInfo("Project is created!");
        }

        #pragma warning disable CS8603
        public Project GetProjectFromPath(string path)
        {
            if (!File.Exists(path)) return null;
            string jsonString = File.ReadAllText(path);
            return JsonSerializer.Deserialize<Project>(jsonString)!;
        }

        public void SaveProjectList()
        {
            string fileName = projectsFileData;
            string jsonString = JsonSerializer.Serialize<ProjectList>(projectList);
            File.WriteAllText(fileName, jsonString);
            OnProjectListSaved?.Invoke();
            UpdateProjectList();
        }

        public void SaveProject(Project project)
        {
            string? fileName = project.Path;
            string jsonString = JsonSerializer.Serialize<Project>(project);
            File.WriteAllText(fileName, jsonString);
            OnProjectListSaved?.Invoke();
            UpdateProjectList();
        }

        public void LoadProjectList()
        {
            string fileName = projectsFileData;
            if (!File.Exists(fileName)) return;
            string jsonString = File.ReadAllText(fileName);
            projectList = JsonSerializer.Deserialize<ProjectList>(jsonString)!;
            OnProjectListLoaded?.Invoke();
        }

        public void UpdateProjectList()
        {
            projectList.ProjectListItems.Clear();

            LoadProjectList();
        }

    }
}
