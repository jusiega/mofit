#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//kompilacja: gcc puason.c -lm


void gestosc(double* rho, int N, int x0, double d) //rho kwadratowe inne nie
{
    int x=0;
    int y=0;
    int sizeofrho=2*N+1;
    for (int i=0; i<sizeofrho; i++)
    {
        for (int j=0; j<sizeofrho; j++)
        {
            x=i-N;
            y=j-N;
            rho[i*sizeofrho+j]=exp(-((x-x0)*(x-x0)+y*y)/d/d)-exp(-((x+x0)*(x+x0)+y*y)/d/d);
        }
    }
}

void chill(double* rho, double* u, double* u2, int N21)
{
    for (int i=1; i<N21-1; i++)
    {
        for (int j=1; j<N21-1; j++)
        {
            u[i*N21+j]=(u[(i+1)*N21+j]+u[(i-1)*N21+j]+u[i*N21+j+1]+u[i*N21+j-1]+rho[i*N21+j])/4;
        }
    }
    /*for (int i=0; i<N21; i++)
    {
        for (int j=0; j<N21; j++)
        {
            u[i*N21+j]=u2[i*N21+j];
        }
    }*/
}

void superchill(double* rho, double* u, double* u2, double w, int N21)
{
    for (int i=1; i<N21-1; i++)
    {
        for (int j=1; j<N21-1; j++)
        {
            u[i*N21+j]=(1-w)*u[i*N21+j]+w*(u[(i+1)*N21+j]+u[(i-1)*N21+j]+u[i*N21+j+1]+u[i*N21+j-1]+rho[i*N21+j])/4;
        }
    }
    /*for (int i=0; i<N21; i++) //relaksacja globalna jeśli wyżej byłoby też u2 ale to chyba nie to zadanie o czym przekonałem się jak mi wyniki stąd uciekały do nieskończoności
    {
        for (int j=0; j<N21; j++)
        {
            u[i*N21+j]=u2[i*N21+j];
        }
    }*/
}


void initzero(double* u, int N21)
{
    for (int i=0; i<N21; i++)
    {
        for (int j=0; j<N21; j++)
        {
            u[i*N21+j]=0;
        }
    }
}


void aaa(double* rho, double* u, int N21, double* a)
{
    *a=0;
    for (int i=1; i<N21-1; i++)
    {
        for (int j=1; j<N21-1; j++)
        {
            *a-=(  (u[(i+1)*N21+j]+u[(i-1)*N21+j]-2*u[i*N21+j])*u[i*N21+j]/2  +  (u[i*N21+j+1]+u[i*N21+j-1]-2*u[i*N21+j])*u[i*N21+j]/2  +  rho[i*N21+j]*u[i*N21+j]  );
        }
    }    
}

void aaa3(double* rho, double* u, int N21, double* a, double d)
{
    *a=0;
    for (int i=1; i<N21-1; i++)
    {
        for (int j=1; j<N21-1; j++)
        {
            u[i*N21+j]+=d;
            *a-=(  (u[(i+1)*N21+j]+u[(i-1)*N21+j]-2*u[i*N21+j])*u[i*N21+j]/2  +  (u[i*N21+j+1]+u[i*N21+j-1]-2*u[i*N21+j])*u[i*N21+j]/2  +  rho[i*N21+j]*u[i*N21+j]  );
        }
    }    
}


void frhoprim(double* rhoprim, double* u, int N21)
{
    for (int i=1; i<N21-1; i++)
    {
        for (int j=1; j<N21-1; j++)
        {
            rhoprim[i*N21+j]=-(u[(i+1)*N21+j]+u[(i-1)*N21+j]+u[i*N21+j+1]+u[i*N21+j-1]-4*u[i*N21+j]);
        }
    }
}

void writetab(char* filename, double* tab, int height, int width)
{
    FILE* fil;
    fil=fopen(filename,"w");
    for(int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            fprintf(fil,"%.10f ",tab[i*width+j]);
        }
        fprintf(fil,"\n");
    }
    fclose(fil);

}

void writetabTS(char* filename, double* tab, int height, int width)
{
    FILE* fil;
    fil=fopen(filename,"w");
    
    for (int j=0; j<width; j++)
    {
        for(int i=0; i<height; i++)
        {
            fprintf(fil,"%.10f ",tab[i*width+j]);
        }
        fprintf(fil,"\n");
    }
    fclose(fil);

}

void writewszystko(char* filename, double* tab, int height, int width, int N)
{
    FILE* fil;
    fil=fopen(filename,"w");
    int x=0;
    int y=0;
    
    for (int j=0; j<width; j++)
    {
        for(int i=0; i<height; i++)
        {
            x=i-N;
            y=j-N;
            fprintf(fil,"%d %d %.10f\n",x,y,tab[i*width+j]);
        }
        //fprintf(fil,"\n");
    }
    fclose(fil);

}

void fdelta(double* delta, double* tab1, double* tab2, int size)
{
    for(int i=0; i<size; i++)
    {
        delta[i]=tab1[i]-tab2[i];
    }
}

