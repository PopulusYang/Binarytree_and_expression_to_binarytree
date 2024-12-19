/*********************************************************
* @Author: PopulusYang
* filename: complex_number.hpp
* description: 复数类,重载了加减乘除
**********************************************************/

#include <iostream>

class Complex 
{
private:
    double real;  // 实部
    double imaginary;  // 虚部
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imaginary(i) {}
    double getReal() const 
    {
        return real;
    }
    double getImaginary() const 
    {
        return imaginary;
    }
    Complex operator+(const Complex& other) const 
    {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    Complex operator-(const Complex& other) const 
    {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    Complex operator*(const Complex& other) const 
    {
        double newReal = real * other.real - imaginary * other.imaginary;
        double newImaginary = real * other.imaginary + imaginary * other.real;
        return Complex(newReal, newImaginary);
    }
    Complex operator/(const Complex& other) const 
    {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double newReal = (real * other.real + imaginary * other.imaginary) / denominator;
        double newImaginary = (imaginary * other.real - real * other.imaginary) / denominator;
        return Complex(newReal, newImaginary);
    }
    static Complex strtoComplex(std::string str) 
    {
    double realPart = 0.0;
    double imaginaryPart = 0.0;
    size_t pos = 0;
    // 先找有没有'+'或'-'作为分隔实部和虚部的标志
    pos = str.find_first_of("+-");
    if (pos == std::string::npos) {
        // 只有实部或者只有虚部的情况
        if (str.find('i')!= std::string::npos) {
            // 只有虚部
            std::string numStr = str.substr(0, str.length() - 1);
            if (numStr.empty()) {
                imaginaryPart = 1.0;
            } 
            else 
            {
                imaginaryPart = stod(numStr);
            }
        } else {
            // 只有实部
            realPart = stod(str);
        }
    } 
    else 
    {
        // 有实部和虚部的情况
        std::string realStr = str.substr(0, pos);
        std::string imaginaryStr = str.substr(pos + 1, str.length() - pos - 1);
        realPart = stod(realStr);
        if (imaginaryStr.find('i')!= std::string::npos) {
            std::string numStr = imaginaryStr.substr(0, imaginaryStr.length() - 1);
            if (numStr.empty()) {
                imaginaryPart = (pos == 0? -1.0 : 1.0);
            } else {
                imaginaryPart = std::stod(numStr) * (pos == 0? -1.0 : 1.0);
            }
        }
    }
    return Complex(realPart, imaginaryPart);
    }
};

// 重载输出流运算符 <<，方便输出复数对象
std::ostream& operator<<(std::ostream& os, const Complex& c) 
{
    if(!(c.getImaginary()||c.getReal()))
        os << 0;
    else
    {
        if(c.getReal())
        os << c.getReal();
        if(c.getImaginary() > 0)
        os << "+" << c.getImaginary() << "i";
        else
        os << c.getImaginary() << "i";
    }
    return os;
}
