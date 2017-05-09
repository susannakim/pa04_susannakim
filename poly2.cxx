// Susanna Kim  5/15/17

#include <iostream>
#include "poly2.h"
#include <cmath>
#include <cassert>
#include <climits>
#include <string>
#include <cstdlib>

using namespace std;

namespace main_savitch_5
{
  polynomial::polynomial(double c, unsigned int exponent){
    if(exponent < DEFAULT_CAPACITY)
      size = DEFAULT_CAPACITY;
    else
      size = exponent +1;
    coef = new double[size];
    for(int i = 0; i< size; i++){
      if(i == exponent) coef[i] = c;
      else coef[i] = 0;
    }
    current_degree = 0;
    for(int i = size -1; i >=0; i--){
      if(coef[i] != 0){
	current_degree = i;
	break;
      }
    }
  }

  polynomial::polynomial(const polynomial& source){
    current_degree = source.current_degree;
    size = source.size;
    coef = new double[size];
    for(int i = 0; i < source.size; i++){
      coef[i] =  source.coef[i];
    }

  }

  polynomial::~polynomial(){
    delete []coef;
  }

  polynomial& polynomial::operator =(const polynomial& source){
    if(this == &source) return *this;
    else{
      size = source.size;
      delete []coef;
      coef = new double[size];
      for(int i = 0; i < size; i++){
	coef[i] = source.coef[i];
      }
      current_degree = source.current_degree;
      return *this;
    }
  }

  void polynomial::add_to_coef(double amount, unsigned int exponent){
    double sum = amount += coefficient(exponent);
    assign_coef(sum, exponent);
    if(current_degree < exponent)
      current_degree = exponent;
    if(coef[exponent] == 0){
      int de = 0;
      for(int i = 0; i <= degree() ; i++){
	if(coefficient(i) != 0)
	  de = i;
      }
      current_degree = de;
    }
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    if(exponent + 1 > size)
      reserve(exponent + 1);
    coef[exponent] = coefficient;
    if(coefficient != 0 && exponent > current_degree)
      current_degree = exponent;
    else if(coefficient == 0 && exponent == current_degree && exponent > 0)
      current_degree = previous_term(current_degree);
  }

  void polynomial::clear(){
    for(int i = 0; i < size; i++){
      coef[i] = 0.0;
    }
    current_degree = 0;
  }

  double polynomial::coefficient(unsigned int exponent) const{
    if(exponent + 1 > size)
      return 0;
    return coef[exponent];
  }

  polynomial polynomial::derivative() const{
    polynomial p1;
    for(int i = 0 ;i < size -1 ; i++){
      p1.assign_coef(coef[i+1]*(i+1),i);
    }
    return p1;
  }

  double polynomial::eval(double x) const{
    double sum = 0;
    for(int i = 0; i < size; i++){
      sum += coef[i]*(pow(x,i));
    }
    return sum;
  }

  void polynomial::find_root(
			     double& answer,
			     bool& success,
			     unsigned int& iterations,
			     double guess,
			     unsigned int maximum_iterations,
			             double epsilon
			     )
    const{
    //stub
  }

  unsigned int polynomial::next_term(unsigned int e) const{
    if(e >= size) return 0;
    else{
      for(int i = e + 1; i < size; i++){
	if(coef[i] != 0)  return i;
      }
      return 0;
    }
  }

  unsigned int polynomial::previous_term(unsigned int e) const{
    if(e == 0) return UINT_MAX;
    else{
      if(e >= size){
	int n = size;
	for(int i = n -1; i >= 0; i--){
	  if(coef[i] != 0) return i;
	}
	return UINT_MAX;
      }else{
	for(int i = e - 1; i >= 0; i--){
	  if(coef[i] != 0) return i;
	}
	return UINT_MAX;
      }
    }
  }

  polynomial operator +(const polynomial& p1, const polynomial& p2){
    polynomial p3;
    if(p1.degree() >= p2.degree()){
      for(int i = 0; i <= p1.degree(); i++)
	p3.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
      return p3;
    }else{
      for(int i = 0; i <= p2.degree(); i++)
	p3.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
      return p3;
    }
  }

  polynomial operator -(const polynomial& p1, const polynomial& p2){
    polynomial p3;
    if(p1.degree() >= p2.degree()){
      for(int i = 0; i <= p1.degree(); i++)
	p3.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
      return p3;
    }else{
      for(int i = 0; i <= p2.degree(); i++)
	p3.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
      return p3;
    }
  }

  polynomial operator *(const polynomial& p1, const polynomial& p2){
    polynomial p3;
    for(int i = 0; i <= p1.degree(); i++){
      for(int j = 0; j <= p2.degree(); j++)
	p3.assign_coef(0, i+j);
    }
    for(int i = 0; i <= p1.degree(); i++){
      for(int j = 0; j <= p2.degree(); j++)
	p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
    }
    return p3;
  }

  std::ostream& operator << (std::ostream& out, const polynomial& p){
    int count = 0;
    for(int i = 0; i <= p.degree(); i++){
      if(p.coefficient(i) != 0) count++;
    }
    if(count == 0){
      out<< 0 << std::endl;
      return out;
    }else{
      for(int i = p.degree(); i >= 0; i--){
	if(p.coefficient(i) >= 0){
	  if(p.coefficient(i) != 0 && (i == 1))
	    out << " + " << p.coefficient(i) << "x";
	  else if((count == 1) && (p.coefficient(i) != 0) && i == 0)
	    out << p.coefficient(i);
	  else if((count == 1) && (p.coefficient(i) != 0) && i == 1)
	    out << p.coefficient(i) << "x";
	  else if((count == 1) && (p.coefficient(i) != 0) && i > 1)
	    out << p.coefficient(i) << "x^" << i;
	  else if(p.coefficient(i) != 0 && (i == 0))
	    out << " + " << p.coefficient(i);
	  else if(p.coefficient(i) != 0 && !(p.next_term(i)))
	    out << p.coefficient(i) << "x^" << i;
	  else if(p.coefficient(i) != 0 && i > 1)
	    out << " + " << p.coefficient(i) << "x^" << i;
	  else if(p.coefficient(i) != 0 && (i == 1))
	    out << " + " << p.coefficient(i) << "x";
	}else{
	  if(p.coefficient(i) !=0 && !(p.next_term(i)) && i >1)
	    out << p.coefficient(i) << "x^" << i;
	  else if(p.coefficient(i) !=0 && !(p.next_term(i)) && i ==1)
	    out << p.coefficient(i) << "x";
	  else if(p.coefficient(i) !=0 && !(p.next_term(i)) && i ==0)
	    out << p.coefficient(i);
	  else if(p.coefficient(i) != 0 && (i > 1))
	    out << " - " << std::abs(p.coefficient(i)) << "x^" << i;
	  else if(p.coefficient(i) != 0 && (i == 1))
	    out << " - " << std::abs(p.coefficient(i)) << "x";
	  else if(p.coefficient(i) != 0 && (i == 0))
	    out << " - " << std::abs(p.coefficient(i));
	}
      }
      out << std::endl;
      return out;
    }
  }
}
