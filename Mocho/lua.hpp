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
#include <algorithm>


#define EXPAND_BEGIN {int expansion[] {0,(
#define EXPAND_END , 0)...};}



namespace mch{
namespace lua{
struct Script{
	public:
			Script();
			~Script();
		int loadFromBuffer(const std::string& buff);
		int loadFromFile(const std::string& file);

		int doChunk();
		int doFile(const std::string& file);
		int doBuffer(const std::string& buffer);

		void registerFunction(const std::string& name, lua_CFunction function);

		template<typename T>
		T getValue(int index){
			return value<T>::get(luaState,index);
		}

		template<typename T>
		int getByFullName(const std::string& fullname, T& ret){

			size_t begin = 0;
			size_t end = fullname.find('.');
			size_t stack = 0;
			lua_getglobal(luaState,fullname.substr(begin,end).c_str());
			++stack;
			if(lua_isnoneornil(luaState,-1)){
				lua_pop(luaState,stack);
				return -1;
			};

			while(end != std::string::npos){

				begin = end+1;
				end = fullname.find('.',begin);
				lua_getfield(luaState, -1
					,fullname.substr(begin,end-begin).c_str());
				++stack;
				if(lua_isnoneornil(luaState,-1)){
					lua_pop(luaState,stack);
					return -1;
				};
			}

			ret = value<T>::ops::get(luaState,-1);

			lua_pop(luaState,stack);

		}

		void getField(const std::string& name);

		void getGlobal(const std::string& name);

		void pop(int n);

		template<typename T>
		void getAndPop(T& ret){
			ret=value<T>::ops::get(luaState, -1);
			lua_pop(luaState, 1);
		};

		template<typename T>
		void push(const T& val){
			value<T>::ops::push(luaState,val);
		}
		lua_State* luaState;


		template <typename... Args>
		struct function{
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
					script.getAndPop(RetTypes)
				EXPAND_END

				return ret;
			}

		};

		template<class... Args>
		struct cfunction{
			template<class Ret>
			struct ret{
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



};




}
}

