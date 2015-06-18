/* 
 * File:   function_module.h
 * Author: m79lol
 *
 */

#ifndef CONTROL_MODULE_H
#define	CONTROL_MODULE_H
typedef void (*sendAxisState_t)(system_value, variable_value);

class ControlModule {
    protected:
        ControlModule() {}
    public:
        //init
        virtual const char *getUID() = 0;
        virtual void prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p) = 0;
        
        //compiler only
        virtual AxisData** getAxis(unsigned int *count_axis) = 0;
        virtual void *writePC(unsigned int *buffer_length) = 0;
        
        //intepreter - devices
        virtual int init() = 0;
        virtual void execute(sendAxisState_t sendAxisState) = 0;
        virtual void final() = 0;
        
        //intepreter - program & lib
        virtual void readPC(void *buffer, unsigned int buffer_length) = 0;
        
        //intepreter - program
        virtual int startProgram(int uniq_index) = 0;
        virtual int endProgram(int uniq_index) = 0;
        
        //destructor
        virtual void destroy() = 0;
        virtual ~ControlModule() {}
};

typedef ControlModule* (*getControlModuleObject_t)();
extern "C" {
	PREFIX_FUNC_DLL ControlModule* getControlModuleObject();
}

#endif	/* CONTROL_MODULE_H */

