#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#ifndef TYPES_H
#include "Types.h"
#endif

class Camera {
public:

    Camera();
    Camera(const double & fov, const double & ratio);
    Camera(const double & fov, const double & ratio, const double & close, const double & far);
    ~Camera();

    // void deplacer(Input const &input);
    void lookAt(glm::mat4 & view);
    void setProjection(const double & fov, const double & ratio, const double & close, const double & far);
    void setTargetPoint(const glm::vec3 & pointCible);
    void setTargetPoint(const float & x, const float & y, const float & z);
    void setPosition(const glm::vec3 & position);
    void setPosition(const float & x, const float & y, const float & z);
    void setAngle(const glm::vec3 & angle);
    void setAngle(const float & x, const float & y, const float & z);

    glm::vec3 getPosition() const;
    glm::vec3 getAngle() const;
    glm::mat4 getProjectionMatrice() const;
    glm::mat4 getViewMatrice() const;
    float getFOV() const;
    float getRatio() const;
    float getClose() const;
    float getFar() const;
private:
    float m_fov;
    float m_ratio;
    float m_close;
    float m_far;

    glm::vec3 m_position;
    glm::vec3 m_targetPoint;
    glm::vec3 m_orientation;
    glm::vec3 m_verticalAxe;
    glm::vec3 m_angle;

    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif
