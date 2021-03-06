/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                      
 */          
 
 
 
 
#ifndef THC_TYPES_H

#define THC_TYPES_H								"@(#)thcTypes.h $Revision: 1.5 $"


#include "thcConst.h"
#include "thcConfig.h"
#include <sys/types.h>


/*General boolean type (true or false)*/
typedef enum {thc_false = 0,thc_true = 1}		boolean;


/*Type used in user inditifier (UID)*/
typedef unsigned long long   thcUserIdentifier;


/*Type user do describe groups*/
typedef enum{
	administrador = 1,
	owner		  = 2,
	ownerAdmin    = 3,
	user          = 4,
	userAdmin     = 5,
	ownerUser     = 6,
	root          = 7
	} thcGroupType;

/*General flags for user*/
typedef  enum
{
	ok,
	abeyance,
	passwordReset,
	emailChange
} thcUserFlagType;


/*Struct used to save user information on binary file*/
/*size 389 bytes*/
typedef struct
{
	thcUserIdentifier UID;
	char nickname [THC_FILE_MAXIMUM_NICKNAME_LENGHT+1];
	char codedPassword [THC_FILE_ENCRYPTED_PASSWORD_LENGHT+1];
	thcGroupType group;
	char fullName[THC_FILE_MAXIMUM_NAME_LENGHT+1];
	char email[THC_FILE_MAXIMUM_EMAIL_LENGHT+1];
	thcUserFlagType flag;

} thcUserDataType;

/*Struct user to save user information on abbeyance file*/
typedef struct
{
	thcUserIdentifier UID;
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	time_t expiration;
	
} thcUserAbeyancesType;


/*Struct user to save password reset information*/
/*Size : 120 bytes*/
typedef struct
{
	thcUserIdentifier UID;
	time_t expiration;
	char tempPasswordCoded[THC_FILE_ENCRYPTED_PASSWORD_LENGHT+1];	
} thcUserAbeyancePasswordType;

/*Struct user to save e-mail change information*/
/*Size : 116 bytes*/
typedef struct
{
	thcUserIdentifier UID;
	char email[THC_EMAIL_MAXIMUM_LENGHT+1];	
	time_t expiration;
} thcUserAbeyanceEmailType;

typedef struct
{
	thcUserIdentifier UID;
	char confirmationCode [THC_COOKIE_CONTENT_LENGHT+1];	
} thcEmailConfirmationType;

typedef struct
{
	thcUserIdentifier UID;
	char email[THC_EMAIL_MAXIMUM_LENGHT+1];
	time_t expiration;
	
} thcEmailAbeyancesType;


/*Type used to select system language*/
typedef enum{english,portuguese} thcLanguageType;


/*Type used for function errors*/
typedef unsigned int 		thcErrorType;


#endif	
	
	