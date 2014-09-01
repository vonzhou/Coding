
#include <math.h>
#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>
#include <lua5.2/lualib.h>

static int hello_sin(lua_State *L){
	double d = luaL_checknumber(L, 1);
	lua_pushnumber(L, sin(d));
	return 1;
}

int hello_map(lua_State *L){
	int i, n;
	// first arg is a table
	luaL_checktype(L, 1, LUA_TTABLE);
	// second is a function ,used for mapping
	luaL_checktype(L, 2, LUA_TFUNCTION);
	
	n = lua_rawlen(L, 1);// the size of the table 

	for(i = 1; i <= n; i++){
		lua_pushvalue(L, 2);   // push the func
		lua_rawgeti(L, 1, i);	// push the t[i]
		lua_call(L, 1, 1);	// call func with 1 arg and 1 result
		printf("after lua_call ...");
		lua_rawseti(L, 1, i);	//update the t[i]
	}
	
	return 0;
}


static const struct luaL_Reg hello_lib[] = {
	{"hello_sin" , hello_sin},
	{"hello_map", hello_map},
	{NULL, NULL}
};



int luaopen_hello_lib(lua_State *L){
	luaL_newlib(L, hello_lib);
	//luaL_register(L, "hello_lib",hello_lib); // lua 5.1
	return 1;
}






















