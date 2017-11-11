#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myAtoi(const char* pstr)
{
    // char* tmp = new char[strlen(pstr)];
    // char* tmp = const_cast<char*>(pstr);
    char* tmp = (char*)malloc(sizeof(char) * strlen(pstr));
    strcpy(tmp, pstr);
    int ans = 0;

    while(*tmp == ' ')  tmp ++; // wipe out spacings
    bool negative = false;
    if (*tmp == '-')            // positive? negative?
    {
        negative = true;
        tmp ++;
    }

    while(*tmp != '\0' && *tmp >= '0' && *tmp <= '9')
    {
        ans = ans * 10 + ((*tmp) - '0');
        tmp ++;
    }
    if(negative)    return ans * (-1);
    else            return ans;
}

int my_atoi(const char *str)
{
    int value = 0;
    int flag = 1; //判断符号

    while (*str == ' ')  //跳过字符串前面的空格
    {
        str++;
    }

    if (*str == '-')  //第一个字符若是‘-’，说明可能是负数
    {
        flag = 0;
        str++;
    }
    else if (*str == '+') //第一个字符若是‘+’，说明可能是正数
    {
        flag = 1;
        str++;
    }//第一个字符若不是‘+’‘-’也不是数字字符，直接返回0
    else if (*str >= '9' || *str <= '0') 
    {
        return 0;    
    }

    //当遇到非数字字符或遇到‘/0’时，结束转化
    while (*str != '\0' && *str <= '9' && *str >= '0')
    {
        value = value * 10 + *str - '0'; //将数字字符转为对应的整形数
        str++;
    }

    if (flag == 0) //负数的情况
    {
        value = -value;
    }

    return value;
}

int main(int argc, char const *argv[])
{
	// char sp[] = "1,2,3,4,5,6,7";
	// int n;
	// n = strlen(sp);
	// for (int i = 0; i < n; i = i + 2)
	// {
	// 	/* code */
	// 	printf("%c\n",  sp[i]);
	// 	char c = sp[i];
	// 	printf("%c\n", c);
	// 	int n = atoi(&c);
	// 	printf("%d\n", n);
	// }

    
	char time[] = "2017-10-14 05:42:00";
	int y,m,d,h,mm,s;
	char year[8] = { 0 },month[4] = {0},day[4] = { 0 },hour[4] = { 0 }, min[4] = { 0 }, se[4] = { 0 };

	printf("%lu\n", strlen(time));
	
	strncpy(year, time, 4);
	strncpy(month, time+5, 2);
    strncpy(day, time+8, 2);
    strncpy(hour, time+11, 2);
    strncpy(min, time+14, 2);
    strncpy(se, time+17, 2);
    printf("%s\n", year);
    printf("%s\n", month);
    printf("%s\n", day);
    printf("%s\n", hour);
    printf("%s\n", min);
    printf("%s\n", se);

    printf("%d\n", myAtoi(hour));
	// sscanf(time,"%4d-%2d-%2d %2d:%2d:%2d",&y,&m,&d,&h,&mm,&s);
	// printf("%d\n", y);
	// printf("%d\n", m);
	// printf("%d\n", d);
	// printf("%d\n", h);
	// printf("%d\n", mm);
	// int s = my_atoi("5223");
	// printf("%d\n", s);
	return 0;
}