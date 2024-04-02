#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH  1000
int main()
{
    FILE *f_iesire, *f_intrare;
    f_intrare = fopen("date/t1/d.in", "rt");
    if( f_intrare == NULL )
    {
        printf("Nu s-a putut deschide fisierul");
        return 1;
    }
    char buff[MAX_LENGTH];
    while(!feof(f_intrare))
    {
        fgets(buff, sizeof(buff), f_intrare);
    }
    fclose(f_intrare);

    //deschidem fisierul r.out
    f_iesire = fopen("out/r.out","wt");
    if( f_iesire == NULL )
    {
        printf("Nu s-a putut deschide fisierul");
        return 1;
    }
    fclose(f_iesire);
    return 0;
}