// ariel.levovich@msmail.ariel.ac.il 
#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
#include <cmath> 

class Complex {
private:
    double real;    
    double imag;    

public:
    Complex() : real(0), imag(0) {}

    Complex(double r, double i) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }    

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    bool operator>(const Complex& other) const {
        return (std::sqrt(real * real + imag * imag) > std::sqrt(other.real * other.real + other.imag * other.imag));
    }

    // Friend function to overload operator<<
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};
#endif