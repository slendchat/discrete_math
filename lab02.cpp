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
//(P ^ (Q V R) -> ((R -> (P -> Q)) <-> (Q -> (R -> P))) )
bool func1(bool p, bool q, bool r)
{
  bool res = equivalence(p && (implication(q,!r) || r),implication(equivalence(p,r || !q),q && !q));
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
// проверка на фиктивные переменные
bool is_dummy(bool* input, int v_count)
{
  bool res=1;
  if(v_count==1)
    goto v1;
  else if(v_count==2)
    goto v2;
  else if(v_count==3)
    goto v3;
  else
    return -1;

v1:
  for(int i = 0; i+4<SIZEARR;i++){
    res = res && (input[i]==input[i+4]);
  }
  return res;
v2:
  for (int i = 0; i <= 4; i+=4){
    res = res && (input[i] == input[i+2]);
    res = res && (input[i+1] == input[i+3]);
  }
  return res;
v3:
  for (int i = 0; i < SIZEARR; i+=2){
    res = res && (input[i]==input[i+1]);
  }
  return res;
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
  cout<<"is p dummy? - "<<is_dummy(res,1)<<endl;
  cout<<"is q dummy? - "<<is_dummy(res,2)<<endl;
  cout<<"is r dummy? - "<<is_dummy(res,3)<<endl;
  

}

