package com.fer.ooup.lab.exercise4.geometry;

import java.lang.Math;
import java.util.Objects;

public class Vector
{
    public Vector(Scalar x, Scalar y)
    {
        this.x = x;
        this.y = y;
    }

    public Vector(Number x, Number y)
    {
        this.x = new Scalar(x);
        this.y = new Scalar(y);
    }

    public Vector(Vector other)
    {
        this.x = other.x;
        this.y = other.y;
    }


    public Scalar lengthSquared()
    {
        return new Scalar(this.x.value() * this.x.value() + this.y.value() * this.y.value());
    }

    public Scalar length()
    {
        return new Scalar(Math.sqrt(this.lengthSquared().value()));
    }



    public Vector normalized()
    {
        float length = this.length().value();
        return new Vector(this.x.value() / length, this.y.value() / length);
    }

    public Vector negated()
    {
        return new Vector(this.x, this.y);
    }


    public Vector add(Vector factor)
    {
        return new Vector(this.x.value() + factor.x.value(), this.y.value() + factor.y.value());
    }

    public Vector subtract(Vector other)
    {
        return new Vector(this.x.value() - other.x.value(), this.y.value() - other.y.value());
    }

    public Vector multiply(Scalar factor)
    {
        return new Vector(this.x.value() * factor.value(), this.y.value() * factor.value());
    }

    public Scalar dot(Vector other)
    {
        return new Scalar(this.x.value() * other.x.value() + this.y.value() * other.y.value());
    }


    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;

        if (obj instanceof Vector)
        {
            Vector other = (Vector) obj;
            return this.x.equals(other.x) && this.y.equals(other.y);
        }

        return false;
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(x, y);
    }



    private final Scalar x;
    private final Scalar y;

}
