using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NullEditor.Engine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct EngineConfig
    {
        public GraphicAPI graphicAPI;
        public bool vSync;
        public float fpsLimit;
    }

    public enum GraphicAPI
    {
        DirectX11,
        OpenGL46
    }
}
