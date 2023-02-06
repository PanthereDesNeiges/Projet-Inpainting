#pragma once

class pixel {
    double x,y;

public:
    double getX();
    double getY();
    void set(double x1, double y1);

    pixel operator+( pixel b); // Sum
    pixel operator-(pixel b); // Difference
    pixel operator*(double lambda); // Multiplication pixel*scalar
    pixel operator/(double lambda); // Multiplication pixel*scalar

    double operator*(pixel b); // Scalar product
    double norm(); // Norm

    pixel rotate(double angle); // Rotation (angle in degrees)
};


