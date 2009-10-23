/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE,  See the above copyright notices for more information.

=========================================================================*/
#include "otbVectorImageToAmplitudeImageFilter.h"
#include "otbVectorImage.h"
#include "otbImage.h"

int otbVectorImageToAmplitudeImageFilterNew(int argc, char * argv[])
{
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef otb::Image<PixelType,Dimension> ImageType;
  typedef otb::VectorImage<PixelType,Dimension> VectorImageType;
  typedef otb::VectorImageToAmplitudeImageFilter<VectorImageType,ImageType> FilterType;

  // Instantiating object
  FilterType::Pointer object = FilterType::New();

  return EXIT_SUCCESS;
}
