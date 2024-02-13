#include "curves.hpp"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>

using namespace std;

int random(int min, int max) //range : [min, max]
{
   return min + rand() % (( max + 1 ) - min);
}

int main() {
    srand(time(nullptr));

    // filling container
    vector<shared_ptr<Curve>> container;
    for (size_t i = 0; i < 100; ++i) {
        switch (random(0, 2))
        {
            case 0:
                container.emplace_back(new Circle{double(random(1, 100))});
                break;
            case 1:
                container.emplace_back(new Ellipse{double(random(1, 100)), double(random(1, 100))});
                break;
            case 2:
                container.emplace_back(new Helix{double(random(1, 100)), double(random(1, 100))});
                break;
        }
    }

    // printing points, derivatives and 3D vectors
    // also filling circles vector
    vector<shared_ptr<Curve>> circles;
    double t = M_PI / 4;
    for (auto &obj: container) {
        cout << obj->curve_type() << " point: ";
        obj->calc_point(t).print();

        if (obj->curve_type() == "Helix") {
            cout << "3D vector: ";
            obj->calc_vector(t).print();
        } else {
            cout << "Derivative: ";
            obj->print_derivative(t);

            if (obj->curve_type() == "Circle") {
                circles.emplace_back(obj);
            }
        }
        cout << endl;
    }

    // sorting circles by radius
    sort(circles.begin(), circles.end(), [](shared_ptr<Curve> a, shared_ptr<Curve> b) {
        return a->get_radius() < b->get_radius();
    });

    double sum = 0;
    for (auto &obj: circles) {
        sum += obj->get_radius();
    }

    cout << "Sum of circle radiuses: " << sum << endl;

    return 0;
}