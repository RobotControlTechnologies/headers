/*
 * File:   control_module.h
 * Author: m79lol
 *
 */

#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H

class ControlModule;

typedef void (*sendAxisState_t)(ControlModule *, system_value, variable_value);

class ControlModule {
 protected:
  ControlModule() {}

 public:
  // init
  virtual const struct ModuleInfo& getModuleInfo() = 0;
  virtual void prepare(colorPrintfModule_t *colorPrintf_p,
                       colorPrintfModuleVA_t *colorPrintfVA_p) = 0;

  // compiler only
  virtual AxisData **getAxis(unsigned int *count_axis) = 0;
  virtual void *writePC(unsigned int *buffer_length) = 0;

  // intepreter - devices
  virtual int init() = 0;
  virtual void execute(int run_index, sendAxisState_t sendAxisState) = 0;
  virtual void final() = 0;

  // intepreter - program & lib
  virtual int readPC(int pc_index, void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual int startProgram(int run_index, int pc_index) = 0;
  virtual int endProgram(int run_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~ControlModule() {}
};

typedef unsigned short (*getControlModuleApiVersion_t)();
typedef ControlModule *(*getControlModuleObject_t)();

#ifndef MODULE_WRAPPER
extern "C" {
  PREFIX_FUNC_DLL unsigned short getControlModuleApiVersion() /*{ return MODULE_API_VERSION; }*/;
  PREFIX_FUNC_DLL ControlModule *getControlModuleObject();
}
#endif

#endif /* CONTROL_MODULE_H */
