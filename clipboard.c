#include <ctype.h>
#include <string.h>
#include "network.h"

char *urlencode(char *c)
{
  int i;
  char tmp[strlen(c) * 3 + 1];

  memset(tmp, 0, sizeof(tmp));

  for(i = 0; i < strlen(c); i++)
    {
      if(isalnum(c[i]) == 0 &&
	 c[i] != '_' &&
	 c[i] != '-' &&
	 c[i] != '.' &&
	 c[i] != '*')
	{
	  char tmp1[4];
	  sprintf(tmp1, "%%%x", c[i]);
	  strcat(tmp, tmp1);
	}

      else
	{
	  tmp[i] = c[i];
	}
    }

  return &tmp;
}

int main(int argc, char **argv)
{
  int soc;
  int portn = 80;
  char *hostnm = "www.bamboo-copter.com";

  char phost[1024];
  char pdata[1024];
  char pleng[1024];

  sprintf(phost, "Host: %s\r\n", hostnm);
  sprintf(pdata, "value=%s\r\n", urlencode(argv[1]));
  sprintf(pleng, "Content-Length: %d\r\n", (int)strlen(pdata));

  soc = getsock(hostnm, portn);

  request(soc, "POST /clip/value.php HTTP/1.1\r\n");
  request(soc, phost);
  request(soc, "Content-Type: application/x-www-form-urlencoded\r\n");
  request(soc, pleng);
  request(soc, "\r\n");
  request(soc, pdata);

  sclose(soc);

  return 0;
}
