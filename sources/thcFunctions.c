/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte                              
 */          

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*
#include <crypt.h>
*/
#include <unistd.h>
#include <ctype.h>

#include "thcConfig.h"
#include "thcFunctions.h"
#include "thcConst.h"
#include "thcTypes.h"
#include "thcError.h"
#include "sendmail.h"



thcErrorType thcGenerateCookie (char *user, time_t *expiration, char *content, char *IPAddress)
{
	FILE *writeFile;
	size_t writtenBytes;
	char cookieDirectory [THC_MAXIMUM_COOKIE_PATH+1]=THC_DEFAULT_COOKIE_DIRECTORY;
	
	if (!user)
		return THC_ERROR_COOKIE_USERNAME;
	
	strcat(cookieDirectory,user);	
	writeFile = fopen (cookieDirectory,THC_WRITE);
	if (!writeFile)
		return THC_ERROR_WRITING_FILE;

	writtenBytes = fwrite(expiration, 1,sizeof(time_t),writeFile);
	if (writtenBytes != sizeof(time_t))
	{
		fclose(writeFile);
		remove(user);  /*remove corrupted file*/
		return THC_ERROR_COOKIE_EXPIRATION;
	}
	
	writtenBytes = fwrite(content,1, THC_COOKIE_CONTENT_LENGHT,writeFile);

	if(!content)
		return THC_ERROR_COOKIE_CONTENT_POINTER;

	if (writtenBytes != THC_COOKIE_CONTENT_LENGHT)
	{
		fclose(writeFile);
		remove(user); /*remove corrupted file*/
		return THC_ERROR_COOKIE_CONTENT;
	}
	
	if(!IPAddress)
		return THC_ERROR_COOKIE_IP_POINTER;
		
	writtenBytes = fwrite(IPAddress,1, strlen(IPAddress),writeFile);
	if (writtenBytes != strlen(IPAddress))
	{
		fclose(writeFile);
		remove(user); /*remove corrupted file*/
		return THC_ERROR_COOKIE_IP;
	}
	
	fclose(writeFile);
	return THC_OK;
}


thcErrorType thcReadCookie (char *username, time_t *expiration, char *content, char *IP)            
{                                             	
	FILE *read;                                              
    size_t readed;       
	char readedContent[THC_COOKIE_CONTENT_LENGHT+1];
	char readedIP [THC_COOKIE_MAXIMUM_IP_LENGHT+1];
	char cookieDirectory [THC_MAXIMUM_COOKIE_PATH+1]=THC_DEFAULT_COOKIE_DIRECTORY;
	
	
	
	strcat(cookieDirectory,username);
		
	read = fopen (cookieDirectory, THC_READ);                               
    if (!read)
		return THC_ERROR_READING_FILE;                                      

	readed = fread (expiration,sizeof(time_t),1,read);

	if (readed != 1)
		return THC_ERROR_COOKIE_EXPIRATION;

	readed = fread (readedContent,1,THC_COOKIE_CONTENT_LENGHT,read);
	if (readed != THC_COOKIE_CONTENT_LENGHT)
		return THC_ERROR_COOKIE_CONTENT;

	readedContent [THC_COOKIE_CONTENT_LENGHT] = '\0';
	strcpy (content,readedContent);

	readed = fread (readedIP,1,THC_COOKIE_MAXIMUM_IP_LENGHT,read);
	if (readed < 7)
		return THC_ERROR_COOKIE_IP;	
	readedIP [readed] = '\0';
	strcpy (IP,readedIP);


	return THC_OK;
}                                          

thcErrorType thcGenerateCookieContent (char *content)
{
	char base64String[64] = THC_BASE64_STRING;
	char generatedString [THC_COOKIE_CONTENT_LENGHT+1];
	int counter;
	time_t seed;

	if(!content)
		return THC_ERROR_EMPTY_POINTER;

	time(&seed);
	srand(seed);
	
	for(counter = 0; counter < THC_COOKIE_CONTENT_LENGHT; counter++)
		generatedString[counter] = base64String[rand()%64];
		
	generatedString [THC_COOKIE_CONTENT_LENGHT] = '\0';
	strcpy(content,generatedString);

	return THC_OK;
}


thcErrorType thcGenerateTemporaryPassword(char *password)
{
	char base64String[64] = THC_BASE64_STRING;
	char generatedString [THC_TEMP_PASSWORD_LENGHT+1];
	int counter;
	time_t seed;

	if(!password)
		return THC_ERROR_EMPTY_POINTER;

	time(&seed);
	srand(seed);
	
		
	for(counter = 0; counter < THC_TEMP_PASSWORD_LENGHT; counter++)
		generatedString[counter] = base64String[rand()%64];
		
	generatedString [THC_TEMP_PASSWORD_LENGHT] = '\0';
	strcpy(password,generatedString);

	return THC_OK;
}


thcErrorType thcSearchUser (char *nickname, thcUserDataType *data)
{
	FILE *read;
	boolean found =  thc_false;
	
	read = fopen(THC_FILE_NAME,THC_READ);
	if (!read) return THC_ERROR_READING_FILE;

	while ((found == thc_false) && (fread(data, sizeof(thcUserDataType),1,read) != 0))
		if (strcmp(data->nickname ,nickname) == 0) found = thc_true; 

	fclose(read);
	
	if (found == thc_false)
		return THC_ERROR_USERNAME_NOT_FOUND;
			
	return THC_OK;
}


