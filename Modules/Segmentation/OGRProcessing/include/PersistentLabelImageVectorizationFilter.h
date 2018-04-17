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

#ifndef PersistentLabelImageVectorizationFilter_h
#define PersistentLabelImageVectorizationFilter_h

#include "otbPersistentImageToOGRLayerFilter.h"
#include "otbPersistentFilterStreamingDecorator.h"
#include "otbOGRDataSourceWrapper.h"
#include "otbImage.h"


namespace otb
{
/**
 * \class PersistentLabelImageVectorizationFilter
 * 
 * \brief Persistent filter to extract sample values from an image
 * 
 * \ingroup OTBSampling
 */
template<class TInputImage>
class ITK_EXPORT PersistentLabelImageVectorizationFilter :
  public PersistentImageToOGRLayerFilter<TInputImage>
{
public:
  /** Standard Self typedef */
  typedef PersistentLabelImageVectorizationFilter             Self;
  typedef PersistentImageToOGRLayerFilter<TInputImage>        Superclass;
  typedef itk::SmartPointer<Self>                             Pointer;
  typedef itk::SmartPointer<const Self>                       ConstPointer;

  typedef TInputImage                                         InputImageType;
  typedef typename InputImageType::Pointer                    InputImagePointer;
  typedef typename InputImageType::RegionType                 RegionType;
  typedef typename InputImageType::PointType                  PointType;
  typedef typename InputImageType::IndexType                  IndexType;
  typedef typename InputImageType::SizeType                   SizeType;
  typedef typename InputImageType::PixelType                  PixelType;
  typedef typename InputImageType::InternalPixelType          InternalPixelType;
  
  typedef otb::LabelImageToOGRDataSourceFilter<InputImageType>          LabelImageToOGRDataSourceFilterType;
  typedef typename Superclass::OGRDataSourceType                        OGRDataSourceType;
  typedef typename Superclass::OGRDataSourcePointerType                 OGRDataSourcePointerType;
  typedef typename Superclass::OGRLayerType                             OGRLayerType;
  typedef typename Superclass::OGRFeatureType                           OGRFeatureType;

  typedef itk::DataObject::DataObjectPointerArraySizeType DataObjectPointerArraySizeType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(PersistentLabelImageVectorizationFilter, PersistentSamplingFilterBase);

  void Synthetize(void) override{}

  /** Reset method called before starting the streaming*/
  void Reset(void) override;
  
  /** Get the sample names */
  const std::vector<std::string> & GetSampleFieldNames();
   
  /** Set the name of the field that will contain the labels in the output image */
  itkSetStringMacro(FieldName);
  
  /** Get the name of the field that will contain the labels in the output image */
  itkGetStringMacro(FieldName);
  
  /** Set the tolerance parameter used for polygon simplification */
  itkSetMacro(Tolerance , double);
  
  /** Get the tolerance parameter used for polygon simplification */
  itkGetMacro(Tolerance , double);
  
  /**
   * Set the value of the enlarge flag, if this option is on, connected components 
   * on tiles with one more pixel than the stream size, and the resulting polygons 
   * will overlap, this can be used to merge more efficiently touching connected 
   * component splitted by streaming. 
   */
  itkSetMacro(Enlarge , bool);
  
  /**
   * Get the value of the enlarge flag
   */
  itkGetMacro(Enlarge , bool);

  /**
   * Set the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  itkSetMacro(Use8Connected, bool);
  /**
   * Get the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  itkGetMacro(Use8Connected, bool);

  /** Set selected input labels to vectorize */
  void SetLabels( const std::vector<int> & labels)
  {
    m_Labels = labels;
  }

  /** Get selected input labels to vectorize */
  const std::vector<int> & GetLabels() const
  {
    return m_Labels;
  }
  
protected:
  /** Constructor */
  PersistentLabelImageVectorizationFilter();
  /** Destructor */
  ~PersistentLabelImageVectorizationFilter() override = default;
  
  void GenerateOutputInformation() override;
  void GenerateInputRequestedRegion() override;

private:
  PersistentLabelImageVectorizationFilter(const Self &) = delete;
  void operator =(const Self&) = delete;
  
  OGRDataSourcePointerType ProcessTile() override;
  int m_TileNumber;
  std::string m_FieldName;
  std::vector<int> m_Labels;
  bool m_Use8Connected;
  bool m_Enlarge;
  double m_Tolerance;
};


/** Streamed Version of PersistentLabelImageVectorizationFilter */

template <class TImageType>
class ITK_EXPORT LabelImageVectorizationFilter :
public PersistentFilterStreamingDecorator<PersistentLabelImageVectorizationFilter<TImageType>>
{

public:
  /** Standard Self typedef */
  typedef LabelImageVectorizationFilter                                                                     Self;
  typedef PersistentFilterStreamingDecorator<PersistentLabelImageVectorizationFilter<TImageType>>           Superclass;
  typedef itk::SmartPointer<Self>                                                       Pointer;
  typedef itk::SmartPointer<const Self>                                                 ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(LabelImageVectorizationFilter, PersistentFilterStreamingDecorator);

  typedef TImageType                               InputImageType;
  typedef typename PersistentLabelImageVectorizationFilter<TImageType>::OGRDataSourcePointerType                 OGRDataSourcePointerType;
  typedef typename PersistentLabelImageVectorizationFilter<TImageType>::OGRLayerType                             OGRLayerType;

  typedef typename InputImageType::SizeType                                   SizeType;
  
  /** Set the input image. */
  using itk::ProcessObject::SetInput;
  void SetInput(InputImageType * input)
  {
    this->GetFilter()->SetInput(input);
  }
  
  /** Get the input image */
  const InputImageType * GetInput()
  {
    return this->GetFilter()->GetInput();
  }

  /** Set the \c ogr::Layer in which the layer LayerName will be created. */
  void SetOGRLayer( const OGRLayerType & ogrLayer )
  {
    this->GetFilter()->SetOGRLayer(ogrLayer);
  }

  /** Set the name of the field that will contain the labels in the output image */
  void SetFieldName( const std::string & fieldName )
  {
    this->GetFilter()->SetFieldName(fieldName);
  }

  /** Get the name of the field that will contain the labels in the output image */
  const std::string & GetFieldName() const
  {
    return this->GetFilter()->GetFieldName();
  }
 
  /** Set selected input labels to vectorize */
  void SetLabels( const std::vector<int> & labels)
  {
    this->GetFilter()->SetLabels(labels);
  }

  /** Get selected input labels to vectorize */
  const std::vector<int> & GetLabels() const
  {
    return this->GetFilter()->GetLabels();
  }
  
  /** Get the tolerance parameter used for polygon simplification */
  void SetTolerance( double tolerance)
  {
    this->GetFilter()->SetTolerance(tolerance);
  }

  /** Get the tolerance parameter used for polygon simplification */
  const std::vector<int> & GetTolerance() const
  {
    return this->GetFilter()->GetTolerance();
  }
  
  /** Retrieve the actual streamsize used */
  SizeType GetStreamSize()
  {
    return this->GetFilter()->GetStreamSize();
  }

  void Initialize()
  {
     this->GetFilter()->Initialize();
  }
  
  /**
   * Set the value of the enlarge flag, if this option is on, connected components 
   * on tiles with one more pixel than the stream size, and the resulting polygons 
   * will overlap, this can be used to merge more efficiently touching connected 
   * component splitted by streaming. 
   */
  void SetEnlarge(bool flag)
  {
     this->GetFilter()->SetEnlarge(flag);
  }
  
  /**
   * Get the value of the enlarge flag
   */
  bool GetEnlarge()
  {
     return this->GetFilter()->GetEnlarge();
  }
  
  /**
   * Set the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  void SetUse8Connected(bool flag)
  {
     this->GetFilter()->SetUse8Connected(flag);
  }
  
  /**
   * Get the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  bool GetUse8Connected()
  {
     return this->GetFilter()->GetUse8Connected();
  }
protected:
  /** Constructor */
  LabelImageVectorizationFilter() = default;
  /** Destructor */
  ~LabelImageVectorizationFilter() override = default;

private:
  LabelImageVectorizationFilter(const Self &) = delete; 
  void operator =(const Self&) = delete; 
};

} // End namespace otb
#ifndef OTB_MANUAL_INSTANTIATION
#include "PersistentLabelImageVectorizationFilter.txx"
#endif

#endif