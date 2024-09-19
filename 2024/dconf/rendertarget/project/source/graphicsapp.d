
import std.stdio;

import bindbc.sdl;
import bindbc.opengl;
import inmath.linalg;

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
		Object3D bunnyOBJ;
		Object3D sponzaOBJ;
		Object3D screenQuad;

//		RenderTarget mRenderTarget;

		SDL_Window* mWindow;
		int mScreenWidth = 800;
		int mScreenHeight = 600;

		bool mGameIsRunning = true;

		// Constructor
		this(string title){
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

				mWindow = SDL_CreateWindow("DConf 2024",0,0,mScreenWidth,mScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

				SDL_GLContext gContext = SDL_GL_CreateContext(mWindow);
				// Now load OpenGL
				auto ret_ogl = loadOpenGL();
				//				SDL_GL_MakeCurrent(mWindow,gContext);

				// Retrieve information about OpenGL
				glInformation();

				// Setup our camera
				camera = Camera(0);

				// Initialize our own frame buffer
//				mRenderTarget = RenderTarget(mScreenWidth, mScreenHeight);

				basicShader = Shader("./shaders/vert.glsl","./shaders/frag.glsl");
				triangleOBJ = Object3D("triangleOBJect name");
				triangleOBJ.Triangle();
				triangleOBJ.make!Format3v3n();

				objShader = Shader("./shaders/obj.vert","./shaders/obj.frag");
				bunnyOBJ = Object3D("obj name");
				bunnyOBJ.LoadGeometry("./bunny_centered.obj");
				bunnyOBJ.make!Format3v3n();

				sponzaOBJ= Object3D("Sponza Object");
				sponzaOBJ.LoadGeometry("./sponza/sponza_triangulated.obj");
				sponzaOBJ.LoadMaterial("./sponza/sponza_triangulated.mtl");
				sponzaOBJ.make!Format3v3n2t();

/*
				mRenderTargetShader = Shader("./shaders/renderTargetVert.glsl","./shaders/renderTargetFrag.glsl");
				screenQuad= Object3D("screen quad name");
				screenQuad.ScreenQuad();
				screenQuad.make!Format3v2t();
*/
		}

		// Destructor
		~this(){
				SDL_DestroyWindow(mWindow);
		}

		// Handle input
		void Input(){

				SDL_Event e;
				// Start our event loop
				while(SDL_PollEvent(&e)){
						// Handle each specific event
						if(e.type == SDL_QUIT){
								mGameIsRunning= false;
						}
						if(e.type==SDL_MOUSEMOTION){
								camera.MouseLook(e.motion.x,e.motion.y);
						}
				}

				const ubyte* keyboardState = SDL_GetKeyboardState(null);

				if(keyboardState[SDL_SCANCODE_LEFT]){
						camera.MoveLeft(0.1f);
				}
				if(keyboardState[SDL_SCANCODE_RIGHT]){
						camera.MoveRight(0.1f);
				}
				if(keyboardState[SDL_SCANCODE_UP]){
						camera.MoveForward(0.1f);
				}
				if(keyboardState[SDL_SCANCODE_DOWN]){
						camera.MoveBackward(0.1f);
				}
				if(keyboardState[SDL_SCANCODE_W]){
						camera.MoveUp(0.1f);
				}
				if(keyboardState[SDL_SCANCODE_S]){
						camera.MoveDown(0.1f);
				}
				if(keyboardState[SDL_SCANCODE_ESCAPE]){
						mGameIsRunning=false;
				}
		}

		void Update(){
		}

		void Render(){
				mat4 view = camera.GetViewMatrix();

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
//				mRenderTarget.Bind();
				// Render as normal

				// Select a shader
				basicShader.Use();
				triangleOBJ.Translate(0.0f,0.0f,0.0f);

				basicShader.SetMat4x4("uModel", triangleOBJ.mModelMatrix.ptr); 
				basicShader.SetMat4x4("uView", view.ptr); 
				basicShader.SetMat4x4("uProjection", camera.mProjection.ptr); 
				triangleOBJ.Draw();

				// Draw obj object
				objShader.Use();

				bunnyOBJ.Identity();
				bunnyOBJ.Translate(0.0f,4.0f,0.0f);
				bunnyOBJ.Scale(0.5,0.5,0.5);
				static float increment=0.0f;
				bunnyOBJ.yRotation(increment+=0.01f);
				if(increment>360){increment=0.0f;}

				objShader.SetMat4x4("uModel", bunnyOBJ.mModelMatrix.ptr); 
				objShader.SetMat4x4("uView", view.ptr); 
				objShader.SetMat4x4("uProjection", camera.mProjection.ptr); 

				bunnyOBJ.Draw();
				objShader.Use();

				sponzaOBJ.Identity();
				sponzaOBJ.Translate(0.0f,0.0f,0.0f);
				sponzaOBJ.Scale(2.0f,2.0f,2.0f);
				
				objShader.SetMat4x4("uModel", sponzaOBJ.mModelMatrix.ptr); 
				objShader.SetMat4x4("uView", view.ptr); 
				objShader.SetMat4x4("uProjection", camera.mProjection.ptr); 
				sponzaOBJ.Draw();
				// Bind to a 'default' render target
//				glBindFramebuffer(GL_FRAMEBUFFER,0);
				// Draw our sceene to the target
//				mRenderTargetShader.Use();
//				mRenderTargetShader.SetInt("screenTexture",0);
				// Draw a simple screen quad
//				screenQuad.Draw();

				// Bind to 'no shader'
				glUseProgram(0);
		}

		// Advance world one frame at a time
		void AdvanceFrame(){
				Input();
				Update();
				// Do opengl stuff
				Render();

				SDL_Delay(25);
		}

		void RunLoop(){
				SDL_WarpMouseInWindow(mWindow,mScreenWidth/2,mScreenHeight/2);
				// Main application loop
				while(mGameIsRunning){
						AdvanceFrame();	
						//				import core.stdc.stdlib;
						//			exit(1);

						// Double Buffering
						SDL_GL_SwapWindow(mWindow);
				}

		}
}
