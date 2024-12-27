#include <stdio.h>
void sayac()
{
    int a =0;
    printf("%i",a);
    a++;
}
void deneme()
{
    static int b=0;
    printf("%i", b);
    b++;
}

int main()
{
    sayac();
    sayac();
    deneme();
    deneme();

}