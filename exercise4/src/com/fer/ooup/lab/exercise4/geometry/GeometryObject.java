package com.fer.ooup.lab.exercise4.geometry;

public interface GeometryObject<T>
{
    T deepClone();

    T in(CoordinateSystem system);
    T translate(Vector difference);
    T scale(Scalar factor);

    Rectangle getBoundingBox();

    String getShapeName();
}
