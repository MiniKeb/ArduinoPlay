#include "Arduino.h"
#include "Html.h"

// struct MenuItem{
//   String label;
//   String link;
// };

String html(String tags[], byte tagCount){
  String html = "<html><head><title>ESP8266 Rocks!</title><style>";
  html += "body{ background-color: #EEEEEE; color: #333333; margin:0; padding:0; font: 50px \"Trebuchet MS\",Arial,sans-serif; line-height: 50px ; }";
  html += "ul.menu{ width: 100%; list-style: none; margin: 0; padding: 0; }";
  html += "ul.menu > li{ background-color: #EEEEEE; border: none; }";
  html += "ul.menu > li > a{ display: block ; background: #EEEEEE ; color: #333333;  text-align: center ; text-decoration: none ; padding: 5px; }";
  html += "ul.menu > li > a:hover{ background: #333333 ; color: #EEEEEE; }";
  html += "ul.menu > li.selected > a{ background-color: #336699; color: #EEEEEE; }";
  html += ".content{ margin-top: 0.5em; padding: 0.5em 0.5em 0 0.5em; border-top: 2px solid #333333; text-align: center; }";
  html += ".error{ color: #FF0000; }";
  html += "</style></head><body>";

  for(byte i = 0; i < tagCount; ++i){
    html += tags[i];
  }
  return html + "</body><html>";
}

String menu(struct MenuItem items[], int itemCount, String selectedLabel){
  String html = "<ul class=\"menu\">";

  for(byte i = 0; i < itemCount; ++i){
    html += "<li";
    if(items[i].label == selectedLabel){
      html += " class=\"selected\"";
    }
    html +="><a href=\""+ items[i].link +"\">"+ items[i].label +"</a></li>";
  }

  return html + "</ul>";
}

String baseContent(bool isError, String children[], byte childCount){
  String cssClass = "content";
  if(isError){
    cssClass += " error";
  }
  String html = "<div class=\""+ cssClass +"\">";
  for(byte i = 0; i < childCount; ++i){
    html += children[i];
  }
  return html + "</div>";
}

String content(String text){
  return baseContent(false, new String[1]{text}, 1);
}

String header(String title){
  return "<h1>"+ title +"</h1>";
}

String error(String errorName, String errorMessage){
  return baseContent(true, new String[2]{
    header(errorName),
    errorMessage
  }, 2);
}

String error(String errorName){
  return baseContent(true, new String[1]{
    header(errorName)
  }, 1);
}

