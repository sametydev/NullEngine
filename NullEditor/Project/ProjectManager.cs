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
        public event Action<Project>? OnProjectCreated;
        public event Action? OnProjectListLoaded;
        public event Action? OnProjectListSaved;

        public void CreateProject(Project project)
        {
            projectList.Projects.Add(project);
            SaveProjectList();

            OnProjectCreated?.Invoke(project);
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
            File.Create(projectFileJson);
            FileInfo finfo = new FileInfo(projectFileJson);

            //Create Engine Config;
            EngineConfig engineConfig = new EngineConfig();
            engineConfig.graphicAPI = GraphicAPI.DirectX11; //Default is DX11
            engineConfig.vSync = true;
            engineConfig.fpsLimit = 60.0f;

            //Update Project
            project.Path = finfo.FullName;
            project.@EngineConfig = engineConfig;


            //Add Project into our Program
            ProjectManager.Instance.CreateProject(project);

            //TODO : Copy Default project

            //TODO : Go To Editor;

            Helper.MessageInfo("Project is created!");
        }

        public void SaveProjectList()
        {
            string fileName = projectsFileData;
            string jsonString = JsonSerializer.Serialize<ProjectList>(projectList);
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
            projectList.Projects.Clear();

            LoadProjectList();
        }

    }
}
