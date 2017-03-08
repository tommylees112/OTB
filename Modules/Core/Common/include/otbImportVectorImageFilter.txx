/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

  Some parts of this code are derived from ITK. See ITKCopyright.txt
  for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbImportVectorImageFilter_txx
#define otbImportVectorImageFilter_txx

#include "otbImportVectorImageFilter.h"
#include "itkObjectFactory.h"

namespace otb
{

/**
 *
 */
template <class TOutputImage>
ImportVectorImageFilter<TOutputImage>
::ImportVectorImageFilter()
{
  unsigned int idx;

  for (idx = 0; idx < TOutputImage::ImageDimension; ++idx)
    {
    m_Spacing[idx] = 1.0;
    m_Origin[idx] = 0.0;
    }
  m_Direction.SetIdentity();

  m_ImportPointer = 0;
  m_FilterManageMemory = false;
  m_Size = 0;
}

/**
 *
 */
template <class TOutputImage>
ImportVectorImageFilter<TOutputImage>
::~ImportVectorImageFilter()
{
  if (m_ImportPointer && m_FilterManageMemory)
    {
    delete[] m_ImportPointer;
    }
}

/**
 *
 */
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  int i;

  Superclass::PrintSelf(os, indent);

  if (m_ImportPointer)
    {
    os << indent << "Imported pointer: (" << m_ImportPointer  << ")" << std::endl;
    }
  else
    {
    os << indent << "Imported pointer: (None)" << std::endl;
    }
  os << indent << "Import buffer size: " << m_Size << std::endl;
  os << indent << "Import buffer size: " << m_Size << std::endl;
  os << indent << "Filter manages memory: " << (m_FilterManageMemory ? "true" : "false") << std::endl;

  os << indent << "Spacing: [";
  for (i = 0; i < static_cast<int>(TOutputImage::ImageDimension) - 1; ++i)
    {
    os << m_Spacing[i] << ", ";
    }
  os << m_Spacing[i] << "]" << std::endl;

  os << indent << "Origin: [";
  for (i = 0; i < static_cast<int>(TOutputImage::ImageDimension) - 1; ++i)
    {
    os << m_Origin[i] << ", ";
    }
  os << m_Origin[i] << "]" << std::endl;
  os << indent << "Direction: " << std::endl << this->GetDirection() << std::endl;
}

/**
 *
 */

template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::SetImportPointer(TPixel *ptr, unsigned long num, bool LetFilterManageMemory)
{
  if (ptr != m_ImportPointer)
    {
    if (m_ImportPointer && m_FilterManageMemory)
      {
      delete[] m_ImportPointer;
      }
    m_ImportPointer = ptr;
    this->Modified();
    }
  m_FilterManageMemory = LetFilterManageMemory;
  m_Size = num;
}

/**
 *
 */
template <class TOutputImage>
typename ImportVectorImageFilter<TOutputImage>::TPixel*
ImportVectorImageFilter<TOutputImage>
::GetImportPointer()
{
  return m_ImportPointer;
}

/**
 *
 */
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::EnlargeOutputRequestedRegion(itk::DataObject *output)
{
  // call the superclass' implementation of this method
  Superclass::EnlargeOutputRequestedRegion(output);

  // get pointer to the output
  OutputImagePointer outputPtr = this->GetOutput();

  // set the requested region to the largest possible region (in this case
  // the amount of data that we have)
  outputPtr->SetRequestedRegion(outputPtr->GetLargestPossibleRegion());
}

/**
 *
 */
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::GenerateOutputInformation()
{
  // call the superclass' implementation of this method
  Superclass::GenerateOutputInformation();

  // get pointer to the output
  OutputImagePointer outputPtr = this->GetOutput();

  // we need to compute the output spacing, the output origin, the
  // output image size, and the output image start index
  outputPtr->SetSpacing(m_Spacing);
  outputPtr->SetOrigin(m_Origin);
  outputPtr->SetDirection(m_Direction);
  outputPtr->SetLargestPossibleRegion(m_Region);

  typename RegionType::SizeType size = m_Region.GetSize();

  int numberOfBands = m_Size / (size[0] * size[1]);

  if (numberOfBands != static_cast<int>(numberOfBands))
    itkExceptionMacro(
      << "Buffer size and image size are not compatible !");

  outputPtr->SetNumberOfComponentsPerPixel(numberOfBands);
}

/**
 *
 */
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::GenerateData()
{
  // Normally, GenerateData() allocates memory.  However, the application
  // provides the memory for this filter via the SetImportPointer() method.
  // Therefore, this filter does not call outputPtr->Allocate().

  // get pointer to the output
  OutputImagePointer outputPtr = this->GetOutput();

  // the output buffer size is set to the size specified by the user via the
  // SetRegion() method.
  outputPtr->SetBufferedRegion(outputPtr->GetLargestPossibleRegion());

  // pass the pointer down to the container during each Update() since
  // a call to Initialize() causes the container to forget the
  // pointer.  Note that we tell the container NOT to manage the
  // memory itself.  This filter will properly manage the memory (as
  // opposed to the container) if the user wants it to.
  outputPtr->GetPixelContainer()->SetImportPointer(m_ImportPointer,
                                                   m_Size, false);

}

/**
 *
 */
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::SetSpacing(const SpacingType& spacing)
{
  double dspacing[TOutputImage::ImageDimension];
  for (unsigned int i = 0; i < TOutputImage::ImageDimension; ++i)
    {
    dspacing[i] = spacing[i];
    }
  this->SetSpacing(dspacing);
}

/**
 *
 */
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::SetOrigin(const OriginType& origin)
{
  double dorigin[TOutputImage::ImageDimension];
  for (unsigned int i = 0; i < TOutputImage::ImageDimension; ++i)
    {
    dorigin[i] = origin[i];
    }
  this->SetOrigin(dorigin);
}

//----------------------------------------------------------------------------
template <class TOutputImage>
void
ImportVectorImageFilter<TOutputImage>
::SetDirection(const DirectionType direction)
{
  bool modified = false;
  for (unsigned int r = 0; r < TOutputImage::ImageDimension; ++r)
    {
    for (unsigned int c = 0; c < TOutputImage::ImageDimension; ++c)
      {
      if (m_Direction[r][c] != direction[r][c])
        {
        m_Direction[r][c] = direction[r][c];
        modified = true;
        }
      }
    }
  if (modified)
    {
    this->Modified();
    }
}

} // end namespace otb

#endif
