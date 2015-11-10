/*
 * File:   function_module.h
 * Author: m79lol
 *
 */

#ifndef FUNCTION_MODULE_H
#define FUNCTION_MODULE_H

#define FUNCTION_MODULE_API_VERSION 100;

class FunctionModule {
 protected:
  FunctionModule() {}

 public:
  // init
  virtual const struct ModuleInfo& getModuleInfo() = 0;
  virtual void prepare(colorPrintfModule_t *colorPrintf_p,
                       colorPrintfModuleVA_t *colorPrintfVA_p) = 0;

  // compiler only
  virtual FunctionData **getFunctions(unsigned int *count_functions) = 0;
  virtual void *writePC(unsigned int *buffer_length) = 0;

  // intepreter - program & lib
  virtual void readPC(void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual FunctionResult *executeFunction(system_value function_index,
                                          void **args) = 0;
  virtual int startProgram(int uniq_index) = 0;
  virtual int endProgram(int uniq_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~FunctionModule() {}
};

typedef unsigned short (*getFunctionModuleApiVersion_t)();
typedef FunctionModule *(*getFunctionModuleObject_t)();

extern "C" {
PREFIX_FUNC_DLL unsigned short getFunctionModuleApiVersion() /*{ return FUNCTION_MODULE_API_VERSION; }*/;
PREFIX_FUNC_DLL FunctionModule *getFunctionModuleObject();
}

#endif /* FUNCTION_MODULE_H */
