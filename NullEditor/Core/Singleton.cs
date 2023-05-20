using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NullEditor.Core
{
    public class Singleton<T>
    {
        public Singleton() { }
        static Singleton() { }
        private static Singleton<T> _instance = new Singleton<T>();
        public static Singleton<T> Instance { get { return _instance; } }
    }
}
