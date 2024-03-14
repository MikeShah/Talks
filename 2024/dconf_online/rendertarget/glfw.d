// ---------------------------------------------------------------------------
/// GLFW Bindings
/// When we link in the library, we need to have what you'd think of as the header
/// available here.
extern(C){
    // Forward declare structures
    struct GLFWmonitor;
    struct GLFWwindow;

    enum{ GLFW_CONTEXT_VERSION_MAJOR = 0x00022002,
          GLFW_CONTEXT_VERSION_MINOR = 0x00022003,
          GLFW_OPENGL_PROFILE =  0x00022008,
          GLFW_OPENGL_CORE_PROFILE  = 0x00032001,
          GLFW_OPENGL_FORWARD_COMPAT =  0x00022006,
    }

    // Types
    alias GLFWglproc = void* function(const char*);

    // Functions
    int glfwInit();
    GLFWwindow* glfwCreateWindow(int,int,const char*, GLFWmonitor*, GLFWwindow*);
    void glfwDestroyWindow (GLFWwindow *window);
    void glfwTerminate();
    int  glfwWindowShouldClose (GLFWwindow *window);
    void glfwPollEvents ();
    int  glfwWindowShouldClose(GLFWwindow *    window);
    void glfwSwapBuffers (GLFWwindow *window);
    void glfwMakeContextCurrent (GLFWwindow *window);
    void glfwWindowHint (int hint, int value);

    GLFWglproc  glfwGetProcAddress (const char *procname);
}
// ---------------------------------------------------------------------------
