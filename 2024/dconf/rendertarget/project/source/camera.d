import std.stdio;

//import linearalgebra;
import inmath.linalg;
import inmath.math;

struct Camera{
		bool firstLook = true;
		// Track the old mouse position
		vec2 mOldMousePosition;
		// Where is our camera positioned
		vec3 mEyePosition;
		// What direction is the camera looking
		vec3 mViewDirection;
		// Which direction is 'up' in our world
		// Generally this is constant, but if you wanted
		// to 'rock' or 'rattle' the camera you might play
		// with modifying this value.
		vec3 mUpVector;

		mat4 mView;
		mat4 mProjection;

		@disable this();

		this(int id){
				writeln("(Constructor) Created a Camera!");
				// Position us at the origin.
				mEyePosition = vec3(-7.0, 2.5f, 0.05f);
				// Looking down along the z-axis initially.
				// Remember, this is negative because we are looking 'into' the scene.
				mViewDirection = vec3(1.0f, 0.0f, .20f);
				// For now--our upVector always points up along the y-axis
				mUpVector = vec3(0.0f, 1.0f, 0.0f);
				mOldMousePosition= vec2(0.0f,0.0f);

				mProjection = mat4.perspective(4.0f,3.0f,45.0f,0.1f,100.0f);

				writeln("Projection:\n\t",mProjection);
				import core.stdc.stdlib;
//				exit(1);
		}

		void MouseLook(float mouseX, float mouseY){
				// Record our new position as a vector
				vec2 newMousePosition = vec2(mouseX, mouseY);
				if(firstLook==true){
						firstLook=false;
						mOldMousePosition = newMousePosition;
				}
				// Detect how much the mouse has moved since
				// the last time
				auto mouseDelta =  mOldMousePosition-newMousePosition;
				writeln("mouseDelta",mouseDelta);

				mat3 temp;	
				vec3 test= temp.rotation(radians(-mouseDelta.x), mUpVector)* mViewDirection * 0.01f;
				mViewDirection=test.normalized();
				
				// Compute the rightVector
				vec3 rightVector = cross(mViewDirection, mUpVector);
				mViewDirection = temp.rotation(radians(-mouseDelta.y),rightVector)*mViewDirection;

				// Update our old position after we have made changes 
				mOldMousePosition = newMousePosition;
		}

		// OPTIONAL TODO: 
		//               The camera could really be improved by
		//               updating the eye position along the mViewDirection.
		//               Think about how you can do this for a better camera!
		void MoveForward(float speed){
				vec3 direction = vec3(mViewDirection.x,mViewDirection.y,mViewDirection.z);
				direction = direction * speed;
				mEyePosition += direction;
		}
		void MoveBackward(float speed){
				vec3 direction = vec3(mViewDirection.x,mViewDirection.y,mViewDirection.z);
				direction = direction * speed;
				mEyePosition -= direction;
		}
		void MoveLeft(float speed){
				vec3 rightVector = cross(mViewDirection, mUpVector);
				vec3 direction = vec3(rightVector.x,0.0,rightVector.z);
				direction = direction * speed;
				mEyePosition -= direction;
		}
		void MoveRight(float speed){
				vec3 rightVector = cross(mViewDirection, mUpVector);
				vec3 direction = vec3(rightVector.x,0.0,rightVector.z);
				direction = direction * speed;
				mEyePosition += direction;
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

		mat4 GetViewMatrix() {
				// Think about the second argument and why that is
				// setup as it is.
				writeln("============");
				writeln("eye:",mEyePosition);
				writeln("viewDir:",mViewDirection);
				vec3 target = mEyePosition + mViewDirection;
				writeln("target:",target);
				writeln("up:",mUpVector);
				writeln("lookat:",mat4.lookAt(mEyePosition,
								mEyePosition + mViewDirection,
								mUpVector));
				writeln("============");



				return mat4.lookAt(mEyePosition,
								target,
								mUpVector);
		}


}

