#ifndef MODELICA_ARRAY_HPP_
#define MODELICA_ARRAY_HPP_

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template <class Tp>
class modelica_array
{
public:
  virtual ~modelica_array() {};

  // ------- Array dimension and size functions -------
  /// Returns the number of dimensions.
  int ndims() const;
  
  /// Returns a vector of lenght ndims() containing the dimensions.
  std::vector<int> size() const;
  
  /// Returns the size of dimension i of the array where 1<=i<=ndims().
  int size(int dim) const;

//   // --------- Dimensionality conversion functions ---------
//   /// Converts a to a scalar
  Tp scalar() const;
  
//   /// Converts a to a vector.
//   modelica_real_array vector();

//   /// Converts a to a matrix.
//   modelica_real_array matrix();

  //void fill_array(Tp s,std::vector<int> dims);
  void fill_array(Tp s);

  friend modelica_array<Tp> create_array<Tp>(std::vector<Tp> data);
  friend modelica_array<Tp> create_array<Tp>(std::vector<modelica_array<Tp> > arrays);
  
  void print_dims();
  void print_data() const;
//  void print();
  modelica_array<Tp> slice(std::vector<int> idx);
  void set_element(std::vector<int> idx,Tp elem);

  friend ostream& operator<< <Tp>(ostream&, const modelica_array<Tp> arr);

protected:
  modelica_array() {};
  modelica_array(std::vector<int> dims);
  modelica_array(std::vector<int> dims,std::vector<Tp> scalars);

  //   /// Returns the number of elements in the matrix.
  int nr_of_elements() const;
  int compute_data_index(const std::vector<int>& idx) const;

  

  typedef vector<Tp>::iterator data_iterator; 
  vector<Tp> m_data;
  
  int m_ndims;
  typedef std::vector<int>::iterator dim_size_iterator;
  std::vector<int> m_dim_size;

};

template <class Tp>
modelica_array<Tp>::modelica_array(std::vector<int> dims)
{
  m_dim_size = dims;
  m_data.resize(nr_of_elements());
}

template <class Tp>
modelica_array<Tp>::modelica_array(std::vector<int> dims,std::vector<Tp> scalars)
{
  assert(size_t(std::accumulate(dims.begin(),dims.end(),1,std::multiplies<size_t>()) 
  			) == scalars.size());
  m_dim_size = dims;
  m_data = scalars;
}

template <class Tp>
int modelica_array<Tp>::ndims() const
{
  return m_dim_size.size();
}

template <class Tp>
std::vector<int> modelica_array<Tp>::size() const
{
  return m_dim_size;
}

template <class Tp>
int modelica_array<Tp>::size(int dim) const
{
  assert((dim>=0) && (dim<m_dim_size.size()));
  return m_dim_size[dim];
}

template <typename Tp>
Tp modelica_array<Tp>::scalar() const
{
  for (int i = 0; i < m_dim_size.size(); ++i)
    {
      cout << m_dim_size[i] << endl;
      assert(m_dim_size[i] == 1);
    }
    assert(m_data.size() > 0);

  return m_data[0];
}

template <typename Tp>
modelica_array<Tp> create_array(std::vector<Tp> data)
{
  modelica_array<Tp> result(std::vector<int>(1,data.size()),data);
  return result;
}

template <typename Tp>
modelica_array<Tp> create_array(std::vector<modelica_array<Tp> > arrays)
{
  modelica_array<Tp> result;

  std::vector<int> dims(1,1);
  //dims = arrays[1].m_dim_size;
  dims.insert(dims.end(),result.m_dim_size.begin(),m_dim_size.end());

  result(dims);
  
  //  result.m_data
  
  return result;
  
}

template <class Tp>
void modelica_array<Tp>::fill_array(Tp s)
{
  for (int i = 0; i < nr_of_elements(); ++i)
    {
      m_data[i] = s;
    }
}

template <typename Tp>
void modelica_array<Tp>::set_element(std::vector<int> idx,Tp elem)
{
  int data_index = compute_data_index(idx);
  assert(data_index < m_data.size());

  m_data[data_index] = elem;
}

template <typename Tp>
ostream& operator<< (ostream& o, const modelica_array<Tp> arr)
{
  o << "{";
  
  assert (arr.ndims() == 1);

  if (arr.m_data.size() > 0)
    {
      o << arr.m_data[0];
      for (size_t i = 1; i < arr.m_data.size(); ++i)
 	{
 	  o << "," << arr.m_data[i] << flush;
	}
    }
  o << "}"; 
 }

