#include "camera.hpp"

Camera::Camera(float fov, float aspectRatio) : fov(fov), aspectRatio(aspectRatio) {
	m_projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 130.0f);
}

void Camera::updateProjView() {
	m_projectionView = createProjectionViewMatrix(m_position, m_rotation, m_projection);
}

void Camera::update(const Transform &transform) {
	m_position = transform.position;
	m_rotation = transform.rotation;

	updateProjView();
}