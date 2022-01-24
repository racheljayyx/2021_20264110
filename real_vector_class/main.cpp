#include <iostream>
#include <limits> // for std::numeric_limits

using namespace std;

class vector_3D;

class vector_3D
{
    private:
        double x_coord;
        double y_coord;
        double z_coord;

    public:

        vector_3D();        //constructor
        -vector_3D();       //destructor


        //mutators (setters)
        void set_x_coord(double x_coord);
        void set_y_coord(double y_coord);
        void set_z_coord(double z_coord);


        //accessors (getters)
        double get_x_coord();
        double get_y_coord();
        double get_z_coord();

        //functions to perform basic vector operations
        vector_3D vector_addition(vector_3D second);
        vector_3D vector_subtraction(vector_3D second);
        double dot_product(vector_3D second);
        vector_3D cross_product(vector_3D second);



};

//initialising all values to zero
vector_3D::vector_3D()
{
    x_coord = 0;
    y_coord = 0;
    z_coord = 0;
}


void vector_3D::set_x_coord(double x_coord)
{
    this->x_coord = x_coord;
}

void vector_3D::set_y_coord(double y_coord)
{
    this->y_coord = y_coord;
}

void vector_3D::set_z_coord(double z_coord)
{
    this->z_coord = z_coord;
}

//get_x_coord returns the value in the x_coordinate member
double  vector_3D::get_x_coord()
{
    return x_coord;
}

//get_y_coord returns the value in the y_coord member
double  vector_3D::get_y_coord()
{
    return y_coord;
}

//get_z_coord returns the value in the z_coord member
double  vector_3D::get_z_coord()
{
    return z_coord;
}

vector_3D  vector_3D::vector_addition(vector_3D second)
{
    vector_3D sum;

    sum.x_coord = x_coord + second.x_coord;
    sum.y_coord = y_coord + second.y_coord;
    sum.z_coord = z_coord + second.z_coord;

    return sum;
}

vector_3D  vector_3D::vector_subtraction(vector_3D second)
{
    vector_3D sum;

    sum.x_coord = x_coord - second.x_coord;
    sum.y_coord = y_coord - second.y_coord;
    sum.z_coord = z_coord - second.z_coord;

    return sum;
}

double  vector_3D::dot_product(vector_3D second)
{
    return (x_coord * second.x_coord +
            y_coord * second.y_coord +
            z_coord * second.z_coord);
}

vector_3D  vector_3D::cross_product(vector_3D second)
{
    vector_3D cross;

    cross.x_coord = y_coord *second.z_coord - z_coord * second.y_coord;
    cross.y_coord = -(x_coord * second.z_coord - z_coord * second.x_coord);
    cross.z_coord = x_coord * second.y_coord - y_coord * second.x_coord;

    return cross;
}

int main()
{
    vector_3D vector_one, vector_two;
    vector_3D vector_addition, vector_subtraction;
    vector_3D cross_product;
    double dot_product;

    vector_one.set_x_coord(4.5);
    vector_one.set_y_coord(3.6);
    vector_one.set_z_coord(2.7);

    vector_two.set_x_coord(5.4);
    vector_two.set_y_coord(6.3);
    vector_two.set_z_coord(7.2);

    cout << "Vector 1: " << vector_one.get_x_coord() << " , " << vector_one.get_y_coord() << " , " << vector_one.get_z_coord() << endl;
    cout << "Vector 2: " << vector_two.get_x_coord() << " , " << vector_two.get_y_coord() << " , " << vector_two.get_z_coord() << endl;

    vector_addition = vector_one.vector_addition(vector_two);
    vector_subtraction = vector_one.vector_subtraction(vector_two);
    dot_product = vector_one.dot_product(vector_two);
    cross_product = vector_one.cross_product(vector_two);

    cout << "Vector 1 + Vector 2 = " << vector_addition.get_x_coord()<< " , " << vector_addition.get_y_coord() << " , " << vector_addition.get_z_coord() << endl;
    cout << "Vector 1 - Vector 2 = " << vector_subtraction.get_x_coord() << " , " << vector_subtraction.get_y_coord() << " , " << vector_subtraction.get_z_coord() << endl;
    cout << "Cross product = " << cross_product.get_x_coord() << " , " << cross_product.get_y_coord() << " , " << cross_product.get_z_coord() << endl;
    cout << "Dot product = " << dot_product << endl;

    return 0;
}
