/* 
 * File:   function_module.h
 * Author: m79lol
 *
 */

#ifndef FUNCTION_MODULE_H
#define	FUNCTION_MODULE_H

class FunctionModule {
    protected:
        FunctionModule() {}
    public: 
        //init
        virtual const char *getUID() = 0;
        virtual void prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p) = 0;
        
        //compiler only
        virtual FunctionData** getFunctions(unsigned int *count_functions) = 0;
        virtual void *writePC(unsigned int *buffer_length) = 0;
        
        //intepreter - program & lib
        virtual void readPC(void *buffer, unsigned int buffer_length) = 0;
        
        //intepreter - program
        virtual FunctionResult* executeFunction(system_value function_index, void **args) = 0;
        virtual int startProgram(int uniq_index) = 0;
        virtual int endProgram(int uniq_index) = 0;
        
        //destructor
        virtual void destroy() = 0;
        virtual ~FunctionModule() {}
};

typedef FunctionModule* (*getFunctionModuleObject_t)();
extern "C" {
	PREFIX_FUNC_DLL FunctionModule* getFunctionModuleObject();
}

#endif	/* FUNCTION_MODULE_H */

