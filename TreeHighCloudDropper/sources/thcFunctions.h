/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                            
 * $Author: joao.duarte $                                   
 * $Date: 2013/04/06 18:55:09 $                                     
 * $Log: thcFunctions.h,v $
 * Revision 1.6  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.5  2013/03/26 02:45:20  joao.duarte
 * fixed bugs on change e-mail function
 *
 * Revision 1.4  2013/03/24 03:26:58  joao.duarte
 * Added functions related to change e-mail adress process
 *
 * Revision 1.3  2013/03/22 21:19:23  joao.duarte
 * added reset password related functions
 *
 * Revision 1.2  2013/03/21 21:03:31  joao.duarte
 * Added clean abeyance file function
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */          

#include "thcTypes.h"
#include <time.h>

#ifndef THC_FUNCTIONS_H
#define THC_FUNCTIONS_H 						"@(#)thcFunctions.h $Revision: 1.6 $"

/*
* thcErrorType thcGenerateCookie (char *cookieName, time_t *expiration, char *content, char *IPAddress)
*
* Arguments:
* char *cookieName   - Cookie Name
* tme_t *expiration  - cookie expiration
* char *content      - Cookie Content
* char *IPAddress    - User IP Address
* 
* Returned code:
* THC_ERROR_COOKIE_USERNAME   		- User field contains a null pointer
* THC_ERROR_WRITING_FILE      		- Could't write the file
* THC_ERROR_COOKIE_EXPIRATION 		- Error writing cookie expiration to file
* THC_ERROR_COOKIE_CONTENT    		- Error writing cookie content to file
* THC_ERROR_COOKIE_IP         		- Error writing cookie IP to file
* THC_ERROR_COOKIE_CONTENT_POINTER	- Content field contains a null pointer
* THC_ERROR_COOKIE_IP_POINTER		- IP field contais a null pointer
* THC_OK							- Cookie created with no errors
* 
* Description:
* This function creates file named user on the directory (NÃO IMPLEMENTADO AINDA !!!) with the cookie content
* 
* ex : thcGenerateCookie("nate.drake",&expirationTime, cookieContent, "146.164.96.154"); 
*/
thcErrorType thcGenerateCookie (char *cookieName, time_t *expiration, char *content, char *IPAddress);


/*
 * thcErrorType thcReadCookie (char *cookieName, time_t *expiration,  char *content, char *IP)
 * 
 * Arguments: 
 * char *cookieName				- Cookie Name
 * time_t *expiration			- cookie expirations
 * char *content    			- Cookie Content
 * char *IPAddress   			- User IP Address
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE		- Error opening file for reading
 * THC_ERROR_COOKIE_EXPIRATION	- Error reading cookie expirations
 * THC_ERROR_COOKIE_CONTENT		- Error reading cookie content
 * THC_ERROR_COOKIE_IP			- Error reading cookie IP
 * THC_OK						- Cookie information readed with no errors
 * 
 * Description:
 * This function reads a cookie with the name username on the directory (NÃO IMPLEMENTADO AINDA !!!!)
 * and saves the content on *expirations, *content and *IPAddress if successful
 */
thcErrorType thcReadCookie (char *cookieName, time_t *expiration, char *content, char *IP);




/* 
 * thcErrorType thcGenerateCookieContent (char *content)
 * 
 * Arguments: 
 * char *content 			- Generated Cookie content
 * 
 * Returned Code:
 * THC_ERROR_EMPTY_POINTER	- Function has received an empty pointer
 * THC_OK					- Function  has successfully generated a random cookie content
 * 
 * Description:
 * This functions generates a random cookie content and stores it on char *
 */
thcErrorType thcGenerateCookieContent (char *content);



/*
 * thcErrorType thcGenerateTemporaryPassword(char *password)
 * 
 * Arguments :
 * char *password 			- Generated password
 * 
 * Returned Code:
 * THC_ERROR_EMPTY_POINTER	- Function has received an empty pointer
 * THC_OK					- Function  has successfully generated a random password
 * 
 * Description:
 * This functions generates a random password and stores it on char *
 */
