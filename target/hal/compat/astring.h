#ifndef ASTRING_H
#define ASTRING_H

#include <string>

// Arduino Compatible String class with std::string container

class String {

public:
  // Base constructors
  String(const char *cstr = "")   : String(std::string(cstr)) {};
  String(const String &str)       : String(str.content) {};
  String(const std::string &str)  { content = str; }

  // Conversion Constructors
  explicit String(char c);
  explicit String(unsigned char, unsigned char base=10);
  explicit String(int, unsigned char base=10);
  explicit String(unsigned int, unsigned char base=10);
  explicit String(long, unsigned char base=10);
  explicit String(unsigned long, unsigned char base=10);
  explicit String(float, unsigned char decimalPlaces=2);
  explicit String(double, unsigned char decimalPlaces=2);

  // Operators
  String &operator =  (const String &astr);
  String &operator =  (const char *cstr);
  String &operator =  (const std::string &str);
  String &operator += (const String &astr);
  String &operator += (const char *cstr);
  String &operator += (char c);
  String &operator += (unsigned char num);
  String &operator += (int num);
  String &operator += (unsigned int num);
  String &operator += (long num);
  String &operator += (unsigned long num);
  String &operator += (float num);
  String &operator += (double num);
  String operator +  (const String &astr);

  char operator[](int index) { return this->content[index]; }

  unsigned char operator == (const String &astr) const {return equals(astr);}
  unsigned char operator == (const char *cstr)   const {return equals(cstr);}
  unsigned char operator != (const String &astr) const {return !equals(astr);}
  unsigned char operator != (const char *cstr)   const {return !equals(cstr);}
  unsigned char operator <  (const String &astr) const;
  unsigned char operator >  (const String &astr) const;
  unsigned char operator <= (const String &astr) const;
  unsigned char operator >= (const String &astr) const;

  // Comparison
  unsigned char equals(const String &s) const;
  unsigned char equals(const char *cstr) const;
  unsigned char equalsIgnoreCase(const String &s) const;
  unsigned char startsWith( const String &prefix) const;
  unsigned char startsWith(const String &prefix, unsigned int offset) const;
  unsigned char endsWith(const String &suffix) const;

  // Conversion
  long toInt(void) const;
  float toFloat(void) const;
  double toDouble(void) const;
  std::string toStdString(void) const { return this->content; }

  // Helpers
  void toLowerCase(void);
  void toUpperCase(void);
  void trim(void);

  int length(void) const { return this->content.length(); };
  int compare(const std::string &s) const { return this->content.compare(s); }
  int compare(const String &s) const { return this->content.compare(s.content); }

  // std::string compat
  const char *c_str(void) const { return this->content.c_str(); }

private:
  std::string content;
};

#endif