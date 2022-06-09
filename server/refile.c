/*
 * @Description: 
 * @Version: 1.0
 * @Autor: Yzc258
 * @Date: 2022-06-08 20:10:19
 */
#include<stdio.h>
//int a;
//char b,c[100];
int main(){
    FILE *fp;
	if ((fp = fopen("msg.txt", "rb")) == NULL)
	{
		exit(0);
	}
	fseek(fp, 0, SEEK_END);
	int fileLen = ftell(fp);
	char *tmp = (char *) malloc(sizeof(char) * fileLen);
	fseek(fp, 0, SEEK_SET);
	fread(tmp, fileLen, sizeof(char), fp);
	fclose(fp);
	for(int i = 0; i < fileLen; ++i)
	{
		printf("%c", tmp[i]);
	}
	printf("\n");
 
	if ((fp = fopen("example.txt", "wb")) == NULL)
	{
        printf("error");
		exit(0);
	}
	rewind(fp);
	fwrite(tmp, fileLen, sizeof(char), fp);
	fclose(fp);
	free(tmp);

    return 0;
}