thcErrorType thcGenerateTemporaryPassword(char *password);



/*
 * thcErrorType thcSearchUser (char *nickname, thcUserDataType *data);
 * 
 * Arguments: 
 * char *nickname					- user nickname
 * thcUserDataType *data			- struct with all user data
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_USERNAME_NOT_FOUND		- Nickname not found on the file
 * THC_OK							- User found without errors
 * 
 * Description:
 * This functions takes a nickname and search for it on the file THC_FILE_NAME and saves user information
 * on *data if found
 */
thcErrorType thcSearchUser (char *nickname, thcUserDataType *data);


/*
 * thcErrorType thcWriteFile(thcUserDataType *data)
 * 
 * Arguments: 
 * thcUserDataType *data				- User data
 * 
 * Returned Code:
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_ERROR_READING_FILE				- Error reading file, this error only ocour when file already exists
 * THC_ERROR_MKSTEMP					- Error creating a temporary file			
 * THC_ERROR_NICKNAME_USED				- Error nickname already used
 * THC_OK								- New user data added to the file
 * 
 * Description:
 * This functions takes user data pointed from *data and saves in the binary file (UPDATES THE TEXT FILE NOT INPLEMENTED)
 * named THC_FILE_NAME and save it in alphabetical order
 */
thcErrorType thcWriteFile(thcUserDataType *data);


/*
 * thcErrorType thcRemoveUser(char *nickname)
 * 
 * Arguments: 
 * char *nickname 						- nickname
 * 
 * Returned Code:
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- User removed from the file
 * 
 * Description:
 * This functions removes a user from the file THC_FILE_NAME
 */
thcErrorType thcRemoveUserData(char *nickname);


/*
 * thcErrorType thcRemoveFromAbeyanceList(char *nickname)
 * 
 * Arguments: 
 * char *nickname						- user nickname
 * 
 * Returned Code:
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- Function executed witouth errors
 * 
 * Description:
 * This function remove user information from the users abeyances file
 */
thcErrorType thcRemoveFromAbeyanceList(char *nickname);


/*
 * thcErrorType thcRemoveFromPasswordAbeyanceList (thcUserIdentifier UID)
 * 
 * Arguments: 
 * thcUserIdentifier 					- UID
 * 
 * Returned Code:
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- Function executed witouth errors
 * Description:
 * This function removes user information from the password abeyances file
 */
thcErrorType thcRemoveFromPasswordAbeyanceList (thcUserIdentifier UID);



/*
 * boolean thcValidatePassword (const char *plainPassword, const char *encryptedPassword)
 * 
 * Arguments: 
 * const char *plainPassword			- User's plain password
 * const char *encriptedPassword		- Encrypted password
 * 
 * Returned Code:
 * THC_CORRECT_PASSWORD					- Valid password
 * THC_INCORRECT_PASSWORD				- Invalid password
 * 
 * Description:
 * This functions receives a plain password and an encrypted password, then compares if
 * the password is correct and return a correspondent code
 */
thcErrorType thcValidatePassword(const char *plainPassword, const char *encriptedPassword);


/*
 * thcErrorType thcRandomSalt (char *salt)
 * 
 * Arguments: 
 * char *salt							- Generated salt
 * 
 * Returned Code:
 * THC_ERROR_EMPTY_POINTER				- Function has received an empty pointer
 * THC_OK								- Function executed with no errors
 * 
 * Description:
 * This function generates a random salt and stores it on char *
 */
thcErrorType thcRandomSalt (char *salt);



/*
 * thcErrorType thcEncryptPassword (const char *password, char *encrypted)
 * 
 * Arguments: 
 * const char *password					- Plain user password
 * char *encrypted						- Generated encrypted password
 * 
 * Returned Code:
 * THC_ERROR_EMPTY_POINTER				- Function has received an empty pointer
 * THC_OK								- Function executed with no errors
 * 
 * Description:
 * This function takes a plain password and encrypt it with a random salt and stores it on char * 
 */
