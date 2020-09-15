#ifndef Html_h
#define Html_h
#include <Arduino.h>

struct MenuItem{
  String label;
  String link;
};
String html(String tags[], byte tagCount);
String menu(struct MenuItem items[], int itemCount, String selectedLabel);
String baseContent(bool isError, String children[], byte childCount);
String content(String text);
String header(String title);
String error(String errorName, String errorMessage);
String error(String errorName);

#endif