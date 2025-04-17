#include <stdio.h>

int	main(int argc, char **argv)
{
  char	*encrypt;
  int	i;

  if (argc != 2)
  {
	printf("Usage: %s <token>\n", argv[0]);
	return (1);
  }
  encrypt = argv[1];
  i = 0;
  while(encrypt[i])
  {
	encrypt[i] = encrypt[i] - i;
	i++;
  }
  printf("Decrypted string: %s\n", encrypt);
  return (0);
}
