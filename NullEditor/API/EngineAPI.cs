using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using NullEditor;

namespace NullEditor.API
{
    internal static class EngineAPI
    {
        [DllImport(Global.ENGINE_LIB)]
        public static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        //TODO : Implement this into editor
        [DllImport(Global.ENGINE_LIB)]
        public static extern IntPtr GetHwnd();
    }
}
