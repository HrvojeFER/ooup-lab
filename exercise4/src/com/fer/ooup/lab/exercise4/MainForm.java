package com.fer.ooup.lab.exercise4;

import javax.swing.*;
import java.awt.*;

class MainForm extends JFrame
{
    private final JPanel drawPanel = new JPanel();

    private final JButton loadButton = new JButton();


    public MainForm()
    {
        super();

        loadButton.setText("Load...");

        JPanel commandPanel = new JPanel();
        commandPanel.setPreferredSize(new Dimension(-1, 30));
        commandPanel.setLayout(new GridLayout(1, 1, 1, 5));
        commandPanel.add(loadButton);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout());
        mainPanel.add(commandPanel, BorderLayout.NORTH);
        mainPanel.add(drawPanel, BorderLayout.CENTER);


        setContentPane(mainPanel);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        pack();
        setMinimumSize(new Dimension(800, 600));
        setPreferredSize(new Dimension(1024, 768));
        setLocationRelativeTo(null);
        setVisible(true);
    }
}
