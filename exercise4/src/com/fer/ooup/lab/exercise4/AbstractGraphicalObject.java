package com.fer.ooup.lab.exercise4;

import java.lang.reflect.Array;
import java.util.*;

import com.fer.ooup.lab.exercise4.geometry.*;
import com.fer.ooup.lab.exercise4.geometry.Vector;


public abstract class AbstractGraphicalObject<GeometryType extends GeometryObject<GeometryType>>
        implements GraphicalObject
{
    public AbstractGraphicalObject(GeometryType inner)
    {
        this.hotPoints = new Point[AbstractGraphicalObject.numberOfHotPoints];

        this.hotPointSelections = new boolean[AbstractGraphicalObject.numberOfHotPoints];
        Arrays.fill(this.hotPointSelections, false);


        this.listeners = new ArrayList<>();


        this.inner = inner;
    }



    @Override
    public boolean isSelected()
    {
        return isSelected;
    }

    @Override
    public void setSelected(boolean selected)
    {
        this.isSelected = selected;
    }


    @Override
    public int getNumberOfHotPoints()
    {
        return this.hotPoints.length;
    }

    @Override
    public Point getHotPoint(int index)
    {
        return this.hotPoints[index];
    }

    @Override
    public void setHotPoint(int index, Point point)
    {
        this.hotPoints[index] = point;
    }

    @Override
    public boolean isHotPointSelected(int index)
    {
        return this.hotPointSelections[index];
    }

    @Override
    public void setHotPointSelected(int index, boolean selected)
    {
        this.hotPointSelections[index] = selected;
    }

    @Override
    public Scalar getHotPointDistance(int index, Point mousePoint)
    {
        return this.hotPoints[index].distance(mousePoint);
    }


    @Override
    public void addListener(GraphicalObject.Listener listener)
    {
        listeners.add(listener);
    }

    @Override
    public void removeListener(GraphicalObject.Listener listener)
    {
        listeners.remove(listener);
    }


    @Override
    public void translate(Vector difference)
    {
        this.inner = this.inner.translate(difference);
    }

    @Override
    public Rectangle getBoundingBox()
    {

    }

    @Override
    public Scalar selectionDistance(Point mousePoint)
    {

    }


    @Override
    public String getShapeName()
    {
        return inner.getShapeName();
    }

    @Override
    public String getShapeID()
    {
        return null;
    }


    @Override
    public void load(Stack<GraphicalObject> stack, String data)
    {

    }

    @Override
    public void save(List<String> rows)
    {

    }


    protected static int numberOfHotPoints = 2;


    private boolean isSelected = false;

    private final Point[] hotPoints;
    private final boolean[] hotPointSelections;

    private final ArrayList<Listener> listeners;

    private GeometryType inner;
}
