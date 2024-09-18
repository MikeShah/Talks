import std.stdio;
import glad.gl.all;
import glad.gl.loader;

void glInformation(){
		import std.string;

		// fromStringz is used here to properly convert the C-string
		writeln(fromStringz(cast(const char*)glGetString(GL_VENDOR)));
		writeln(fromStringz(cast(const char*)glGetString(GL_RENDERER)));
		writeln(fromStringz(cast(const char*)glGetString(GL_VERSION)));
		writeln(fromStringz(cast(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
}
