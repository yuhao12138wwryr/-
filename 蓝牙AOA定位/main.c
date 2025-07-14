#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#include "rt_nonfinite.h"
#include "testangle.h"
#include "main.h"
#include "testangle_terminate.h"
#include "testangle_initialize.h"


#define MAX_BUFFER_SIZE 1024
#define MAX_SIZE 100000
int main(int argc, const char * const argv[])
{ int yh;
int i5,i6,i7,i8;
  (void)argc;
  (void)argv;
    testangle_initialize();
  double dv2[91]={0,-8,-6,4,5,-2,-3,1,2,-4,-7,4,8,-4,-6,6,2,-2,-4,-5,-4,-9,-2,-13,2,-6,-2,-9,-2,-8,3,-9,3,-10,1,-8,3,-12,2,-6,6,-10,6,-8,1,-5,3,-9,6,-4,3,-6,5,-10,10,-4,8,-2,9,-1,12,-2,10,0,7,2,6,-2,3,1,10,4,5,2,2,2,7,5,9,5,6,5,4,9,7,11,2,2,2,5,7};
  double dv3[91]={0,2,-15,-3,22,1,-21,-4,17,-2,-18,1,20,-1,-18,6,19,-6,-19,-6,-16,-17,-15,-18,-14,-15,-14,-15,-11,-14,-14,-19,-9,-17,-7,-17,-8,-20,3,-15,2,-23,0,-18,5,-18,5,-19,6,-16,11,-13,9,-12,15,-11,16,-13,14,-3,16,-10,14,-4,19,1,16,-3,17,2,12,3,13,4,16,6,16,9,17,13,14,8,10,15,9,14,11,12,9,15,6};
  double anss[3];
    testangle(dv2, dv3, 0,0,0.65,1,0,0.65, anss);
    printf("%f",anss[0]);
//串口接收用 	
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    char buffer[MAX_BUFFER_SIZE];
    int bytesRead,i;
    BOOL endOfLine = FALSE;
    int mowei1,mowei2;
    
    HANDLE hSerial3;
    DCB dcbSerialParams3 = {0};
    COMMTIMEOUTS timeouts3 = {0};
    char buffer3[MAX_BUFFER_SIZE];
    int bytesRead3,i3;
    BOOL endOfLine3 = FALSE;
    int mowei3;
//串口接受用 

//文件读取用 
  char *p ;	
    FILE *fp;
    FILE *file4;
        FILE *file5;
            FILE *file6;
    char buffer1[MAX_SIZE];
    float b1[MAX_SIZE];
    int i1 = 0, j1 = 0;
static    int isFirstXFound = 0, isSecondXFound = 0;
    
       char *p2 ;	
    FILE *fp2;
    char buffer2[MAX_SIZE];
    float b2[MAX_SIZE];
    int i2 = 0, j2 = 0;
    int isFirstXFound2 = 0, isSecondXFound2 = 0;
//文件用 
    fp = fopen("a.txt", "w"); 
    fclose(fp);     
	fp2 = fopen("b.txt", "w"); 
    fclose(fp2);  

    // 打开串口1
    hSerial = CreateFile("\\\\.\\COM3", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening serial port");
        return 1;
    }

    // 配置串口参数1
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        fprintf(stderr, "Error getting serial port state");
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        fprintf(stderr, "Error setting serial port state");
        CloseHandle(hSerial);
        return 1;
    }

    // 配置串口读取超时时间1
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 0;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    if (!SetCommTimeouts(hSerial, &timeouts))
    {
        fprintf(stderr, "Error setting timeouts");
        CloseHandle(hSerial);
        return 1;
    }
    
 // 打开串口2
    hSerial3 = CreateFile("\\\\.\\COM47", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial3 == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening serial port");
        return 1;
    }

    // 配置串口参数2
    dcbSerialParams3.DCBlength = sizeof(dcbSerialParams3);
    if (!GetCommState(hSerial, &dcbSerialParams3))
    {
        fprintf(stderr, "Error getting serial port state");
        CloseHandle(hSerial3);
        return 1;
    }
    dcbSerialParams3.BaudRate = CBR_115200;
    dcbSerialParams3.ByteSize = 8;
    dcbSerialParams3.StopBits = ONESTOPBIT;
    dcbSerialParams3.Parity = NOPARITY;
    if (!SetCommState(hSerial3, &dcbSerialParams3))
    {
        fprintf(stderr, "Error setting serial port state");
        CloseHandle(hSerial3);
        return 1;
    }

    // 配置串口读取超时时间2
    timeouts3.ReadIntervalTimeout = MAXDWORD;
    timeouts3.ReadTotalTimeoutConstant = 0;
    timeouts3.ReadTotalTimeoutMultiplier = 0;
    timeouts3.WriteTotalTimeoutConstant = 0;
    timeouts3.WriteTotalTimeoutMultiplier = 0;
    if (!SetCommTimeouts(hSerial3, &timeouts3))
    {
        fprintf(stderr, "Error setting timeouts");
        CloseHandle(hSerial3);
        return 1;
    }    

    // 创建文件并准备写入1
    FILE *file = fopen("a.txt", "a");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file");
        CloseHandle(hSerial);
        return 1;
    }
    fclose(file);
        // 创建文件并准备写入2
    FILE *file3 = fopen("b.txt", "a");
    if (file3 == NULL)
    {
        fprintf(stderr, "Error opening file");
        CloseHandle(hSerial3);
        return 1;
    }
    fclose(file3);
    while (1)
    {
        // 读取串口数据1
        if (!ReadFile(hSerial, buffer, MAX_BUFFER_SIZE, &bytesRead, NULL))
        {
            fprintf(stderr, "Error reading from serial port");
            fclose(file);
            CloseHandle(hSerial);
            return 1;
        }
         // 读取串口数据1
        file = fopen("a.txt", "a");
        // 将接收到的数据写入文本文件1
        for ( i = 0; i < bytesRead; i++)
        {
            if (buffer[i] == '\n')
            {
                endOfLine = TRUE;
                break;
            }
            fprintf(file, "%c", buffer[i]);
        }
        for(i=0;i<1022;i++)
{buffer[i]=0;
}
        if (endOfLine)
        {
            fprintf(file, "\n");
            fflush(file);
            endOfLine = FALSE;
        }
      fclose(file);          
        // 将接收到的数据写入文本文件1
 
 
         // 读取串口数据2
        if (!ReadFile(hSerial3, buffer3, MAX_BUFFER_SIZE, &bytesRead3, NULL))
        {
            fprintf(stderr, "Error reading from serial port");
            fclose(file3);
            CloseHandle(hSerial3);
            return 1;
        }
         // 读取串口数据2
        file3 = fopen("b.txt", "a");
        // 将接收到的数据写入文本文件2
        for ( i3 = 0; i3 < bytesRead3; i3++)
        {
            if (buffer3[i3] == '\n')
            {
                endOfLine3 = TRUE;
                break;
            }
            fprintf(file3, "%c", buffer3[i3]);
        }
        for(i3=0;i3<1022;i3++)
{buffer3[i]=0;
}
        if (endOfLine3)
        {
            fprintf(file3, "\n");
            fflush(file3);
            endOfLine3 = FALSE;
        }
      fclose(file3);          
        // 将接收到的数据写入文本文件2
 
    // 读取文件中数据存入b
    fp = fopen("a.txt", "r"); 
    while (fgets(buffer1, MAX_SIZE, fp) != NULL) {
         p = buffer1;
        while (*p != '\0') {
            if (*p == 'X') {
                if (isFirstXFound == 0) {
                    isFirstXFound = 1;
                } else {
                    isSecondXFound = 1;
                    break;
                }
            }

            if (isFirstXFound == 1 && isSecondXFound == 0 && (*p >= '0' && *p <= '9' || *p == '.'|| *p == '-')) {
                b1[j1++] = strtod(p, &p);
            } else {
                p++;
                mowei1++;
             if(mowei1>500)
			 {   fclose(fp); 
			fp = fopen("a.txt", "w");
			mowei1=0;
			 break;
				}   
            }
        }

        if (isSecondXFound == 1) {
            break;
        }
    }
    //printf("%d,",mowei1);
fclose(fp); 

    // 读取文件中数据存入b
    
    
    
    
    
     // 读取文件中数据存入b2222222222222222222222222
    fp2 = fopen("b.txt", "r"); 
    while (fgets(buffer2, MAX_SIZE, fp2) != NULL) {
         p2 = buffer2;
        while (*p2 != '\0') {
            if (*p2 == 'X') {
                if (isFirstXFound2 == 0) {
                    isFirstXFound2 = 1;
                } else {
                    isSecondXFound2 = 1;
                    break;
                }
            }

            if (isFirstXFound2 == 1 && isSecondXFound2 == 0 && (*p2 >= '0' && *p2 <= '9' || *p2 == '.'|| *p2 == '-')) {
                b2[j2++] = strtod(p2, &p2);
            } else {
                p2++;
                mowei2++;
             if(mowei2>500)
			 {   fclose(fp2); 
			fp = fopen("b.txt", "w");
			mowei2=0;
			 break;
				}   
            }
        }

        if (isSecondXFound == 1) {
            break;
        }
    }
    //printf("%d,",mowei1);
fclose(fp); 

    // 读取文件中数据存入b2   
    
    
    // 输出数组b中的数据 
   // printf("%d,",isSecondXFound);
    if(isSecondXFound)
   {printf("channel:%d\n",j1);
	 for (i1 = 0; i1 < j1; i1++) {
 //      printf("%.2f ", b1[i1]);
    }      

    fp = fopen("a.txt", "w"); 
      fclose(fp);    
}

    // 输出数组b2222222222222222222中的数据 
   // printf("%d,",isSecondXFound);
    if(isSecondXFound2)
   {printf("channe2:%d\n",j2);
     
if(j2==91&&j1==91)
{    
  for (i2 = 0; i2 < j2; i2++) {
 //      printf("%.2f ", b2[i2]);
 dv3[i2]=b2[i2];
    } 
  for (i1 = 0; i1 < j1; i1++) {
 //      printf("%.2f ", b1[i1]);
 dv2[i1]=b1[i1];
    } 
testangle(dv2, dv3, 0,0,0.65,1,0,0.65, anss);
printf("%.2f,%.2f,%.2f\n ", anss[0],anss[1],anss[2]);
        file4 = fopen("x_y_z.txt", "a");
     fprintf(file4, "%.2f,%.2f,%.2f\n", anss[0],anss[1],anss[2]);
           fclose(file4);  

file5 = fopen("iq_ag_x_y_z.txt", "a");
for(i5=1;i5<=90;i5++)
{ fprintf(file5, "%.2f,", dv2[i5]);
}
fprintf(file5, "\n");
for(i5=1;i5<=90;i5++)
{ fprintf(file5, "%.2f,", dv3[i5]);
}
fprintf(file5, "\n");
fprintf(file5, "%.2f,%.2f,%.2f,%.2f", anss[3],anss[4],anss[5],anss[6]);
fprintf(file5, "\n");
fprintf(file5, "%.2f,%.2f,%.2f,%.2f\n", anss[0],anss[1],anss[2],anss[3]);
fclose(file5);  

j2=0;j1=0;
}
    fp2 = fopen("b.txt", "w"); 
      fclose(fp2);    
}



    i1 = 0;
    j1 = 0;
    isFirstXFound = 0;
    mowei1=0;
	isSecondXFound = 0;     
	    i2 = 0;
    j2 = 0;
    isFirstXFound2 = 0;
    mowei2=0;
	isSecondXFound2 = 0;    
    // 输出数组b的数据      
    }

    //  
    fclose(file);
    CloseHandle(hSerial);
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////