thcErrorType thcEncryptPassword (const char *password, char *encrypted);


/*
 * thcErrorType thcGenerateNickname (const char *fullName,char *nickname)
 * 
 * Arguments: 
 * const char *fullName		- Full User name
 * char *nickname			- Variable to store generated nickname
 * 
 * Returned Code:
 * THC_ERROR_EMPTY_POINTER		- Function has received a NULL pointer
 * THC_ERROR_GENERATE_NICKNAME	- Could't make a nickname, user should contact admin
 * THC_OK 						- Nickname Generated
 * 
 * Description:
 * This functions takes the full name and generates a valid nickname for the system
 * e.g. : 	"thcGenerateNickname ("Uellerson Dion da Silva",nickname)
 * 			nickname will be uellerson.silva, if this nickname is already been used
 * 			nickname will be uellerson.dion, the functions change all to lower case
 * 			and ignores middle names with less than 3 caracters
 * 
 * If this both of this names are used, nickname will return only "uellerson".
 * If even this is already in use, the function will return a error code
 * 
 */
thcErrorType thcGenerateNickname (const char *fullName,char *nickname);


/*
 * thcErrorType thcGenerateTextFile (void); 
 * 
 * Returned Code:
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_OK								- Successfull generated text file
 * Description:
 * This functions takes the content from THC_FILE_NAME and generates a text file with the
 * user information in the same order that is found on the binary file
 */
thcErrorType thcGenerateTextFile (void);


/*
 * thcErrorType thcUserLogin (char *nickname, char *password, thcUserDataType *userData);
 *
 * Arguments:
 * char *nickname 				- User nickname
 * char *password 				- User password
 * thcUserDataType *userData	- Readed User data
 * 
 * Returned Code:
 * Same return codes from thcSearchUser() and thcValidatePassword()
 * THC_OK						- Successfull logged id
 * 
 * Description:
 * This function takes a nickname and a password, if they are correct, the
 * function will return THC_OK and thcUserDataType *userData will store the user data
 */
thcErrorType thcUserLogin (char *nickname, char *password, thcUserDataType *userData);



/*
 * thcErrorType thcResetPassword (char *nickname, thcLanguageType language)
 * 
 * Arguments: 
 * char *nickname					- user nickname
 * thcLanguageType language			- selected language
 * 
 * Returned Code:
 * THC_ERROR_EMAIL					- Error sending e-mail to the user
 * THC_OK							- Function executed with no errors
 * 
 * it also has the same return codes as thcSearchUser, thcGenerateTemporaryPassword and
 * thcAddAbeyancePassword 
 * 
 * Description:
 * This functions generates a temporary password for the selected user and sends it
 * to his e-mail to be able to log again on the system
 */
thcErrorType thcResetPassword (char *nickname, thcLanguageType language);



/*
 * thcErrorType thcAddAbeyanceUser (const thcUserAbeyancesType data,const char *fileName)
 * 
 * Arguments:
 * const thcUserAbeyancesType data	- User data
 * const char *fileName				- File name to store user data
 * 
 * Returned Code :
 * THC_ERROR_WRITING_FILE				- Error opening file for append data
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to file
 * THC_OK								- Successfull added user to abeyances file
 * 
 * Description:
 * This function takes user data from the struct data, and appends this on the file
 * with the name described by fileName.
 */
thcErrorType thcAddAbeyanceUser (const thcUserAbeyancesType data,const char *fileName);



/*
 * thcErrorType thcAddAbeyanceEmail (const thcUserIdentifier UID, const char *newEmail, char* confirmationCode)
 * 
 * Arguments: 
 * const thcUserIdentifier UID			- User ID 
 * const char *newEmail					- New user's e-mail
 * char* confirmationCode				- Generated confirmation code
 * 
 * Returned Code:
 * THC_ERROR_WRITING_FILE				- Error Creating the file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- Function executed with no errors
 * 
 * and it has the same errorCodes from thcGenerateCookieContent
 * 
 * Description:
 * This functions starts the change e-mail process, it will add the user new email to the abeyance file
 * and will generate a confirmation Code to confirm or deny the new e-mail
 */
