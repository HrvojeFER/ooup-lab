package com.fer.ooup.lab.exercise4.geometry;

import java.util.Objects;

public class Ellipse implements GeometryObject<Ellipse>
{
    public Ellipse(Point center, Scalar radiusX, Scalar radiusY)
    {
        this.center = center;

        this.radiusX = radiusX;
        this.radiusY = radiusY;
    }

    public Ellipse(Ellipse other)
    {
        this.center = new Point(other.center);

        this.radiusX = new Scalar(other.radiusX);
        this.radiusY = new Scalar(other.radiusY);
    }



    @Override
    public Ellipse deepClone() {
        return new Ellipse(this);
    }


    @Override
    public Ellipse in(CoordinateSystem system)
    {
        return new Ellipse(this.center.in(system), this.radiusX, this.radiusY);
    }

    @Override
    public Ellipse translate(Vector difference)
    {
        return new Ellipse(this.center.translate(difference), this.radiusX, this.radiusY);
    }

    @Override
    public Ellipse scale(Scalar factor)
    {
        return new Ellipse(this.center,
                new Scalar(this.radiusX.value() * factor.value()),
                new Scalar(this.radiusY.value() * factor.value()));
    }


    @Override
    public Rectangle getBoundingBox()
    {
        return new Rectangle(
                this.center.translate(
                        new Vector(
                                new Scalar(-this.radiusX.value()),
                                new Scalar(-this.radiusY.value()))),
                new Scalar(this.radiusX.value() * 2),
                new Scalar(this.radiusY.value() * 2));
    }


    @Override
    public String getShapeName()
    {
        return Ellipse.name;
    }



    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;

        if (obj instanceof Ellipse)
        {
            Ellipse other = (Ellipse) obj;

            return Objects.equals(center, other.center) &&
                    Objects.equals(radiusX, other.radiusX) &&
                    Objects.equals(radiusY, other.radiusY);
        }

        return false;
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(center, radiusX, radiusY);
    }



    private static final String name = "Ellipse";


    private final Point center;

    private final Scalar radiusX;
    private final Scalar radiusY;
}