thcErrorType thcWriteFile(thcUserDataType *data)
{
	FILE *write,*original;
	size_t written,readed;
	int fDescriptor;
	thcUserDataType buffer;
	boolean found = thc_false;
	char tempFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;


	/*Checks if file already exists*/
	if (access(THC_FILE_NAME,F_OK) == -1)
	{
		/*Create the file*/
			#ifdef _DEBUG_
				printf("Creating file\n");
			#endif
		write = fopen(THC_FILE_NAME,THC_WRITE);
		if (!write)
			return THC_ERROR_WRITING_FILE;
		
		written = fwrite(data,1,sizeof(thcUserDataType),write);
			#ifdef _DEBUG_
				printf("Struct size : %d\n",sizeof(thcUserDataType));
				printf("written bytes : %d\n",written);
			#endif
		if (written != sizeof(thcUserDataType))
			{
				fclose(write);
				remove(THC_FILE_NAME);
				return THC_ERROR_WRITING_DATA_TO_FILE;
			}
			
		return THC_OK;
		
	} /*if (access)*/
	
			#ifdef _DEBUG_
				printf("File Already Exists\n");
			#endif
	
	/*Opens Original File*/
	original = fopen(THC_FILE_NAME,THC_READ);
	if (!original)
		return THC_ERROR_READING_FILE;
	
	/*Starts File Descriptor */
	fDescriptor = mkstemp(tempFileName);
	if (fDescriptor == -1)
	{
		fclose(original);
		return THC_ERROR_MKSTEMP;
	}
	
	/*Starts File Descriptor as FILE stream*/
	write = fdopen(fDescriptor,THC_WRITE);
	if (!write)
	{
		fclose(original);
		return THC_ERROR_WRITING_FILE;
	}

	/*Copy content from original file and save on temp file*/
	while (found == thc_false)
	{
		readed = fread(&buffer,1,sizeof(thcUserDataType),original);
		if (readed == 0) /*End of File reached, add the new user at the end*/
		{
			found = thc_true;
			written = fwrite(data,1,sizeof(thcUserDataType),write);
			if (written != sizeof(thcUserDataType))
			{
				fclose(original);
				fclose(write);
				remove(tempFileName);
				return THC_ERROR_WRITING_DATA_TO_FILE;			
			}
		}
		else
		{
			if (buffer.UID < data->UID)
			{
				/*Buffer is less than new data, so buffer is written to the file*/
				written = fwrite(&buffer,1,sizeof(thcUserDataType),write);
				if (written != sizeof(thcUserDataType))
				{
					fclose(original);
					fclose(write);
					remove(tempFileName);
					return THC_ERROR_WRITING_DATA_TO_FILE;			
				}			
				
			}
			if (buffer.UID > data->UID)
			{
				/*Buffer bigger than new data, so write new data, then write buffer*/
				found = thc_true;
				written = fwrite(data,1,sizeof(thcUserDataType),write);
				if (written != sizeof(thcUserDataType))
				{
					fclose(original);
					fclose(write);
					remove(tempFileName);
					return THC_ERROR_WRITING_DATA_TO_FILE;			
				}			

				written = fwrite(&buffer,1,sizeof(thcUserDataType),write);
				if (written != sizeof(thcUserDataType))
				{
					fclose(original);
					fclose(write);
					remove(tempFileName);
					return THC_ERROR_WRITING_DATA_TO_FILE;			
				}			

			}
			
			if (buffer.UID == data->UID)
			{
				/*Name already used, exit without saving*/
				fclose(original);
				fclose(write);
				remove(tempFileName);
				return THC_ERROR_UID_USED;
			}
			
		}
		
	}/*while (found == thc_false)*/	

	while (fread(&buffer,1,sizeof(thcUserDataType),original) != 0)
	{
		fwrite(&buffer,1,sizeof(thcUserDataType),write);
		if (written != sizeof(thcUserDataType))
		{
			fclose(original);
			fclose(write);
			remove(tempFileName);
			return THC_ERROR_WRITING_DATA_TO_FILE;			
		}			
	}
	
	fclose(original);
	fclose(write);
	remove(THC_FILE_NAME);
	rename(tempFileName,THC_FILE_NAME);
	return THC_OK;
}


thcErrorType thcRemoveUserData(char *nickname)
{
	thcUserDataType *buffer;
	size_t copiedBytes;
	FILE *read,*copy;
	int fileDescriptor;
	char tempFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;

	
	if((buffer = malloc(sizeof(thcUserDataType))) == NULL)
		return THC_ERROR_INSUFICIENT_MEMORY;
	
	read = fopen(THC_FILE_NAME,THC_READ);
	if (!read) 
		return THC_ERROR_READING_FILE;
	
	fileDescriptor = mkstemp(tempFileName);
	
	if (fileDescriptor == -1)
	{
		free(buffer);
		fclose(read);
		return THC_ERROR_MKSTEMP;
	}
	
	/*Starts File Descriptor as FILE stream*/
	copy = fdopen(fileDescriptor,THC_WRITE);
	if (!copy)
	{
		free(buffer);
		fclose(read);
		return THC_ERROR_WRITING_FILE;
	}
	
	while ((copiedBytes = fread(buffer,1,sizeof(thcUserDataType),read)) == sizeof(thcUserDataType))
	{		
		if (strcmp(buffer->nickname,nickname) != 0)
		{	
			if(fwrite(buffer,1,sizeof(thcUserDataType),copy) != sizeof(thcUserDataType))
				return THC_ERROR_WRITING_DATA_TO_FILE;
		}
	} /*while*/

	free(buffer);	
	fclose(copy);
	fclose(read);
	rename(tempFileName,THC_FILE_NAME);
	
	return THC_OK;
}

thcErrorType thcRemoveFromAbeyanceList(char *nickname)
{
	thcUserAbeyancesType *buffer;
	size_t copiedBytes;
	FILE *read,*copy;
	int fileDescriptor;
	char tempFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;

	
	if((buffer = malloc(sizeof(thcUserAbeyancesType))) == NULL)
		return THC_ERROR_INSUFICIENT_MEMORY;
	
	read = fopen(THC_ABEYANCES_FILE_NAME,THC_READ);
	if (!read) 
		return THC_ERROR_READING_FILE;
	
	fileDescriptor = mkstemp(tempFileName);
	
	if (fileDescriptor == -1)
	{
		free(buffer);
		fclose(read);
		return THC_ERROR_MKSTEMP;
	}
	
	/*Starts File Descriptor as FILE stream*/
	copy = fdopen(fileDescriptor,THC_WRITE);
	if (!copy)
	{
		free(buffer);
		fclose(read);
		return THC_ERROR_WRITING_FILE;
	}
	
	while ((copiedBytes = fread(buffer,1,sizeof(thcUserAbeyancesType),read)) == sizeof(thcUserAbeyancesType))
	{		
		if (strcmp(buffer->nickname,nickname) != 0)
		{	
			if(fwrite(buffer,1,sizeof(thcUserAbeyancesType),copy) != sizeof(thcUserAbeyancesType))
				return THC_ERROR_WRITING_DATA_TO_FILE;
		}
	} /*while*/

	free(buffer);	
	fclose(copy);
	fclose(read);
	rename(tempFileName,THC_ABEYANCES_FILE_NAME);
	
	return THC_OK;
}


