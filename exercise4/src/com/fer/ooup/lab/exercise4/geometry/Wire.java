package com.fer.ooup.lab.exercise4.geometry;

import java.util.Objects;

public class Wire implements GeometryObject
{
    public Wire(Point a, Point b)
    {
        this.a = a;
        this.b = b;
    }

    public Wire(Wire other)
    {
        this.a = other.a;
        this.b = other.b;
    }


    @Override
    public Wire deepClone()
    {
        return new Wire(this);
    }


    @Override
    public Wire in(CoordinateSystem system)
    {
        return new Wire(this.a.in(system), this.b.in(system));
    }

    @Override
    public Wire translate(Vector difference)
    {
        return new Wire(this.a.translate(difference), this.b.translate(difference));
    }

    @Override
    public Wire scale(Scalar factor)
    {
        return new Wire(
                new Point(this.a.getPositionVector().multiply(factor)),
                new Point(this.b.getPositionVector().multiply(factor)));
    }


    @Override
    public Rectangle getBoundingBox()
    {
        return new Rectangle();
    }


    @Override
    public String getShapeName()
    {
        return Wire.name;
    }



    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;

        if (obj instanceof Wire)
        {
            Wire other = (Wire) obj;
            return (Objects.equals(a, other.a) &&
                    Objects.equals(b, other.b)) ||
                    (Objects.equals(a, other.b) &&
                    Objects.equals(b, other.a));
        }

        return false;
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(a) ^ Objects.hash(b);
    }



    private static final String name = "Wire";


    private final Point a;
    private final Point b;

}
