#include <iostream>

using std::cin; 
using std::cout;
using std::endl;

#define SIZEARR 8

bool implication(bool a, bool b) 
{
    return !a || b;
}
bool equivalence(bool a, bool b)
{
  return a == b;
}
bool func1(bool p, bool q,bool r)
{
  bool res = implication(p && (q || r), equivalence(implication( r , implication(p, q) ), implication(q, implication(r,p) )) );
  return res;
}

void calculate_truth_table(bool* p, bool* q,bool* r, bool* res)
{
  for (int i = 0; i < SIZEARR; i++){
    res[i] = func1(p[i],q[i],r[i]);
  }
  
}

//TRUTH TABLE ANALISYS
bool satisfiability(bool* res)
{
  for (int i = 0; i < SIZEARR; i++){
    if(res[i]==1)
      return 1;
  }
  return 0;
}
bool unsatisfiability(bool* res)
{
  for (int i = 0; i < SIZEARR; i++){
    if(res[i]==0)
      return 1;
  }
  return 0;
}
bool tautology(bool* res)
{
  return !(unsatisfiability(res));
}
bool contradiction(bool* res)
{
  return !(satisfiability(res));
}
bool is_dummy(bool* v, bool* t, int v_count)
{
  bool temp=1;
  if(v_count==1)
    goto v1;
  else if(v_count==2)
    goto v2;
  else if(v_count==3)
    goto v3;
  else
    return 0;

v1:
  return (v[0]==v[3] && t[0]==t[3])&&(v[4]==v[7] && t[4]==t[7]);

v2:
  for (int i = 0; i <= 4; i+=4){
    temp = temp && (v[i]==v[i+2] && t[i] == t[i+2]);
    temp = temp && (v[i+1]==v[i+3] && t[i+1] == t[i+3]);
  }
  return temp;

v3:
  for (int i = 0; i < SIZEARR; i+=2){
    temp = temp && (v[i] == v[i+1] && t[i]==t[i+1]);
  }
  return temp;
}

int main()
{
  bool p[SIZEARR] = {0,0,0,0,1,1,1,1};
  bool q[SIZEARR] = {0,0,1,1,0,0,1,1};
  bool r[SIZEARR] = {0,1,0,1,0,1,0,1};

  bool res[SIZEARR] = {0};



  calculate_truth_table(p,q,r,res);

  cout<<"p\tq\tr\tres"<<endl;
  for (int i = 0; i < SIZEARR; i++){
    cout<<p[i]<<'\t'<<q[i]<<'\t'<<r[i]<<'\t'<<res[i]<<endl;
  }
  cout<<endl;
  cout<<"satisfiability: "<<satisfiability(res)<<endl;
  cout<<"unsatisfiability: "<<unsatisfiability(res)<<endl;
  cout<<"tautology: "<<tautology(res)<<endl;
  cout<<"contradiction: "<<contradiction(res)<<endl;
  cout<<endl;
  cout<<"is dummy p? - "<<is_dummy(p,res,1)<<endl;
  cout<<"is dummy q? - "<<is_dummy(q,res,2)<<endl;
  cout<<"is dummy r? - "<<is_dummy(r,res,3)<<endl;
  

}

