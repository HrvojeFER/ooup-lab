using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OoupLab.TextEditor
{
    internal class TextEditorModel : IDisposable, IAsyncDisposable
    {
        public TextEditorModel(string pathToFile)
        {
            _openFile = File.Open(pathToFile, FileMode.Open, FileAccess.ReadWrite);

            Lines = new List<string>();
            using var reader = new StreamReader(_openFile);
            string? line;
            while ((line = reader.ReadLine()) != null)
            {
                Lines.Add(line);
            }
        }


        public async void SaveToFileAsync()
        {
            await using var writer = new StreamWriter(_openFile);
            foreach (var line in Lines)
            {
                await writer.WriteLineAsync(line);
            }
        }

        public IEnumerable<string> LinesRange(int start, int end)
        {
            return Lines.Skip(start).Take(end - start);
        }

        private readonly FileStream _openFile;
        public List<string> Lines { get; private set; }


        public void RegisterCursorObserver(ICursorObserver observer)
        {
            _cursorObservers.Add(observer);
        }

        public bool UnregisterCursorObserver(ICursorObserver observer)
        {
            return _cursorObservers.Remove(observer);
        }

        private void NotifyCursorObservers()
        {
            foreach (var observer in _cursorObservers)
            {
                observer.UpdateCursorPosition(CurrentCursorPosition);
            }
        }

        public void MoveCursorLeft()
        {
            if (CurrentCursorPosition.CurrentChar == 0)
            {
                if (CurrentCursorPosition.CurrentLine == 0) return;
                
                CurrentCursorPosition.CurrentLine -= 1;
                CurrentCursorPosition.CurrentChar = 
                    Lines[CurrentCursorPosition.CurrentLine].Length;
            }
            else
            {
                CurrentCursorPosition.CurrentChar -= 1;
            }
            NotifyCursorObservers();
        }
        public void MoveCursorRight()
        {
            if (CurrentCursorPosition.CurrentChar == 
                Lines[CurrentCursorPosition.CurrentLine].Length)
            {
                if (CurrentCursorPosition.CurrentLine == Lines.Count - 1) return;
                
                CurrentCursorPosition.CurrentLine += 1;
                CurrentCursorPosition.CurrentChar = 0;
            }
            else
            {
                CurrentCursorPosition.CurrentChar += 1;
            }
            NotifyCursorObservers();
        }

        public void MoveCursorDown()
        {
            if (CurrentCursorPosition.CurrentLine == Lines.Count - 1) return;
            CurrentCursorPosition.CurrentLine += 1;
            NotifyCursorObservers();
        }
        public void MoveCursorUp()
        {
            if (CurrentCursorPosition.CurrentLine == 0) return;
            CurrentCursorPosition.CurrentLine -= 1;
            NotifyCursorObservers();
        }

        private readonly List<ICursorObserver> _cursorObservers = new List<ICursorObserver>();
        public CursorPosition CurrentCursorPosition;


        public void RegisterTextObserver(ITextObserver observer)
        {
            _textObservers.Add(observer);
        }

        public bool UnregisterTextObserver(ITextObserver observer)
        {
            return _textObservers.Remove(observer);
        }

        private void NotifyTextObservers()
        {
            foreach (var textObserver in _textObservers)
            {
                textObserver.UpdateText();
            }
        }

        public void DeleteBefore()
        {
            if (CurrentCursorPosition.CurrentChar == 0)
            {
                if (CurrentCursorPosition.CurrentLine == 0) return;
                var target = Lines[CurrentCursorPosition.CurrentLine - 1];
                Lines[CurrentCursorPosition.CurrentLine - 1] = 
                    target.Remove(target.Length - 1, 1);
            }
            else
            {
                Lines[CurrentCursorPosition.CurrentLine] = 
                    Lines[CurrentCursorPosition.CurrentLine].Remove(
                        CurrentCursorPosition.CurrentChar - 1, 1);
            }
            NotifyTextObservers();
            MoveCursorLeft();
        }

        public void DeleteAfter()
        {
            if (CurrentCursorPosition.CurrentChar == 
                Lines[CurrentCursorPosition.CurrentLine].Length - 1)
            {
                if (CurrentCursorPosition.CurrentLine == Lines.Count - 1) return;
                Lines[CurrentCursorPosition.CurrentLine] = 
                    Lines[CurrentCursorPosition.CurrentLine].Remove(0, 1);
            }
            else
            {
                Lines[CurrentCursorPosition.CurrentLine] = 
                    Lines[CurrentCursorPosition.CurrentLine].Remove(
                        CurrentCursorPosition.CurrentChar, 1);
            }
            NotifyTextObservers();
        }

        private readonly List<ITextObserver> _textObservers = new List<ITextObserver>();

        public Tuple<int, int> SelectionRange = new Tuple<int, int>(0, 0);



        private bool _disposed;


        private void Dispose(bool disposing)
        {
            if (_disposed) return;

            if (disposing)
            {
                _openFile.Dispose();
            }

            _disposed = true;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~TextEditorModel()
        {
            Dispose(false);
        }


        private async ValueTask DisposeAsync(bool disposing)
        {
            if (_disposed) return;

            if (disposing)
            {
                await _openFile.DisposeAsync();
            }

            _disposed = true;
        }

        public async ValueTask DisposeAsync()
        {
            await DisposeAsync(true);
            GC.SuppressFinalize(this);
        }
    }
}
