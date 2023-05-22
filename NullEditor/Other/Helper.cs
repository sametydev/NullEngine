using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace NullEditor.Other
{
    public static class Helper
    {

        public static void MessageError(string message) =>
            MessageBox.Show(message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
        public static void MessageWarn(string message) =>
            MessageBox.Show(message, "Warning", MessageBoxButton.OK, MessageBoxImage.Warning);
        public static void MessageInfo(string message) =>
            MessageBox.Show(message, "Information", MessageBoxButton.OK, MessageBoxImage.Information);

        public static string GenerateProjectPath(string value) =>
            string.Format("Projects/{0}/{0}.{1}", value, Global.PROJECT_EXT);
        public static string GenerateProjectBaseDirPath(string value) =>
            string.Format("Projects/{0}", value);
    }
}
