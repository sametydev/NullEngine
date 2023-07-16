using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace NullEditor.Core
{
    internal class WindowHost : HwndHost
    {
        [DllImport("user32.dll", SetLastError = true)]
        static extern IntPtr CreateWindowEx(IntPtr exStyle, string lpClassName, string lpWindowName, int dwStyle, int x, int y, int nWidth, int nHeight, IntPtr hWndParent, IntPtr hMenu, IntPtr hInstance, IntPtr lpParam);

        protected override HandleRef BuildWindowCore(HandleRef hWndParent)
        {
            return new HandleRef(this, CreateWindowEx(IntPtr.Zero, "static", "", 0x40000000, 0, 0, 200, 200, hWndParent.Handle, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero));
        }
        protected override void DestroyWindowCore(HandleRef hwnd) { }
    }
}
