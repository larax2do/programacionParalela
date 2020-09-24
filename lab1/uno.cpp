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
void prueba(int **A, int *x, int *y, int n, int opc)
{

	
	switch(opc)
	{
		case 0:
		for(int i =0; i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				y[i]+=A[i][j]*x[j];
				//std::cout<<"Acceso a A["<<i<<"]["<<j<<"]"<<std::endl;
			}
		}
		break;

		case 1:
		for(int j=0;j<n;j++)
		{
			for(int i=0;i<n;i++)
			{
				y[i]+=A[i][j]*x[j];
				//std::cout<<"Acceso a A["<<i<<"]["<<j<<"]"<<std::endl;
			}
		}
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
		//std::cout<<n<<" ";
		for(int algo=1;algo<2;algo++)
		{
			int **A=new int*[n];
			std::ifstream entrada("entrada.txt",std::ifstream::in);
			for(int i=0;i<n;i++)
			{
				A[i]=new int[n];
				for(int j=0;j<n;j++)
				{
					entrada>>A[i][j];
				}
			}
			int *x=new int[n]{};
			for(int i=0;i<n;i++)
			{
				entrada>>x[i];
			}
			int *y=new int[n]{};
			for(int i=0;i<n;i++)
			{
				y[i]=0;
			}


			t0=clock();

			prueba(A,x,y,n,algo);

			t1=clock();//FIn de cronometro
	        time = (double(t1-t0)/CLOCKS_PER_SEC);
	        std::cout <<time<<" ";
		
			delete [] x;
			delete [] y;
			for(int i=0;i<n;i++)
			{
				
				delete [] A[i];
			}
			delete [] A;	
			entrada.close();
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
		
		

	}




	return 0;
}

