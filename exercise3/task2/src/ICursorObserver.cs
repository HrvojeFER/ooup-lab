using System;
using System.Collections.Generic;
using System.Text;

namespace OoupLab.TextEditor
{
    public struct CursorPosition
    {
        public int CurrentLine;
        public int CurrentChar;
    }

    internal interface ICursorObserver
    {
        void UpdateCursorPosition(CursorPosition position);

    }
}