thcErrorType thcRemoveFromPasswordAbeyanceList (thcUserIdentifier UID)
{
	thcUserAbeyancePasswordType *buffer;
	size_t copiedBytes;
	FILE *read,*copy;
	int fileDescriptor;
	char tempFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;

	
	if((buffer = malloc(sizeof(thcUserAbeyancePasswordType))) == NULL)
		return THC_ERROR_INSUFICIENT_MEMORY;
	
	read = fopen(THC_ABEYANCES_PASSWORD_FILE_NAME,THC_READ);
	if (!read) 
		return THC_ERROR_READING_FILE;
	
	fileDescriptor = mkstemp(tempFileName);
	
	if (fileDescriptor == -1)
	{
		free(buffer);
		fclose(read);
		return THC_ERROR_MKSTEMP;
	}
	
	/*Starts File Descriptor as FILE stream*/
	copy = fdopen(fileDescriptor,THC_WRITE);
	if (!copy)
	{
		free(buffer);
		fclose(read);
		return THC_ERROR_WRITING_FILE;
	}
	
	while ((copiedBytes = fread(buffer,1,sizeof(thcUserAbeyancePasswordType),read)) == sizeof(thcUserAbeyancePasswordType))
	{		
		if (buffer->UID != UID)
		{	
			if(fwrite(buffer,1,sizeof(thcUserAbeyancePasswordType),copy) != sizeof(thcUserAbeyancePasswordType))
				return THC_ERROR_WRITING_DATA_TO_FILE;
		}
	} /*while*/

	free(buffer);	
	fclose(copy);
	fclose(read);
	rename(tempFileName,THC_ABEYANCES_PASSWORD_FILE_NAME);
	
	return THC_OK;
}

thcErrorType thcConfirmEmailCode (thcUserIdentifier UID, char *code)
{
	FILE *read;
	thcEmailConfirmationType buffer;
	
	read = fopen (THC_ABEYANCES_EMAIL_CODES_FILE_NAME,THC_READ);
	if (!read)
		return THC_ERROR_READING_FILE;
		
	while (fread(&buffer,1,sizeof(thcEmailConfirmationType),read) != 0)
	{
		/*UID found*/
		if(buffer.UID == UID)
		{
			fclose(read);
			
			/*Valid Code*/
			if (strcmp(buffer.confirmationCode, code) == 0)
				return THC_OK;
			
			/*Invalid code*/
			return THC_ERROR_INVALID_CODE;
		}
	}
	
	fclose(read);
	
	/*UID not found*/
	return THC_ERROR_UID_NOT_FOUND;
}

thcErrorType thcRemoveFromEmailAbeyanceList (thcUserIdentifier UID, int flag)
{
	thcUserAbeyanceEmailType buffer;
	thcEmailConfirmationType confirmationBuffer;
	FILE *read,*copy;
	int fileDescriptor;
	char tempFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;
	char tempCodesFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;
	
	/***Remove data from confirmation codes file***/
	
	read = fopen(THC_ABEYANCES_EMAIL_CODES_FILE_NAME,THC_READ);
	if (!read) 
		return THC_ERROR_READING_FILE;
	
	fileDescriptor = mkstemp(tempCodesFileName);
	
	if (fileDescriptor == -1)
	{
		fclose(read);
		return THC_ERROR_MKSTEMP;
	}
	
	/*Starts File Descriptor as FILE stream*/
	copy = fdopen(fileDescriptor,THC_WRITE);
	if (!copy)
	{
		fclose(read);
		return THC_ERROR_WRITING_FILE;
	}
	
	while (fread(&confirmationBuffer,1,sizeof(thcEmailConfirmationType),read) == sizeof(thcEmailConfirmationType))
	{		
		if (confirmationBuffer.UID != UID)
		{	
			if(fwrite(&confirmationBuffer,1,sizeof(thcEmailConfirmationType),copy) != sizeof(thcEmailConfirmationType))
				return THC_ERROR_WRITING_DATA_TO_FILE;
		}
	} /*while*/
	
	fclose(copy);
	fclose(read);
	rename(tempCodesFileName,THC_ABEYANCES_EMAIL_CODES_FILE_NAME);
	
	if (flag == -1) return THC_OK;
	
	/**Now remove data from the e-mail abeyances file**/
	/**(Same code as above)**/
	read = fopen(THC_ABEYANCES_EMAIL_FILE_NAME,THC_READ);
	if (!read) 
		return THC_ERROR_READING_FILE;
	
	fileDescriptor = mkstemp(tempFileName);
	
	if (fileDescriptor == -1)
	{
		fclose(read);
		return THC_ERROR_MKSTEMP;
	}
	
	/*Starts File Descriptor as FILE stream*/
	copy = fdopen(fileDescriptor,THC_WRITE);
	if (!copy)
	{
		fclose(read);
		return THC_ERROR_WRITING_FILE;
	}
	
	while (fread(&buffer,1,sizeof(thcUserAbeyanceEmailType),read) == sizeof(thcUserAbeyanceEmailType))
	{		
		if (buffer.UID != UID)
		{	
			if(fwrite(&buffer,1,sizeof(thcUserAbeyanceEmailType),copy) != sizeof(thcUserAbeyanceEmailType))
				return THC_ERROR_WRITING_DATA_TO_FILE;
		}
	} /*while*/
	
	fclose(copy);
	fclose(read);
	rename(tempFileName,THC_ABEYANCES_EMAIL_FILE_NAME);
	
	return THC_OK;
}		



thcErrorType thcRandomSalt (char *salt)
{
	char base64String[64] = THC_BASE64_STRING;
	char generatedString [THC_SALT_LENGHT+1];

	int counter;
	time_t seed;
	
	if(!salt)
		return THC_ERROR_EMPTY_POINTER;

	time(&seed);
	srand(seed);
	
	for(counter = 0; counter < THC_SALT_LENGHT; counter++)
		generatedString[counter] = base64String[rand()%64];
		
	generatedString [THC_SALT_LENGHT] = '\0';
	strcpy(salt,generatedString);

	return THC_OK;
}


thcErrorType thcValidatePassword(const char *plainPassword, const char *encriptedPassword)
{
	char salt[THC_FULL_SALT_LENGHT+1];
	char *encriptedPasswordCopy; //CORRIGIR ISSO AKI **************
	
	strncpy(salt,encriptedPassword,THC_FULL_SALT_LENGHT);
	
	salt [THC_FULL_SALT_LENGHT] = '\0';
	
	encriptedPasswordCopy = crypt(plainPassword,salt);
	
	if ( strcmp(encriptedPassword,encriptedPasswordCopy) == 0) 
		return THC_CORRECT_PASSWORD;

	return THC_INCORRECT_PASSWORD;
	
}


