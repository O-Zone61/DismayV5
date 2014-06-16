#ifndef MISCGARRY_H
#define MISCGARRY_H

typedef int (*CLuaFunction)(lua_State*);

struct UserData
{
    void*			data;
    unsigned char	type;
};

#endif // MISCGARRY_H