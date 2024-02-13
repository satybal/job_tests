#include <cmath>
#include <iostream>

using namespace std;

struct Point 
{
    Point();
    Point(const double &x, const double &y, const double &z): x{x}, y{y}, z{z} {}

    void print() {
        cout << "{ " << this->x << ", " << this->y << ", " << this->z << " }" << endl;
    }

    Point zero_point() const {
        return {0., 0., 0.};
    }

    double x, y, z;
};

class Curve 
{
public:
    virtual Point calc_point(const double &t) const = 0;

    virtual double calc_derivative(const double& t) const = 0;

    virtual Point calc_vector(const double& t) const = 0;

    virtual void print_derivative(const double& t) const {
        std::cout << "y'(x) = " << this->calc_derivative(t) << std::endl;
    }

    virtual const char* curve_type() const {
        return "Curve";
    }

    virtual double get_radius() const = 0;
};

class Circle : public Curve 
{
public:
    Circle(const double &radius): radius{radius} {}
           
    Point calc_point(const double& t) const override {
        return { radius * cos(t), radius * sin(t), 0. };
    }

    double calc_derivative(const double& t) const override {
        return -(1 / tan(t));
    }

    Point calc_vector(const double& t) const { return {0., 0., 0.}; }

    const char* curve_type() const override {
        return "Circle";
    }

    double get_radius() const override {
        return radius;
    }
    
private:
    double radius;
};

class Ellipse : public Curve 
{
public:
    Ellipse(const double &radius_x, const double &radius_y): 
        radius_x{radius_x},
        radius_y{radius_y}
        {}
           
    Point calc_point(const double& t) const override {
        return { radius_x * cos(t), radius_y * sin(t), 0. };
    }

    double calc_derivative(const double& t) const override {
        return -(radius_y / radius_x / tan(t));
    }

    Point calc_vector(const double& t) const { return {0., 0., 0.}; }

    const char* curve_type() const override {
        return "Ellipse";
    }

    double get_radius() const override {
        return radius_x;
    }
    
private:
    double radius_x;
    double radius_y;
};

class Helix : public Curve 
{
public:
    Helix(const double &radius, const double &step): 
        radius{radius},
        step{step}
        {}
           
    Point calc_point(const double& t) const override {
        return { radius * cos(t), radius * sin(t), t / (2 * M_PI) * step };
    }

    Point calc_vector(const double& t) const {
        return { - radius * sin(t), radius * cos(t), step };
    }

    double calc_derivative(const double& t) const override { return 0; }

    const char* curve_type() const override {
        return "Helix";
    }

    double get_radius() const override {
        return radius;
    }
    
private:
    double radius;
    double step;
};