#include <ScriptEngine/BaseScript.h>
#include <ScriptEngine/ScriptRegistry.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Scripts
{
	class CameraMovement : public Scripts::BaseScript
	{
	private:
		ME_PROPERTY(float, sens);
		ME_PROPERTY(float, speed);
		ME_PROPERTY(float, pitchLimit);

		float _lastMouseX = 0, _lastMouseY = 0, _mouseX = 0, _mouseY = 0, _yaw = 0, _pitch = 0;

		void RegisterProperties() override;
		void Update() override;
		void OnGameObjectEnable() override;

	public:
		void OnCollisionEnter() override;
		void OnCollisionStay() override;
		void OnCollisionExit() override;
	};

	ME_REGISTER_SCRIPT(CameraMovement);
}