package com.fer.ooup.lab.exercise4.geometry;

public class CoordinateSystem
{
    public CoordinateSystem()
    {
        origin = new Vector(0, 0);
    }

    public CoordinateSystem(Vector origin)
    {
        this.origin = origin;
    }

    public CoordinateSystem(Scalar x, Scalar y)
    {
        this.origin = new Vector(x, y);
    }

    public CoordinateSystem(Number x, Number y)
    {
        this.origin = new Vector(x, y);
    }

    public CoordinateSystem(CoordinateSystem other)
    {
        this.origin = new Vector(other.origin);
    }


    public CoordinateSystem translate(Vector difference)
    {
        return new CoordinateSystem(this.origin.add(difference));
    }

    public Vector in(Vector vector)
    {
        return vector.subtract(origin);
    }


    private final Vector origin;
}
