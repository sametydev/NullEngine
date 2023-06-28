using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
#pragma warning disable CS8604

namespace NullEditor
{
    public static class Global
    {
        public const string ENGINE_LIB         = "NullEngine.dll";
        public const string ENGINE_VERSION     = "1.0.0.0";
        public const string PROJECT_NAME_REGEX = "^[a-zA-Z0-9]*$";
        public const string PROJECT_EXT        = "nproj";
        public const string META_EXT           = "nmeta";
        public const string PROJECTLIST_FILE   = "Projects.json";
    }
}
