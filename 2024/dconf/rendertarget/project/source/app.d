module main;
// Objects

// Linux
// IMPORTANT simply run with DUB
// make sure to add "versions" in dub configuration to unlock more features
import graphicsapp;

/// Program entry point 
/// NOTE: When debugging, this is '_Dmain'
void main(string[] args){
	GraphicsApplication app = GraphicsApplication("title");
	app.RunLoop();
}