thcErrorType thcEncryptPassword (const char *password, char *encrypted)
{
	char salt[THC_FULL_SALT_LENGHT+1] = "$6$";
	char saltContent[THC_SALT_LENGHT+1];
	
	if (!encrypted)
		return THC_ERROR_EMPTY_POINTER;
	
	if (thcRandomSalt(saltContent))
		return THC_ERROR_EMPTY_POINTER;
	
	strcat(salt,saltContent);
	
	strcat(salt,"$");

	strcpy(encrypted,crypt(password,salt));
	
	return THC_OK;
}



thcErrorType thcGenerateNickname (const char *fullName,char *nickname)
{
	int counter=0;
	int nameCounter=0;
	char copy[THC_FULL_NAME_MAXIMUM_LENGHT];
	char singleName[THC_MAXIMUM_NAMES][THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char *auxString;
	thcUserDataType data;
	int checkAvailableName;
	
	/*0 - Check pointer*/
	if (!fullName) 
		return THC_ERROR_EMPTY_POINTER;
	if (!nickname)
		return THC_ERROR_EMPTY_POINTER;
	
	
	/*1 - Copy full name to auxiliar string*/
	strcpy(copy,fullName);
	
	/*2 - Convert full name to lower case*/
	do
	{
		copy[counter] = tolower(copy[counter]);
		counter++;
	}
	while (counter < strlen(copy));
	
	/*3 - Count how many spaces on full name*/
	for (counter = 0; counter < strlen(copy); counter++)
		if (copy[counter] == ' ') nameCounter++;
	
	
	/*4 - Put the single names on the array*/
	for (counter = 0; counter < nameCounter; counter++)
	{		
		auxString = strstr(copy," ");
		memset(singleName[counter],0x00,THC_FULL_NAME_MAXIMUM_LENGHT+1);
		strncpy(singleName[counter],copy,strlen(copy)-strlen(auxString));
		auxString++;
		strcpy(copy,auxString);	
	}
	
	strcpy(singleName[nameCounter],copy);
	
	/*5 - Generate a valid nickname*/
	
	memset(nickname,0x00,THC_NICKNAME_MAXIMUM_LENGHT+1);
	strcat(nickname,singleName[0]);
	strcat(nickname,".");
	strcat(nickname,singleName[nameCounter]);
	
	do
	{	
		if (strlen(singleName[nameCounter]) > 2)
		{
			memset(nickname,0x00,THC_NICKNAME_MAXIMUM_LENGHT+1);
			strcat(nickname,singleName[0]);
			strcat(nickname,".");
			strcat(nickname,singleName[nameCounter]);
			checkAvailableName = thcSearchUser(nickname, &data);
		}
		nameCounter--;
		
		if (nameCounter == -1)
		{
			memset(nickname,0x00,THC_NICKNAME_MAXIMUM_LENGHT+1);
			strcat(nickname,singleName[0]);
		}
		
		if (nameCounter == -2)
			return THC_ERROR_GENERATE_NICKNAME;

	}
	while (checkAvailableName != THC_ERROR_USERNAME_NOT_FOUND); /*This check if the name is already in use*/
	
	if (strlen(nickname) < THC_MINUMUM_NICKNAME_LENGHT)
		return THC_ERROR_GENERATE_NICKNAME;
	
	return THC_OK;
}	
	


thcErrorType thcGenerateTextFile ()
{
	FILE *binary,*text;
	int fDescriptor;
	thcUserDataType *buffer;
	char tempFileName[THC_TEMP_FILE_NAME_LENGHT+1] = THC_TEMP_FILE_NAME;
	
	buffer = malloc (sizeof(thcUserDataType));
	if (!buffer)
		return THC_ERROR_INSUFICIENT_MEMORY;
	
	binary = fopen(THC_FILE_NAME,THC_READ);
	if (!binary)
		return THC_ERROR_READING_FILE;
		
	fDescriptor = mkstemp(tempFileName);
	if (fDescriptor == -1)
		return THC_ERROR_MKSTEMP;
	
	text = fdopen(fDescriptor, THC_WRITE);
	if (!text)
		return THC_ERROR_WRITING_TEXT_FILE;

	fread(buffer,1,sizeof(thcUserDataType),binary);
	
	fprintf(text,"%llu:",buffer->UID);
	fprintf(text,"%s:",buffer->nickname);
	if(buffer->flag == ok)
		fprintf(text,"%s",buffer->codedPassword);
		
	fprintf(text,":%d:%s:%s",buffer->group,buffer->email,buffer->fullName);

	while (fread(buffer,1,sizeof(thcUserDataType),binary) == sizeof(thcUserDataType))
	{
		fprintf(text,"\n%llu:",buffer->UID);
		fprintf(text,"%s:",buffer->nickname);
		if(buffer->flag == ok)
			fprintf(text,"%s",buffer->codedPassword);
		fprintf(text,":%d:%s:%s",buffer->group,buffer->email,buffer->fullName);
	}	
	fclose(binary);
	fclose(text);
	
	rename(tempFileName, THC_TEXT_FILE_NAME);
	
	return THC_OK;
	
}

thcErrorType thcUserLogin (char *nickname, char *password, thcUserDataType *userData)
{
	thcErrorType errorCode;
	
	errorCode = thcSearchUser(nickname, userData);
	if (errorCode != THC_OK)
		return errorCode;
	
	errorCode = thcValidatePassword(password, userData->codedPassword);
	
	/*Returns ok if password is correct*/
	if (errorCode == THC_CORRECT_PASSWORD)
		return THC_OK;
	
	/*Check if user has reseted the password*/
	if (userData->flag == passwordReset)
	{
		if (thcPasswordResetLogin(userData->UID,password) == THC_CORRECT_PASSWORD);
			return THC_OK;
	}
	
	return THC_INCORRECT_PASSWORD;	
}

thcErrorType thcPasswordResetLogin (thcUserIdentifier UID, char *password)
{
	char codedPassword [THC_ENCRYPTED_PASSWORD_LENGHT+1];
	thcErrorType errorCode;
	
	errorCode = thcPasswordResetSearch(UID,codedPassword);
	if (errorCode != THC_OK)
		return errorCode;
		
	return thcValidatePassword(password,codedPassword);
}

thcErrorType thcPasswordResetSearch (thcUserIdentifier UID, char *encryptedPassword)
{
	FILE *read;
	thcUserAbeyancePasswordType buffer;
	boolean found = thc_false;
	
	read = fopen(THC_ABEYANCES_PASSWORD_FILE_NAME,THC_READ);
	if (!read)
		return THC_ERROR_READING_FILE;
		
		
	while ((fread(&buffer,1,sizeof (thcUserAbeyancePasswordType),read) != 0) && (found == thc_false))
	{
		if (buffer.UID == UID) 
		{
			found = thc_true;
			strcpy(encryptedPassword,buffer.tempPasswordCoded);
		}	
	}
	
	if (found == thc_false) return THC_ERROR_UID_NOT_FOUND;
	
	return THC_OK;
}

thcErrorType thcEmailChangeSearch (thcUserIdentifier UID)
{
	FILE *read;
	thcUserAbeyanceEmailType buffer;
	boolean found = thc_false;
	
	read = fopen(THC_ABEYANCES_EMAIL_FILE_NAME,THC_READ);
	if (!read)
		return THC_ERROR_READING_FILE;
		
		
	while ((fread(&buffer,1,sizeof (thcUserAbeyanceEmailType),read) != 0) && (found == thc_false))
	{
		if (buffer.UID == UID)
			found = thc_true;
	}
	
	if (found == thc_false) return THC_ERROR_UID_NOT_FOUND;
	
	return THC_OK;
}

thcErrorType thcResetPassword (char *nickname, thcLanguageType language)
{
	thcUserDataType data;
	thcErrorType errorCode;
	char password [THC_TEMP_PASSWORD_LENGHT+1];
	
	/*Grab user data*/
	errorCode = thcSearchUser(nickname,&data);
	if (errorCode != THC_OK)
		return errorCode;
	
	/*Make a temporary password*/
	errorCode = thcGenerateTemporaryPassword(password);
	if (errorCode != THC_OK)
		return errorCode;

	/*Save data to abeyance file*/
	errorCode = thcAddAbeyancePassword(data,password);
	if (errorCode != THC_OK)
		return errorCode;
		
	/*Change flag from data*/
	data.flag = passwordReset;
	thcRemoveUserData(nickname);
	thcWriteFile(&data);
	
	/*Send e-mail with password*/
	if (thcSendPasswordResetEmail(data,password,language) != THC_OK)
		return THC_ERROR_EMAIL;
	
	return thcGenerateTextFile();
}

thcErrorType thcAddAbeyanceUser (const thcUserAbeyancesType data,const char *fileName)
{
	FILE *abeyanceFile;
	
	abeyanceFile = fopen(fileName,THC_APPEND);	
	if (!abeyanceFile)
		return THC_ERROR_WRITING_FILE;
	
	if (fwrite(&data,1,sizeof(thcUserAbeyancesType),abeyanceFile) != sizeof(thcUserAbeyancesType))
		return THC_ERROR_WRITING_DATA_TO_FILE;
	
	fclose(abeyanceFile);
	
	return THC_OK;
}



thcErrorType thcClearUserFlag (const thcUserIdentifier UID, thcUserFlagType flagToClean)
{
	FILE *read;
	boolean found =  thc_false;
	thcUserDataType data;
	thcErrorType errorCode;
	
	read = fopen(THC_FILE_NAME,THC_READ);
	if (!read) return THC_ERROR_READING_FILE;

	while ((found == thc_false) && (fread(&data, sizeof(thcUserDataType),1,read) != 0))
		if (data.UID == UID) found = thc_true; 

	fclose(read);
	
	if (found == thc_false)
		return THC_ERROR_UID_NOT_FOUND;
	
	/*Change flag and set to file*/
	if (data.flag != flagToClean)
	{
		if (flagToClean == passwordReset)	
			return THC_ERROR_USER_DIDNT_RESET;
		if (flagToClean == emailChange)
			return THC_ERROR_USER_DIDNT_EMAIL;
	}
	data.flag = ok;
	
	/*Saves new data on file*/
	errorCode = thcRemoveUserData(data.nickname);
	if (errorCode != THC_OK)
		return errorCode;
	
	errorCode = thcWriteFile(&data);
	if (errorCode != THC_OK)
		return errorCode;
			
	return THC_OK;
	
}


thcErrorType thcChangeEmailAdress(char *nickname, char *newEmail, thcLanguageType language)
{
	thcErrorType errorCode;
	thcUserDataType data;
	char confirmationCode[THC_COOKIE_CONTENT_LENGHT+1];
	
	/*1 - grab all user data*/
	errorCode = thcSearchUser(nickname, &data);
	if (errorCode != THC_OK)
		return errorCode;
	
	/*2 - create abeyance file with the e-mail*/
	errorCode = thcAddAbeyanceEmail(data.UID, newEmail , confirmationCode);
	if (errorCode != THC_OK)
		return errorCode;
		
	/*3 - Change flag to e-mail change*/
	data.flag = emailChange;
	errorCode = thcRemoveUserData(nickname);	
	if (errorCode != THC_OK)
		return errorCode;
	errorCode = thcWriteFile(&data);
	if (errorCode != THC_OK)
		return errorCode;
		
	/*4 - send email to confirm*/
	if (thcSendEmailAdressChangeEmail(data,newEmail,confirmationCode,language) != THC_OK)
		return THC_ERROR_EMAIL;	
	
	return THC_OK;	
}



thcErrorType thcAddAbeyancePassword (const thcUserDataType data, char *tempPassword)
{
	FILE *abeyanceFile;
	thcUserAbeyancePasswordType buffer;
	char encrypted [THC_ENCRYPTED_PASSWORD_LENGHT+1];
	time_t expiration;
	thcErrorType errorCode;
	
	/*Search if user already reseted password and remoeve the old reset*/
	if (thcPasswordResetSearch(data.UID,encrypted) == THC_OK)
		thcRemoveFromPasswordAbeyanceList(data.UID);
		
	abeyanceFile = fopen (THC_ABEYANCES_PASSWORD_FILE_NAME,THC_APPEND);
	if (!abeyanceFile)
		return THC_ERROR_WRITING_FILE;
	
	
	/*Clears trash from buffer and encrypted password*/
	memset(&buffer,0x00,sizeof(thcUserAbeyancePasswordType));
	memset(encrypted,0x00,THC_ENCRYPTED_PASSWORD_LENGHT+1);
	
	
	/*Copy information to another file*/
	buffer.UID = data.UID;
	
	expiration = time(NULL) + THC_PASSWORD_RESET_EXPIRATION;
	buffer.expiration = expiration;
	
	errorCode = thcEncryptPassword(tempPassword,encrypted);
		
	if (errorCode != THC_OK)
	{
		fclose(abeyanceFile);
		return errorCode;		
	}
	
	strcpy(buffer.tempPasswordCoded, encrypted);
	
	if (fwrite(&buffer,sizeof(thcUserAbeyancePasswordType),1,abeyanceFile) != 1)
	{
		fclose(abeyanceFile);
		return THC_ERROR_WRITING_DATA_TO_FILE;	
	}
	
	fclose(abeyanceFile);
	return THC_OK;
}

thcErrorType thcAddAbeyanceEmail (const thcUserIdentifier UID, const char *newEmail, char* confirmationCode)
{
	FILE *abeyanceFile, *confirmationFile;
	thcUserAbeyanceEmailType buffer;
	thcEmailConfirmationType confirm;
	time_t expiration;
	char code[THC_COOKIE_CONTENT_LENGHT+1];
	thcErrorType errorCode;

	/*Search if user already reseted password and remove old data*/
	if (thcEmailChangeSearch (UID) == THC_OK)
		thcRemoveFromEmailAbeyanceList(UID,0);
		
	/*Generates a confirmation code*/
	errorCode = thcGenerateCookieContent(code);
	if (errorCode != THC_OK)
		return errorCode;
	
	/*Opens both files*/
	abeyanceFile = fopen (THC_ABEYANCES_EMAIL_FILE_NAME,THC_APPEND);
	if (!abeyanceFile)
		return THC_ERROR_WRITING_FILE;
	
	confirmationFile = fopen (THC_ABEYANCES_EMAIL_CODES_FILE_NAME,THC_APPEND);
	if (!confirmationFile)
		return THC_ERROR_WRITING_FILE;
	
	/*Clears trash from buffer*/
	memset(&buffer,0x00,sizeof(thcUserAbeyanceEmailType));
		
	/*Copy information to variables*/
	buffer.UID = UID;
	expiration = time(NULL) + THC_EMAIL_RESET_EXPIRATION;
	buffer.expiration = expiration;
	strcpy(buffer.email,newEmail); 
	
	confirm.UID = UID;
	strcpy(confirm.confirmationCode,code);
		
	
	/*Save data to file*/
	if (fwrite(&buffer,sizeof(thcUserAbeyanceEmailType),1,abeyanceFile) != 1)
	{
		fclose(abeyanceFile);
		return THC_ERROR_WRITING_DATA_TO_FILE;	
	}
	
	if (fwrite(&confirm,sizeof(thcEmailConfirmationType),1,confirmationFile) != 1)
	{
		fclose(abeyanceFile);
		fclose(confirmationFile);
		return THC_ERROR_WRITING_DATA_TO_FILE;
	}
	
	/*Send back the code*/
	strcpy(confirmationCode,code);
	
	fclose(confirmationFile);
	fclose(abeyanceFile);
	return THC_OK;
}


thcErrorType thcGetValidUid (thcUserIdentifier *UID)
{
	thcUserDataType data;
	thcUserIdentifier id = 1;


	while (thcSearchUserByUID(id,&data) != THC_ERROR_UID_NOT_FOUND)
		id++;
	
	*UID = id;

	return THC_OK;
}


thcErrorType thcSendConfirmationMail(const char *username,const char *password,char *email, const char *nickname, thcLanguageType language)
{
	
	char body[700];
	memset(body,0x00,700);
	
	if (language == english)
	{
		strcat(body,username);
		strcat(body," , your registration was successfully made\nThis is your username: ");
		strcat(body,nickname);
		strcat(body,"\nYour temporary password is :");
		strcat(body,password);
		strcat(body,"\nAccess your account at http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index.html");	
		strcat(body,"\nYou have 72h to login and change your password or your account will be deleted");	
	}

	if (language == portuguese)
	{
		strcat(body,username);
		strcat(body," , seu cadastro foi efetuado com sucesso\nEsse é o seu nickname: ");
		strcat(body,nickname);
		strcat(body,"\nSua senha temporaria é :");
		strcat(body,password);
		strcat(body,"\nAcesse sua conta em http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index_br.html");	
		strcat(body,"\nVoce tem 72h para logar e trocar sua senha, caso contrario sua conta será deletada");	
	}

	sendMail("del.ufrj.br","smtp.del.ufrj.br",25,"no-reply-thc@del.ufrj.br",email,NULL,NULL,"Tree High CloudDropper",body,NULL);
	
	
	return THC_OK;
}

thcErrorType thcInvitationMail(const char *username,const char *invitedBy ,const char *password,char *email, const char *nickname, thcLanguageType language)
{
	
	char body[700];
	
	memset(body,0x00,700);
		
	if (language == english)
	{		
		strcat(body,username);
		strcat(body," ,you have been invited by ");
		strcat(body,invitedBy);
		strcat(body," to join Tree High CloudDropper ");
		strcat(body,"\nYour username is :");
		strcat(body,nickname);
		strcat(body,"\nAnd your temporary password is :");
		strcat(body,password);
		strcat(body,"\nAccess your account at http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index.html");	
		strcat(body,"\nYou have 72h to login and change your password or your account will be deleted");
	}
	
	
	if (language == portuguese)
	{		
		strcat(body,username);
		strcat(body," ,voce foi convidado por ");
		strcat(body,invitedBy);
		strcat(body," para participar de Tree High CloudDropper ");
		strcat(body,"\nSeu login é :");
		strcat(body,nickname);
		strcat(body,"\nE sua senha temporaria é :");
		strcat(body,password);
		strcat(body,"\nAcesse sua conta em http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index_br.html");	
		strcat(body,"\nVoce tem 72h para logar e trocar sua senha, caso contrario sua conta será deletada");	
	}
	
	
	sendMail("del.ufrj.br","smtp.del.ufrj.br",25,"no-reply-thc@del.ufrj.br",email,NULL,NULL,"Tree High CloudDropper",body,NULL);
		
	
	return THC_OK;
}

thcErrorType thcSendPasswordResetEmail(thcUserDataType data,char *password,thcLanguageType language)
{
		
	char body[700];
	
	memset(body,0x00,700);
		
	if (language == english)
	{		
		strcat(body,data.fullName);
		strcat(body," ,you have requested a password change in our system\nUse this following password to access the system : ");
		strcat(body,password);
		strcat(body,"\n\nAccess your account at http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index.html");	
		strcat(body,"\nYou have 24h to login and change your password");
	}
	
	
	if (language == portuguese)
	{		
		strcat(body,data.fullName);
		strcat(body," ,você solicitou um reset de senha no nosso sistema\nUse a seguinte senha para ter acesso novamente : ");
		strcat(body,password);
		strcat(body,"\n\nAcesse sua conta em http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index_br.html");	
		strcat(body,"\nVoce tem 24h para logar e trocar sua senha");
	}
	
	
	sendMail("del.ufrj.br","smtp.del.ufrj.br",25,"no-reply-thc@del.ufrj.br",data.email,NULL,NULL,"Tree High CloudDropper",body,NULL);
		
	
	return THC_OK;	
	
}


thcErrorType thcSendEmailAdressChangeEmail(thcUserDataType data, char *newEmail ,char *confirmationCode ,thcLanguageType language)
{
		
	char body[700];
	
	memset(body,0x00,700);
	
	/*Send e-mail to the new adress*/	
	if (language == english)
	{		
		strcat(body,data.fullName);
		strcat(body," ,you have requested an e-mail change, to confirm this as your new e-mail click on the link below : \n");
		strcat(body,THC_EMAIL_CONFIRM_CGI_NAME);
		strcat(body,"?thcNickname=");
		strcat(body,data.nickname);
		strcat(body,"&thcConfirmationCode=");
		strcat(body,confirmationCode);	
		strcat(body,"&thcLanguage=en");	
		strcat(body,"\nYou have 24h to confirm this as your new email.");
	}
	
	
	if (language == portuguese)
	{		
		strcat(body,data.fullName);
		strcat(body," , você solicitou uma troca de endereço de e-mail, para confirmar esta operação clique no link a seguir : \n");
		strcat(body,THC_EMAIL_CONFIRM_CGI_NAME);
		strcat(body,"?thcNickname=");
		strcat(body,data.nickname);
		strcat(body,"&thcConfirmationCode=");
		strcat(body,confirmationCode);
		strcat(body,"&thcLanguage=br");	
		strcat(body,"\nVocê tem 24h para confirmar este como seu novo e-mail.");
	}
	
	sendMail("del.ufrj.br","smtp.del.ufrj.br",25,"no-reply-thc@del.ufrj.br",newEmail,NULL,NULL,"Tree High CloudDropper",body,NULL);
	
	/*Now send the deny email link to the old adress*/
	memset(body,0x00,700);
	
	if (language == english)
	{		
		strcat(body,data.fullName);
		strcat(body," ,you have requested an e-mail change, to deny thus change and keep thus as your e-mail adress click on the link below: \n");
		strcat(body,THC_EMAIL_DENY_CGI_NAME);
		strcat(body,"?thcNickname=");
		strcat(body,data.nickname);
		strcat(body,"&thcConfirmationCode=");
		strcat(body,confirmationCode);	
		strcat(body,"&thcLanguage=en");	
		strcat(body,"\nIf you don't confirm this change in 24h, it will auto deny the e-mail change");
	}
	
	
	if (language == portuguese)
	{		
		strcat(body,data.fullName);
		strcat(body," , você solicitou uma troca de endereço de e-mail, para confirmar esta operação clique no link a seguir : \n");
		strcat(body,THC_EMAIL_DENY_CGI_NAME);
		strcat(body,"?thcNickname=");
		strcat(body,data.nickname);
		strcat(body,"&thcConfirmationCode=");
		strcat(body,confirmationCode);
		strcat(body,"&thcLanguage=br");	
		strcat(body,"\nVocê tem 24h para cancelar essa alteração, caso não confirme em 24h, seu pedido será cancelado automaticamente.");
	}
		
	sendMail("del.ufrj.br","smtp.del.ufrj.br",25,"no-reply-thc@del.ufrj.br",data.email,NULL,NULL,"Tree High CloudDropper",body,NULL);
	
	return THC_OK;	
	
}

thcErrorType thcWebShowMenu(thcLanguageType language, thcUserDataType data)



{
	char *menuOptions[][2]=
	{
		{"home","pagina inicial"},
		{"user options","opões de usuário"},
		{"invite an user","convidar um amigo"},
		{"change password","trocar senha"},
		{"change e-mail","trocar e-mail"},
		{"change username","alterar nome"},
		{"remove account","remover conta"},
		{"Help","ajuda"},
		{"contact","contato"},
		{"logout","sair"},
		{"change user group","trocar grupo de usuario"},
		{"add user to group","adicionar usuario ao grupo"},
	};

	
	char *selectedLanguage[2] = {"en","br"};
	
	
	/*Check for admin member*/
	if ((data.group != administrador) && (data.group != userAdmin) && (data.group != ownerAdmin) &&(data.group != root))
	{
		/*print user menu*/
		printf("<div id='left-sidebar'>                                                                                 \n");
		printf("	<div id='cssmenu'>                                                                                  \n");
		printf("	<ul>                                                                                                \n");
		printf("	   <li class='active'><a href='thcHome.cgi?thcNickname=%s'><span>%s</span></a></li>                 \n",data.nickname,menuOptions[0][language]);
		printf("	   <li class='has-sub'><a href='#'><span>%s</span></a>                                              \n",menuOptions[1][language]);  
		printf("		  <ul>                                                                                          \n");
		printf("			 <li><a href='thcCgiShowInviteUserForm.cgi?thcNickname=%s'><span>%s</span></a></li>         \n",data.nickname,menuOptions[2][language]);  
		printf("			 <li><a href='thcCgiShowChangePasswordForm.cgi?thcNickname=%s'><span>%s</span></a></li>     \n",data.nickname,menuOptions[3][language]);
		printf("			 <li><a href='thcCgiShowChangeUserEmailForm.cgi?thcNickname=%s'><span>%s</span></a></li>    \n",data.nickname,menuOptions[4][language]);
		printf("			 <li><a href='thcCgiShowChangeUsernameForm.cgi?thcNickname=%s'><span>%s</span></a></li>     \n",data.nickname,menuOptions[5][language]);
		printf("			 <li class='last'><a href='thcCgiShowRemoveUserForm.cgi?thcNickname=%s'><span>%s</span></a></li>\n",data.nickname,menuOptions[6][language]); 
		printf("		  </ul>                                                                                         \n");
		printf("	   </li>                                                                                            \n");
		printf("	   <li><a href='thcShowHelp.cgi?thcLanguage=%s'><span>%s</span></a></li>                            \n",selectedLanguage[language],menuOptions[7][language]); 
		printf("	   <li><a href='mailto:joaov.ferreira@poli.ufrj.br'><span>%s</span></a></li>                        \n",menuOptions[8][language]);
		printf("	   <li class='last'><a href='thcLogout.cgi?thcNickname=%s&thcLanguage=%s'><span>%s</span></a></li>  \n",data.nickname,selectedLanguage[language],menuOptions[9][language]);
		printf("	</ul>                                                                                               \n"); 
		printf("	</div>                                                                                              \n");
		printf("</div>		                                                                                            \n"); 
		return THC_OK;
	}
	
	/*Print admin menu*/
	printf("<div id='left-sidebar'>                                                                                 \n");
	printf("	<div id='cssmenu'>                                                                                  \n");
	printf("	<ul>                                                                                                \n");
	printf("	   <li class='active'><a href='thcHome.cgi?thcNickname=%s'><span>%s</span></a></li>                 \n",data.nickname,menuOptions[0][language]);
	printf("	   <li class='has-sub'><a href='#'><span>%s</span></a>                                              \n",menuOptions[1][language]);  
	printf("		  <ul>                                                                                          \n");
	printf("			 <li><a href='thcCgiShowInviteUserForm.cgi?thcNickname=%s'><span>%s</span></a></li>         \n",data.nickname,menuOptions[2][language]);  
	printf("			 <li><a href='thcCgiShowChangePasswordForm.cgi?thcNickname=%s'><span>%s</span></a></li>     \n",data.nickname,menuOptions[3][language]);
	printf("			 <li><a href='thcCgiShowChangeUserEmailForm.cgi?thcNickname=%s'><span>%s</span></a></li>    \n",data.nickname,menuOptions[4][language]);
	printf("			 <li><a href='thcCgiShowChangeUsernameForm.cgi?thcNickname=%s'><span>%s</span></a></li>     \n",data.nickname,menuOptions[5][language]);
	printf("			 <li><a href='thcCgiShowChangeUserGroup.cgi?thcNickname=%s'><span>%s</span></a></li>        \n",data.nickname,menuOptions[10][language]);
	printf("			 <li><a href='thcCgiShowAddUserToGroup.cgi?thcNickname=%s'><span>%s</span></a></li>         \n",data.nickname,menuOptions[11][language]);
	printf("			 <li class='last'><a href='thcCgiShowRemoveUserForm.cgi?thcNickname=%s'><span>%s</span></a></li>\n",data.nickname,menuOptions[6][language]); 
	printf("		  </ul>                                                                                         \n");
	printf("	   </li>                                                                                            \n");
	printf("	   <li><a href='thcShowHelp.cgi?thcLanguage=%s'><span>%s</span></a></li>                            \n",selectedLanguage[language],menuOptions[7][language]); 
	printf("	   <li><a href='mailto:joaov.ferreira@poli.ufrj.br'><span>%s</span></a></li>                        \n",menuOptions[8][language]);
	printf("	   <li class='last'><a href='thcLogout.cgi?thcNickname=%s&thcLanguage=%s'><span>%s</span></a></li>  \n",data.nickname,selectedLanguage[language],menuOptions[9][language]);
	printf("	</ul>                                                                                               \n"); 
	printf("	</div>                                                                                              \n");
	printf("</div>		                                                                                            \n"); 
	return THC_OK;
}


thcErrorType thcWebShowHeader()
{
	printf("<html xmlns=\"http://www.w3.org/1999/xhtml\"                                                           \n"); 
	printf("                                                                                                       \n");
	printf("<head>                                                                                                 \n");
	printf("	<title>Tree High CloudDropper</title>                                                              \n");
	printf("	<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />                           \n");
	printf("	<link rel=\"stylesheet\" href=\"css/styles.css\">                                                  \n");
	printf("	<meta name=\"generator\" content=\"Geany 1.22\" />                                                 \n");
	printf("</head>                                                                                                \n");
	
	return THC_OK;
}	


thcErrorType thcWebShowFooter()
{
	printf("  <div id='footer'>  \n");
	printf("    Copyright 2013   \n");
	printf("  </div>             \n");
	printf("	</body>          \n");                            
	printf("</html>              \n");
	
	return THC_OK;
}

thcErrorType thcReadEmailFromAbeyanceFile(thcUserIdentifier UID, thcEmailAbeyancesType *data)
{
	FILE *read;
	boolean found =  thc_false;
	
	read = fopen(THC_ABEYANCES_EMAIL_FILE_NAME,THC_READ);
	if (!read) return THC_ERROR_READING_FILE;

	while ((found == thc_false) && (fread(data, sizeof(thcEmailAbeyancesType),1,read) != 0))
		if (data->UID == UID) found = thc_true; 

	fclose(read);
	
	if (found == thc_false)
		return THC_ERROR_UID_NOT_FOUND;
			
	return THC_OK;
	
}

thcErrorType thcSearchUserByUID(thcUserIdentifier UID,thcUserDataType *data)                                              
{
	FILE *read;
	boolean found =  thc_false;
	
	read = fopen(THC_FILE_NAME,THC_READ);
	if (!read) return THC_ERROR_READING_FILE;

	while ((found == thc_false) && (fread(data, sizeof(thcUserDataType),1,read) != 0))
		if (data->UID == UID) found = thc_true; 

	fclose(read);
	
	if (found == thc_false)
		return THC_ERROR_UID_NOT_FOUND;
			
	return THC_OK;	
}                            

thcErrorType thcCookieNameToNickname(const char *cookieName, char *nickname)
{
	thcErrorType errorCode;
	thcUserIdentifier UID;
	thcUserDataType data;
	
	UID = strtoull(cookieName,NULL,10);
		
	errorCode = thcSearchUserByUID(UID, &data);
	if (errorCode != THC_OK)
		return errorCode;
	
	strcpy(nickname,data.nickname);
	
	return THC_OK;
}