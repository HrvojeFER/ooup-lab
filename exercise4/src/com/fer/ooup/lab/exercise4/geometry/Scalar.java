package com.fer.ooup.lab.exercise4.geometry;

import java.lang.Math;

public class Scalar
{
    public static Scalar zero()
    {
        return new Scalar(0);
    }

    public static Scalar one()
    {
        return new Scalar(1);
    }


    public Scalar(Number number)
    {
        this.value = number.floatValue();
    }

    public Scalar(Scalar other)
    {
        this.value = other.value;
    }


    public float value()
    {
        return value;
    }


    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;
        if (obj instanceof  Scalar)
        {
            Scalar other = (Scalar) obj;
            return Math.abs(this.value - other.value) < Scalar.epsilon;
        }
        else if (obj instanceof Number)
        {
            Number other = (Number) obj;
            return Math.abs(this.value - other.floatValue()) < Scalar.epsilon;
        }
        else return false;
    }


    private static final float epsilon = 0.001f;

    private final float value;
}
