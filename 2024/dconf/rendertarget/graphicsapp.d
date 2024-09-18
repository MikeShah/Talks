
import std.stdio;
import glad.gl.all;
import glad.gl.loader;

import glfw;

import shader;
import object3d;
import rendertarget;
import camera;
import glutility;

struct GraphicsApplication{
		Shader basicShader;
		Shader objShader;
		Shader mRenderTargetShader;
		Camera camera;

		Object3D triangleOBJ;
		Object3D objOBJ;
		Object3D sponzaOBJ;
		Object3D screenQuad;

		RenderTarget mRenderTarget;

		GLFWwindow* mWindow;
		int mScreenWidth = 640;
		int mScreenHeight = 480;

		bool mGameIsRunning = true;

		// Constructor
		this(string title){
				// Initialize glfw
				if(!glfwInit()){
						writeln("glfw failed to initialize");
				}

				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
				glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

				mWindow = glfwCreateWindow(mScreenWidth,mScreenHeight,"DConf 2024",null,null);
				glfwMakeContextCurrent(mWindow);

				// Setup extensions
				if(!glad.gl.loader.gladLoadGL()){    
						writeln("Some error: Did you create a window and context first?");
						import core.stdc.stdlib;
						exit(1);
				}

				// Retrieve information about OpenGL
				glInformation();

				// Setup our camera
				camera = Camera(0);

				// Initialize our own frame buffer
				mRenderTarget = RenderTarget(mScreenWidth, mScreenHeight);

				basicShader = Shader("./shaders/vert.glsl","./shaders/frag.glsl");
				triangleOBJ = Object3D("triangleOBJect name");
				triangleOBJ.Triangle();
				triangleOBJ.make!Format3v3n();

				objShader = Shader("./shaders/obj.vert","./shaders/obj.frag");
				objOBJ = Object3D("obj name");
				objOBJ.LoadGeometry("./bunny_centered.obj");
				objOBJ.make!Format3v3n();

				sponzaOBJ= Object3D("Sponza Object");
				sponzaOBJ.LoadGeometry("./sponza/sponza_triangulated_small.obj");
				sponzaOBJ.LoadMaterial("./sponza/sponza_triangulated_small.mtl");
				sponzaOBJ.make!Format3v3n2t();

				mRenderTargetShader = Shader("./shaders/renderTargetVert.glsl","./shaders/renderTargetFrag.glsl");
				screenQuad= Object3D("screen quad name");
				screenQuad.ScreenQuad();
				screenQuad.make!Format3v2t();
		}

		// Destructor
		~this(){
				glfwDestroyWindow(mWindow);
				glfwTerminate();
		}

		// Handle input
		void Input(){
				static int x=0;
				++x;
				writeln(__FILE__,":",__LINE__,"-",camera.GetViewMatrix());
				if(x%2==0){
						camera.MouseLook(53,52);
				}else{
						camera.MouseLook(51,53);
				}
				writeln(__FILE__,":",__LINE__,"-",camera.GetViewMatrix());
		}

		void Update(){
		}

		void Render(){
				// Enable depth test and face culling.
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);

				// Initialize clear color
				// This is the background of the screen.
				glViewport(0, 0, mScreenWidth, mScreenHeight);
				glClearColor( 0.0f, 0.7f, 0.7f, 1.0f );

				//Clear color buffer and Depth Buffer
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

				// Bind to the target that we want to draw to
				mRenderTarget.Bind();
				// Render as normal

				// Draw triangleOBJect
				// Select a shader
				//g.basicShader.Use();
				//g.triangleOBJ.Draw();

				// Draw obj object

				objShader.Use();
				static float z=-8.0001f;
//				z-=0.01f;
				objOBJ.Translate(0.0f,0.0f,-z);
				camera.MoveForward(0.1f);

				objShader.SetMat4x4("uModel", objOBJ.GetModelMatrixPtr()); 
				objShader.SetMat4x4("uView", camera.GetViewMatrix().flatten!float().ptr); 
				objShader.SetMat4x4("uProjection", camera.GetPerspectiveMatrix(90.0f,800.0f/600.0f,0.1f,100.0f).flatten!float().ptr); 

				objOBJ.Draw();

//				sponzaOBJ.Translate(0.0f,0.0f,z);
//				objShader.SetMat4x4("uModel", objOBJ.GetModelMatrixPtr()); 
//				objShader.SetMat4x4("uView", camera.GetViewMatrix().flatten!float().ptr); 
//				static fov= 45.0f;
//				objShader.SetMat4x4("uProjection", camera.GetPerspectiveMatrix(fov,800.0f/600.0f,0.1f,1000.0f).flatten!float().ptr); 
//				sponzaOBJ.Draw();

				// Bind to a 'default' render target
				glBindFramebuffer(GL_FRAMEBUFFER,0);
				// Draw our sceene to the target
				mRenderTargetShader.Use();
				mRenderTargetShader.SetInt("screenTexture",0);
				// Draw a simple screen quad
				screenQuad.Draw();

				// Bind to 'no shader'
				glUseProgram(0);
		}

		// Advance world one frame at a time
		void AdvanceFrame(){
				Input();
				Update();
				// Do opengl stuff
				Render();

		}

		void RunLoop(){
				// Main application loop
				while(!glfwWindowShouldClose(mWindow) && mGameIsRunning){
						glfwPollEvents();

						AdvanceFrame();	
						//				import core.stdc.stdlib;
						//			exit(1);

						// Double Buffering
						glfwSwapBuffers(mWindow);

				}

		}
}
