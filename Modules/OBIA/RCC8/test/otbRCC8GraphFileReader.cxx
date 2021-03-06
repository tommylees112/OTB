/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "otbRCC8VertexIterator.h"
#include "otbRCC8EdgeIterator.h"
#include "otbRCC8VertexBase.h"
#include "otbRCC8GraphFileReader.h"
#include "otbMacro.h"
#include "otbPolygon.h"

int otbRCC8GraphFileReader(int itkNotUsed(argc), char* argv[])
{
  char * inputFilename = argv[1];
  typedef otb::Polygon<>                          PathType;
  typedef otb::RCC8VertexBase<PathType>           VertexType;
  typedef otb::RCC8Graph<VertexType>              RCC8GraphType;
  typedef otb::RCC8GraphFileReader<RCC8GraphType> RCC8GraphFileReaderType;
  typedef otb::RCC8VertexIterator<RCC8GraphType>  VertexIteratorType;
  typedef otb::RCC8EdgeIterator<RCC8GraphType>    EdgeIteratorType;

  // Instantiation
  RCC8GraphFileReaderType::Pointer rcc8GraphReader = RCC8GraphFileReaderType::New();
  rcc8GraphReader->SetFileName(inputFilename);

  rcc8GraphReader->Update();

  // Getting the output graph
  RCC8GraphType::Pointer graph = rcc8GraphReader->GetOutput();

  // Checking vertices
  VertexIteratorType vIt(graph);
  unsigned int       count = 0;

  otbControlConditionTestMacro(graph->GetNumberOfVertices() != 4,
                               "graph->GetNumberOfVertices()!=4");
  otbControlConditionTestMacro(graph->GetNumberOfEdges() != 6,
                               "graph->GetNumberOfEdges()!=6");

  // Checking edges
  EdgeIteratorType eIt(graph);
  count = 0;
  for (eIt.GoToBegin(); !eIt.IsAtEnd(); ++eIt, ++count)
    {
    switch (count)
      {
      case 0:
        otbControlConditionTestMacro(eIt.GetValue() != otb::OTB_RCC8_EC,
                                     "eIt.GetValue()!=otb::OTB_RCC8_EC");
        otbControlConditionTestMacro(eIt.GetSourceIndex() != 0,
                                     "eIt.GetSourceIndex()!=0");
        otbControlConditionTestMacro(eIt.GetTargetIndex() != 1,
                                     "eIt.GetTargetIndex()!=1");
        break;
      case 1:
        otbControlConditionTestMacro(eIt.GetValue() != otb::OTB_RCC8_PO,
                                     "eIt.GetValue()!=otb::OTB_RCC8_PO");
        otbControlConditionTestMacro(eIt.GetSourceIndex() != 1,
                                     "eIt.GetSourceIndex()!=1");
        otbControlConditionTestMacro(eIt.GetTargetIndex() != 2,
                                     "eIt.GetTargetIndex()!=2");
        break;
      case 2:
        otbControlConditionTestMacro(eIt.GetValue() != otb::OTB_RCC8_TPP,
                                     "eIt.GetValue()!=otb::OTB_RCC8_TPP");
        otbControlConditionTestMacro(eIt.GetSourceIndex() != 2,
                                     "eIt.GetSourceIndex()!=2");
        otbControlConditionTestMacro(eIt.GetTargetIndex() != 3,
                                     "eIt.GetTargetIndex()!=3");
        break;
      case 3:
        otbControlConditionTestMacro(eIt.GetValue() != otb::OTB_RCC8_TPPI,
                                     "eIt.GetValue()!=otb::OTB_RCC8_TPPI");
        otbControlConditionTestMacro(eIt.GetSourceIndex() != 0,
                                     "eIt.GetSourceIndex()!=0");
        otbControlConditionTestMacro(eIt.GetTargetIndex() != 2,
                                     "eIt.GetTargetIndex()!=2");
        break;
      case 4:
        otbControlConditionTestMacro(eIt.GetValue() != otb::OTB_RCC8_NTPP,
                                     "eIt.GetValue()!=otb::OTB_RCC8_NTPP");
        otbControlConditionTestMacro(eIt.GetSourceIndex() != 1,
                                     "eIt.GetSourceIndex()!=1");
        otbControlConditionTestMacro(eIt.GetTargetIndex() != 3,
                                     "eIt.GetTargetIndex()!=3");
        break;
      case 5:
        otbControlConditionTestMacro(eIt.GetValue() != otb::OTB_RCC8_NTPPI,
                                     "eIt.GetValue()!=otb::OTB_RCC8_NTPPI");
        otbControlConditionTestMacro(eIt.GetSourceIndex() != 0,
                                     "eIt.GetSourceIndex()!=0");
        otbControlConditionTestMacro(eIt.GetTargetIndex() != 3,
                                     "eIt.GetTargetIndex()!=3");
        break;
      default:
        otbControlConditionTestMacro(true, "Error in graph reading.");
        break;
      }
    }

  return EXIT_SUCCESS;
}
