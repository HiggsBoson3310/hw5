#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*Definimos un número de iteraciones para la aplicacion de Monte Carlo*/
int N=50000;

double likelihood(double *y_obs, double *y_model, int n);
/*Definimos Una funcion de la norma de vectores en R2*/
double norm(double x, double y);
/*Una función que obtinene el máximo de una lista (puede dar su posicion o el valor)*/
double amax(double * list, int size, int loc);
/*Una función que obtinene el mínimo de una lista (puede dar su posicion o el valor)*/
double amin(double * list, int size, int loc);
/*Definimos Una función que genera números aleatorios uniformemente distribuidos en el intervalo min-max*/
double rand_lim(double min, double max);
/*Definimos una función que obtiene el radio máximo dado un centro y las posiciones de las moleculas*/
double radius(double *x, double *y, double c_x, double c_y, double atom_r);
/*Definimos una función que determina si reemplazamos o no un punto en la caminata*/
int replace(double previuos, double next);
int main(){
  /*Creamos y leemos los archivos necesarios*/
  FILE *canal1, *canal2, *resul1, *resul2;
  canal1 = fopen("Canal_ionico.txt","r");
  canal2 = fopen("Canal_ionico1.txt","r");
  resul1 = fopen("Resultados1.txt","w");
  resul2 = fopen("Resultados2.txt","w");
  /*Definimos las variables para dividir las lineas en los dos valores de posicion
  que necesitamos guardar*/
  char line[500]; //Linea del documento
  double x1[43],y1[43],x2[43],y2[43]; //Valor de la posicion x o y
  double norm1[43];
  int i=0; //Contador
  /*Inicializamos el arreglo de posiciones para tener valores conocidos*/
  for (i=0;i<43;i++){
    x1[i]=0;
    y1[i]=0;
    x2[i]=0;
    y2[i]=0;
  }
  i=0;
  /*Dividimos el archivo en lineas separadas y lo guardamos en dos listas diferentes*/
  while(!feof(canal1)){
    char * pEnd;
    fgets(line,500,canal1);
    double x,y;
    x = strtod(line,&pEnd);
    y = strtod(pEnd,NULL);
    x1[i]=x;
    y1[i]=y;
    i++;
  }
  i=0;
  while(!feof(canal2)){
    char * pEnd;
    fgets(line,500,canal2);
    double x,y;
    x = strtod(line,&pEnd);
    y = strtod(pEnd,NULL);
    x2[i]=x;
    y2[i]=y;
    i++;
  }
  /*Vamos ahora a definir un cuadrado dentro del cual hemos de aplicar el método de montecarlo
  para encontrar el radio del máximo circulo. Este cuadrado lo hemos de definir teniendo en cuenta
  el punto con el x más pequeño y con el x mas grande para definir su base y los puntos con el y mas pequeño y con el
  y mas grande para definir su altura*/
  double y_min1 = amin(y1,43,0);
  double y_max1 = amax(y1,43,0);
  double x_min1 = amin(x1,43,0);
  double x_max1 = amax(x1,43,0);
  /*Vamos ahora a definir una lista que contendra la caminata aleatoria, inicializandola con un valor aleatorio dentro del canal
  Para esto generamos una semilla aleatoria en las listas de numeros semi-aleatorios*/
  srand(time(NULL));
  /*Definimos las listas*/
  double C_x[N+1];
  double C_y[N+1];
  double R[N+1];
  /*Ubicamos el primer elemento*/
  C_x[0]=rand_lim(x_min1,x_max1);
  C_y[0]=rand_lim(y_min1,y_max1);
  R[0]=radius(x1,y1,C_x[0],C_y[0],1);
  /*Comienza el proceso de iteración */
  for(i=0;i<N;i++){
    /*Generamos un centro aleatorio dentro del canal y calculamos el raadio*/
    double c_x = rand_lim(x_min1,x_max1), c_y = rand_lim(y_min1,y_max1);
    double r=radius(x1,y1,c_x,c_y,1);
    /*Verificamos si este nuevo punto debe reemplazar el punto anterior*/
    if(replace(R[i],r)!= 0){
      C_x[i+1]=c_x;
      C_y[i+1]=c_y;
      R[i+1]=r;
    }
    else{
      C_x[i+1]=C_x[i];
      C_y[i+1]=C_y[i];
      R[i+1]=R[i];
    }

  }
  /*Guardamos ahora nuestros resultados en los archivos correspondientes*/
  //fprintf(resul1, "%s\t%s\t%s\n","C_x","C_y","R");
  for (i=0; i<N+1;i++){
    fprintf(resul1, "%f\t%f\t%f\n",C_x[i],C_y[i],R[i]);
  }
  double y_min2 = amin(y2,43,0);
  double y_max2 = amax(y2,43,0);
  double x_min2 = amin(x2,43,0);
  double x_max2 = amax(x2,43,0);
  /*Repetimos el procedimiento para el segundo conjunto de datos*/
  double C_x2[N+1];
  double C_y2[N+1];
  double R2[N+1];
  /*Ubicamos el primer elemento*/
  C_x2[0]=rand_lim(x_min2,x_max2);
  C_y2[0]=rand_lim(y_min2,y_max2);
  R2[0]=radius(x2,y2,C_x2[0],C_y2[0],1);
  /*Comienza el proceso de iteración */
  for(i=0;i<N;i++){
    /*Generamos un centro aleatorio dentro del canal y calculamos el raadio*/
    double c_x = rand_lim(x_min2,x_max2), c_y = rand_lim(y_min2,y_max2);
    double r=radius(x2,y2,c_x,c_y,1);
    /*Verificamos si este nuevo punto debe reemplazar el punto anterior*/
    if(replace(R2[i],r)!= 0){
      C_x2[i+1]=c_x;
      C_y2[i+1]=c_y;
      R2[i+1]=r;
    }
    else{
      C_x2[i+1]=C_x2[i];
      C_y2[i+1]=C_y2[i];
      R2[i+1]=R2[i];
    }

  }
  /*Guardamos ahora nuestros resultados en los archivos correspondientes*/
  //fprintf(resul2, "%s\t%s\t%s\n","C_x","C_y","R");
  for (i=0; i<N+1;i++){
    fprintf(resul2, "%f\t%f\t%f\n",C_x2[i],C_y2[i],R2[i]);
  }
  fclose(canal1);
  fclose(canal2);
  fclose(resul1);
  fclose(resul2);
  return 0;
}

