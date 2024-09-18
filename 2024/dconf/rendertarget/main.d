module deferred;
// Objects

// Linux
// dmd -g *.d ./glad/gl/*.d -L-L/usr/local/lib -L-lglfw3 -of=prog
//
// Mac 
// dmd -g *.d ./glad/gl/*.d -L-lglfw -L-L/opt/homebrew/Cellar/glfw/3.4/lib -of=prog
import graphicsapp;

/// Program entry point 
/// NOTE: When debugging, this is '_Dmain'
void main(string[] args){
	GraphicsApplication app = GraphicsApplication("title");
	app.RunLoop();
}
