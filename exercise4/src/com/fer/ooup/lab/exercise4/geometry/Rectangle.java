package com.fer.ooup.lab.exercise4.geometry;

import java.util.Objects;

public class Rectangle implements GeometryObject<Rectangle>
{
    public Rectangle(Point start, Scalar width, Scalar height)
    {
        this.start = start;

        this.width = width;
        this.height = height;
    }

    public Rectangle(Rectangle other)
    {
        this.start = new Point(other.start);

        this.width = new Scalar(other.width);
        this.height = new Scalar(other.height);
    }


    @Override
    public Rectangle deepClone() {
        return new Rectangle(this);
    }

    @Override
    public Rectangle in (CoordinateSystem system)
    {
        return new Rectangle(this.start.in(system), this.width, this.height);
    }

    @Override
    public Rectangle translate(Vector difference)
    {
        return new Rectangle(this.start.translate(difference), this.width, this.height);
    }

    @Override
    public Rectangle scale(Scalar factor)
    {
        return new Rectangle(
                this.start,
                new Scalar(this.width.value() * factor.value()),
                new Scalar(this.height.value() * factor.value()));
    }


    @Override
    public Rectangle getBoundingBox()
    {
        return new Rectangle(this);
    }


    @Override
    public String getShapeName()
    {
        return Rectangle.name;
    }



    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;

        if (obj instanceof Rectangle)
        {
            Rectangle rectangle = (Rectangle) obj;

            return Objects.equals(start, rectangle.start) &&
                    Objects.equals(width, rectangle.width) &&
                    Objects.equals(height, rectangle.height);
        }

        return false;
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(start, width, height);
    }



    private static final String name = "Rectangle";


    private final Point start;

    private final Scalar width;
    private final Scalar height;
}