double likelihood(double *y_obs, double *y_model,int n){
  int i=0;
  double chi=0;
  for(i=0; i<n;i++){
    chi += 0.5*(y_obs[i]-y_model[i])*(y_obs[i]-y_model[i]);
  }
  printf("%f\n",chi );
  return exp(-chi);
}
double norm(double x, double y){
  return pow((x*x)+(y*y),0.5);
}
double amax(double * list, int size, int loc){
  double max=list[0];
  int i, l=0;
  for (i=1; i<size; i++){
    if(list[i]>max){
      max=list[i];
      l=i;
    }
  }
  if(loc==0){return max;}
  else{return l;}
}
double amin(double * list, int size, int loc){
  double min=list[0];
  int i, l=0;
  for (i=1; i<size; i++){
    if(list[i]<min){
      min=list[i];
      l=i;
    }
  }
  if(loc==0){return min;}
  else{return l;}
}
double rand_lim(double min, double max){
  double a=max-min;
  return min+((float)rand()/(float)(RAND_MAX)) * a;
}
double radius(double *x, double *y, double c_x, double c_y, double atom_r){
  double radii[43];
  int i;
  for(i=0; i<43; i++){
    radii[i]=norm(x[i]-c_x,y[i]-c_y)-atom_r;
  }
  return amin(radii,43,0);
}
int replace(double previuos, double next){
  if(next<previuos){
    return 0;
  }
  else{
    return 1;
  }

}
