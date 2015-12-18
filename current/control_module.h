/*
 * File:   control_module.h
 * Author: m79lol
 *
 */

#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H

#define CONTROL_MODULE_API_VERSION 100;

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
  virtual void execute(sendAxisState_t sendAxisState) = 0;
  virtual void final() = 0;

  // intepreter - program & lib
  virtual void readPC(void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual int startProgram(int uniq_index) = 0;
  virtual int endProgram(int uniq_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~ControlModule() {}
};

typedef unsigned short (*getControlModuleApiVersion_t)();
typedef ControlModule *(*getControlModuleObject_t)();

#ifndef MODULE_WRAPPER
extern "C" {
  PREFIX_FUNC_DLL unsigned short getControlModuleApiVersion() /*{ return CONTROL_MODULE_API_VERSION; }*/;
  PREFIX_FUNC_DLL ControlModule *getControlModuleObject();
}
#endif

#endif /* CONTROL_MODULE_H */
