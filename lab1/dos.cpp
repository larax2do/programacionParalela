#include <iostream>
#include <time.h>
#include <fstream>


void mostrar(int **A, int n)
{
	for (int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
		{
			std::cout<<A[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}
void mostrar(int *A,int n)
{
	for(int j=0;j<n;++j)
	{
		std::cout<<A[j]<<" ";
	}
	std::cout<<std::endl;
}
void prueba(int **A, int **B, int **R, int n, int opc)
{

	
	switch(opc)
	{
		case 0:
			for(int i=0; i<n; ++i)
			{
		        for(int j=0; j<n; ++j)
		        {
		            for(int z=0; z<n; ++z)
		            {
		                R[i][j] += A[i][z] * B[z][j];
		            }
		        }
			}
		break;

		case 1:
		    int bi=0;
		    int bj=0;
		    int bk=0;
		    int i=0;
		    int j=0;
		    int k=0;
		    int blockSize=n/2; 
		    
		    for(bi=0; bi<n; bi+=blockSize)
		        for(bj=0; bj<n; bj+=blockSize)
		            for(bk=0; bk<n; bk+=blockSize)
		                for(i=0; i<blockSize; i++)
		                    for(j=0; j<blockSize; j++)
		                        for(k=0; k<blockSize; k++)
		                            R[bi+i][bj+j] += A[bi+i][bk+k]*B[bk+k][bj+j];
				break;
	}
}


int main()
{
	int limite = 1001;
	int salto=1000;
	double t0,t1,time;

	for (int n=salto;n<limite;n=n+salto)
	{
		std::cout<<n<<" ";
		for(int algo=0;algo<1;algo++)
		{
			int **A=new int*[n];
			int **B=new int*[n];
			int **R=new int*[n];
			std::ifstream entrada("entrada.txt",std::ifstream::in);
			for(int i=0;i<n;i++)
			{
				A[i]=new int[n];
				B[i]=new int[n];
				R[i]=new int[n];
				for(int j=0;j<n;j++)
				{
					entrada>>A[i][j];
					entrada>>B[i][j];
				
				}
			}


			t0=clock();

			prueba(A,B,R,n,algo);

			t1=clock();//FIn de cronometro
	        time = (double(t1-t0)/CLOCKS_PER_SEC);
	        std::cout <<time<<" ";

			for(int i=0;i<n;i++)
			{
				
				delete [] A[i];
			}
			delete [] A;	
			entrada.close();
		}
		std::cout<<std::endl;
		
		

	}




	return 0;
}

