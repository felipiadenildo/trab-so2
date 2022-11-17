

#ifndef MBR_H
#define MBR_H

void __attribute((naked, fastcall)) print (const char *buffer);
extern char nl[];
#define printnl(str) do{print(str); print (nl);}while(0)
void __attribute__((naked, fastcall)) clear (void);
void __attribute__((naked, fastcall)) read (char *buffer);
#define BUFFER_MAX_LENGTH 5
int __attribute__((fastcall, naked)) compare (char *s1, char *s2);

// Commandos 
#define HELP_CMD "help"
#define QUIT_CMD "quit"
#define DATE_CMD "date"
void __attribute__((naked)) date (void);
#define NOT_FOUND "not found"
#endif	
