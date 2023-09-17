#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

namespace camera {

class Camera {
public:
    Camera() = default;
    Camera(const Camera &)=delete;
    Camera(Camera &&)=delete;
    Camera& operator=(const Camera &)=delete;
    Camera& operator=(Camera &&)=delete;
    ~Camera() = default;

    void set_project_matrix(int32_t width, int32_t height);

    const glm::mat4 &get_view_matrix() { return m_view_matrix; }
    const glm::mat4 &get_project_matrix() { return m_project_matrix; }
private:
    //int32_t _window_width = -1;
    //int32_t _window_height = -1;

    glm::mat4 m_view_matrix{0.0};
    glm::mat4 m_project_matrix{0.0};
};

} // namespace camera

#endif // CAMERA_H