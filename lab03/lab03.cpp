#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int f(int x, int y, int z)
{
  return (x || y || z);
}

void fill_table(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size)
{
  vector<int> values = {0, 1};
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

  for (int i = 0; i+ size/2 < size; i++){
    xdummy = xdummy && (f_arr[i] == f_arr[i+4]);
  }
  for (int i = 0; i <= size/2; i+=size/2){
    ydummy = ydummy && (f_arr[i] == f_arr[i+2]);
    ydummy = ydummy && (f_arr[i+1] == f_arr[i+3]);
  }
  for (int i = 0; i < size; i+=size/4){
    zdummy = zdummy && (f_arr[i] == f_arr[i+1]);
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
  bool res = 1;
  for (int i = 1; i < size; i++){
    res = res && (1 == f_arr[i]);
  }
  cout<<"t1: "<<res<<endl;
  return res;
}

int t0(int *f_arr, int size){
  bool res = 1;
  for (int i = 0; i < size; i++){
    res = res && (0 == f_arr[i]);
  }
  cout<<"t0: "<<res<<endl;
  return res;
}


void is_monotonic(int *x_arr, int *y_arr, int *z_arr, int *f_arr, int size){
  
  int is_monotonic = 1;


  if(t0(f_arr, size) || t1(f_arr, size)){
    cout<<"monotonic"<<endl;
    return;
  }

  for (int i = 0; i < size-1; i++){

    if (!(x_arr[i]<=x_arr[i+1] || y_arr[i]<=y_arr[i+1] || z_arr[i]<=z_arr[i+1])){
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


int main()
{
  int *x_arr = new int[8];
  int *y_arr = new int[8];
  int *z_arr = new int[8];
  int *f_arr = new int[8];
  
  fill_table(x_arr, y_arr, z_arr, f_arr, 8);
  print_table(x_arr, y_arr, z_arr, f_arr, 8);
  is_dummy(x_arr, y_arr, z_arr, f_arr, 8);
  t1(f_arr, 8);
  t0(f_arr, 8);
  is_monotonic(x_arr, y_arr, z_arr, f_arr, 8);

  delete[] x_arr;
  delete[] y_arr;
  delete[] z_arr;
  delete[] f_arr;
  return 0;
}

