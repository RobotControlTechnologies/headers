/*
 * File:   robot_module.h
 * Author: m79lol
 *
 */

#ifndef CHOICE_MODULE_H
#define CHOICE_MODULE_H

struct ChoiceFunctionData {
  enum CallType {
    Unknow = 0,
    Guarante = 1,
    Probably = 2
  };
  const char *name;
  const char *context_hash;
  system_value position;
  CallType call_type;
};

struct ChoiceModuleData {
  const char *iid;
  const char *hash;
  unsigned short version;
};

struct ChoiceRobotData {
  const ChoiceModuleData *module_data;
  const char *robot_uid;
};

class ChoiceModule {
 protected:
  ChoiceModule() {}

 public:
  // init
  virtual const struct ModuleInfo& getModuleInfo() = 0;
  virtual void prepare(colorPrintfModule_t *colorPrintf_p,
                       colorPrintfModuleVA_t *colorPrintfVA_p) = 0;

  // compiler only
  virtual void *writePC(unsigned int *buffer_length) = 0;

  // intepreter - devices
  virtual int init() = 0;
  virtual void final() = 0;

  // intepreter - program & lib
  virtual int readPC(int pc_index, void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual int startProgram(int run_index, int pc_index) = 0;
  virtual const ChoiceRobotData *makeChoice(int run_index, const ChoiceFunctionData** function_data, unsigned int count_functions, const ChoiceRobotData** robots_data, unsigned int count_robots) = 0;
  virtual int endProgram(int run_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~ChoiceModule() {}
};

typedef unsigned short (*getChoiceModuleApiVersion_t)();
typedef ChoiceModule *(*getChoiceModuleObject_t)();

#ifndef MODULE_WRAPPER
extern "C" {
    PREFIX_FUNC_DLL unsigned short getChoiceModuleApiVersion() /*{ return MODULE_API_VERSION; }*/;
    PREFIX_FUNC_DLL ChoiceModule *getChoiceModuleObject();
}
#endif

#endif /* CHOICE_MODULE_H */
