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
 * $Log: thcRunNcursesInterface.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef 	THC_RUN_NCURSES_INTERFACE_H                                       
 #define    THC_RUN_NCURSES_INTERFACE_H    		"@(#)thcRunNcursesInterface.h $Revision: 1.2 $"                                  

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
                                             

/*
 * thcErrorType thcRunNcursesInterface (char*, thcLanguageType)
 * 
 * Arguments : 
 * char *					- User nickname
 * thcLanguageType			- Interface's language
 * 
 * Return Code : 
 * THC_OK					- Exited with no errors
 * 
 * Description :
 * Runs NCurses interface of the system, if the field char* is empty, it will ask
 * fot an username, and it will allways ask for password and display menu for the logged user
 */ 
thcErrorType thcRunNcursesInterface (char*, thcLanguageType);  

/*
 * thcErrorType thcCursesChangeEmail(thcUserDataType * , thcLanguageType)
 * 
 * Arguments : 
 * 
 */  
thcErrorType thcCursesChangeEmail(thcUserDataType * , thcLanguageType);

/*
 * 
 * 
 */ 
thcErrorType thcCursesInvite(thcUserDataType , thcLanguageType);

/*
 * 
 * 
 */ 
thcErrorType thcCursesChangePassword(thcUserDataType *data, thcLanguageType);

/*
 * 
 * 
 */ 
thcErrorType thcCursesChangeUsername(thcUserDataType data, thcLanguageType);

/*
 * 
 * 
 */ 
thcErrorType thcCursesChangeGroup (char operation, thcLanguageType language);

/*
 * 
 * 
 */ 
thcErrorType thcCursesRemoveUser (thcUserDataType data, thcLanguageType language);

/*Menu Functions*/
enum
{
	THC_CURSES_INVITE				= 1,
	THC_CURSES_CHANGE_EMAIL			= 2,
	THC_CURSES_CHANGE_USERNAME		= 3,
	THC_CURSES_SHOW_HELP			= 4,
	THC_CURSES_PASSWORD				= 5,
	THC_CURSES_REMOVE				= 6,
	THC_CURSES_CHANGE_GROUP			= 7,
	THC_CURSES_ADD_GROUP			= 8
};
                                          
 #endif     
                                   
/*$RCSfile: thcRunNcursesInterface.h,v $*/									
