/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "otbExtendedFilenameHelper.h"
#include "otb_boost_string_header.h"
#include "otbStringUtils.h"

namespace otb
{

void
ExtendedFilenameHelper
::SetExtendedFileName(const char *extFname)
{
  if (extFname == ITK_NULLPTR)
  {
    itkGenericExceptionMacro( << "Filename is NULL" );
  }
  this->m_ExtendedFileName = extFname;
  this->m_OptionMap.clear();
  std::vector<std::string> tmp1;
  std::vector<std::string> tmp2;
  if (!m_ExtendedFileName.empty())
    {
    boost::split(tmp1, m_ExtendedFileName, boost::is_any_of("?"), boost::token_compress_on);
    this->SetSimpleFileName(tmp1[0]);
    if (tmp1.size()>1)
      {
      boost::split(tmp2, tmp1[1], boost::is_any_of("&"), boost::token_compress_on);
      for (unsigned int i=0; i<tmp2.size(); i++)
      if (tmp2[i].length() >0)
        {
        std::vector<std::string> tmp;
        boost::split(tmp, tmp2[i], boost::is_any_of("="), boost::token_compress_on);
        if (tmp.size()>1)
          {
          if (tmp[1].length()>0)
            {
            if (m_OptionMap[tmp[0]].empty())
              {
              m_OptionMap[tmp[0]]=tmp[1];
              }
            else
              {
              itkWarningMacro("Duplicated option detected: " << tmp[0] << ". Using value " << tmp[1] << ".");
              }
            }
          else
            itkGenericExceptionMacro( << "Value for option '" << tmp[0] << "' is not set.");
          }
        }
      }
    }
}

const ExtendedFilenameHelper::OptionMapType &
ExtendedFilenameHelper
::GetOptionMap(void) const
{
  return this->m_OptionMap;
}

/*-------------------- GenericBandRange ----------------------*/

ExtendedFilenameHelper::GenericBandRange
::GenericBandRange(const int& a)
  : std::pair<int,int>(a,a)
  {
  }

ExtendedFilenameHelper::GenericBandRange
::GenericBandRange(const std::pair<int,int>& a)
  : std::pair<int,int>(a)
  {
    if (a.second>=0 && a.second < a.first)
      {
      throw std::range_error("Invalid range");
      }
  }

ExtendedFilenameHelper::GenericBandRange
::GenericBandRange(const int& a,const int& b)
  : std::pair<int,int>(a,b)
  {
    if (b>=0 && b < a)
      {
      throw std::range_error("Invalid range");
      }
  }

bool
ExtendedFilenameHelper::GenericBandRange
::SetString(const std::string& str, size_t start , size_t size)
  {
  assert(start < str.size());
  bool ret = true;
  if (size == 0)
    {
    first = 0;
    second = 0;
    return false;
    }
  size_t end = str.size();
  if (size != std::string::npos && (start+size) <= str.size())
    {
    end = start + size;
    }
  size_t pos = str.find(':',start);
  if (pos != std::string::npos && pos<end)
    {
    // range of values
    if (pos > start)
      {
      try
        {
        first = boost::lexical_cast<int>(str.c_str()+start, pos-start);
        }
      catch(boost::bad_lexical_cast &)
        {
        ret = false;
        }
      }
    else
      {
      first = 0;
      }
    if (end > pos + 1)
      {
      try
        {
        second = boost::lexical_cast<int>(str.c_str()+ pos + 1, end - pos - 1);
        }
      catch(boost::bad_lexical_cast &)
        {
        ret = false;
        }
      }
    else
      {
      second = 0;
      }
    }
  else
    {
    // single value
    try
      {
      first = boost::lexical_cast<int>(str.c_str()+start, end-start);
      second = first;
      }
    catch(boost::bad_lexical_cast &)
      {
      ret = false;
      }
    }
  return ret;
  }

void
ExtendedFilenameHelper::GenericBandRange
::Print(std::ostream& os)
  {
  if (this->first)
    {
    os << this->first;
    }
  if (this->first != this->second)
    {
    if (this->first || this->second)
      {
      os << ":";
      }
    if (this->second)
      {
      os << this->second;
      }
    }
  }

} // end namespace otb
