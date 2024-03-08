module glad.gl.types;


alias GLenum = uint;
alias GLvoid = void;
alias GLboolean = ubyte;
alias GLbitfield = uint;
alias GLchar = char;
alias GLbyte = byte;
alias GLshort = short;
alias GLint = int;
alias GLclampx = int;
alias GLsizei = int;
alias GLubyte = ubyte;
alias GLushort = ushort;
alias GLuint = uint;
alias GLhalf = ushort;
alias GLfloat = float;
alias GLclampf = float;
alias GLdouble = double;
alias GLclampd = double;
alias GLfixed = int;
alias GLintptr = ptrdiff_t;
alias GLsizeiptr = ptrdiff_t;
alias GLintptrARB = ptrdiff_t;
alias GLsizeiptrARB = ptrdiff_t;
alias GLcharARB = byte;
alias GLhandleARB = uint;
alias GLhalfARB = ushort;
alias GLhalfNV = ushort;
alias GLint64EXT = long;
alias GLuint64EXT = ulong;
alias GLint64 = long;
alias GLuint64 = ulong;
alias GLvdpauSurfaceNV = ptrdiff_t;
alias GLeglImageOES = void*;
struct ___GLsync; alias __GLsync = ___GLsync*;
alias GLsync = __GLsync*;
struct __cl_context; alias _cl_context = __cl_context*;
struct __cl_event; alias _cl_event = __cl_event*;
extern(System) {
alias GLDEBUGPROC = void function(GLenum, GLenum, GLuint, GLenum, GLsizei, GLchar*, GLvoid*);
alias GLDEBUGPROCARB = GLDEBUGPROC;
alias GLDEBUGPROCKHR = GLDEBUGPROC;
alias GLDEBUGPROCAMD = void function(GLuint, GLenum, GLenum, GLsizei, GLchar*, GLvoid*);
}
