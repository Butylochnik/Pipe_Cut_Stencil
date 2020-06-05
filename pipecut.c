#include <stdio.h>
#include <math.h>
#include <string.h>

char nl[]={"\n"};
char defnl[]={" (default)\n"};

int main(int argc, char *argv[])
{
    int i, n = 8;
    char *pname, *adef = defnl, *bdef = defnl, *ddef = defnl;
    float d = 100.0, av = 45.0, b = 10.0, par;
    float lmax, x, arel, r, tangav, l, h;

    if(argc < 2)
    {
        pname = strrchr(argv[0], '/') + 1;
        printf("Calculation of stencil parameters for angle pipe cutting.\n");
        printf("Usage:\n");
        printf(" %s [-d=diameter] [-a=angle] [-b=belt] [-n=points]\n\n", pname);
        printf("Now default values are used.\n");
    }

    printf("\n");

    for(i = 1; i < argc; i++)
    {
        if((argv[i][0] != '-') || (argv[i][2] != '='))
        {
            printf("%s invalid parameter\n\n", argv[i]);
            continue;
        }

        if(sscanf(&argv[i][3], "%f", &par) == 0)
        {
            printf("%s invalid parameter\n\n", argv[i]);
            continue;
        }

        switch(argv[i][1])
        {
            case 'a':
                if(par >= 90.0)
                {
                    printf("%s invalid parameter\n\n", argv[i]);
                    break;
                }
                av = par;
                adef = nl;
                break;
            case 'b':
                b = par;
                bdef = nl;
                break;
            case 'd':
                d = par;
                ddef = nl;
                break;
            case 'n':
                n = (int)par;
                break;
            default:
                printf("%s invalid parameter\n\n", argv[i]);
        }

    }

    lmax = M_PI * d;
    r = d/2.0;
    tangav = tan(M_PI * av / 180.0);

    printf(" Stencil calculation for:\n");
    printf(" Dpipe = %.1f%s", d, ddef);
    printf(" Angle = %.1f deg%s", av, adef);
    printf(" Belt  = %.1f%s\n", b, bdef);
    printf(" Lcirc = %.1f\n\n", lmax);
    printf(" length  hight\n");

    for(i = 0; i <= n; i++)
    {
        arel = (float)(i)/(float)(n);
        l = lmax * arel;
        x = r * (1 - cos(2 * M_PI * arel));
        h = x * tangav + b;
        printf(" %6.1f %6.1f\n", l, h);
    }

    return 0;
}
