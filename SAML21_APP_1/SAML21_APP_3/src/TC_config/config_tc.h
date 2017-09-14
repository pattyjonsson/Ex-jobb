/*
 * config_tc.h
 *
 * Created: 2017-06-14 13:52:51
 *  Author: Patricia
 */ 


#ifndef CONFIG_TC_H_
#define CONFIG_TC_H_

#define CONF_TC_MODULE TC3

struct tc_module tc_instance;


void configure_tc(void);
void configure_tc_callbacks(void);
void tc_callback_FIR(struct tc_module *const module_inst);




#endif /* CONFIG_TC_H_ */