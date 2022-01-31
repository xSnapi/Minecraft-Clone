#pragma once

#include <GLM/glm.hpp>

namespace hv {
	inline glm::vec4 RGBToNVec4(const glm::vec4& c) {
		return glm::vec4
		(
			(float)c.r / 255.0f,
			(float)c.g / 255.0f,
			(float)c.b / 255.0f,
			(float)c.a / 255.0f
		);
	}

	inline glm::vec4 NVec3ToRGB(const glm::vec3& v) { // Note alpha is striped here
		return glm::vec4
		(
			v.x >= 0.0f ? v.x > 1.0f ? 1.0f : v.x * 255.0f : 0.0f,
			v.y >= 0.0f ? v.y > 1.0f ? 1.0f : v.y * 255.0f : 0.0f,
			v.z >= 0.0f ? v.z > 1.0f ? 1.0f : v.z * 255.0f : 0.0f,
			255.0f
		);
	}

	static glm::vec4 NVec4ToRGB(const glm::vec4& v) { // Note alpha is striped here
		return glm::vec4
		(
			v.x >= 0.0f ? v.x > 1.0f ? 1.0f : v.x * 255.0f : 0.0f,
			v.y >= 0.0f ? v.y > 1.0f ? 1.0f : v.y * 255.0f : 0.0f,
			v.z >= 0.0f ? v.z > 1.0f ? 1.0f : v.z * 255.0f : 0.0f,
			v.w >= 0.0f ? v.w > 1.0f ? 1.0f : v.w * 255.0f : 0.0f
		);
	}
}