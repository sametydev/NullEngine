using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace NullEditor.EditorWindow
{
    /// <summary>
    /// Interaction logic for EditorWindow.xaml
    /// </summary>
    public partial class EditorWindow : Window
    {

        public EditorWindow()
        {
            InitializeComponent();
        }

        public EditorWindow(Project.Project project)
        {
            InitializeComponent();
            base.Title = string.Format("Null Engine Editor - {0} - <{1}> - [Engine Version : {2}]",
                project.Name,project.EngineConfig.graphicAPI,project.Version);
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            Application.Current.Shutdown();
        }
    }
}
