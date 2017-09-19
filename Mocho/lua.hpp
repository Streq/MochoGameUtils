/*
 * lua.hpp
 *
 *  Created on: Sep 16, 2017
 *      Author: santiago
 */

#pragma once

#include <lua.hpp>
#include <string>
#include "lua_val_ops.hpp"

#define EXPAND_BEGIN {int expansion[] {0,(
#define EXPAND_END , 0)...};}



namespace mch{
namespace lua{
struct Script{
	public:
		Script(){
			luaState = luaL_newstate();
		}
		~Script(){
			lua_close(luaState);
		}
		int loadFromBuffer(const std::string& buff){
			int ret = luaL_loadbuffer(luaState,buff.c_str(),buff.length(),nullptr);
			if(ret){
				printf("error loading chunk from buffer:\n%s\n%s\n",
						buff.c_str(), lua_tostring(luaState, -1));
			}
			return ret;
		};
		int loadFromFile(const std::string& file){
			int ret = luaL_loadfile(luaState,file.c_str());
			if(ret){
				printf("error loading chunk from file %s:%s\n",
						file.c_str(), lua_tostring(luaState, -1));
			}
			return ret;
		};
		int doChunk(){
			int ret = function<>::call<>(*this);
			if(ret){
				printf("error running chunk:\n%s\n",
						lua_tostring(luaState, -1));
			}
			return ret;

		}
		int doFile(const std::string& file){
			int ret=loadFromFile(file);
			if(!ret)return doChunk();
			return ret;
		};
		int doBuffer(const std::string& buffer){
			int ret = loadFromBuffer(buffer);
			if(!ret)return doChunk();
			return ret;
		};

		void registerFunction(const std::string& name, lua_CFunction function){
			lua_register(luaState,name.c_str(),function);
		}


		template <typename... Args> struct function{
			template <typename... Ret>
			static int call(Script& script, const char* name, Args... ArgTypes, Ret&... RetTypes){
				printf("calling function %s, with %u arguments and %u return fields\n"
						,name, sizeof...(Args), sizeof...(Ret));

				if(lua_getglobal(script.luaState,name)!=LUA_TFUNCTION){
					printf("error finding function %s: %s\n",
						name, lua_tostring(script.luaState, -1));
				}

				return call(script,ArgTypes...,RetTypes...);
			}

			template <typename... Ret>
			static int call(Script& script, Args... ArgTypes, Ret&... RetTypes){

				//this is ugly as shit
				//the expansion array allows for calling push for each argument

				EXPAND_BEGIN
					script.push(ArgTypes)
				EXPAND_END

				int ret = lua_pcall(script.luaState, sizeof...(Args), sizeof...(Ret), 0);
				if (ret){
					printf("error running function: %s\n",
						lua_tostring(script.luaState, -1));
				}

				EXPAND_BEGIN
					script.get_and_pop(RetTypes)
				EXPAND_END

				return ret;
			}

		};

		template<class... Args>struct cfunction{
			template<class Ret> struct ret{
				template<Ret (*F)(Args...)>
				static int function(lua_State* state){
					int i = 0;
					value<Ret>::ops::push(
						state,
						F(value<Args>::ops::get(state,++i)...)
					);
					return 1;
				};
			};

			template<void (*F)(Args...)>
			static int function(lua_State* state){
				int i = 0;
				F(value<Args>::ops::get(state,++i)...);
				return 0;
			};


		};


	private:

		template<typename T>
		void get_and_pop(T& ret){
			ret=value<T>::ops::get(luaState, -1);
			lua_pop(luaState, 1);
		};

		template<typename T>
		void push(const T& val){
			value<T>::ops::push(luaState,val);
		}
		lua_State* luaState;


};




}
}

