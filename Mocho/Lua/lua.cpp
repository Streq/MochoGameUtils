#include "Mocho/Lua/lua.hpp"
namespace mch{
namespace lua{

Script::Script(){
	luaState = luaL_newstate();
}
Script::~Script(){
	lua_close(luaState);
}



int Script::loadFromBuffer(
		const std::string& buff) {
	int ret = luaL_loadbuffer(luaState,buff.c_str(),buff.length(),nullptr);
	if(ret){
		printf("error loading chunk from buffer:\n%s\n%s\n",
				buff.c_str(), lua_tostring(luaState, -1));
	}
	return ret;
}

int Script::loadFromFile(const std::string& file){
	int ret = luaL_loadfile(luaState,file.c_str());
	if(ret){
		printf("error loading chunk from file %s:%s\n",
				file.c_str(), lua_tostring(luaState, -1));
	}
	return ret;
}

int Script::doChunk(){
	int ret = function<>::call<>(*this);
	if(ret){
		printf("error running chunk:\n%s\n",
				lua_tostring(luaState, -1));
	}
	return ret;

}

int Script::doFile(const std::string& file){
	int ret=loadFromFile(file);
	if(!ret)return doChunk();
	return ret;
}

int Script::doBuffer(const std::string& buffer){
	int ret = loadFromBuffer(buffer);
	if(!ret)return doChunk();
	return ret;
}

void Script::registerFunction(const std::string& name, lua_CFunction function){
	lua_register(luaState,name.c_str(),function);
}



void Script::getField(const std::string& name) {
	lua_getfield(luaState, -1, name.c_str());
}

void Script::getGlobal(const std::string& name) {
	lua_getglobal(luaState, name.c_str());
}

void Script::pop(int n) {
}


}
}