void trzy(double* rho, double* u, int N21, double* a)
{
    double aloc=0;
    double aloc0=0;

    double d[4]={0, 0.5, 1, 0};
    double A[4]={0,0,0,0};

    int indyks=0;
    
    for (int I=1; I<N21-1; I++)
    {
        for (int J=1; J<N21-1; J++)
        {
            
            aloc=0;
            aloc0=0;
            for (int i=I-1; i<=I+1; i++)
            {
                for (int j=J-1; j<=J+1; j++)
                {
                    aloc0-=(  (u[(i+1)*N21+j]+u[(i-1)*N21+j]-2*u[i*N21+j])*u[i*N21+j]/2  +  (u[i*N21+j+1]+u[i*N21+j-1]-2*u[i*N21+j])*u[i*N21+j]/2  +  rho[i*N21+j]*u[i*N21+j]  );
                }
            }
            
            for (int n=0; n<3; n++)
            {
                aloc=0;
                u[I*N21+J]+=d[n];
                for (int i=I-1; i<=I+1; i++)
                {
                    for (int j=J-1; j<=J+1; j++)
                    {
                        aloc-=(  (u[(i+1)*N21+j]+u[(i-1)*N21+j]-2*u[i*N21+j])*u[i*N21+j]/2  +  (u[i*N21+j+1]+u[i*N21+j-1]-2*u[i*N21+j])*u[i*N21+j]/2  +  rho[i*N21+j]*u[i*N21+j]  );
                    }
                }
                u[I*N21+J]-=d[n];
                //printf("%.4f//", (*a)-aloc0+aloc);
                
                A[n]=*a-aloc0+aloc;
                //printf("%.4f ", A[n]);
            }
            
            
            aloc=0;
            d[3]=0.25*(3*A[0]-4*A[1]+A[2])/(A[0]-2*A[1]+A[2]);
            u[I*N21+J]+=d[3];
            //printf("%.5f",d[3]);
            for (int i=I-1; i<=I+1; i++)
            {
                for (int j=J-1; j<=J+1; j++)
                {
                    aloc-=(  (u[(i+1)*N21+j]+u[(i-1)*N21+j]-2*u[i*N21+j])*u[i*N21+j]/2  +  (u[i*N21+j+1]+u[i*N21+j-1]-2*u[i*N21+j])*u[i*N21+j]/2  +  rho[i*N21+j]*u[i*N21+j]  );
                }
            }
            u[I*N21+J]-=d[3];
            A[3]=*a-aloc0+aloc;

            indyks=0;
            for(int i=1; i<4; i++)
            {
                if(A[i]<=A[indyks])
                {
                    indyks=i;
                }
            }

            u[I*N21+J]+=d[indyks];
            *a=A[indyks];
        }
    }   
}

int main()
{   
    static const int N=31; //to mogło wylądować nad mainem
    static const int N21=2*N+1; //i to też
    double* u=malloc((N21)*(N21)*sizeof(double));
    double* u2=malloc((N21)*(N21)*sizeof(double));
    double* rho=malloc((N21)*(N21)*sizeof(double));
    double* rhoprim=malloc((N21)*(N21)*sizeof(double));
    double* delta=malloc((N21)*(N21)*sizeof(double));
    double a=0;
    gestosc(rho,N,4,4);
    initzero(u, N21);
    initzero(u2, N21);
    initzero(rhoprim, N21);
    int niter=500;
    double* atab=malloc(niter*sizeof(double));
    
    //1
    for(int i=0; i<niter; i++)
    {
        chill(rho,u,u2,N21);
        aaa(rho,u,N21,&a);
        atab[i]=a;
        if (i==99){
            frhoprim(rhoprim,u,N21);
            fdelta(delta,rhoprim,rho,N21*N21);
            writewszystko("output/u100.txt",u,N21,N21,N);
            writewszystko("output/rhoprim100.txt",rhoprim,N21,N21,N);
            writewszystko("output/delta100.txt",delta,N21,N21,N);
        }
    }

    frhoprim(rhoprim,u,N21);
    fdelta(delta,rhoprim,rho,N21*N21);
    writewszystko("output/u500.txt",u,N21,N21,N);
    writewszystko("output/rhoprim500.txt",rhoprim,N21,N21,N);
    writewszystko("output/delta500.txt",delta,N21,N21,N);
    writetab("output/a.txt",atab,niter,1);
    
    //2
    initzero(u, N21);
    initzero(u2, N21);
    double w=1.9;
    for(int i=0; i<niter; i++)
    {
        superchill(rho,u,u2,w,N21);
        aaa(rho,u,N21,&a);
        atab[i]=a;
    }
    writetab("output/asuperchill.txt",atab,niter,1);

    //3
    initzero(u, N21);
    initzero(u2, N21);
    a=0;
    for(int i=0; i<niter; i++)
    {
        trzy(rho,u,N21,&a);
        //aaa(rho,u,N21,&a);
        atab[i]=a;
    }
    writetab("output/a3.txt",atab,niter,1);
    writewszystko("output/u3.txt",u,N21,N21,N);

    free(u);
    free(u2);
    free(rho);
    free(rhoprim);
    free(atab);
    free(delta);
    return 0;
}