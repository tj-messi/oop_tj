/*2351114 朱俊泽 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//返回类型definite_integration(形参表)
double definite_integration(double (*func)(double), double low, double high, int n)
{  
	//通用函数的实现部分(不允许任何选择形式[if/switch/条件表达式]语句出现)
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
      //输入上下限及划分数量(不考虑输入错误)
	  
	  printf("请输入sinxdx的下限、上限及区间划分数量\n");
	  scanf("%lf %lf %d",&low,&high,&n);
	  
      value =definite_integration(sin,low, high, n);
	  //sin为math.h中已有函数printf sinxdx的值
		
	  printf("sinxdx[%g~%g/n=%d] : %g\n",low,high,n,value);	
		
      //输入上下限及划分数量(不考虑输入错误)
	  printf("请输入cosxdx的下限、上限及区间划分数量\n");
	  scanf("%lf %lf %d",&low,&high,&n);	
		
      value =definite_integration(cos,low, high, n);
	  //cos为math.h中已有函数printf cosxdx的值
		
	  printf("cosxdx[%g~%g/n=%d] : %g\n",low,high,n,value);	
      //输入上下限及划分数量(不考虑输入错误)
	
	  printf("请输入e^xdx的下限、上限及区间划分数量\n");
	  scanf("%lf %lf %d",&low,&high,&n);	

      value =definite_integration(exp,low, high, n);
	  //exp为math.中已有函数printf e*dx的值
		
	  printf("e^xdx[%g~%g/n=%d] : %g\n",low,high,n,value);		
      return 0;
}