thcErrorType thcAddAbeyanceEmail (const thcUserIdentifier UID, const char *newEmail, char* confirmationCode);



/*
 * thcErrorType thcAddAbeyancePassword (const thcUserDataType data, char *tempPassword)
 * 
 * Arguments: 
 * const thcUserDataType data			- User data
 * char *tempPassword					- temporary password
 * 
 * Returned Code:
 * THC_ERROR_WRITING_FILE				- Error Creating the file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- Function executed with no errors
 * 
 * and it has the same return codes as thcEncryptPassword
 * 
 * Description:
 * This functions adds a user UID and his encrypted temporary password to the abeyance file
 */
thcErrorType thcAddAbeyancePassword (const thcUserDataType data, char *tempPassword);



/*
 * thcErrorType thcGetValidUid (thcUserIdentifier *UID);
 *
 * Arguments:
 * thcUserIdentifier *UID		- User ID
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE		- Error reading UID file
 * THC_OK						- Successfull obtained a UID
 * 
 * Description:
 * This functions generates an unused UID and store it on thcUserIdentifier *
 * 
 */
thcErrorType thcGetValidUid (thcUserIdentifier *UID);

/*
 * thcErrorType thcClearUserFlag (const thcUserIdentifier UID, thcUserFlagType flagToClean)
 * 
 * Arguments: 
 * const thcUserIdentifier UID		- User UID
 * thcUserFlagType flagToClean		- Flag to the function
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE			- Error opening the file
 * THC_ERROR_UID_NOT_FOUND			- User uid not found on system
 * THC_ERROR_USER_DIDNT_RESET		- Selected user didn't reseted his password
 * THC_ERROR_USER_DIDNT_EMAIL		- Selected user didn't reseted his e-mail
 * THC_OK							- Function executed with no errors
 * 
 * and the same return codes from thcWriteFile and thcRemoveUserData
 * 
 * Description:
 * This function will search a user by UID and will check if user flag is equal to selected
 * flat (flagToClean). If they match, it will change it to ok, else will return an errorCode
 */
thcErrorType thcClearUserFlag (const thcUserIdentifier UID, thcUserFlagType flagToClean);

/*
 * thcErrorType thcInvitationMail(const char *username,const char *invitedBy ,const char *password,
 *	       						    char *email, const char *nickname, thcLanguageType language)
 * 
 * Arguments: 
 * const char *username				- Full invited user name
 * const char *invitedBy			- Full name from user that sent the invitation
 * const char *password				- Temporary password
 * char *email						- Invited user's e-mail
 * const char *nickname				- invited user's nickname
 * thcLanguageType language			- e-mail language
 * 
 * Returned Code:
 * THC_OK							- e-mail sent
 * 
 * Description:
 * This function will send and e-mail to the selected adress with all user information
 * to be able to join the system
 * 
 */
thcErrorType thcInvitationMail(const char *username,const char *invitedBy ,const char *password,
							    char *email, const char *nickname, thcLanguageType language);

/*
 * thcErrorType thcRemoveFromEmailAbeyanceList (thcUserIdentifier UID, int flag)
 * 
 * Arguments: 
 * thcUserIdentifier UID			- User ID to be removed from selected file(s)
 * int flag							- use -1 to clear only the abeyance e-mail confirmations codes file
 * 									  and 0 to clear UID from both files
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_MKSTEMP				- Error generatins temporary file
 * THC_ERROR_WRITING_FILE			- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE	- Error writing data to the file
 * THC_OK							- Function executed with no errors
 * 
 * Description:
 * It will remove user data with selected UID from 1 or both of the e-mail abeyances file,
 * depends on wich flag was sent to the function
 */
thcErrorType thcRemoveFromEmailAbeyanceList (thcUserIdentifier UID, int flag);


