/*
 * =====================================================================================
 *
 *       Filename:  Mathril.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/2022 07:31:34 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  YOUR NAME (Twins), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Mathril.h"

Vec2::Vec2()
{
}

Vec2::Vec2(float x, float y): data{x,y}
{
}

Vec2::~Vec2()
{
}

Vec2::Vec2(Vec2& vec): data{vec.data[0],vec.data[1]}
{
}

Vec2::Vec2(Vec2&& vec)
{
    std::move(vec.data, vec.data + 2, data);
}

Vec2& Vec2::operator=(Vec2& vec)
{
    if(this == &vec) [[unlikely]]
	return *this;
    data[0] = vec.data[0];
    data[1] = vec.data[1];
    return *this;
}

Vec2& Vec2::operator=(Vec2&& vec)
{
   std::move(vec.data, vec.data + 2, data);
   return *this;
}

float& Vec2::operator[](int n)
{
    if(n >= 0 && n < 2)
        return data[n];
    else
    {
        std::cerr << "Vec2 index " << n << " is out of bounds " << std::endl;
        n>0 ? n=n : n=-n;
        return data[n%2];
    }
}

Vec2 operator+(Vec2& v, Vec2& w)
{
    return Vec2(v.data[0] + w.data[0], v.data[1] + w.data[1]);
}

Vec2 operator+(Vec2& v, Vec2&& w)
{
    w.data[0] = w.data[0]+v.data[0];
    w.data[1] = w.data[1]+v.data[1];
    return std::move(w);
}

Vec2 operator+(Vec2&& v, Vec2& w)
{
    v.data[0] = w.data[0]+v.data[0];
    v.data[1] = w.data[1]+v.data[1];
    return std::move(v);
}

Vec2 operator+(Vec2&& v, Vec2&& w)
{
    v.data[0] = w.data[0]+v.data[0];
    v.data[1] = w.data[1]+v.data[1];
    return std::move(v);
}


Vec2 operator-(Vec2& v, Vec2& w)
{
    return Vec2(v.data[0] - w.data[0], v.data[1] - w.data[1]);
}

Vec2 operator-(Vec2& v, Vec2&& w)
{
    w.data[0] = v.data[0] - w.data[0];
    w.data[1] = v.data[1] - w.data[1];
    return std::move(w);
}

Vec2 operator-(Vec2&& v, Vec2& w)
{
    v.data[0] = v.data[0] - w.data[0];
    v.data[1] = v.data[1] - w.data[1];
    return std::move(v);
}

Vec2 operator-(Vec2&& v, Vec2&& w)
{
    v.data[0] = v.data[0]-w.data[0];
    v.data[1] = v.data[1]-w.data[1];
    return std::move(v);
}

Vec2 operator*(float s, Vec2& vec)
{
    return Vec2(s*vec.data[0], s*vec.data[1]);
}

Vec2 operator*(float s, Vec2&& vec)
{
    vec.data[0] = s*vec.data[0];
    vec.data[1] = s*vec.data[1];
    return std::move(vec);
}



std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
	os << "[" << v.data[0] << ", " << v.data[1] <<  "]";
	return os;
}

Vec2::operator float() const
{
    return sqrt(data[0]*data[0] + data[1]*data[1]);
}

Vec3::Vec3()
{}

Vec3::Vec3(float x, float y, float z): data{x, y, z}
{
}

Vec3::Vec3(Vec3& vec): data{vec.data[0], vec.data[1], vec.data[2]}
{
} 

Vec3::Vec3(Vec3&& vec)
{
    std::move(vec.data, vec.data + 3, data);
}

Vec3::~Vec3()
{
}

Vec3& Vec3::operator=(Vec3& vec)
{
    if(this== &vec) [[unlikely]]
	return *this;
    for(int i=0; i<3; i++)
        data[i] = vec.data[i];
     return *this; 
}

Vec3& Vec3::operator=(Vec3&& vec)
{
      std::move(vec.data, vec.data + 3, data);
     return *this; 
}

float& Vec3::operator[](int n)
{
    
   if(n>=0 && n<3)
       return data[n];
   else
   {
       std::cerr << " Vec3 index "<<n<<" out of bounds "<<std::endl;
       n>0 ? n=n : n=-n;
       return data[n%3];
   }
}

Vec3 operator+(Vec3& v, Vec3& w)
{
    return Vec3(v.data[0]+w.data[0], v.data[1]+w.data[1], v.data[2]+w.data[2]);
}

Vec3 operator+(Vec3& v, Vec3&& w)
{
    for(int i=0; i<3; i++)
        w.data[i] = w.data[i] + v.data[i];
    return std::move(w);
}

Vec3 operator+(Vec3&& v, Vec3& w)
{
    for(int i=0; i<3; i++)
        v.data[i] = w.data[i] + v.data[i];
    return std::move(v);
}

Vec3 operator+(Vec3&& v, Vec3&& w)
{
    for(int i=0; i<3; i++)
        v.data[i] = w.data[i] + v.data[i];
    return std::move(v);
}

Vec3 operator-(Vec3& v, Vec3& w)
{
    return Vec3(v.data[0]-w.data[0], v.data[1]-w.data[1], v.data[2]-w.data[2]);
}

Vec3 operator-(Vec3& v, Vec3&& w)
{
    for(int i=0; i<3; i++)
        w.data[i] = v.data[i] - w.data[i];
    return std::move(w);
}

Vec3 operator-(Vec3&& v, Vec3& w)
{
    for(int i=0; i<3; i++)
        v.data[i] = v.data[i] - w.data[i];
    return std::move(v);
}

Vec3 operator-(Vec3&& v, Vec3&& w)
{
    for(int i=0; i<3; i++)
        v.data[i] = v.data[i] - w.data[i];
    return std::move(v);

}
float operator*(Vec3& v, Vec3& w)
{
    return (v.data[0]*w.data[0] + v.data[1]*w.data[1] + v.data[2]*w.data[2]); 
}

float operator*(Vec3& v, Vec3&& w)
{
    return (v.data[0]*w.data[0] + v.data[1]*w.data[1] + v.data[2]*w.data[2]); 
}


float operator*(Vec3&& v, Vec3& w)
{
    return (v.data[0]*w.data[0] + v.data[1]*w.data[1] + v.data[2]*w.data[2]); 
}


float operator*(Vec3&& v, Vec3&& w)
{
    return (v.data[0]*w.data[0] + v.data[1]*w.data[1] + v.data[2]*w.data[2]); 
}

Vec3 operator%(Vec3& a, Vec3& b)
{
	return Vec3(a.data[1]*b.data[2] -a.data[2]*b.data[1], a.data[2]*b.data[0] - a.data[0]*b.data[2], a.data[0]*b.data[1]-a.data[1]*b.data[0]);
}

Vec3 operator%(Vec3& a, Vec3&& b)
{
	float x = a.data[1] * b.data[2] - a.data[2] * b.data[1];
	float y = a.data[2] * b.data[0] - a.data[0] * b.data[2];
	float z = a.data[0] * b.data[1] - a.data[1] * b.data[0];
	b[0] = x;	b[1] = y;	b[2] = z;
	return std::move(b);
}

Vec3 operator%(Vec3&& a, Vec3& b)
{
	float x = a.data[1] * b.data[2] - a.data[2] * b.data[1];
	float y = a.data[2] * b.data[0] - a.data[0] * b.data[2];
	float z = a.data[0] * b.data[1] - a.data[1] * b.data[0];
	a[0] = x;	a[1] = y;	a[2] = z;
	return std::move(a);
}

Vec3 operator%(Vec3&& a, Vec3&& b)
{
	float x = a.data[1] * b.data[2] - a.data[2] * b.data[1];
	float y = a.data[2] * b.data[0] - a.data[0] * b.data[2];
	float z = a.data[0] * b.data[1] - a.data[1] * b.data[0];
	b[0] = x;	b[1] = y;	b[2] = z;
	return std::move(b);
}

Vec3 operator*(float s, Vec3& v)
{
    return Vec3(s*v.data[0], s*v.data[1], s*v.data[2]);
}

Vec3 operator*(float s, Vec3&& v)
{
    for(int i=0; i<3; i++)
        v.data[i] = s*v.data[i];
    return std::move(v);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "[" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << "]";
	return os;
}

Vec3::operator float() const
{
    return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}

Vec4::Vec4()
{
}

Vec4::Vec4(float x, float y, float z, float w): data{x, y, z, w}
{
}

Vec4::~Vec4()
{
}

Vec4::Vec4(Vec4& vec): data{vec.data[0], vec.data[1], vec.data[2], vec.data[3]}
{
}

Vec4::Vec4(Vec4&& vec)
{
      std::move(vec.data, vec.data+4, data);
}

Vec4& Vec4::operator=(Vec4& vec)
{
    if(this == &vec) [[unlikely]]
    	return *this;
    data[0] = vec.data[0];
    data[1] = vec.data[1];
    return *this;
}

Vec4& Vec4::operator=(Vec4&& vec)
{
     std::move(vec.data, vec.data+4, data);
    return *this;
}

float& Vec4::operator[](int n)
{
   if(n >= 0 && n < 4)
   {
        return data[n];
   }
   else
   {
       std::cerr << "index of Vec4 is out of bounds" << std::endl;
       n>0 ? n=n : n=-n;
       return data[n%4];
   }
}

Vec4 operator+(Vec4& v, Vec4& w)
{
    return Vec4(v.data[0]+w.data[0], v.data[1]+w.data[1], v.data[2]+w.data[2], v.data[3]+w.data[3]);
}

Vec4 operator+(Vec4& v, Vec4&& w)
{
    for(int i=0; i<4; i++)
        w.data[i] = v.data[i] + w.data[i];
    return std::move(w);
}

Vec4 operator+(Vec4&& v, Vec4& w)
{
    for(int i=0; i<4; i++)
        v.data[i] = v.data[i] + w.data[i];
    return std::move(v);
}

Vec4 operator+(Vec4&& v, Vec4&& w)
{
    for(int i=0; i<4; i++)
        v.data[i] = v.data[i] + w.data[i];
    return std::move(v);
}


Vec4 operator-(Vec4& v, Vec4& w)
{
    return Vec4(v.data[0]-w.data[0], v.data[1]-w.data[1], v.data[2]-w.data[2], v.data[3]-w.data[3]);
}

Vec4 operator-(Vec4& v, Vec4&& w)
{
    for(int i=0; i<4; i++)
        w.data[i] = v.data[i] - w.data[i];
    return std::move(w);
}

Vec4 operator-(Vec4&& v, Vec4& w)
{
    for(int i=0; i<4; i++)
        v.data[i] = v.data[i] - w.data[i];
    return std::move(v);
}

Vec4 operator-(Vec4&& v, Vec4&& w)
{
    for(int i=0; i<4; i++)
        v.data[i] = v.data[i] - w.data[i];
    return std::move(v);
}

Vec4 operator*(float s, Vec4& v)
{
    return Vec4(s*v.data[0], s*v.data[1], s*v.data[2], s*v.data[3]);
}

Vec4 operator*(float s, Vec4&& v)
{
    for(int i=0; i<4; i++)
        v.data[i] = s*v.data[i];
    return std::move(v);
}


std::ostream& operator<<(std::ostream& os, const Vec4& v)
{
	os << "[" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ", " << v.data[3] << "]";
	return os;
}

Vec4::operator float() const
{
    return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3]);
}


Mat2::Mat2()
{ 
}

Mat2::Mat2(float m00, float m01, float m10, float m11)
{
    data[0][0] = m00;
    data[0][1] = m01;
    data[1][0] = m10;
    data[1][1] = m11;
}

Mat2::Mat2(Mat2& m)
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }

}

Mat2::Mat2(Mat2&& m)
{
    std::move(m.data[0], m.data[0] + 4, data[0]);
}

Mat2::~Mat2()
{
}


Mat2& Mat2::operator=(Mat2& m)
{
    if( this == &m ) [[unlikely]] 
    	return *this;

    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            data[i][j] = m.data[i][j];

    return *this;
}

Mat2& Mat2::operator=(Mat2&& m)
{
    std::move(m.data[0], m.data[0] + 4, data[0]);
    return *this;
}

float* Mat2::operator[](int n)
{
    return data[n];
}

Mat2 operator+(Mat2& m, Mat2& w)
{
    return Mat2( m.data[0][0] + w.data[0][0],  m.data[0][1] + w.data[0][1],
                 m.data[1][0] + w.data[1][0],  m.data[1][1] + w.data[1][1] );
}

Mat2 operator+(Mat2& m, Mat2&& w)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            w[i][j] = m[i][j] + w[i][j];
    return std::move(w);
}

Mat2 operator+(Mat2&& m, Mat2& w)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            m[i][j] = m[i][j] + w[i][j];
    return std::move(m);
}

Mat2 operator+(Mat2&& m, Mat2&& w)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            m[i][j] = m[i][j] + w[i][j];
    return std::move(m);
}

Mat2 operator-(Mat2& m, Mat2& w)
{
    return Mat2( m.data[0][0] - w.data[0][0],  m.data[0][1] - w.data[0][1],
                 m.data[1][0] - w.data[1][0],  m.data[1][1] - w.data[1][1] );
}

Mat2 operator-(Mat2& m, Mat2&& w)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            w[i][j] = m[i][j] - w[i][j];
    return std::move(w);
}

Mat2 operator-(Mat2&& m, Mat2& w)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            m[i][j] = m[i][j] - w[i][j];
    return std::move(m);
}

Mat2 operator-(Mat2&& m, Mat2&& w)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            m[i][j] = m[i][j] - w[i][j];
    return std::move(m);
}

Mat2 operator*(Mat2& m, Mat2& w)
{    
    return Mat2( m.data[0][0]*w.data[0][0] + m.data[0][1]*w.data[1][0],
                 m.data[0][0]*w.data[0][1] + m.data[0][1]*w.data[1][1],
                 m.data[1][0]*w.data[0][0] + m.data[1][1]*w.data[1][0],
                 m.data[1][0]*w.data[0][1] + m.data[1][1]*w.data[1][1] );
}

Mat2 operator*(Mat2&& m, Mat2& w)
{ 
    for(int i=0; i<2; i++)
    {
       float temp[2] = {0};
       for(int j=0; j<2; j++)
        {
            for(int k=0; k<2; k++)
                temp[j] += m.data[i][k]*w.data[k][j];
        }
        for(int x=0; x<2; x++) 
            m.data[i][x] = temp[x];    
    }

    return std::move(m);
}

Mat2 operator*(Mat2& m, Mat2&& w)
{
    for(int i=0; i<2; i++)
    { 
        float temp[2] = {0};
        for(int j=0; j<2; j++)
        {
            for(int k=0; k<2; k++)
                temp[j] += m.data[j][k]*w.data[k][i];
        }
        for(int x=0; x<2; x++)
            w.data[x][i] = temp[x];
   }

    return std::move(w);
}

Mat2 operator*(Mat2&& m, Mat2&& w)
{ 
    for(int i=0; i<2; i++)
    {
       float temp[2] = {0};
       for(int j=0; j<2; j++)
        {
            for(int k=0; k<2; k++)
            {
                temp[j] += m.data[i][k]*w.data[k][j];
            }
        }
        for(int x=0; x<2; x++) 
            m.data[i][x] = temp[x]; 
    }

    return std::move(m);
}


Vec2 operator*(Mat2& m, Vec2& v)
{
    return Vec2(
                v[0]*m.data[0][0] + v[1]*m.data[0][1],
                v[0]*m.data[1][0] + v[1]*m.data[1][1]
           );
}

Vec2 operator*(Mat2& m, Vec2&& v)
{
    float temp[2] = {0};
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            temp[i] += v[j]*m.data[i][j];
        }
    }
    for(int i=0; i<2; i++)
        v[i] = temp[i];

    return std::move(v);
}

Vec2 operator*(Mat2&& m, Vec2& v)
{
  
    return Vec2(
                v[0]*m.data[0][0] + v[1]*m.data[0][1],
                v[0]*m.data[1][0] + v[1]*m.data[1][1]
             );
}

Vec2 operator*(Mat2&& m, Vec2&& v)
{
    float temp[2] = {0};
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            temp[i] += v[j]*m.data[i][j];
        }
    }
    for(int i=0; i<2; i++)
        v[i] = temp[i];

    return std::move(v);
}


std::ostream& operator<<(std::ostream& os, const Mat2& m)
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            os << m.data[i][j] << ", ";
        }
        os << std::endl;
    }

    return os;
}

  
Mat3::Mat3()
{
}

Mat3::Mat3(float m00, float m01, float m02,
           float m10, float m11, float m12,
           float m20, float m21, float m22)
{ 
    data[0][0] = m00; data[0][1] = m01; data[0][2] = m02;
    data[1][0] = m10; data[1][1] = m11; data[1][2] = m12;
    data[2][0] = m20; data[2][1] = m21; data[2][2] = m22;
}

Mat3::Mat3(Mat3& mat)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            data[i][j] = mat.data[i][j];
        }
    }
}

Mat3::Mat3(Mat3&& mat)
{
    std::move(mat.data[0], mat.data[0] + 9, data[0]);
}

Mat3::~Mat3()
{
}

Mat3& Mat3::operator=(Mat3& mat)
{
    if(this == &mat) [[unlikely]] 
    	return *this;

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            data[i][j] = mat.data[i][j];

    return *this;
}



Mat3& Mat3::operator=(Mat3&& mat)
{
    std::move(mat.data[0], mat.data[0] + 9, data[0]);
   return *this;
}

float* Mat3::operator[](int n)
{
    return data[n];
}
  
Mat3 operator+(Mat3& m, Mat3& n)
{
    return Mat3(m.data[0][0]+n.data[0][0], m.data[0][1]+n.data[0][1], m.data[0][2]+n.data[0][2],
                m.data[1][0]+n.data[1][0], m.data[1][1]+n.data[1][1], m.data[1][2]+n.data[1][2],
                m.data[2][0]+n.data[2][0], m.data[2][1]+n.data[2][1], m.data[2][2]+n.data[2][2]);
}

Mat3 operator+(Mat3& m, Mat3&& n)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            n[i][j] = m[i][j] + n[i][j];
    return std::move(n);
}

Mat3 operator+(Mat3&& m, Mat3& n)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i][j] = m[i][j] + n[i][j];
    return std::move(m);
}

Mat3 operator+(Mat3&& m, Mat3&& n)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i][j] = m[i][j] + n[i][j];
    return std::move(m);
}


Mat3 operator-(Mat3& m, Mat3& n)
{
    return Mat3(m.data[0][0]-n.data[0][0], m.data[0][1]-n.data[0][1], m.data[0][2]-n.data[0][2],
                m.data[1][0]-n.data[1][0], m.data[1][1]-n.data[1][1], m.data[1][2]-n.data[1][2],
                m.data[2][0]-n.data[2][0], m.data[2][1]-n.data[2][1], m.data[2][2]-n.data[2][2]);
}

Mat3 operator-(Mat3& m, Mat3&& n)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            n[i][j] = m[i][j] - n[i][j];
    return std::move(n);
}

Mat3 operator-(Mat3&& m, Mat3& n)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i][j] = m[i][j] - n[i][j];
    return std::move(m);
}

Mat3 operator-(Mat3&& m, Mat3&& n)
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i][j] = m[i][j] - n[i][j];
    return std::move(m);
}

Mat3 operator*(Mat3& m, Mat3& n)
{
   return Mat3(m.data[0][0]*n.data[0][0] + m.data[0][1]*n.data[1][0] + m.data[0][2]*n.data[2][0],
               m.data[0][0]*n.data[0][1] + m.data[0][1]*n.data[1][1] + m.data[0][2]*n.data[2][1],
               m.data[0][0]*n.data[0][2] + m.data[0][1]*n.data[1][2] + m.data[0][2]*n.data[2][2],
               m.data[1][0]*n.data[0][0] + m.data[1][1]*n.data[1][0] + m.data[1][2]*n.data[2][0],
               m.data[1][0]*n.data[0][1] + m.data[1][1]*n.data[1][1] + m.data[1][2]*n.data[2][1],
               m.data[1][0]*n.data[0][2] + m.data[1][1]*n.data[1][2] + m.data[1][2]*n.data[2][2],
               m.data[2][0]*n.data[0][0] + m.data[2][1]*n.data[1][0] + m.data[2][2]*n.data[2][0],
               m.data[2][0]*n.data[0][1] + m.data[2][1]*n.data[1][1] + m.data[2][2]*n.data[2][1],
               m.data[2][0]*n.data[0][2] + m.data[2][1]*n.data[1][2] + m.data[2][2]*n.data[2][2] 
              );
}

Mat3 operator*(Mat3&& m, Mat3& n)
{
    for(int i=0; i<3; i++)
    {
        float temp[3] = {0};
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                temp[j] += m.data[i][k] * n.data[k][j];
            }
        }
        for(int x=0; x<3; x++)
            m.data[i][x] = temp[x];
    }

    return std::move(m);
}

Mat3 operator*(Mat3& m, Mat3&& n)
{
    for(int i=0; i<3; i++)
    {
        float temp[3] = {0};
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                temp[j] += m.data[j][k] * n.data[k][i];
            }
        }
        for(int x=0; x<3; x++)
            n.data[x][i] = temp[x];
    }

    return std::move(n);
}


Mat3 operator*(Mat3&& m, Mat3&& n)
{
    for(int i=0; i<3; i++)
    {
        float temp[3] = {0};
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                temp[j] += m.data[i][k] * n.data[k][j];
            }
        }
        for(int x=0; x<3; x++)
            m.data[i][x] = temp[x];
    }

    return std::move(m);
}

Vec3 operator*(Mat3& m, Vec3& v)
{
    return Vec3(v[0]*m.data[0][0] + v[1]*m.data[0][1] + v[2]*m.data[0][2],
                v[0]*m.data[1][0] + v[1]*m.data[1][1] + v[2]*m.data[1][2],
                v[0]*m.data[2][0] + v[1]*m.data[2][1] + v[2]*m.data[2][2]);
}

Vec3 operator*(Mat3& m, Vec3&& v)
{
    float temp[3] = {0};
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            temp[i] += v[j]*m.data[i][j];
        }
    }
    for(int i=0; i<3; i++)
        v[i] = temp[i];

    return std::move(v);
}

Vec3 operator*(Mat3&& m, Vec3& v)
{
    return Vec3(v[0]*m.data[0][0] + v[1]*m.data[0][1] + v[2]*m.data[0][2],
                v[0]*m.data[1][0] + v[1]*m.data[1][1] + v[2]*m.data[1][2],
                v[0]*m.data[2][0] + v[1]*m.data[2][1] + v[2]*m.data[2][2]);
}


Vec3 operator*(Mat3&& m, Vec3&& v)
{
    float temp[3] = {0};
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            temp[i] += v[j]*m.data[i][j];
        }
    }
    for(int i=0; i<3; i++)
        v[i] = temp[i];

    return std::move(v);
}


std::ostream& operator<<(std::ostream& os, const Mat3& m)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            os << m.data[i][j] << ", ";
        }
        os << std::endl;
    }

    return os;
}


Mat4::Mat4()
{
}

Mat4::Mat4(
     float m00, float m01, float m02, float m03,
     float m10, float m11, float m12, float m13,
     float m20, float m21, float m22, float m23,
     float m30, float m31, float m32, float m33
                                                )
{
    data[0][0] = m00;   data[0][1] = m01;   data[0][2] = m02;   data[0][3] = m03;
    data[1][0] = m10;   data[1][1] = m11;   data[1][2] = m12;   data[1][3] = m13;
    data[2][0] = m20;   data[2][1] = m21;   data[2][2] = m22;   data[2][3] = m23;
    data[3][0] = m30;   data[3][1] = m31;   data[3][2] = m32;   data[3][3] = m33;
}

Mat4::Mat4(Mat4& m)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
            data[i][j] = m.data[i][j];
    }
}

Mat4::Mat4(Mat4&& m)
{
    std::move(m.data[0],m.data[0]+16,data[0]);
}

Mat4::~Mat4()
{
}

Mat4& Mat4::operator=(Mat4& m)
{
    if( this == &m ) [[unlikely]] 
    	return *this;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            data[i][j] = m.data[i][j];

    return *this;
}

Mat4& Mat4::operator=(Mat4&& m)
{
    std::move(m.data[0], m.data[0]+16, data[0]);
    return *this;
}

float* Mat4::operator[](int n)
{
    return data[n];
}

Mat4 operator+(Mat4& m, Mat4& w)
{
    return Mat4(
        m.data[0][0]+w.data[0][0], m.data[0][1]+w.data[0][1], m.data[0][2]+w.data[0][2], m.data[0][3]+w.data[0][3],
        m.data[1][0]+w.data[1][0], m.data[1][1]+w.data[1][1], m.data[1][2]+w.data[1][2], m.data[1][3]+w.data[1][3],
        m.data[2][0]+w.data[2][0], m.data[2][1]+w.data[2][1], m.data[2][2]+w.data[2][2], m.data[2][3]+w.data[2][3],
        m.data[3][0]+w.data[3][0], m.data[3][1]+w.data[3][1], m.data[3][2]+w.data[3][2], m.data[3][3]+w.data[3][3]
    );
} 

Mat4 operator+(Mat4& m, Mat4&& w)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            w[i][j] = m[i][j] + w[i][j];
    return std::move(w);
}

Mat4 operator+(Mat4&& m, Mat4& w)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            m[i][j] = m[i][j] + w[i][j];
    return std::move(m);
}

Mat4 operator+(Mat4&& m, Mat4&& w)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            m[i][j] = m[i][j] + w[i][j];
    return std::move(m);
}

Mat4 operator-(Mat4& m, Mat4& w)
{
    return Mat4(
            m.data[0][0]-w.data[0][0], m.data[0][1]-w.data[0][1], m.data[0][2]-w.data[0][2], m.data[0][3]-w.data[0][3],
            m.data[1][0]-w.data[1][0], m.data[1][1]-w.data[1][1], m.data[1][2]-w.data[1][2], m.data[1][3]-w.data[1][3],
            m.data[2][0]-w.data[2][0], m.data[2][1]-w.data[2][1], m.data[2][2]-w.data[2][2], m.data[2][3]-w.data[2][3],
            m.data[3][0]-w.data[3][0], m.data[3][1]-w.data[3][1], m.data[3][2]-w.data[3][2], m.data[3][3]-w.data[3][3]
        );
}

Mat4 operator-(Mat4& m, Mat4&& w)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            w[i][j] = m[i][j] - w[i][j];
    return std::move(w);
}

Mat4 operator-(Mat4&& m, Mat4& w)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            m[i][j] = m[i][j] - w[i][j];
    return std::move(m);
}

Mat4 operator-(Mat4&& m, Mat4&& w)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            m[i][j] = m[i][j] - w[i][j];
    return std::move(m);
}

Mat4 operator*(Mat4& m, Mat4& w)
{    
    return Mat4(
                 m.data[0][0]*w.data[0][0] + m.data[0][1]*w.data[1][0] + m.data[0][2]*w.data[2][0] + m.data[0][3]*w.data[3][0],
                 m.data[0][0]*w.data[0][1] + m.data[0][1]*w.data[1][1] + m.data[0][2]*w.data[2][1] + m.data[0][3]*w.data[3][1],
                 m.data[0][0]*w.data[0][2] + m.data[0][1]*w.data[1][2] + m.data[0][2]*w.data[2][2] + m.data[0][3]*w.data[3][2],
                 m.data[0][0]*w.data[0][3] + m.data[0][1]*w.data[1][3] + m.data[0][2]*w.data[2][3] + m.data[0][3]*w.data[3][3],

                 m.data[1][0]*w.data[0][0] + m.data[1][1]*w.data[1][0] + m.data[1][2]*w.data[2][0] + m.data[1][3]*w.data[3][0],
                 m.data[1][0]*w.data[0][1] + m.data[1][1]*w.data[1][1] + m.data[1][2]*w.data[2][1] + m.data[1][3]*w.data[3][1],
                 m.data[1][0]*w.data[0][2] + m.data[1][1]*w.data[1][2] + m.data[1][2]*w.data[2][2] + m.data[1][3]*w.data[3][2],
                 m.data[1][0]*w.data[0][3] + m.data[1][1]*w.data[1][3] + m.data[1][2]*w.data[2][3] + m.data[1][3]*w.data[3][3],

                 m.data[2][0]*w.data[0][0] + m.data[2][1]*w.data[1][0] + m.data[2][2]*w.data[2][0] + m.data[2][3]*w.data[3][0],
                 m.data[2][0]*w.data[0][1] + m.data[2][1]*w.data[1][1] + m.data[2][2]*w.data[2][1] + m.data[2][3]*w.data[3][1],
                 m.data[2][0]*w.data[0][2] + m.data[2][1]*w.data[1][2] + m.data[2][2]*w.data[2][2] + m.data[2][3]*w.data[3][2],
                 m.data[2][0]*w.data[0][3] + m.data[2][1]*w.data[1][3] + m.data[2][2]*w.data[2][3] + m.data[2][3]*w.data[3][3],

                 m.data[3][0]*w.data[0][0] + m.data[3][1]*w.data[1][0] + m.data[3][2]*w.data[2][0] + m.data[3][3]*w.data[3][0],
                 m.data[3][0]*w.data[0][1] + m.data[3][1]*w.data[1][1] + m.data[3][2]*w.data[2][1] + m.data[3][3]*w.data[3][1],
                 m.data[3][0]*w.data[0][2] + m.data[3][1]*w.data[1][2] + m.data[3][2]*w.data[2][2] + m.data[3][3]*w.data[3][2],
                 m.data[3][0]*w.data[0][3] + m.data[3][1]*w.data[1][3] + m.data[3][2]*w.data[2][3] + m.data[3][3]*w.data[3][3]

            );
}

Mat4 operator*(Mat4&& m, Mat4& w)
{ 
    for(int i=0; i<4; i++)
    {
       float temp[4] = {0};
       for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
                temp[j] += m.data[i][k]*w.data[k][j];
        }
        for(int x=0; x<4; x++) 
            m.data[i][x] = temp[x];    
    }

    return std::move(m);
}

Mat4 operator*(Mat4& m, Mat4&& w)
{
    for(int i=0; i<4; i++)
    { 
        float temp[4] = {0};
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
                temp[j] += m.data[j][k]*w.data[k][i];
        }
        for(int x=0; x<4; x++)
            w.data[x][i] = temp[x];
   }

    return std::move(w);
}

Mat4 operator*(Mat4&& m, Mat4&& w)
{ 
    for(int i=0; i<4; i++)
    {
       float temp[4] = {0};
       for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                temp[j] += m.data[i][k]*w.data[k][j];
            }
        }
        for(int x=0; x<4; x++) 
            m.data[i][x] = temp[x];    
    }

    return std::move(m);
}

Vec4 operator*(Mat4& m, Vec4& v)
{
    return Vec4(
                v[0]*m.data[0][0] + v[1]*m.data[0][1] + v[2]*m.data[0][2] + v[3]*m.data[0][3],
                v[0]*m.data[1][0] + v[1]*m.data[1][1] + v[2]*m.data[1][2] + v[3]*m.data[1][3],
                v[0]*m.data[2][0] + v[1]*m.data[2][1] + v[2]*m.data[2][2] + v[3]*m.data[2][3],
                v[0]*m.data[3][0] + v[1]*m.data[3][1] + v[2]*m.data[3][2] + v[3]*m.data[3][3]
            );
}

Vec4 operator*(Mat4& m, Vec4&& v)
{
    float temp[4] = {0};
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            temp[i] += v[j]*m.data[i][j];
        }
    }
    for(int i=0; i<4; i++)
        v[i] = temp[i];

    return std::move(v);
}

Vec4 operator*(Mat4&& m, Vec4& v)
{
  
    return Vec4(
                v[0]*m.data[0][0] + v[1]*m.data[0][1] + v[2]*m.data[0][2] + v[3]*m.data[0][3],
                v[0]*m.data[1][0] + v[1]*m.data[1][1] + v[2]*m.data[1][2] + v[3]*m.data[1][3],
                v[0]*m.data[2][0] + v[1]*m.data[2][1] + v[2]*m.data[2][2] + v[3]*m.data[2][3],
                v[0]*m.data[3][0] + v[1]*m.data[3][1] + v[2]*m.data[3][2] + v[3]*m.data[3][3]
            );
}

Vec4 operator*(Mat4&& m, Vec4&& v)
{
    float temp[4] = {0};
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            temp[i] += v[j]*m.data[i][j];
        }
    }
    for(int i=0; i<4; i++)
        v[i] = temp[i];

    return std::move(v);
}

std::ostream& operator<<(std::ostream& os, const Mat4& m)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            os << m.data[i][j] <<", ";
        }
        os << std::endl;
    }

    return os;
}


double Quat::slerp_dot_threshHold = 0.9995;

Quat::Quat()
{
}

Quat::Quat(float r, float x, float y, float z) : data{r,x,y,z}
{
}

Quat::Quat(Quat& q)
{
    for(int i=0; i<4; i++)
        data[i] = q.data[i];
}

Quat::Quat(Quat&& q)
{
    std::move(q.data, q.data+4, data);
}

Quat::~Quat()
{
}

Quat& Quat::operator=(Quat& q)
{
    if(this == &q) [[unlikely]] 
    	return *this;

    for(int i=0; i<4; i++)
        data[i] = q.data[i];

    return *this;
}

Quat& Quat::operator=(Quat&& q)
{
   std::move(q.data, q.data+4, data);
   return *this;
}

float& Quat::operator[](int n)
{
   if(n >= 0 && n < 4)
   {
        return data[n];
   }
   else
   {
       std::cerr << "index of Quat is out of bounds" << std::endl;
       n>0 ? n=n : n=-n;
       return data[n%4];
   }

}

Quat operator~(Quat& q)
{
    return Quat(q.data[0],-q.data[1],-q.data[2],-q.data[3]);
}

Quat operator~(Quat&& q)
{
   for(int i=1; i<3; i++)
       q.data[i] = -q.data[i];
    return std::move(q);
}

Quat operator+(Quat& q, Quat& p)
{
    return Quat(q.data[0]+p.data[0], q.data[1]+p.data[1], q.data[2]+p.data[2], q.data[3]+p.data[3]);
}

Quat operator+(Quat&& q, Quat& p)
{
    for(int i=0; i<4; i++) 
        q.data[i] = q.data[i] + p.data[i];
    
    return std::move(q);
}

Quat operator+(Quat& q, Quat&& p)
{
    for(int i=0; i<4; i++)
        p.data[i] = q.data[i] + p.data[i];

    return std::move(p);
}

Quat operator+(Quat&& q, Quat&& p)
{
    for(int i=0; i<4; i++) 
        q.data[i] = q.data[i] + p.data[i];
    
    return std::move(q);
}


Quat operator-(Quat& q, Quat& p)
{
    return Quat(q.data[0]-p.data[0], q.data[1]-p.data[1], q.data[2]-p.data[2], q.data[3]-p.data[3]);
}

Quat operator-(Quat&& q, Quat& p)
{
    for(int i=0; i<4; i++) 
        q.data[i] = q.data[i] - p.data[i];
    
    return std::move(q);
}

Quat operator-(Quat& q, Quat&& p)
{
    for(int i=0; i<4; i++)
        p.data[i] = q.data[i] - p.data[i];

    return std::move(p);
}

Quat operator-(Quat&& q, Quat&& p)
{
    for(int i=0; i<4; i++) 
        q.data[i] = q.data[i] - p.data[i];
    
    return std::move(q);
}



Quat operator*(Quat& q, Quat& p)
{
    return Quat(q.data[0]*p.data[0] - q.data[1]*p.data[1] - q.data[2]*p.data[2] - q.data[3]*p.data[3],
                q.data[0]*p.data[1] + q.data[1]*p.data[0] + q.data[2]*p.data[3] - q.data[3]*p.data[2],
                q.data[0]*p.data[2] - q.data[1]*p.data[3] + q.data[2]*p.data[0] + q.data[3]*p.data[1],
                q.data[0]*p.data[3] + q.data[1]*p.data[2] - q.data[2]*p.data[1] + q.data[3]*p.data[0]);
}

Quat operator*(Quat&& q, Quat& p)
{
    float temp[4];
    temp[0] = q.data[0]*p.data[0] - q.data[1]*p.data[1] - q.data[2]*p.data[2] - q.data[3]*p.data[3];
    temp[1] = q.data[0]*p.data[1] + q.data[1]*p.data[0] + q.data[2]*p.data[3] - q.data[3]*p.data[2];
    temp[2] = q.data[0]*p.data[2] - q.data[1]*p.data[3] + q.data[2]*p.data[0] + q.data[3]*p.data[1];
    temp[3] = q.data[0]*p.data[3] + q.data[1]*p.data[2] - q.data[2]*p.data[1] + q.data[3]*p.data[0];

    for(int i=0; i<4; i++)
        q.data[i] = temp[i];


    return std::move(q);
}


Quat operator*(Quat& q, Quat&& p)
{
    float temp[4];
    temp[0] = q.data[0]*p.data[0] - q.data[1]*p.data[1] - q.data[2]*p.data[2] - q.data[3]*p.data[3];
    temp[1] = q.data[0]*p.data[1] + q.data[1]*p.data[0] + q.data[2]*p.data[3] - q.data[3]*p.data[2];
    temp[2] = q.data[0]*p.data[2] - q.data[1]*p.data[3] + q.data[2]*p.data[0] + q.data[3]*p.data[1];
    temp[3] = q.data[0]*p.data[3] + q.data[1]*p.data[2] - q.data[2]*p.data[1] + q.data[3]*p.data[0];

    for(int i=0; i<4; i++)
        p.data[i] = temp[i];


    return std::move(p);
}


Quat operator*(Quat&& q, Quat&& p)
{
    float temp[4];
    temp[0] = q.data[0]*p.data[0] - q.data[1]*p.data[1] - q.data[2]*p.data[2] - q.data[3]*p.data[3];
    temp[1] = q.data[0]*p.data[1] + q.data[1]*p.data[0] + q.data[2]*p.data[3] - q.data[3]*p.data[2];
    temp[2] = q.data[0]*p.data[2] - q.data[1]*p.data[3] + q.data[2]*p.data[0] + q.data[3]*p.data[1];
    temp[3] = q.data[0]*p.data[3] + q.data[1]*p.data[2] - q.data[2]*p.data[1] + q.data[3]*p.data[0];

    for(int i=0; i<4; i++)
        p.data[i] = temp[i];


    return std::move(p);
}


Quat operator*(float s, Quat& q)
{
    return Quat(s*q.data[0], s*q.data[1], s*q.data[2], s*q.data[3]);
}

Quat operator*(float s, Quat&& q)
{
    for(int i=0; i<4; i++)
        q.data[i] = s*q.data[i];

    return std::move(q);
}

Quat::operator float() const
{
    return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2] + data[3]*data[3]);
}
  
Quat slerp(Quat& q, Quat& p, float t)
{
    	double cosA = (q.data[0] * p.data[0] + q.data[1] * p.data[1] + q.data[2] * p.data[2] + q.data[3] * p.data[3]) / ( (float)q * (float)p );
	if (cosA < 0.0)
	{
		p = ~p;
		p.data[0] = -p.data[0];
		cosA = -cosA;
	}

	if (cosA > Quat::slerp_dot_threshHold)
	{
		Quat result = (1.0 - t) * q + t * p;
		result = result.normal();
		return result;
	}
	double alpha = acos(cosA);

	Quat res = (sin((1.0 - t) * alpha) / sin(alpha)) * q + (sin(t * alpha) / sin(alpha)) * p;
	res = res.normal();
	return res;
	
}


Quat Quat::normal()
{
   float inv = 1.0f/(float)(*this); 
   return Quat(inv*data[0], inv*data[1], inv*data[2], inv*data[3]);
}

std::ostream& operator<<(std::ostream& os, const Quat& q)
{
    os << "[" << q.data[0] << ", " << q.data[1] << "i, " << q.data[2] << "j, " << q.data[3] << "k]";
    return os;
}
