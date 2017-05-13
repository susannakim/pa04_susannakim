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
    head_ptr = new polynode(c, 0);
    if((exponent == 0) || (c == 0)) {
      recent_ptr = head_ptr;
      tail_ptr = head_ptr;
      current_degree = 0;
    }
    else {
      head_ptr->set_coef(0);
      tail_ptr = new polynode(c, exponent, NULL, head_ptr);
      head_ptr->set_fore(tail_ptr);
      recent_ptr = tail_ptr;
      current_degree = tail_ptr->exponent();
    }
  }

  polynomial::polynomial(const polynomial& source){
    head_ptr = new polynode();
    tail_ptr = head_ptr;
    recent_ptr = tail_ptr;
    current_degree = tail_ptr->exponent(); 
    head_ptr->set_fore(NULL);
    head_ptr->set_back(NULL);
  }

  polynomial::~polynomial(){
    clear();
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
    recent_ptr = tail_ptr;
    polynode* cursor = tail_ptr;
    while(recent_ptr->back() != NULL){
      cursor = recent_ptr->back();
      recent_ptr = cursor;
    }
  }

  double polynomial::coefficient(unsigned int exponent) const{
    set_recent(exponent);
    if(recent_ptr->exponent() == exponent) {
      return recent_ptr->coef();
    }
    else {
      return 0;
    }
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
