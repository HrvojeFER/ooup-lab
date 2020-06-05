package com.fer.ooup.lab.exercise4;

import java.util.*;

import com.fer.ooup.lab.exercise4.geometry.Point;
import com.fer.ooup.lab.exercise4.geometry.Rectangle;
import com.fer.ooup.lab.exercise4.geometry.Scalar;
import com.fer.ooup.lab.exercise4.geometry.Vector;

public interface GraphicalObject
{
    boolean isSelected();
    void setSelected(boolean selected);
    int getNumberOfHotPoints();
    Point getHotPoint(int index);
    void setHotPoint(int index, Point point);
    boolean isHotPointSelected(int index);
    void setHotPointSelected(int index, boolean selected);
    Scalar getHotPointDistance(int index, Point mousePoint);


    void translate(Vector delta);
    Rectangle getBoundingBox();
    Scalar selectionDistance(Point mousePoint);


    public interface Renderer
    {
        void drawLine(Point start, Point end);
        void fillPolygon(Point[] points);
    }

    void render(Renderer renderer);


    interface Listener
    {
        void graphicalObjectChanged(GraphicalObject graphicalObject);
        void graphicalObjectSelectionChanged(GraphicalObject graphicalObject);
    }

    public void addListener(Listener listener);
    public void removeListener(Listener listener);


    String getShapeName();
    GraphicalObject duplicate();

    public String getShapeID();
    public void load(Stack<GraphicalObject> stack, String data);
    public void save(List<String> rows);
}