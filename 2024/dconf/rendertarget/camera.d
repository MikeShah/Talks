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

		@disable this();

		this(int id){
				writeln("(Constructor) Created a Camera!");
				// Position us at the origin.
				mEyePosition = vec3!(float)(0.0f, 0.0f, 0.0f);
				// Looking down along the z-axis initially.
				// Remember, this is negative because we are looking 'into' the scene.
				mViewDirection = vec3!float(0.0f,0.0f, -1.0f);
				// For now--our upVector always points up along the y-axis
				mUpVector = vec3!float(0.0f, 1.0f, 0.0f);
				mOldMousePosition= vec2!float(0.0f,0.0f);
		}

		void MouseLook(int mouseX, int mouseY){
				// Record our new position as a vector
				vec2!float newMousePosition = vec2!float(mouseX, mouseY);
				// Detect how much the mouse has moved since
				// the last time
				auto mouseDelta = vec2!float(0.0f,0.0f);
				mouseDelta =  newMousePosition - mOldMousePosition;

				auto rotateVectorAngle = rotate(-mouseDelta.x, mUpVector);
				writeln(__MODULE__,":",__LINE__,"|mViewDirection|",mViewDirection);
				mViewDirection = MatrixTimesVector(rotateVectorAngle,mViewDirection);
				writeln(__MODULE__,":",__LINE__,"|mViewDirection|",mViewDirection);

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

		mat4!float GetViewMatrix() {
				// Think about the second argument and why that is
				// setup as it is.

				vec3!float v1 = mEyePosition;
				vec3!float v2 = mViewDirection;
				vec3!float eyeAndView = v1+v2;

				writeln(__FILE__,":",__LINE__,"|v1|",v1);
				writeln(__FILE__,":",__LINE__,"|v2|",v2);
				writeln(__FILE__,":",__LINE__,"|eyeAndView|",eyeAndView);

				return lookAt!float(mEyePosition,
								eyeAndView,
								mUpVector);
		}

		mat4!float GetPerspectiveMatrix(float FOV, float AspectRatio, float Near, float Far)
		{

				// See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml
				import std.math;

				mat4!float result;
				result.makeZero!float();

				float Cotangent = 1.0f / tan(FOV / 2.0f);
				result.data[0][0] = Cotangent / AspectRatio;
				result.data[1][1] = Cotangent;
				result.data[2][3] = -1.0f;

				result.data[2][2] = (Near + Far) / (Near - Far);
				result.data[3][2] = (2.0f * Near * Far) / (Near - Far);
				//				result.data[3][3] = 1.0f;

				return result;
		}
		mat4!float makeFrustum(float fovY, float aspectRatio, float front, float back)
		{
				import std.math;
				const float DEG2RAD = acos(-1.0f) / 180;

				float tangent = tan(fovY/2 * DEG2RAD);    // tangent of half fovY
				float top = front * tangent;              // half height of near plane
				float right = top * aspectRatio;          // half width of near plane

				// params: left, right, bottom, top, near(front), far(back)
				mat4!float matrix;
				matrix.makeIdentity!float();
				matrix.data[0][0]  =  front / right;
				matrix.data[2][1]  =  front / top;
				matrix.data[3][1] = -(back + front) / (back - front);
				matrix.data[3][2] = -1;
				matrix.data[3][2] = -(2 * back * front) / (back - front);
				matrix.data[3][3] =  0;
				return matrix;
		}

}

