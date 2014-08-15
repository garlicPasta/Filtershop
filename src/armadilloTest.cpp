/*
 * =====================================================================================
 *
 *       Filename:  armadilloTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28.06.2014 01:02:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <armadillo>
#include <iostream>

using namespace arma;

int main(void)
{
  int a_data [] = {4, 6, 7,  8, 9, 11};
  Mat<int> a = Mat<int>(a_data, 3, 2);

  Mat<int> left = a.col(0);
  Mat<int> right = a.col(1);

  a = join_horiz(left, a);
  a = join_horiz(a, right);
  std::cout << a << std::endl;

  auto _size = a.n_cols;
  std::cout << _size << std::endl;

}


