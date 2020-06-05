package com.fer.ooup.lab.exercise4.geometry;

public interface LineLike
{
    Point getPoint(Scalar parameter);
    Scalar getProjectionParameter(Point point);
    boolean contains(Point point);
}
