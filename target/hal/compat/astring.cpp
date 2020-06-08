#include <compat/astring.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <bitset>

// Conversion Constructors
String::String(char c) {
  content += c;
}

String::String(unsigned char value, unsigned char base) {
  std::stringstream ss;

  switch (base) {
    case 2:
      ss << std::bitset<sizeof(unsigned char)*8>(value).to_string();
      break;
    case 8:
      ss << std::oct << (int)value;
      break;
    case 16:
      ss << std::hex << (int)value;
      break;
    default: // Base 10
      ss << (int)value;
  }

  content = ss.str();
}

String::String(int value, unsigned char base) {
  std::stringstream ss;

  switch (base) {
    case 2:
      ss << std::bitset<sizeof(int)*8>(value).to_string();
      break;
    case 8:
      ss << std::oct << (int)value;
      break;
    case 16:
      ss << std::hex << (int)value;
      break;
    default: // Base 10
      ss << (int)value;
  }

  content = ss.str();
}

String::String(unsigned int value, unsigned char base) {
  std::stringstream ss;

  switch (base) {
    case 2:
      ss << std::bitset<sizeof(unsigned int)*8>(value).to_string();
      break;
    case 8:
      ss << std::oct << (int)value;
      break;
    case 16:
      ss << std::hex << (int)value;
      break;
    default: // Base 10
      ss << (int)value;
  }

  content = ss.str();
}

String::String(long value, unsigned char base) {
  std::stringstream ss;

  switch (base) {
    case 2:
      ss << std::bitset<sizeof(long)*8>(value).to_string();
      break;
    case 8:
      ss << std::oct << (int)value;
      break;
    case 16:
      ss << std::hex << (int)value;
      break;
    default: // Base 10
      ss << (int)value;
  }

  content = ss.str();
}

String::String(unsigned long value, unsigned char base) {
  std::stringstream ss;

  switch (base) {
    case 2:
      ss << std::bitset<sizeof(unsigned long)*8>(value).to_string();
      break;
    case 8:
      ss << std::oct << (int)value;
      break;
    case 16:
      ss << std::hex << (int)value;
      break;
    default: // Base 10
      ss << (int)value;
  }

  content = ss.str();
}

String::String(float value, unsigned char decimalPlaces) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(decimalPlaces) << value;
  content = ss.str();
}

String::String(double value, unsigned char decimalPlaces) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(decimalPlaces) << value;
  content = ss.str();
}



String &String::operator+=(const String &astr)  {
  content += astr.content;
  return *this;
}

String &String::operator+=(const char *cstr)    {
  content += std::string(cstr);
  return *this;
}

String &String::operator+=(char c)              {
  content += c;
  return *this;
}

String &String::operator+=(unsigned char num)   {
  *this += String(num);
  return *this;
}

String &String::operator+=(int num)             {
  *this += String(num);
  return *this;
}

String &String::operator+=(unsigned int num)    {
  *this += String(num);
  return *this;
}

String &String::operator+=(long num)            {
  *this += String(num);
  return *this;
}

String &String::operator+=(unsigned long num)   {
  *this += String(num);
  return *this;
}

String &String::operator+=(float num)           {
  *this += String(num);
  return *this;
}

String &String::operator+=(double num)          {
  *this += String(num);
  return *this;
}

String String::operator + (const String &astr) {
  String newStr = *this;
  newStr += astr;
  return newStr;
}

unsigned char String::operator < (const String &astr) const {
  return this->compare(astr) < 0;
}

unsigned char String::operator > (const String &astr) const {
  return this->compare(astr) > 0;
}

unsigned char String::operator <= (const String &astr) const {
  return this->compare(astr) <= 0;
}

unsigned char String::operator >= (const String &astr) const {
  return this->compare(astr) >= 0;
}

// Comparison
unsigned char String::equals(const String &s) const {
  return (this->length() == s.length() && this->compare(s));
}

unsigned char String::equals(const char *cstr) const {
  std::string tmp(cstr);
  return this->equals(tmp);
}

unsigned char String::equalsIgnoreCase(const String &s) const {
  String thisCopy = *this;
  String sCopy = s;

  thisCopy.toLowerCase();
  sCopy.toLowerCase();

  return thisCopy.equals(sCopy);
}

unsigned char String::startsWith( const String &prefix) const {
  if (this->length() < prefix.length()) {
    return 0;
  }

  return this->startsWith(prefix, 0);
}

unsigned char String::startsWith(const String &prefix, unsigned int offset) const {
  if (int(offset) > this->length() - prefix.length()) {
    return 0;
  }

  const char *buff0 = this->content.c_str();
  const char *buff1 = prefix.content.c_str();

  return strncmp( &buff0[offset], buff1, prefix.length() ) == 0;
}

unsigned char String::endsWith(const String &suffix) const {
  if ( this->length() < suffix.length()) {
    return 0;
  }
  const char *buff0 = this->content.c_str();
  const char *buff1 = suffix.content.c_str();

  return strcmp(&buff0[this->length() - suffix.length()], buff1) == 0;
}


// Conversion
long String::toInt(void) const {
  return std::atol(this->content.c_str());
}

float String::toFloat(void) const {
  return float(this->toDouble());
}

double String::toDouble(void) const {
  return std::atof(this->content.c_str());
}




// Helpers
void String::toLowerCase(void) {
  std::transform(this->content.begin(), this->content.end(), this->content.begin(),
    [](unsigned char c){ return std::tolower(c); });
}

void String::toUpperCase(void) {
  std::transform(this->content.begin(), this->content.end(), this->content.begin(),
    [](unsigned char c){ return std::toupper(c); });
}

void String::trim(void) {
  // TODO
}
