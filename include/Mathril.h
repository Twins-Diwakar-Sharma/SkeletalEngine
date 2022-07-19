#ifndef H_M4THR1L_H
#define H_M4THR1L_H

#include <iostream>
#include <math.h>

class Vec2
{
    private:
        float data[2] = {0};
    public:
        Vec2();
        Vec2(float x, float y);
        ~Vec2();
        Vec2(Vec2&);
        Vec2(Vec2&&);

        Vec2& operator=(Vec2&);
        Vec2& operator=(Vec2&&);
        
        float& operator[](int);

        friend Vec2 operator+(Vec2& v, Vec2& w);
        friend Vec2 operator+(Vec2& v, Vec2&& w);
        friend Vec2 operator+(Vec2&& v, Vec2& w);
        friend Vec2 operator+(Vec2&& v, Vec2&& w);

        friend Vec2 operator-(Vec2& v, Vec2& w);
        friend Vec2 operator-(Vec2& v, Vec2&& w);
        friend Vec2 operator-(Vec2&& v, Vec2& w);
        friend Vec2 operator-(Vec2&& v, Vec2&& w);

        friend Vec2 operator*(float,Vec2&);
        friend Vec2 operator*(float,Vec2&&);

        friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
        
        explicit operator float() const; // Returns Magnitude
};

class Vec3
{
    private:
        float data[3] = {0};
    public:
        Vec3();
        Vec3(float x, float y, float z);
        Vec3(Vec3&);
        Vec3(Vec3&&);
        ~Vec3();

        Vec3& operator=(Vec3&);
        Vec3& operator=(Vec3&&);

        float& operator[](int);

        friend Vec3 operator+(Vec3& v, Vec3& w);
        friend Vec3 operator+(Vec3& v, Vec3&& w);
        friend Vec3 operator+(Vec3&& v, Vec3& w);
        friend Vec3 operator+(Vec3&& v, Vec3&& w);

        friend Vec3 operator-(Vec3& v, Vec3& w);
        friend Vec3 operator-(Vec3& v, Vec3&& w);
        friend Vec3 operator-(Vec3&& v, Vec3& w);
        friend Vec3 operator-(Vec3&& v, Vec3&& w);
        
        friend float operator*(Vec3& v, Vec3& w);
        friend float operator*(Vec3& v, Vec3&& w);
        friend float operator*(Vec3&& v, Vec3& w);
        friend float operator*(Vec3&& v, Vec3&& w);
       
        friend Vec3 operator%(Vec3& v, Vec3& w);
        friend Vec3 operator%(Vec3& v, Vec3&& w);
        friend Vec3 operator%(Vec3&& v, Vec3& w);
        friend Vec3 operator%(Vec3&& v, Vec3&& w);
        
        friend Vec3 operator*(float, Vec3&);
        friend Vec3 operator*(float, Vec3&&); 

        friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

        explicit operator float() const; // returns Magnitude
};


class Vec4
{
    private:
        float data[4] = {0};
    public:
        Vec4();
        Vec4(float x, float y, float z, float w);
        ~Vec4();
        Vec4(Vec4&);
        Vec4(Vec4&&);

        Vec4& operator=(Vec4&);
        Vec4& operator=(Vec4&&);

        float& operator[](int);

        friend Vec4 operator+(Vec4& v, Vec4& w);
        friend Vec4 operator+(Vec4& v, Vec4&& w);
        friend Vec4 operator+(Vec4&& v, Vec4& w);
        friend Vec4 operator+(Vec4&& v, Vec4&& w);        

        friend Vec4 operator-(Vec4& v, Vec4& w);
        friend Vec4 operator-(Vec4& v, Vec4&& w);
        friend Vec4 operator-(Vec4&& v, Vec4& w);
        friend Vec4 operator-(Vec4&& v, Vec4&& w);
       
        friend Vec4 operator*(float,Vec4&);
        friend Vec4 operator*(float,Vec4&&);

        friend std::ostream& operator<<(std::ostream& os, const Vec4& v);

        explicit operator float() const; // returns Magnitude
};

class Mat2
{
    private:
        float data[2][2] = {0};
    public:
        Mat2();
        Mat2(float m00, float m01, float m10, float m11);
        Mat2(Mat2&);
        Mat2(Mat2&&);
        ~Mat2();

        Mat2& operator=(Mat2&);
        Mat2& operator=(Mat2&&);

        float* operator[](int); 

        friend Mat2 operator+(Mat2& m, Mat2& w);
        friend Mat2 operator+(Mat2& m, Mat2&& w);
        friend Mat2 operator+(Mat2&& m, Mat2& w);
        friend Mat2 operator+(Mat2&& m, Mat2&& w);

        friend Mat2 operator-(Mat2& m, Mat2& w);
        friend Mat2 operator-(Mat2& m, Mat2&& w);
        friend Mat2 operator-(Mat2&& m, Mat2& w);
        friend Mat2 operator-(Mat2&& m, Mat2&& w);

        friend Mat2 operator*(Mat2& m, Mat2& w);
        friend Mat2 operator*(Mat2& m, Mat2&& w);
        friend Mat2 operator*(Mat2&& m, Mat2& w);
        friend Mat2 operator*(Mat2&& m, Mat2&& w);

