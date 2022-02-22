#include <stdio.h>
#define INIREAD_IMPL
#include "iniread.h"


void iniread_error_assert(iniread_t ctx)
{
	if (ctx.status){
	 	printf("[error]: inireader produced an error: %s\n", iniread_get_error(ctx));
	 	exit(1);
	 }
	 
}


char* iniread_get_value(iniread_t instance, char* section, char* id, iniread_token_type_t type)
{
	iniread_key_t key = iniread_get_key(instance, section, id);
	iniread_error_assert(instance);
	if (key.type == type) return key.value;
	else {
		printf("\x1b[1;31m Query failed: [%s:%s] are not valid types\x1b[0;0m\n", section, id);
 		return 0x0;
	}
}

int main(int argc, char** argv)
{
	const char* dataset = "data.ini";
	iniread_t read = iniread_open(dataset);
	
	iniread_error_assert(read);

	printf("OK - %s\n", dataset);

	char type[1024]; /* [section] */
	char element[1024]; /* a= */
	printf("syntax: [section] [element]\n");
	
	while(1) 
	{	
		
		printf("find: "); scanf("%s %s", type, element);
		
		const char* val = iniread_get_value(read, type, element, INIREAD_STRING);
		if (val != NULL)
			printf("\n-> \t[%s:%s]: \x1b[1;37m%s\x1b[0;0m\n", type,element,val);
	}
	
}


