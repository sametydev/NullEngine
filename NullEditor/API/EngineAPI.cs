using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NullEditor.API
{
    internal static class EngineAPI
    {
        //TODO Change : (currently engine is static lib not dll)
        private const string engineDll = "NullEngine.dll";

        [DllImport(engineDll)]
        public static extern IntPtr GetProcAddress(IntPtr hModule, string procName);
        [DllImport(engineDll)]
        public static extern IntPtr GetHwnd();
    }
}
