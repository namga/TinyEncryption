#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*********************************
*	FUNC: 	encryptTea
*	Param: 	unsigned char* v
*			unsigned char* k
*   Return: void
*********************************/
void encryptTea (unsigned char* v, unsigned char* k) 
{
    unsigned char v0 = v[0], v1 = v[1], sum = 0, i;           	/* set up */
    unsigned char delta = 0x9e3779b9;                     		/* a key schedule constant */
    unsigned char k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   	/* cache key */
    
	for (i = 0; i < 32; i++) 
	{                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                       /* end cycle */
    v[0] = v0; 
	v[1] = v1;
}

/*********************************
*	FUNC: 	decryptTea
*	Param: 	unsigned char* v
*			unsigned char* k
*   Return: void
*********************************/
void decryptTea (unsigned char* v, unsigned char* k) 
{
    unsigned char v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;  /* set up */
    unsigned char delta = 0x9e3779b9;                     /* a key schedule constant */
    unsigned char k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
    
	for (i = 0; i < 32; i++) 
	{                        /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }
	                		/* end cycle */
    v[0] = v0; 
	v[1] = v1;
}

/*********************************
*	FUNC: 	encryt
*	Param: 	char* key
*			char* data_in
*			int in_length
*			char* data_out
*			int *out_length
*   Return: int
*********************************/
int encrypt(char* key, char* data_in, int in_length, char* data_out, int *out_length)
{
	printf(">>>>>>>>>>>>>>>>>>>> encrypt() <<<<<<<<<<<<<<<<<<<<<<<<<\n");
	
	unsigned char temp[2];
	char i;
	
	if((in_length %2) != 0)
	{
		data_in[in_length] = '\0';
	}
	
	for(i = 0; i < in_length; i = i + 2)
	{
		temp[0] = (char) data_in[i];
		temp[1] = (char) data_in[i+1];
		
		printf("%d-%d \n", temp[0], temp[1]);
		
		encryptTea(temp, key);
		
		printf("%d-%d \n", temp[0], temp[1]);
		
		data_out[i] = (char) temp[0];
		data_out[i+1] = (char) temp[1];
		
		printf("----->>>data_out: %c-%c \n", temp[0], temp[1]);
	}
	
	*out_length = strlen(data_out);
	
	return 0;
}


/*********************************
*	FUNC: 	decryt
*	Param: 	char* key
*			char* data_in
*			int in_length
*			char* data_out
*			int *out_length
*   Return: int
*********************************/
int decrypt(char* key, char* data_in, int in_length, char* data_out, int *out_length)
{
	printf(">>>>>>>>>>>>>>>>>>>> decrypt() <<<<<<<<<<<<<<<<<<<<<<<<<\n");
	
	unsigned char temp[2];
	char i;
	
	for(i = 0; i < in_length; i = i + 2)
	{
		temp[0] = (char) data_in[i];		
		temp[1] = (char) data_in[i + 1];
		
		printf("%d-%d \n", temp[0], temp[1]);
		
		decryptTea(temp, key);
		
		printf("%d-%d \n", temp[0], temp[1]);
		
		data_out[i] = (char) temp[0];
		data_out[i+1] = (char) temp[1];
		
		printf("----->>>data_out: %c-%c \n", temp[0], temp[1]);
	}
	
	*out_length = strlen(data_out);
	
	return 0;
}

/*********************************
*	FUNC: 	main
*	Param: 	int argc
*			char* *argc[]
*   Return: int
*********************************/
int main(int argc, char *argv[]) 
{
	char key[4] 	= "svik";
	char command[128] 	= "{\"mod\" : \"tp\", \"IP\" : \"10.100.30.90\"}";
	char data_encrypt[128];
	char data_decrypt[128];
	
	memset(data_encrypt, '\0', sizeof(data_encrypt));
	memset(data_encrypt, '\0', sizeof(data_encrypt));
	
	int  encrypt_len = 0;
	int  decrypt_len = 0;
	int i;
	
	for(i = 0; i < strlen(command); i++)
	{
		printf("-- Data base: %c \n", command[i]);
	}
	
	encrypt(key, command, strlen(command), data_encrypt, &encrypt_len);
	
	//printf("-- Data_Out: %c \n", data_encrypt[0]);
	//printf("-- Data_Out: %c \n", data_encrypt[1]);
	
	printf("-- Lenght: %d \n", encrypt_len);
	
	decrypt(key, data_encrypt, strlen(data_encrypt), data_decrypt, &decrypt_len);
	
	//printf("-- Data_Out: %c \n", data_decrypt[0]);
	//printf("-- Data_Out: %c \n", data_decrypt[1]);
	
	printf("-- Lenght: %d \n", decrypt_len);
		
	return 0;
}
