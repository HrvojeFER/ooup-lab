package com.fer.ooup.lab.exercise4.geometry;

public class Point
{
    public Point(Vector position)
    {
        this.position = position;
    }

    public Point(Scalar x, Scalar y)
    {
        this.position = new Vector(x, y);
    }

    public Point(Number x, Number y)
    {
        this.position = new Vector(x, y);
    }

    public Point(Point other)
    {
        this.position = other.position;
    }


    public Vector getPositionVector()
    {
        return this.position;
    }


    public Scalar distanceSquared(Point other)
    {
        return other.position.subtract(this.position).lengthSquared();
    }

    public Scalar distance(Point other)
    {
        return other.position.subtract(this.position).length();
    }

    public Scalar distance(LineLike lineLike)
    {
        return lineLike.getPoint(lineLike.getProjectionParameter(this)).distance(this);
    }


    public Point in(CoordinateSystem system)
    {
        return new Point(system.in(this.position));
    }

    public Point translate(Vector difference)
    {
        return new Point(this.position.add(difference));
    }


    private final Vector position;
}
