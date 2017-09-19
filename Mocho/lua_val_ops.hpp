
#pragma once
#include<lua.hpp>

namespace mch{
namespace lua{
	template <typename T>
	struct integer_ops{
		static void push(lua_State* L, T val){
			lua_pushinteger(L,static_cast<lua_Integer>(val));
		};
		static T get(lua_State* L, int i){
			return static_cast<T>(lua_tointeger(L,i));
		};

	};
	template <typename T>
	struct number_ops{
		static void push(lua_State* L, T val){
			lua_pushnumber(L,static_cast<lua_Number>(val));
		};
		static T get(lua_State* L, int i){
			return static_cast<T>(lua_tonumber(L,i));
		};

	};
	template <typename T>
	struct boolean_ops{
		static void push(lua_State* L, T val){
			lua_pushboolean(L,static_cast<bool>(val));
		};
		static T get(lua_State* L, int i){
			return static_cast<T>(lua_toboolean(L,i));
		};

	};
	template <typename T>
	struct string_ops{
		static void push(lua_State* L, T val){
			lua_pushstring(L,static_cast<const char*>(val));
		};
		static T get(lua_State* L, int i){
			return static_cast<T>(lua_tostring(L,i));
		};
	};

	template <typename T>
	struct userdata_ops{
		static void push(lua_State* L, T val){
			lua_pushlightuserdata(L,static_cast<void*>(val));
		};
		static T get(lua_State* L, int i){
			return static_cast<T>(lua_touserdata(L,i));
		};
	};


	//specializations
	template<typename T>
	struct value{
		using ops = userdata_ops<T>;
	};

	template<>
	struct value<long long>{
		using ops = integer_ops<long long>;
	};
	template<>
	struct value<long>{
		using ops = integer_ops<long>;
	};
	template<>
	struct value<int>{
		using ops = integer_ops<int>;
	};
	template<>
	struct value<char>{
		using ops = integer_ops<char>;
	};

	template<>
	struct value<double>{
		using ops = number_ops<float>;
	};
	template<>
	struct value<float>{
		using ops = number_ops<float>;
	};

	template<>
	struct value<const char*>{
		using ops = string_ops<const char*>;
	};

	template<>
	struct value<bool>{
		using ops = boolean_ops<bool>;
	};
}
}
