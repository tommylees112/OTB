/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbKMLVectorDataIO.h"
#include <iostream>

int otbKMLVectorDataIOTestCanRead(int itkNotUsed(argc), char* argv[])
{
  typedef otb::KMLVectorDataIO KMLVectorDataIOType;
  KMLVectorDataIOType::Pointer object = KMLVectorDataIOType::New();
  bool                         lCanRead = object->CanReadFile(argv[1]);
  if (lCanRead == false)
    {
    std::cerr << "Erreur otb::KMLVectorDataIO : impossible to open the file " << argv[1] << "." << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
