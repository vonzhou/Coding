#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(){
	char buff[1024];
	int error;
	memset(buff, 0, sizeof(buff));
	lua_State *L = luaL_newstate(); // open lua
	luaL_openlibs(L); // open the standard lib

	while(fgets(buff, sizeof(buff), stdin) != NULL){
		// if success, return 0
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
								lua_pcall(L, 0, 0, 0);
		if(error){
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);  // pop the err msg from stack
		}
	}

	lua_close(L);
	return 0;
}


















