package com.fer.ooup.lab.exercise4.geometry;

import java.util.Objects;

public class Line implements LineLike
{
    public Line(Point start, Vector direction)
    {
        this.start = start;
        this.direction = direction.normalized();
    }

    public Line(Point a, Point b)
    {
        this.start = a;
        this.direction = b.getPositionVector().subtract(a.getPositionVector()).normalized();
    }

    public Line(Line other)
    {
        this.start = new Point(other.start);
        this.direction = new Vector(other.direction);
    }


    public Line in(CoordinateSystem system)
    {
        return new Line(this.start.in(system), system.in(this.direction));
    }

    public Line translate(Vector difference)
    {
        return new Line(this.start.translate(difference), this.direction);
    }


    @Override
    public Point getPoint(Scalar parameter)
    {
        return new Point(this.start.getPositionVector().add(this.direction.multiply(parameter)));
    }

    @Override
    public Scalar getProjectionParameter(Point point)
    {
        return this.direction.dot(point.getPositionVector().subtract(this.start.getPositionVector()));
    }

    @Override
    public boolean contains(Point point)
    {
        return point.equals(this.getPoint(this.getProjectionParameter(point)));
    }


    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (!(o instanceof Line)) return false;

        Line other = (Line) o;
        return this.contains(other.start) &&
                (this.direction.equals(other.direction) || this.direction.equals(other.direction.negated()));
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(Objects.hash(direction) ^ Objects.hash(direction.negated()));
    }



    private final Point start;
    private final Vector direction;
}
