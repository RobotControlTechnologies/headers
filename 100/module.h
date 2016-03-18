/*
 * File:   module.h
 * Author: m79lol
 *
 */

#ifndef MODULE_H_100
#define MODULE_H_100

#ifndef MODULE_WRAPPER_H
#define MODULE_API_VERSION 100
#endif

#include <cstdarg>
#include <cstddef>

typedef int system_value;
typedef double variable_value;

enum class ModuleTypes {
	Robot = 1,
	Control = 2,
	Function = 3
};

struct ModuleInfo {
  char *uid;
  enum Modes { PROD, SPEC } mode;
  unsigned short version;
  char *digest;
};

struct FunctionData {
  enum ParamTypes { STRING, FLOAT };

  system_value command_index;
  unsigned int count_params;
  ParamTypes *params;
  const char *name;
  FunctionData()
      : command_index(0), count_params(0), params(NULL), name(NULL) {}
  FunctionData(system_value command_index, system_value count_params,
               ParamTypes *params, const char *name)
      : command_index(command_index),
        count_params(count_params),
        params(params),
        name(name) {}
};

struct AxisData {
  system_value axis_index;
  variable_value upper_value;
  variable_value lower_value;
  const char *name;
  AxisData() : axis_index(0), upper_value(0), lower_value(0), name(NULL) {}
  AxisData(system_value axis_index, variable_value upper_value,
           variable_value lower_value, const char *name)
      : axis_index(axis_index),
        upper_value(upper_value),
        lower_value(lower_value),
        name(name) {}
};

class FunctionResult {
 public:
  enum Types { EXCEPTION, VALUE };
 private:
  Types type;
  variable_value result;

 public:
  FunctionResult(Types type) : type(type), result(0.0f) {}
  FunctionResult(Types type, variable_value result)
      : type(type), result(result) {}
  virtual Types getType() { return type; }
  virtual variable_value getResult() { return result; }
  virtual void destroy() { delete this; }
  virtual ~FunctionResult(){};
};

struct ConsoleColor {
  enum colors {
    black = 0,
    dark_blue = 1,
    dark_green = 2,
    dark_aqua = 3,
    dark_red = 4,
    dark_purple = 5,
    dark_yellow = 6,
    dark_white = 7,
    gray = 8,
    blue = 9,
    green = 10,
    aqua = 11,
    red = 12,
    purple = 13,
    yellow = 14,
    white = 15
  };

  colors color_text;
  colors color_back;
  ConsoleColor()
      : color_text(ConsoleColor::white), color_back(ConsoleColor::black){};
  ConsoleColor(colors color_text)
      : color_text(color_text), color_back(ConsoleColor::black){};
  ConsoleColor(colors color_text, colors color_back)
      : color_text(color_text), color_back(color_back){};
};

typedef void(colorPrintfModule_t)(void *, ConsoleColor, const char *, ...);
typedef void(colorPrintfModuleVA_t)(void *, ConsoleColor, const char *,
                                    va_list);

typedef void(colorPrintfRobot_t)(void *, const char *, ConsoleColor,
                                 const char *, ...);
typedef void(colorPrintfRobotVA_t)(void *, const char *, ConsoleColor,
                                   const char *, va_list);

#ifdef _WIN32
#define PREFIX_FUNC_DLL __declspec(dllexport)
#else
#define PREFIX_FUNC_DLL
#endif

#endif /* MODULE_H_100 */
