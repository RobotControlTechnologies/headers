/*
 * File:   robot_module.h
 * Author: m79lol
 *
 */

#ifndef ROBOT_MODULE_H
#define ROBOT_MODULE_H

#define ROBOT_MODULE_API_VERSION 100;

#define ROBOT_COMMAND_FREE 0
#define ROBOT_COMMAND_HAND_CONTROL_BEGIN -1
#define ROBOT_COMMAND_HAND_CONTROL_END -2

enum CommandMode : unsigned char {
  wait = 1,
  not_wait = 2,
  package = 3,
  end_of_package_wait = 4,
  end_of_package_no_wait = 5
};

class Robot {
 protected:
  Robot() {}

 public:
  virtual void prepare(colorPrintfRobot_t *colorPrintf_p,
                       colorPrintfRobotVA_t *colorPrintfVA_p) = 0;
  virtual FunctionResult *executeFunction(CommandMode mode,
                                          system_value command_index,
                                          void **args) = 0;
  virtual void axisControl(system_value axis_index, variable_value value) = 0;
  virtual ~Robot() {}
};

class RobotModule {
 protected:
  RobotModule() {}

 public:
  // init
  virtual const struct ModuleInfo& getModuleInfo() = 0;
  virtual void prepare(colorPrintfModule_t *colorPrintf_p,
                       colorPrintfModuleVA_t *colorPrintfVA_p) = 0;

  // compiler only
  virtual FunctionData **getFunctions(unsigned int *count_functions) = 0;
  virtual AxisData **getAxis(unsigned int *count_axis) = 0;
  virtual void *writePC(unsigned int *buffer_length) = 0;

  // intepreter - devices
  virtual int init() = 0;
  virtual Robot *robotRequire() = 0;
  virtual void robotFree(Robot *robot) = 0;
  virtual void final() = 0;

  // intepreter - program & lib
  virtual void readPC(void *buffer, unsigned int buffer_length) = 0;

  // intepreter - program
  virtual int startProgram(int uniq_index) = 0;
  virtual int endProgram(int uniq_index) = 0;

  // destructor
  virtual void destroy() = 0;
  virtual ~RobotModule() {}
};

typedef unsigned short (*getRobotModuleApiVersion_t)();
typedef RobotModule *(*getRobotModuleObject_t)();

#ifndef MODULE_WRAPPER
extern "C" {
    PREFIX_FUNC_DLL unsigned short getRobotModuleApiVersion() /*{ return ROBOT_MODULE_API_VERSION; }*/;
    PREFIX_FUNC_DLL RobotModule *getRobotModuleObject();
}
#endif

#endif /* ROBOT_MODULE_H */
