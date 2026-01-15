#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char p[100];
    int u=0,l=0,d=0,s=0,score=0;
    scanf("%99s", p);

    int n = strlen(p);
    if(n >= 8) score++;
    if(n >= 12) score++;

    for(int i=0;i<n;i++){
        if(isupper(p[i])) u=1;
        else if(islower(p[i])) l=1;
        else if(isdigit(p[i])) d=1;
        else s=1;
        if(i>1 && p[i]==p[i-1] && p[i]==p[i-2]) score--; // aaa
    }

    score += u + l + d + s;

    if(score >= 5) printf("Strong\n");
    else if(score >= 3) printf("Medium\n");
    else printf("Weak\n");
}
