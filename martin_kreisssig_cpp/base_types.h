#ifndef DATATYPES_H
#define DATATYPES_H

#include <vector>

/**
  * \typedef integer vector
  */
typedef std::vector<int> i_v;
/**
  * \typedef integer matrix
  */
typedef std::vector<std::vector<int> > i_m;
/**
  * \typedef double vector
  */
typedef std::vector<double> d_v;
/**
  * \typedef double matrix
  */
typedef std::vector<std::vector<double> > d_m;
/**
  * \typedef bool vector
  */
typedef std::vector<bool> b_v;
/**
  * \typedef bool matrix
  */
typedef std::vector<std::vector<bool> > b_m;
/**
  * \typedef integer iterator
  */
typedef std::vector<int>::iterator i_it;

#endif // DATATYPES_H
