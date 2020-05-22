using System;
using System.Windows.Forms;

namespace OoupLab.TextEditor
{
    // ReSharper disable once UnusedMember.Global
    internal static class Program
    {
        // ReSharper disable once UnusedMember.Local
        [STAThread]
        private static void Main()
        {
            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
