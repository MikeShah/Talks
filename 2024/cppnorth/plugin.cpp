class PluginManager {
	public:
		static PluginManager &GetInstance();
		bool LoadAll();
		bool Load(const std::string &name);
		bool UnloadAll();
		bool Unload(const std::string &name); 
		std::vector<PluginInstance *> GetAllPlugins();
	private:
		PluginManager();
		~PluginManager();
		PluginManager(const PluginManager &);
		const PluginManager &operator (const PluginManager &); 
		std::vector<PluginInstance *> mPlugins;
};


class IPlugin{
	public:
		virtual ~IPlugin() {}
		virtual void Load(const char* file)   =0
			virtual void Update() =0;
		virtual void Render() =0;
};


/// Your C++ Implementation
class MyCustomPlugin : public IPlugin {
	public:
		MyCustomPlugin() {}
		override void Load(const char* file){}
		override void Update(){}
		override void Render(){}
};

/// C API for exposing some functionality
// 
PLUGIN FUNC IPlugin *CreateInstanceMyCustomPlugin() {
	return new MyCustomPlugin(); 
}
PLUGIN FUNC void DestroyMyCustomPlugin(MyCustomPlugin *p) {
	delete p; 
}

/// Interface to your 'Plugin Manager' to register and name your plugin
PLUGIN INIT()
{
	RegisterPlugin("my_custom_plugin", CreateInstanceMyCustomPlugin, DestroyMyCustomPlugin;
			return 0; 
			}

			int main(){

			return 0;
			}
