
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace camera {

void Camera::set_project_matrix(int32_t width, int32_t height) {
    m_project_matrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

} // namespace camera