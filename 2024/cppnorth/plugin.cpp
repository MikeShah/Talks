// g++ plugin.cpp -o prog
#include <vector>
#include <string>

// Provided by Engine Maintainers are some 'base class'
// from which you can override behavior and 'hook' into systems.
class IPlugin{
		public:
				virtual ~IPlugin() {}
				virtual void Load(const char* file)   =0;
				virtual void Update() =0;
				virtual void Render() =0;
};

// In 'Core' Application or 'engine'
class PluginManager {
		public:
				static PluginManager &GetInstance(){}
				bool LoadAll(){}
				bool Load(const std::string &name){}
				bool UnloadAll(){}
				bool Unload(const std::string &name){}

				std::vector<IPlugin*> GetAllPlugins(){
					return mPlugins;
				}
		private:
				PluginManager(){}
				~PluginManager(){}
				PluginManager(const PluginManager &){}
/*				const PluginManager(const PluginManager & rhs){
					return *this;
				}
*/
				std::vector<IPlugin*> mPlugins;
};

/// Your C++ Implementation
class MyCustomPlugin : public IPlugin {
		public:
				MyCustomPlugin() {}
				void Load(const char* file) override {}
				void Update() override {}
				void Render() override {}
};

/// C API for exposing some functionality
// 
extern "C" IPlugin *CreateInstanceMyCustomPlugin() {
		return new MyCustomPlugin(); 
}
extern "C" void DestroyMyCustomPlugin(MyCustomPlugin *p) {
		delete p; 
}

/// Interface to your 'Plugin Manager' to register and name your plugin
extern "C" int Plugin_Registry()
{
		RegisterPlugin("my_custom_plugin", CreateInstanceMyCustomPlugin, DestroyMyCustomPlugin);
		return 0; 
}

// Entry point of program
int main(){

		return 0;
}
