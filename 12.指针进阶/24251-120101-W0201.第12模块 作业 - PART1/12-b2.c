/*2351114 �쿡�� ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//��������definite_integration(�βα�)
double definite_integration(double (*func)(double), double low, double high, int n)
{  
	//ͨ�ú�����ʵ�ֲ���(�������κ�ѡ����ʽ[if/switch/�������ʽ]������)
    double dx = (high - low) / n;  
    double sum = 0; 
    for (int i = 1; i <= n; ++i) {  
        double x = low + i * dx;  
        sum += func(x);  
    }
    return sum*dx;  
}  
  

int main()
{
      int n;
      double low,high,value;
      //���������޼���������(�������������)
	  
	  printf("������sinxdx�����ޡ����޼����仮������\n");
	  scanf("%lf %lf %d",&low,&high,&n);
	  
      value =definite_integration(sin,low, high, n);
	  //sinΪmath.h�����к���printf sinxdx��ֵ
		
	  printf("sinxdx[%g~%g/n=%d] : %g\n",low,high,n,value);	
		
      //���������޼���������(�������������)
	  printf("������cosxdx�����ޡ����޼����仮������\n");
	  scanf("%lf %lf %d",&low,&high,&n);	
		
      value =definite_integration(cos,low, high, n);
	  //cosΪmath.h�����к���printf cosxdx��ֵ
		
	  printf("cosxdx[%g~%g/n=%d] : %g\n",low,high,n,value);	
      //���������޼���������(�������������)
	
	  printf("������e^xdx�����ޡ����޼����仮������\n");
	  scanf("%lf %lf %d",&low,&high,&n);	

      value =definite_integration(exp,low, high, n);
	  //expΪmath.�����к���printf e*dx��ֵ
		
	  printf("e^xdx[%g~%g/n=%d] : %g\n",low,high,n,value);		
      return 0;
}
