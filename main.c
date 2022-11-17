



#include <mbr.h>

int main()
{
  int count = 0;
  char cmd[BUFFER_MAX_LENGTH];

  clear();
  
  while (1)
    {
      read (cmd);
      
      if (compare(cmd, HELP_CMD))
	      printnl ("try more");
      else if (compare(cmd, QUIT_CMD))
	      printnl ("impossible");
      else if (compare(cmd, DATE_CMD))
        date();
      else
	      printnl (NOT_FOUND);
      count += 1;
      if(count == 12){
        clear();
        count = 0;
      }
    }
  
  return 0;

}
