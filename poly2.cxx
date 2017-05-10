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
    // stub
  }

  polynomial::polynomial(const polynomial& source){
    // stub
  }

  polynomial::~polynomial(){
    // stub
  }

  polynomial& polynomial::operator =(const polynomial& source){
    // stub
  }

  void polynomial::add_to_coef(double amount, unsigned int exponent){
    // stub
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    // stub
  }

  void polynomial::clear(){
    // stub
  }

  double polynomial::coefficient(unsigned int exponent) const{
    // stub
  }

  polynomial polynomial::derivative() const{
    // stub
  }

  double polynomial::eval(double x) const{
    // stub
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
    // stub
  }

  unsigned int polynomial::previous_term(unsigned int e) const{
    // stub
  }

  void polynomial::set_recent(unsigned int exponent) const {
    if(exponent == 0) {
      recent_ptr = head_ptr;
    }
    else if(exponent >= current_degree) {
      recent_ptr = tail_ptr;
    }
    else if(exponent < recent_ptr->exponent()) {
      while((recent_ptr->back() != NULL) && (recent_ptr->exponent() > exponent)) {
	recent_ptr = recent_ptr->back();
      }
    }
    else {
      while((recent_ptr->fore() != NULL) && (recent_ptr->exponent() < exponent)) {
	recent_ptr = recent_ptr->fore();
      }
    }
  }
  
  polynomial operator +(const polynomial& p1, const polynomial& p2){
    // stub
  }

  polynomial operator -(const polynomial& p1, const polynomial& p2){
    // stub
  }

  polynomial operator *(const polynomial& p1, const polynomial& p2){
    // stub
  }

  std::ostream& operator << (std::ostream& out, const polynomial& p){
    // stub
  }
}
