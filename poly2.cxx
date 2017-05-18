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
    polynode* source_node;
    for (source_node = source.head_ptr; source_node != NULL; source_node = source_node->fore()) {
      assign_coef(source_node->coef(), source_node->exponent());
    }
  }

  polynomial::~polynomial(){
    clear();
  }

  polynomial& polynomial::operator =(const polynomial& source){
    // stub
  }

  void polynomial::add_to_coef(double amount, unsigned int exponent){
    set_recent(exponent);
    if (recent_ptr->exponent() == exponent) {
      recent_ptr->set_coef(recent_ptr->coef() + amount);
      if (recent_ptr->coef() == 0) {
	if (head_ptr->exponent() == exponent) {
	  current_degree = tail_ptr->exponent();
	  return;
	}
	if (tail_ptr->exponent() == exponent) {
	  tail_ptr = tail_ptr->back();
	  recent_ptr = tail_ptr;
	  delete tail_ptr->fore();
	  tail_ptr->set_fore(NULL);
	  current_degree = tail_ptr->exponent();
	}
        else {
	  polynode* temp_node = recent_ptr;
	  recent_ptr = recent_ptr->back();
	  recent_ptr->set_fore(temp_node->fore());
	  temp_node->fore()->set_back(temp_node->back());
	  current_degree = tail_ptr->exponent();
	  delete temp_node;
	}
      }
    }
    else {
      polynode* p = new polynode(amount, exponent);
      if ((tail_ptr->exponent() > exponent) && (recent_ptr->exponent() < exponent)) {
	recent_ptr->fore()->set_back(p);
	recent_ptr->set_fore(p);
	current_degree = tail_ptr->exponent();
	p->set_back(recent_ptr);
	recent_ptr = p;
      }
      else {
	recent_ptr->set_fore(p);
	tail_ptr = p;
	tail_ptr->set_fore(NULL);
	current_degree = tail_ptr->exponent();
	p->set_back(recent_ptr);
	recent_ptr = p;
      }
    }
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    set_recent(exponent);
    if(recent_ptr->exponent() < exponent) {
      polynode* temp_node = new polynode(coefficient, exponent, recent_ptr->fore(), recent_ptr);
      if (recent_ptr->fore() != NULL) {
	recent_ptr->fore()->set_back(temp_node);
	recent_ptr->set_fore(temp_node);
	current_degree = tail_ptr->exponent();
	recent_ptr = temp_node;
      }
      else {
	recent_ptr->set_fore(temp_node);
	tail_ptr = temp_node;
	tail_ptr->set_fore(NULL);
	current_degree = tail_ptr->exponent();
	recent_ptr = temp_node;
      }
    }
    else if(exponent == 0) {
      recent_ptr->set_coef(coefficient);
      if (exponent > current_degree) {
	current_degree = exponent;
      }
    }
    else if (exponent == current_degree) {
      tail_ptr = tail_ptr->back();
      recent_ptr = tail_ptr;
      delete tail_ptr->fore();
      tail_ptr->set_fore(NULL);
      current_degree = tail_ptr->exponent();
    }
    else if(exponent > current_degree) {
      return;
    }
    else {
      if (exponent == recent_ptr->exponent()) {
	polynode* temp_node = recent_ptr;
	recent_ptr = recent_ptr->back();
	recent_ptr->set_fore(temp_node->fore());
	temp_node->fore()->set_back(temp_node->back());
	delete temp_node;
      }
    }
  }
  
  void polynomial::clear(){
    recent_ptr = tail_ptr;
    polynode* tmp = tail_ptr;
    while(recent_ptr->back() != NULL){
      tmp = recent_ptr->back();
      recent_ptr = tmp;
      delete tmp;
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
    polynomial deriv;
    unsigned int e = next_term(0);
    do {
      deriv.assign_coef(e * coefficient(e), e-1);
      e = next_term(e);
    }
    while (e != 0);
    return deriv;
  }

  double polynomial::eval(double x) const{
    double total = 0;
    unsigned int i = 0;
    do {
      total += coefficient(i) * pow((double) x, (unsigned int) i);
      i = next_term(i);
    }
    while(i != 0);
    return total;
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
    set_recent(e);
    if(recent_ptr->fore() != NULL) {
      return recent_ptr->fore()->exponent();
    }
    else {
      return 0;
    }
  }
  
  unsigned int polynomial::previous_term(unsigned int e) const{
    if(e == 0) {
      return UINT_MAX;
    }
    else {
      do {
	e--;
	if(coefficient(e) != 0.0) {
	  return e;
	}
	if(e > degree()) {
	  return degree();
	}
      }
      while(e > 0);
    }
    return UINT_MAX;
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
