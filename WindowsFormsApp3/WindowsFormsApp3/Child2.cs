using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp3
{
    class Child2 : Parents
    {
        public Child2() { }
        
        public new int num = 2;
        public override int GetNum() { return num; }
    }
}
