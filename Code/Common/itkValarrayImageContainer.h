/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkValarrayImageContainer.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef __itkValarrayImageContainer_h
#define __itkValarrayImageContainer_h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkSmartPointer.h"

#include <utility>
#include <valarray>

namespace itk
{

/** \class ValarrayImageContainer
 * Defines a front-end to the STL "valarray" container that conforms to the
 * ImageContainerInterface.  This is a full-fleged Object, so
 * there is modification time, debug, and reference count information.
 *
 * Template parameters for ValarrayImageContainer:
 *
 * TElementIdentifier =
 *    An INTEGRAL type for use in indexing the valarray.
 *    It must have a < operator defined for ordering.
 *
 * TElement =
 *    The element type stored in the container.
 */
  
template <
  typename TElementIdentifier,
  typename TElement
  >
class ValarrayImageContainer: 
  public Object,
  private std::valarray<TElement>
{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef ValarrayImageContainer     Self;
  
  /**
   * Standard "Superclass" typedef.
   */
  typedef Object  Superclass;

  /**
   * Smart pointer typedef support.
   */
  typedef SmartPointer<Self>  Pointer;
  
  /** \typedef
   * Save the template parameters.
   */
  typedef TElementIdentifier  ElementIdentifier;
  typedef TElement            Element;
  

private:
  /**
   * Quick access to the STL valarray type that was inherited.
   */
  typedef std::valarray<Element>  Valarray;
  
  
protected:
  /**
   * Provide pass-through constructors corresponding to all the STL
   * valarray constructors.  These are for internal use only since
   * this is also an Object which must be constructed through the
   * "New()" routine.
   */
  
  /**
   *
   */
  ValarrayImageContainer():
    Valarray() {}
  
  /**
   *
   */
  ValarrayImageContainer(unsigned long n):
    Valarray(n) {}
  
  /**
   *
   */
  ValarrayImageContainer(unsigned long n, const Element& x):
    Valarray(n, x) {}
  
  /**
   *
   */
  ValarrayImageContainer(const Self& r):
    Valarray(r) {}
  

public:
  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);
  
  /**
   * Index operator. This version can be an lvalue.
   */
  TElement & operator[](const ElementIdentifier id)
    { return this->Valarray::operator[](id); };

  /**
   * Index operator. This version can only be an rvalue
   */
  const TElement & operator[](const ElementIdentifier id) const
    { return this->Valarray::operator[](id); };
    

  /**
   * Return a pointer to the beginning of the buffer.  This is used by
   * the image iterator class.
   */
  TElement *GetBufferPointer()
    { return &(this->Valarray::operator[](0)); };
  
  /**
   * Get the number of elements currently stored in the container.
   */
  unsigned long Size(void) const
    { return this->Valarray::size(); };

  /**
   * Tell the container to allocate enough memory to allow at least
   * as many elements as the size given to be stored.  This is NOT
   * guaranteed to actually allocate any memory, but is useful if the
   * implementation of the container allocates contiguous storage.
   */
  void Reserve(ElementIdentifier num)
    { this->Valarray::resize(num); };
  
  /**
   * Tell the container to try to minimize its memory usage for storage of
   * the current number of elements.  This is NOT guaranteed to decrease
   * memory usage.
   */
  void Squeeze(void)
    { this->Valarray::resize( this->Valarray::size() ); };
  
  /**
   * Standard part of every itk Object.
   */
  itkTypeMacro(ValarrayImageContainer, Object);
};

} // end namespace itk
  
#endif
