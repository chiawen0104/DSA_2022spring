//
//  main.c
//  hw3-4
//
//  Created by 盧家雯 on 2022/5/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strrev(char* s){
    char *s2;
    unsigned long len = strlen(s);
    s2 = (char*)malloc(sizeof(char)*(len+1));
    strcpy(s2, s);

    for (int i=0; i<=(len/2)-1; i++) {
        char tmp = s2[i];
        s2[i] = s2[len-i-1];
        s2[len-i-1] = tmp;
    }
    return s2;
}

unsigned long computeLPS (char* str){
    unsigned long m = strlen(str);
    unsigned long *lps;
    lps = (unsigned long*)calloc(m, sizeof(unsigned long));
 
    unsigned long len = 0;
 
    // the loop calculates lps[i] for i = 1 to m-1
    unsigned long i = 1;
    while (i < m)
    {
        if (str[i] == str[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (str[i] != str[len])
        {
            if (len != 0)
            {
                len = lps[len-1];
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    unsigned long ans = lps[m-1];
    free(lps);
    return ans;
}

unsigned long Add_Front(char* s, char* rs)
{
    char *s2;
    s2 = (char*)malloc(sizeof(char)*(2*strlen(s)+3));
    
    strcpy(s2, s);
    strcat(s2, "$");
    strcat(s2, rs);
 
    unsigned long lastLPS = computeLPS(s2);
    free(s2);
    return (lastLPS);
}

unsigned long Add_Back(char* s, char* rs)
{
    char *s2;
    s2 = (char*)malloc(sizeof(char)*(2*strlen(s)+3));
    
    strcpy(s2, rs);
    strcat(s2, "$");
    strcat(s2, s);
 
    unsigned long lastLPS = computeLPS(s2);
    free(s2);
    return (lastLPS);
}

int main() {
    char *str;
    str = (char*)malloc(sizeof(char)*(10000001));
    scanf("%s",str);
    unsigned long len = strlen(str);
    
    //reverse string
    char *rstr = strrev(str);
    
    if (strcmp(str, rstr) == 0) {
        printf("0\n%s",rstr);
        free(str);
        free(rstr);
        return 0;
    }
    unsigned long front = len-Add_Front(str, rstr);//number of char added in front
    unsigned long back = len-Add_Back(str, rstr);//number of char added in back
    
    if (front < back) {
        printf("%lu\n", front);
        
        for (unsigned long i=0; i<front ; i++) {
            printf("%c", rstr[i]);
        }
        printf("%s\n", str);
    }
    else if (back < front){
        printf("%lu\n", back);
        
        printf("%s", str);
        for (unsigned long i=back-1; i>=0; i--) {
            printf("%c", str[i]);
            if (i == 0) {
                break;
            }
        }
        printf("\n");
    }
    else { // front == back
        printf("%lu\n", front);
        
        for (unsigned long i=0; i<front ; i++) {
            printf("%c", rstr[i]);
        }
        printf("%s\n", str);
        
        printf("%s", str);
        for (unsigned long i=back-1; i>=0; i--) {
            printf("%c", str[i]);
            if (i == 0) {
                break;
            }
        }
        printf("\n");
    }
    free(str);
    free(rstr);
    return 0;
}
