#include "Camera.h"

Camera::Camera(Vec3f _eye, Vec3f _lookat, Vec3f _up)
:eye(_eye), lookat(_lookat), up(_up)
{
    compute_ONB();
}

void Camera::compute_ONB()
{
    z_cam = (eye - lookat).normalize();
    x_cam = up.cross(z_cam).normalize();
    y_cam = z_cam.cross(x_cam); //Don't need to normalize
}

void Camera::set_roll_angle(FLOAT_T angle)
{

}