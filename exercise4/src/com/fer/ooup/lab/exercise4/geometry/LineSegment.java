package com.fer.ooup.lab.exercise4.geometry;

import java.util.Objects;

public class LineSegment implements LineLike, GeometryObject<LineSegment>
{
    public LineSegment(Line line, Scalar length)
    {
        this.line = line;
        this.length = length;
    }

    public LineSegment(Point a, Point b)
    {
        this.line = new Line(a, b);
        this.length = b.getPositionVector().subtract(a.getPositionVector()).length();
    }

    public LineSegment(Line line, Scalar aParameter, Scalar bParameter)
    {
        Point a = line.getPoint(aParameter);
        Point b = line.getPoint(bParameter);

        this.line = new Line(a, b);
        this.length = b.getPositionVector().subtract(a.getPositionVector()).length();
    }

    public LineSegment(LineSegment other)
    {
        this.line = other.line();
        this.length = other.length();
    }


    public Line line()
    {
        return this.line;
    }

    public Scalar length()
    {
        return this.length;
    }

    public Wire wire()
    {
        return new Wire(this.getPoint(Scalar.zero()), this.getPoint(Scalar.one()));
    }



    @Override
    public LineSegment deepClone() {
        return new LineSegment(this);
    }

    @Override
    public LineSegment in(CoordinateSystem system)
    {
        return new LineSegment(this.line.in(system), this.length);
    }

    @Override
    public LineSegment translate(Vector difference)
    {
        return new LineSegment(this.line.translate(difference), this.length);
    }

    @Override
    public LineSegment scale(Scalar factor)
    {
        return new LineSegment(this.line, new Scalar(this.length.value() * factor.value()));
    }


    @Override
    public String getShapeName()
    {
        return LineSegment.name;
    }



    @Override
    public Point getPoint(Scalar parameter)
    {
        parameter = clampParameter(parameter);
        return this.line.getPoint(new Scalar(parameter.value() * this.length.value()));
    }

    @Override
    public Scalar getProjectionParameter(Point point)
    {
        return this.clampParameter(new Scalar(
                this.line.getProjectionParameter(point).value() / this.length.value()));
    }

    @Override
    public boolean contains(Point point)
    {
        Scalar lineProjectionParameter = this.line.getProjectionParameter(point);
        if (lineProjectionParameter.value() < 0 || lineProjectionParameter.value() > 1) return false;
        return point.equals(this.line.getPoint(lineProjectionParameter));
    }


    private Scalar clampParameter(Scalar parameter)
    {
        if (parameter.value() > 1) return new Scalar(1);
        if (parameter.value() < 0) return new Scalar(0);
        return new Scalar(parameter);
    }



    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;

        if (obj instanceof LineSegment)
        {
            LineSegment other = (LineSegment) obj;
            return Objects.equals(this.wire(), other.wire());
        }

        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(line, length);
    }



    private static final String name = "Line Segment";


    private final Line line;
    private final Scalar length;
}
