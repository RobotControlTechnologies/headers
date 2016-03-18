/*
 * File:   robot_module.h
 * Author: m79lol
 *
 */

#ifndef DB_MODULE_H
#define DB_MODULE_H

struct DBModuleData {
  const char *iid;
  const char *hash;
  unsigned short version;
};

struct DBRobotData {
  const DBModuleData *module_data;
  const char *robot_uid;
};

class DBModule {
 protected:
  DBModule() {}

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
  virtual void readPC(void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual int startProgram(int uniq_index) = 0;
  virtual const DBRobotData *makeChoise(const DBRobotData** robots_data, unsigned int count_robots) = 0;
  virtual int endProgram(int uniq_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~DBModule() {}
};

typedef unsigned short (*getDBModuleApiVersion_t)();
typedef DBModule *(*getDBModuleObject_t)();

#ifndef MODULE_WRAPPER
extern "C" {
    PREFIX_FUNC_DLL unsigned short getDBModuleApiVersion() /*{ return MODULE_API_VERSION; }*/;
    PREFIX_FUNC_DLL DBModule *getDBModuleObject();
}
#endif

#endif /* DB_MODULE_H */