/*
 * thcErrorType thcSendPasswordResetEmail(thcUserDataType data,char *password,thcLanguageType language)
 * 
 * Arguments: 
 * thcUserDataType data				- User data (already includes nickname and e-mail)
 * char *password					- Temporary password
 * thcLanguageType language			- Selected language
 * 
 * Returned Code:
 * THC_OK							- e-mail sent
 * 
 * Description:
 * this function will send a temporary password to selected user's e-mail in the selected language
 * 
 */
thcErrorType thcSendPasswordResetEmail(thcUserDataType data,char *password,thcLanguageType language);


/*
 * thcErrorType thcConfirmEmailCode (thcUserIdentifier UID, char *code)
 * 
 * Arguments: 
 * thcUserIdentifier UID				- User ID
 * char *code							- Confirmation code
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE				- Error reading file
 * THC_ERROR_INVALID_CODE				- Invalid confirmation code
 * THC_ERROR_UID_NOT_FOUND				- UID not found on system
 * THC_OK								- Confirmation code is correct
 * 
 * Description:
 * This function will test if the given confirmation code matches with the 
 * confirmation code stored on the file and returns OK if correct
 * 
 */
thcErrorType thcConfirmEmailCode (thcUserIdentifier UID, char *code);


/*
 * thcErrorType thcPasswordResetLogin (thcUserIdentifier UID, char *password)
 * 
 * Arguments: 
 * thcUserIdentifier UID				- User's ID
 * char *password						- Plain password
 * 
 * Returned Code:
 * THC_CORRECT_PASSWORD					- Password is correct
 * THC_INCORRECT_PASSWORD				- Password is incorrect
 * 
 * and the same error codes from thcPasswordResetSearch
 * 
 * Description:
 * This functions will try to login a user that reseted his password using the temporary password
 * it will return the correspondent code if the password is correct or incorrect or an error occour
 */
thcErrorType thcPasswordResetLogin (thcUserIdentifier UID, char *password);


/*
 * thcErrorType thcPasswordResetSearch (thcUserIdentifier UID, char *encryptedPassword)
 * 
 * Arguments: 
 * thcUserIdentifier UID			- User's ID
 * char *encryptedPassword			- Readed encrypted password
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_UID_NOT_FOUND			- User ID not found on file
 * THC_OK							- No errors
 * 
 * Description:
 * This function will search for the selected UID on the password abeyances file and will
 * store his encrypted temporary password on char * in case of no errors
 */
thcErrorType thcPasswordResetSearch (thcUserIdentifier UID, char *encryptedPassword);


/*
 * thcErrorType thcSendConfirmationMail(const char *username,const char *password,char *email, const char *nickname, thcLanguageType language);
 *
 * Arguments:
 * char *username				- User full name
 * char *password 				- User password
 * char *email					- Destination e-mail
 * const char *nickname			- User nickname
 * thcLanguageType language		- Selected language
 * 
 * Returned Code:
 * THC_OK						- Successfull sent e-mail
 * 
 * Description:
 * This function sends an e-mail to confirm a new user's registration, it will send his temporary password and
 * username to be able to login in the system
 */
thcErrorType thcSendConfirmationMail(const char *username,const char *password,char *email, const char *nickname, thcLanguageType language);


/*
 * thcErrorType thcSendEmailAdressChangeEmail(thcUserDataType data, char *newEmail ,char *confirmationCode ,thcLanguageType language)
 * 
 * Arguments: 
 * thcUserDataType data					- User data
 * char *newEmail						- New user e-mail
 * char *confirmationCode				- Confirmation Code
 * thcLanguageType language				- Selected language
 * 
 * Returned Code:
 * THC_OK								- No errors * 
 * 
 * Description:
 * This function will send 2 e-mails, one deny e-mail to the old adress (that is included in the user data)
 * and a confirmation e-mail to the new adress, so the use can confirm or deny a e-mail change 
 */
thcErrorType thcSendEmailAdressChangeEmail(thcUserDataType data, char *newEmail ,char *confirmationCode ,thcLanguageType language);


