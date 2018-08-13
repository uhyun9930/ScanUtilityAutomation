using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp3
{
    class Child1 : Parents
    {

        public Child1() { }
        public new int num = 1;
        public override int GetNum() { return num; }
    }
}
