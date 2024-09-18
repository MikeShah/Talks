import std.stdio;

import linearalgebra;

struct Camera{
		// Track the old mouse position
		vec2!float mOldMousePosition;
		// Where is our camera positioned
		vec3!float mEyePosition;
		// What direction is the camera looking
		vec3!float mViewDirection;
		// Which direction is 'up' in our world
		// Generally this is constant, but if you wanted
		// to 'rock' or 'rattle' the camera you might play
		// with modifying this value.
		vec3!float mUpVector;

		this(int id){
				writeln("(Constructor) Created a Camera!");
				// Position us at the origin.
				mEyePosition = vec3!(float)(0.0f, 0.0f, 0.0f);
				// Looking down along the z-axis initially.
				// Remember, this is negative because we are looking 'into' the scene.
				mViewDirection = vec3!float(0.0f,0.0f, -1.0f);
				// For now--our upVector always points up along the y-axis
				mUpVector = vec3!float(0.0f, 1.0f, 0.0f);
				vec2!float mOldMousePosition= vec2!float(0.0f,0.0f);
		}

		void MouseLook(int mouseX, int mouseY){
				// Record our new position as a vector
				vec2!float newMousePosition = vec2!float(mouseX, mouseY);
				// Detect how much the mouse has moved since
				// the last time
				auto mouseDelta = vec2!float(0.0f,0.0f);
				mouseDelta =  newMousePosition - mOldMousePosition;

				auto rotateVectorAngle = rotate(-mouseDelta.x, mUpVector);
				auto view =  OuterProduct(rotateVectorAngle, mViewDirection);
				
				mViewDirection = view[0];

				// Update our old position after we have made changes 
				mOldMousePosition = newMousePosition;
		}

		// OPTIONAL TODO: 
		//               The camera could really be improved by
		//               updating the eye position along the mViewDirection.
		//               Think about how you can do this for a better camera!
		void MoveForward(float speed){
				mEyePosition.z -= speed;
		}
		void MoveBackward(float speed){
				mEyePosition.z += speed;
		}
		void MoveLeft(float speed){
				mEyePosition.x -= speed;
		}
		void MoveRight(float speed){
				mEyePosition.x += speed;
		}
		void MoveUp(float speed){
				mEyePosition.y += speed;
		}
		void MoveDown(float speed){
				mEyePosition.y -= speed;
		}
		// Set the position for the camera
		void SetCameraEyePosition(float x, float y, float z){
				mEyePosition.x = x;
				mEyePosition.y = y;
				mEyePosition.z = z;
		}

		// TODO: Just generate these automatically
		float GetEyePosition(){
				return mEyePosition.x;
		}
		float GetEyeYPosition(){
				return mEyePosition.y;
		}

		float GetEyeZPosition(){
				return mEyePosition.z;
		}

		float GetViewXDirection(){
				return mViewDirection.x;
		}

		float GetViewYDirection(){
				return mViewDirection.y;
		}

		float GetViewZDirection(){
				return mViewDirection.z;
		}

		mat4!float GetViewMatrix() const{
				// Think about the second argument and why that is
				// setup as it is.
				
				vec3!float v1 = mEyePosition;;
				vec3!float v2 = mViewDirection;
				vec3!float eyeAndView = v1+v2;

				return lookAt!float(mEyePosition,
														eyeAndView,
														mUpVector);
		}
}