        friend Vec2 operator*(Mat2& m, Vec2& v);
        friend Vec2 operator*(Mat2& m, Vec2&& v);
        friend Vec2 operator*(Mat2&& m, Vec2& v);
        friend Vec2 operator*(Mat2&& m, Vec2&& v);

        friend std::ostream& operator<<(std::ostream& os, const Mat2& m);
};


  
class Mat3
{
    private:
        float data[3][3] ={0};
    public:
        Mat3();
        Mat3(float m00, float m01, float m02,
             float m10, float m11, float m12,
             float m20, float m21, float m22);
        Mat3(Mat3&);
        Mat3(Mat3&&);
        ~Mat3();

        Mat3& operator=(Mat3&);
        Mat3& operator=(Mat3&&);

        float* operator[](int);

        friend Mat3 operator+(Mat3& m, Mat3& n);
        friend Mat3 operator+(Mat3& m, Mat3&& n);
        friend Mat3 operator+(Mat3&& m, Mat3& n);
        friend Mat3 operator+(Mat3&& m, Mat3&& n);

        friend Mat3 operator-(Mat3& m, Mat3& n);
        friend Mat3 operator-(Mat3& m, Mat3&& n);
        friend Mat3 operator-(Mat3&& m, Mat3& n);
        friend Mat3 operator-(Mat3&& m, Mat3&& n);

        friend Mat3 operator*(Mat3& m, Mat3& n); 
        friend Mat3 operator*(Mat3& m, Mat3&& n);
        friend Mat3 operator*(Mat3&& m, Mat3& n);
        friend Mat3 operator*(Mat3&& m, Mat3&& n);
  
        friend Vec3 operator*(Mat3& m, Vec3& v);
        friend Vec3 operator*(Mat3& m, Vec3&& v);
        friend Vec3 operator*(Mat3&& m, Vec3& v);
        friend Vec3 operator*(Mat3&& m, Vec3&& v);


        friend std::ostream& operator<<(std::ostream& os, const Mat3& v);

};

class Mat4
{
    private:
         float data[4][4] = {0};
    public:
         Mat4();
         Mat4(
                 float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33
             );

         Mat4(Mat4&);
         Mat4(Mat4&&);
         ~Mat4();

         Mat4& operator=(Mat4&);
         Mat4& operator=(Mat4&&);

         float* operator[](int);

         friend Mat4 operator+(Mat4& m, Mat4& w);
         friend Mat4 operator+(Mat4& m, Mat4&& w);
         friend Mat4 operator+(Mat4&& m, Mat4& w);
         friend Mat4 operator+(Mat4&& m, Mat4&& w);

         friend Mat4 operator-(Mat4& m, Mat4& w);
         friend Mat4 operator-(Mat4& m, Mat4&& w);
         friend Mat4 operator-(Mat4&& m, Mat4& w);
         friend Mat4 operator-(Mat4&& m, Mat4&& w);

         friend Mat4 operator*(Mat4& m, Mat4& w);
         friend Mat4 operator*(Mat4& m, Mat4&& w);
         friend Mat4 operator*(Mat4&& m, Mat4& w);
         friend Mat4 operator*(Mat4&& m, Mat4&& w);

         friend Vec4 operator*(Mat4& m, Vec4& w);
         friend Vec4 operator*(Mat4& m, Vec4&& w);
         friend Vec4 operator*(Mat4&& m, Vec4& w);
         friend Vec4 operator*(Mat4&& m, Vec4&& w);

         friend std::ostream& operator<<(std::ostream& os, const Mat4& m);
};

class Quat
{
    private:
        float data[4] = {0};
        static double slerp_dot_threshHold;
    public:
        Quat();
        Quat(float r, float x, float y, float z);
        Quat(Quat&);
        Quat(Quat&&);
        ~Quat();

        Quat& operator=(Quat&);
        Quat& operator=(Quat&&);

        float& operator[](int n);

        friend Quat operator~(Quat&);
        friend Quat operator~(Quat&&);

        friend Quat operator+(Quat& q, Quat& p);
        friend Quat operator+(Quat&& q, Quat& p);
        friend Quat operator+(Quat& q, Quat&& p);
        friend Quat operator+(Quat&& q, Quat&& p); 

        friend Quat operator-(Quat& q, Quat& p);
        friend Quat operator-(Quat&& q, Quat& p);
        friend Quat operator-(Quat& q, Quat&& p);
        friend Quat operator-(Quat&& q, Quat&& p); 

        friend Quat operator*(Quat& q, Quat& p);
        friend Quat operator*(Quat&& q, Quat& p);
        friend Quat operator*(Quat& q, Quat&& p);
        friend Quat operator*(Quat&& q, Quat&& p);

        friend Quat operator*(float s, Quat& q);
        friend Quat operator*(float s, Quat&& q);

        friend Quat slerp(Quat& q, Quat& p, float t);
        
        explicit operator float() const; // get magnitude
        
        Quat normal(); 

        friend std::ostream& operator<<(std::ostream& os, const Quat& q);
};


#endif