/*
 * thcErrorType thcWebShowMenu(thcLanguageType language, thcUserDataType data)
 * 
 * Arguments: 
 * thcLanguageType language			- Selected menu language
 * thcUserDataType data				- User data
 * 
 * Returned Code:
 * THC_OK							- No errors
 * 
 * Description:
 * This function will print the menu on html, so it must be used on web interface.
 * It will check the User permissions and will print a menu with correspondent available functions
 * (like add and user to a group if he is on the admins group)
 */
thcErrorType thcWebShowMenu(thcLanguageType language, thcUserDataType data);


/*
 * thcErrorType thcWebShowHeader(void)
 * 
 * Returned Code:
 * THC_OK							- No errors
 * 
 * Description:
 * This function will print the default header in html format.
 */
thcErrorType thcWebShowHeader(void);


/*
 * thcErrorType thcWebShowFooter(void)
 * 
 * Returned Code:
 * THC_OK							- No errors
 * 
 * Description:
 * This function will print the default footer in html format.
 */
thcErrorType thcWebShowFooter(void);


/*
 * thcErrorType thcEmailChangeSearch (thcUserIdentifier UID)
 * 
 * Arguments: 
 * thcUserIdentifier UID		- User ID
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE		- Error reading the file 
 * THC_ERROR_UID_NOT_FOUND		- User ID not found	
 * THC_OK						- User found
 * 
 * Description:
 * This function will search if the selected user data is on the email abeyances file
 */
thcErrorType thcEmailChangeSearch (thcUserIdentifier UID);


/*
 * thcErrorType thcChangeEmailAdress(char *nickname, char *newEmail, thcLanguageType language)
 * 
 * Arguments: 
 * char *nickname				- User nickname
 * char *newEmail				- New user's e-mail
 * thcLanguageType language		- Selected language
 * 
 * Returned Code:
 * THC_OK						- No errors
 * 
 * and it has the same error codes from thcSearchUser, thcAddAbeyanceEmail, thcRemoveUserData,
 * thcWriteFile and thcSendEmailAdressChangeEmail
 * 
 * Description:
 * This function will begin the chage e-mail process for the user with the 'nickname' and change to
 * 'newEmail' in the selected 'language'
 */
thcErrorType thcChangeEmailAdress(char *nickname, char *newEmail, thcLanguageType language);


/*
 * thcErrorType thcReadEmailFromAbeyanceFile(thcUserIdentifier UID, thcEmailAbeyancesType *data)
 * 
 * Arguments: 
 * thcUserIdentifier UID			- User ID
 * thcEmailAbeyancesType *data		- Readed user data
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE			- Error Reading file
 * THC_ERROR_UID_NOT_FOUND			- User ID not found on the file
 * THC_OK							- No error
 * 
 * Description:
 * This function will read the user with 'UID' from email abeyances file
 * and will store it on 'data'
 */
thcErrorType thcReadEmailFromAbeyanceFile(thcUserIdentifier UID, thcEmailAbeyancesType *data);


/*
 * thcErrorType thcSearchUserByUID(thcUserIdentifier UID,thcUserDataType *data)
 * 
 * Arguments: 
 * thcUserIdentifier UID			- User ID
 * thcUserDataType *data			- Readed user data
 * 
 * Returned Code:
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_UID_NOT_FOUND			- User not found
 * THC_OK							- User found
 * 
 * Description:
 * This function will search the user by your UID. If found it will save his data on 'data'
 * else, it will return an error code
 */
thcErrorType thcSearchUserByUID(thcUserIdentifier UID,thcUserDataType *data);       

/*
 * thcErrorType thcCookieNameToNickname(const char *cookieName, char *nickname)
 * 
 * Arguments :
 * char *cookieName				- Cookie name (input)
 * char *nickname				- User nickname (output)
 * 
 * ErrorCodes :
 * THC_OK						- No errors
 * 
 * and the same return codes as thcSearchUserByUID
 * 
 * Description:
 * This function takes a cookie name and sends back the correspondent nickname
 */ 

thcErrorType thcCookieNameToNickname(const char *cookieName, char *nickname);
#endif
/*$RCSfile: thcFunctions.h,v $*/
