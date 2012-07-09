#include <string.h>
#include "network.h"

int main(int argc, char **argv)
{
  int soc;
  int portn = 80;
  char *hostnm = "www.bamboo-copter.com";
  char req[6][1024];
  int i;

  sprintf(req[0], "POST: /clip/value.php HTTP/1.1\n");
  sprintf(req[1], "Host: %s\n", hostnm);
  sprintf(req[2], "Content-Type: application/x-www-form-urlencoded\n");
  sprintf(req[3], "Content-Length: %d\n", strlen(argv[1]) + 4);
  sprintf(req[4], "\n");
  sprintf(req[5], "str=%s\n", argv[1]);
  sprintf(req[6], "\n");
  
  soc = getsock(hostnm, portn);

  for(i = 0; i < 6; i++)
    {
      printf("%s", req[i]);
      request(soc, req[i]);
    }

  sclose(soc);

}