template <class Tp>
void modelica_array<Tp>::print_dims() 
{
  for (int i = 0; i < m_dim_size.size();++i)
    {
      cout << "dim_size[" << i << "] : " << m_dim_size[i] << endl;
    }
}

template <class Tp>
modelica_array<Tp>  modelica_array<Tp>::slice(std::vector<int> idx) 
{
  // Determine number of dimensions
  
  // Determine size of output

  // Copy data
}

template <class Tp>
int modelica_array<Tp>::nr_of_elements() const
{
  return std::accumulate(m_dim_size.begin(),m_dim_size.end(),1,std::multiplies<int>());
}

template <typename Tp>
int modelica_array<Tp>::compute_data_index(const std::vector<int>& idx) const
{
  assert(idx.size() > 0);
  int stride = idx[0];
  for (int i = 1; i < idx.size(); ++i)
    {
      assert((idx[i] >= 0) && (idx[i] < m_dim_size[i]));
      stride = idx[i] + m_dim_size[i]*stride;
    }
  return stride;
}


template <class Tp>
void modelica_array<Tp>::print_data() const
{
  for (int i = 0; i < m_data.size();++i)
    {
      cout << "m_data[" << i <<"] = " << m_data[i] << endl;
    }
}
// template <class Tp>
// void modelica_array<Tp>::print() 
// {
//   for (int i = 0; i < m_dim_size.size();++i)
//     {
      
//     }
// }




// class modelica_real_array //: public numerical_array
// {
// public:
//   typedef std::vector<int> index;

// public:
//   /// Constructs an empty array.
//   modelica_real_array();
//   /// Constructs an empty array with specified dimensions.
//   modelica_real_array(std::vector<int> dimensions);
//   /// Constructs an array with specified dimensions from scalars.
//   modelica_real_array(std::vector<double> dimensions,std::vector<double> scalars);
//   /// Destructor
//   virtual ~modelica_real_array();
  
  

  
//   //  friend ostream& operator<< (ostream& o, const value& v);

//   modelica_real_array slice(const index& idx) const;

//   double operator() (const index& idx) const;

//   // Specialized constructor functions
  
//   /// Returns an array with all elements equal to one. The dimensions are given by dim.
//   friend modelica_real_array ones(std::vector<int> dim);

//   /// Returns an array with all elements equal to the scalar s.
//   friend modelica_real_array fill(double s,std::vector<int> dim);

//   /// Returns the n x n identity matrix.
//   friend modelica_real_array identity(int n);

//   /// Returns a square matrix with the elements of v on the diagonal and all other elements set to zero.
//   friend modelica_real_array diagonal() const;

//   /// Returns a vector with n equally spaced elements such that v[i] = x1+(x2-x1)*(i-1)/(n-1)
//   friend modelica_real_array linspace(double x1, double x2, int n);

//   // Matrix and vector algebra functions
//   /// Permutes the first two dimensions.
//   friend modelica_real_array transpose(const modelica_real_array& a);

//   /// Returns the outer product of a and b.
//   friend modelica_real_array outer_product(const modelica_real_array& a,
// 					   const modelica_real_array& b);

//   /// Returns a symmetric array created from a.
//   friend modelica_real_array symmetric(const modelica_real_array& a);

//   /// Returns the cross product of a and b.
//   friend modelica_real_array cross(const modelica_real_array& a,
// 				   const modelica_real_array& b);

//   /// Returns the 3x3 skew symmetric matrix.
//   friend modelica_real_array skew(const modelica_real_array& a);


//   // arithmetic operators
//   const modelica_real_array& operator+= (const modelica_real_array& arr);
//   modelica_real_array operator+ (const modelica_real_array& arr) const;

//   const modelica_real_array& operator-= (const modelica_real_array& arr);
//   modelica_real_array operator- (const modelica_real_array& arr) const;

//   //  friend modelica_real_array operator* (const modelica_real_array& a, const modelica_real_array& b);

//   //  modelica_real_array symmetric();

//   // modelica_real_array identity() const;
//   //  modelica_real_array cross() const;
//   //  modelica_real_array pow(const int n) const;
  
// protected:
//   /// Returns the number of elements in the matrix.
//   int nr_of_elements() const;
//   /// Help function to map index to array index (m_data).
//   int compute_data_index(const index& idx) const;
  
//   typedef vector<double>::iterator data_iterator; 
//   vector<double> m_data;
  
//   int m_ndims;
//   typedef std::vector<int>::iterator dim_size_iterator;
//   std::vector<int> m_dim_size;
  

// };



#endif