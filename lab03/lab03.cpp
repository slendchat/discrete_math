// доделать отчет и написать вывод программы в выводе отчета
// Добавить функцию из 2 лабы

#include <iostream>

using std::cout;
using std::endl;

int implication(int a, int b) 
{
    return !a || b;
}
int equivalence(int a, int b)
{
  return a == b;
}
int f1(int x, int y, int z)
{
  return (x || (y && !y) || z);
}
//(P ^ (Q V R) -> ((R -> (P -> Q)) <-> (Q -> (R -> P))) )
int f2(int x, int y, int z)
{
  return (equivalence(x && (implication(y,!z) || z),implication(equivalence(x,z || !y),y && !y)));
}

//((x | y)+(y|z))->(x v (!(y pirs z)))
int f3(int x, int y, int z)
{
  return implication(!(x && y) ^ !(y && z), (x || !(!(y || z))));
}

//((x -> y) pirs z) | (!(x -> y))
int f4(int x, int y, int z)
{
  return (!((implication(x,y) || z) && (!(implication(x,y)))));
}


void fill_table(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size, int(*f)(int x, int y, int z))
{
  int values[2] = {0, 1};
  int i = 0;
  for (int x : values){
    for (int y : values){
      for (int z : values){
        x_arr[i] = x;
        y_arr[i] = y;
        z_arr[i] = z;
        f_arr[i] = f(x, y, z);
        i++;
      }
    }
  }

}

void print_table(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size)
{
  cout << "Table of function's values:" << endl;
  cout << "x | y | z | f" << endl;
  cout << "-------------" << endl;
  for (int i = 0; i < size; i++){
    cout << x_arr[i] << " | " << y_arr[i] << " | " << z_arr[i] << " | " << f_arr[i] << endl;
  }
  cout << endl;
}

void is_dummy(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size)
{
  int xdummy = 1;
  int ydummy = 1;
  int zdummy = 1;

  for (int i = 0; i < size-1; i++){
    int x = x_arr[i];
    int y = y_arr[i];
    int z = z_arr[i];
    int f = f_arr[i];
    
    for(int j = i+1; j < size; j++){
      if (x != x_arr[j] && y == y_arr[j] && z == z_arr[j]){
        xdummy = xdummy && (f == f_arr[j]);
      }
      if (y != y_arr[j] && x == x_arr[j] && z == z_arr[j]){
        ydummy = ydummy && (f == f_arr[j]);
      }
      if (z != z_arr[j] && y == y_arr[j] && x == x_arr[j]){
        zdummy = zdummy && (f == f_arr[j]);
      }
    }
  }

  cout<<"find dummy variables"<<endl;

  if (xdummy){
    cout << "x is dummy" << endl;
  }
  else{
    cout << "x is not dummy" << endl;
  }
  if (ydummy){
    cout << "y is dummy" << endl;
  }
  else{
    cout << "y is not dummy" << endl;
  }
  if (zdummy){
    cout << "z is dummy" << endl;
  }
  else{
    cout << "z is not dummy" << endl;
  }

  return;
}


int t1(int *f_arr, int size){
  int res = f_arr[7];
  cout<<"t1: "<<res<<endl;
  return res;
}

int t0(int *f_arr, int size){
  int res = !f_arr[0];
  cout<<"t0: "<<res<<endl;
  return res;
}


void is_monotonic(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size){
  
  int is_monotonic = 1;

  for (int i = 0; i < size-1; i++){

    if (!(x_arr[i]<=x_arr[i+1] && y_arr[i]<=y_arr[i+1] && z_arr[i]<=z_arr[i+1])){
      continue;
    }

    is_monotonic = is_monotonic && (f_arr[i]<=f_arr[i+1]);

    if (is_monotonic==0){
      cout<<"not monotonic"<<endl;
      return;
    }
  }
  cout<<"monotonic"<<endl;
  
  return;
}

void analyze_func(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size, int(*f)(int x, int y, int z))
{
  fill_table(x_arr, y_arr, z_arr, f_arr, 8,f);
  print_table(x_arr, y_arr, z_arr, f_arr, 8);
  is_dummy(x_arr, y_arr, z_arr, f_arr, 8);
  t1(f_arr, 8);
  t0(f_arr, 8);
  is_monotonic(x_arr, y_arr, z_arr, f_arr, 8);
}

int main()
{
  int *x_arr = new int[8];
  int *y_arr = new int[8];
  int *z_arr = new int[8];
  int *f_arr = new int[8];
  
  //f1
  analyze_func(x_arr, y_arr, z_arr, f_arr, 8,f1);
  //f2
  analyze_func(x_arr, y_arr, z_arr, f_arr, 8,f2);
  //f3
  analyze_func(x_arr, y_arr, z_arr, f_arr, 8,f3);
  //f4
  analyze_func(x_arr, y_arr, z_arr, f_arr, 8,f4);


  delete[] x_arr;
  delete[] y_arr;
  delete[] z_arr;
  delete[] f_arr;

  return 0;
}


