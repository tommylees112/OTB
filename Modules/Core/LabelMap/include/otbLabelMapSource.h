/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef otbLabelMapSource_h
#define otbLabelMapSource_h


#include "itkProcessObject.h"
#include "itkMacro.h"

namespace otb
{
/** \class LabelMapSource
 * \brief Base class for filter that output LabelMap
 *
 * \ingroup IO
 *
 *
 * \ingroup OTBLabelMap
 */

template <class TOutputLabelMap>
class ITK_EXPORT LabelMapSource : public itk::ProcessObject
{
public:

  /** Standard class typedefs. */
  typedef LabelMapSource                Self;
  typedef itk::ProcessObject            Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LabelMapSource, itk::ProcessObject);

  typedef itk::ProcessObject::DataObjectPointerArraySizeType DataObjectPointerArraySizeType;
  typedef TOutputLabelMap                   OutputLabelMapType;
  typedef typename TOutputLabelMap::Pointer OutputLabelMapPointer;

  /** Overriding GetOutput() method */
  virtual OutputLabelMapType* GetOutput(void);
  virtual OutputLabelMapType* GetOutput(DataObjectPointerArraySizeType idx);

protected:
  LabelMapSource();
  ~LabelMapSource() ITK_OVERRIDE;

  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;

  /** Ensure that the output vector data are cleared before processing */
  virtual void  AllocateOutputs();

private:
  LabelMapSource(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbLabelMapSource.txx"
#endif

#endif // otbLabelMapSource_h
