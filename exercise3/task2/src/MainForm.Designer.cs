using System;
using System.Drawing;
using System.Windows.Forms;

namespace OoupLab.TextEditor
{
    partial class MainForm : ICursorObserver, ITextObserver
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        private TextEditorModel editorModel = new TextEditorModel("./test.txt");

        private static int _fontSizeInPixels = 20;
        private static int _lineSeparation = 5;
        private static Font _arial = new Font(
            "Arial", _fontSizeInPixels, FontStyle.Regular, GraphicsUnit.Pixel);

        private static int _textStartYOffset = 10;
        private static int _textYOffsetIncrement = _fontSizeInPixels + _lineSeparation;
        private static int _textStartXOffset = 10;
        private static int _cursorXIncrement = _fontSizeInPixels / 2;
        private static Pen _cursorPen = new Pen(Brushes.HotPink);


        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed;
        /// otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
                editorModel.Dispose();
                _arial.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(1024, 768);
            this.ForeColor = System.Drawing.Color.DarkOrange;
            this.Name = "MainForm";
            this.Text = "OOUPLAB Text Editor";
            this.ResumeLayout(false);

            editorModel.RegisterCursorObserver(this);
            editorModel.RegisterTextObserver(this);
        }
        #endregion

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var yOffset = _textStartYOffset;
            foreach (var line in editorModel.Lines)
            {
                PointF textStart = new PointF(_textStartXOffset, yOffset);
                e.Graphics.DrawString(line, _arial, Brushes.Coral, textStart);

                yOffset += _textYOffsetIncrement;
            }

            var cursorLineYPostition =
                _textStartYOffset + _textYOffsetIncrement * 
                editorModel.CurrentCursorPosition.CurrentLine;
            var cursorLineXPosition =
                _textStartXOffset + _cursorXIncrement * 
                editorModel.CurrentCursorPosition.CurrentChar;

            e.Graphics.DrawLine(_cursorPen, 
                new Point(cursorLineXPosition, cursorLineYPostition), 
                new Point(cursorLineXPosition, cursorLineYPostition + _fontSizeInPixels));
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            if (e.KeyCode == Keys.Escape)
            {
                Close();
            }
            else if (e.KeyCode == Keys.Left)
            {
                editorModel.MoveCursorLeft();
            }
            else if (e.KeyCode == Keys.Right)
            {
                editorModel.MoveCursorRight();
            }
            else if (e.KeyCode == Keys.Down)
            {
                editorModel.MoveCursorDown();
            }
            else if (e.KeyCode == Keys.Up)
            {
                editorModel.MoveCursorUp();
            }
            else if (e.KeyCode == Keys.Delete)
            {
                editorModel.DeleteAfter();
            }
            else if (e.KeyCode == Keys.Back)
            {
                editorModel.DeleteBefore();
            }
        }

        public void UpdateCursorPosition(CursorPosition position)
        {
            Invalidate();
        }

        public void UpdateText()
        {
            Invalidate();
        }
    }
}

