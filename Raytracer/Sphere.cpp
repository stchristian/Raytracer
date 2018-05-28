#include "Sphere.h"

bool Sphere::hit(const Ray& ray, FLOAT_T& tmin, ShadeRec& shadeRec) const
{
    Vec3f temp = ray.origin - center;
    FLOAT_T a = ray.direction.dot(ray.direction);
    FLOAT_T b = temp.dot(ray.direction) * 2.0;
    FLOAT_T c = temp.dot(temp) - radius * radius;
    FLOAT_T t1, t2;

    if (solve_quadratic_equation(a, b, c, t1, t2))
    {
        if (t1 > K_EPSILON)
        {
            tmin = t1;
            shadeRec.normal = (temp + ray.direction * t1) / radius;
            shadeRec.hit_point = ray.origin + ray.direction * t1;
            return true;
        }
        if (t2 > K_EPSILON)
        {
            tmin = t2;
            shadeRec.normal = (temp + ray.direction * t2) / radius;
            shadeRec.hit_point = ray.origin + ray.direction * t2;
            return true;
        }
    }
    return false;
}