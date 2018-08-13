using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        Parents p;
        /*
        // 1 - 전역으로 Mode 클래스 생성
        // 2 - Mode에 따라(scangear, custom, photo...) 업캐스팅
        업캐스팅이란 말 그대로 자식 클래스의 객체가 부모 클래스의 형태로 변환되는 것
        반대로, 다운캐스팅(downcasting)은 부모 클래스의 객체가 자식 클래스의 형태로 변환되는 것
        class Animal{}
        class Dog : Animal{}
        Dog dog = new Dog();
        Animal animal = dog; - 업캐스팅
        Dog sameDog = (Dog)animal; - 다운캐스팅
        3 - 자식클래스의 메소드에는 override 부모클래스 메소드는 virtual, new 적절히 사용

             * 
             */
        private void button1_Click(object sender, EventArgs e)
        {
            p = new Child1();
            MessageBox.Show(p.GetNum().ToString());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            p = new Child2();
            MessageBox.Show(p.GetNum().ToString());

        }
    }
}
